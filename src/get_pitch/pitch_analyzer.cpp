/// @file

#include <iostream>
#include <math.h>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc {
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {

    for (unsigned int l = 0; l < r.size(); ++l) {
  		/// \TODO Compute the autocorrelation r[l]
      /// \FET Autocorrelation computed
      /// - Inicialitzem l'autocorrelació a 0
      /// - Afegim el producte
      /// - Dividim per la durada
      /// *** TAXANNNN ***

      // for(unsigned int n=l; n< x.size(); n++){
      //   r[l] += x[n]*x[n-l];
      // }
      // r[l] = r[l]/x.size();

      r[l]=0;
      for (unsigned int n = 0; n < x.size()-l; n++){
        r[l] += x[n+l]*x[n];
      }
      r[l]=r[l]/x.size();
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero 
      r[0] = 1e-10; 
  }

  void PitchAnalyzer::set_window(Window win_type) {
    if (frameLen == 0)
      return;

    window.resize(frameLen);

    switch (win_type) {
      //Nose pq dona error si no poso els {}
    case HAMMING:{
      /// \TODO Implement the Hamming window
      /// \FET fnestra de hamming
      /// - Apliquem la fòrmula de hamming

      for(unsigned int i = 0; i < frameLen; i++){
        window[i]=0.53836-(1-0.53836)*cos((2*M_PI*i)/frameLen);
      }
      break;
    }
    case RECT:{
      window.assign(frameLen, 1);
      break;
    }
    default:
      window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0) {
    npitch_min = (unsigned int) samplingFreq/max_F0;
    if (npitch_min < 2)
      npitch_min = 2;  // samplingFreq/2

    npitch_max = 1 + (unsigned int) samplingFreq/min_F0;

    //frameLen should include at least 2*T0
    if (npitch_max > frameLen/2)
      npitch_max = frameLen/2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm, float zcr) const {
    /// \TODO Implement a rule to decide whether the sound is voiced or not.
    /// \FET Creem més umbrals per a la potència, la màxima autocorrelació i l'autocorrelació normalitzada
    /// * You can use the standard features (pot, r1norm, rmaxnorm),
    ///   or compute and use other ones.

    // if(rmaxnorm> umaxnorm){
    //   if(r1norm>unorm){
    //     if(pot>upot){
    //        return false;
    //     }
    //   }}
    // return true;

  if( rmaxnorm < umbral2 || r1norm < 0.260 || (zcr > umbral4)){
    return true;
  }
 if(pot > umbral3){ 
      if((rmaxnorm < 0.558 && r1norm > 0.99)){
        return true;
      }
      else if (rmaxnorm < 0.378 && r1norm > umbral1){
        return true;
      }
      else if((rmaxnorm > 0.386 || r1norm > 0.925)){
        return false;
      }
      else{
        return true;
      }
   }else{
      if(rmaxnorm > 0.5){
        return false;
      }else{
        return true;
      }
    }
  }

  float PitchAnalyzer::compute_zcr(vector<float> & x, unsigned int N, unsigned int fm) const {
	  unsigned int i = 0;
	  float zcr = 0;
	  for(i=1; i<N; i++){

		  if((x[i]*x[i-1]) < 0){
			  zcr = zcr + 1;
		  }

	  }
	  zcr = ((float)1 / (N-1)) * zcr;

	  zcr = fm / ((float)2) * zcr;
	  return zcr;
  }

  float PitchAnalyzer::compute_pitch(vector<float> & x,float maxPot) const {
    if (x.size() != frameLen){
      return -1.0F;
    }
    //Window input frame
    for (unsigned int i=0; i < x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);

    //Compute correlation
    autocorrelation(x, r);

    vector<float>::const_iterator iR = r.begin(), iRMax = r.begin() + npitch_min;

    /// \TODO 
	/// Find the lag of the maximum value of the autocorrelation away from the origin.<br>
	/// Choices to set the minimum value of the lag are:
	///    - The first negative value of the autocorrelation.
	///    - The lag corresponding to the maximum value of the pitch.
    ///	   .
	/// In either case, the lag should not exceed that of the minimum value of the pitch.
  /// \FET busquem el màxim entre el primer lòbul  el segon
    for(iRMax = iR = r.begin() + npitch_min; iR< r.begin()+ npitch_max; iR++){ //Com que el màxim ha d'estar entre en màx i el mín pitch fem el for que recorri aquest espai
      if(*iR>*iRMax){
        iRMax= iR;   //Si el iR és més gran que el màxim, actualitzem el valor d'aquest màxim
      }
    }

    unsigned int lag = iRMax - r.begin();

    float pot = 10 * log10(r[0]); 
    pot = pot-maxPot;
    float zcr  =compute_zcr(x, frameLen, samplingFreq) ;

    //You can print these (and other) features, look at them using wavesurfer
    //Based on that, implement a rule for unvoiced
    //change to #if 1 and compile
#if 1
    if (r[0] > 0.0F){
      //cout << pot << '\t' << r[1]/r[0] << '\t' << r[lag]/r[0] << endl;
      cout << '\t' << pot << endl;
    }
#endif
    
      if (unvoiced(pot, r[1]/r[0], r[lag]/r[0], zcr))
        return 0;
      else{
        return (float) samplingFreq/(float) lag;
      }
  }
}
