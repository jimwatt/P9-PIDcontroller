#ifndef PID_H
#define PID_H

#include "twiddle.hpp"

class PID {
public:

  /*
  * Constructor
  */
  PID(const std::vector<double>& K, const bool use_twiddler);

  double getControl(const double error);


private:

  /*
  * PID Coefficients
  */ 
  std::vector<double> K_;
  const bool use_twiddler_;


  double integrated_error_;
  double previous_error_;

  Twiddle twiddler_;

};

#endif /* PID_H */
