#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>

class Twiddle {
public:

  Twiddle(const int num_settle_steps, const int num_record_steps, 
	const std::vector<double>& p);

  void updateError(const double error);


private:

	const int num_settle_steps_;
	const int num_record_steps_;
	const double tolerance_;

	std::vector<double> p_;
	std::vector<double> dp_;

  int steps_since_reset_;
  double total_error_;
  double best_error_;


};

#endif /* TWIDDLE_H */

