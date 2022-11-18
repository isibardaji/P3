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
    -m REAL, --umaxnorm=REAL  Llindar/umbral del màxim de l'autocorrelació [default: 0.85]
    -n REAL, --unorm=REAL  Llindar/umbral de l'autocorrelació normalitzada [default: 0.75]
    -p REAL, --upot=REAL  Llindar/umbral potència [default: -40]
    -1 REAL, --uclip1=REAL  Umbral center clipping 1 [default: 0.01]
    -2 REAL, --uclip2=REAL  Umbral center clipping 2 [default: -0.01]
    -h, --help  Show this screen
    --version   Show the version of the project

Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the estimation:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";
//upot -38 uclip1 0.01 uclip2 -0.01 umaxnorm 1 unoorm 0.9
int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();
  float umaxnorm = stof(args["--umaxnorm"].asString());  
  float unorm = stof(args["--unorm"].asString());
  float upot = stof(args["--upot"].asString());
  float uclip1 = stof(args["--uclip1"].asString());
  float uclip2 = stof(args["--uclip2"].asString());
  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;

  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, PitchAnalyzer::RECT, 50, 500, umaxnorm, unorm, upot);

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.
  
  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
 // vector<float> nou;
 

  float max = *std::max_element(x.begin(), x.end());
  //nou=x;
  for(int i=0; i< int(x.size()); i++){
   // nou[i]=x[i];
    if(x[i]<uclip1*max && x[i]>uclip2*max){
      x[i]=0;
    }
   
  } 

  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.
  
  vector<float> valors_f0_filtrada(f0.size());
  for(int i= 0; i< int(f0.size()); i++){
    if((f0[i-1]>f0[i]&&f0[i-1]<f0[i+1]) || (f0[i-1]<f0[i]&&f0[i-1]>f0[i+1])){
       valors_f0_filtrada[i] = f0[i-1];
    }else if((f0[i-1]<f0[i]&&f0[i]<f0[i+1]) || (f0[i-1]>f0[i]&&f0[i]>f0[i+1])){
       valors_f0_filtrada[i] = f0[i];
    }else if((f0[i-1]<f0[i+1]&&f0[i]>f0[i+1]) || (f0[i-1]>f0[i+1]&&f0[i]<f0[i+1])){
      valors_f0_filtrada[i] = f0[i+1];
    }
   

  }
  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = valors_f0_filtrada.begin(); iX != valors_f0_filtrada.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
}
