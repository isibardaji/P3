/// @file

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>

#include "wavfile_mono.h"
#include "pitch_analyzer.h"
#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Estimator 

Usage:
    get_pitch [options] <input-wav> <output-txt> 
    get_pitch (-h | --help)
    get_pitch --version

Options:
    -1=FLOAT, --unorm=FLOAT  Llindar/umbral de l'autocorrelació normalitzada [default: 0.85]
    -2=FLOAT, --umaxnorm=FLOAT  Llindar/umbral del màxim de l'autocorrelació [default: 0.27]
    -3=FLOAT, --tpot=FLOAT  Llindar/umbral potència normalitzada [default: -54.5]
    -4=FLOAT, --tzcr=FLOAT  Llindar/umbral zcr [default: 1830]
    -l=INT, --long=INT  Longitud finestra per el filtre de mitjana [default: 3]
    -c=FLOAT, --cclipping=FLOAT  Llindar/umbral Center Clipping [default: 0.00555]
    -h, --help  Show this screen
    --version   Show the version of the project
    

Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the estimation:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";

int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
  /// \FET
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();
  float norm=stof(args["--unorm"].asString());
  float umaxnorm=stof(args["--umaxnorm"].asString());
  float tpot=stof(args["--tpot"].asString());
  float tzcr=stof(args["--tzcr"].asString());
  unsigned int L=stoi(args["--long"].asString());
  float cclipping=stof(args["--cclipping"].asString());

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;

  // Define analyzer
  PitchAnalyzer analyzer(len, rate, PitchAnalyzer::RECT, 50, 500, norm, umaxnorm, tpot, tzcr);

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  /// \FET

  vector<float>::iterator iterador;
  vector<float> cclip;
  float umbral = cclipping;

  for(iterador = x.begin(); iterador != x.end(); ++iterador){
    if(*iterador > umbral){
      cclip.push_back(*iterador-umbral);
    } else if(*iterador < -umbral) {
      cclip.push_back(*iterador+umbral);
    } else {
      cclip.push_back(0);
    }
  }

  x=cclip;

  vector<float>::iterator ite;

  float Pmax = 1.e-9;
  float potencia;

  for (ite = x.begin(); ite + len < x.end(); ite = ite + n_shift) {
    potencia=0;

    std::vector<float> x2((ite + len)-ite);
    std::copy(ite, ite + len, x2.begin());

    for(int i=0; i < len; ++i){
      potencia+=(x2[i]*x2[i]);
    }

    potencia=potencia/len;

    if(potencia>Pmax){
      Pmax=potencia;
    }
    x2.clear();
  }

  vector<float>::iterator iX;
  vector<float> f0;

  for (iX = x.begin(); iX + len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + len, Pmax);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
  /// \FET
  
  if(L%2){
    
    unsigned int Lmitja = L;
    vector<float> filteredf0 = f0;

    unsigned int offset = (Lmitja-1)/2;
    vector<float> window(Lmitja);
    

    for (unsigned int n = offset; n < f0.size()-offset; ++n){

      for (unsigned int j = 0; j < Lmitja; ++j)
        window[j] = f0[n - offset + j];
      sort(window.begin(), window.end());
      filteredf0[n]=window[offset];
    }
    f0=filteredf0;
  }
  
  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
  
}