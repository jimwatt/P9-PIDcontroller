#ifndef PID_H
#define PID_H

#include "twiddle.hpp"

class PID {
public:

  /*
  * Constructor
  */
  PID(const std::vector<double>& K);

  double getControl(const double error);


private:

  /*
  * Coefficients
  */ 
  std::vector<double> K_;

      /*
  * State variables
  */
  double integrated_error_;
  double previous_error_;

  Twiddle twiddler_;

};

#endif /* PID_H */
