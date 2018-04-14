#include <iostream>
#include <limits>
#include "twiddle.hpp"

Twiddle::Twiddle(const int num_settle_steps, const int num_record_steps, 
	const std::vector<double>& p) :
	num_settle_steps_(num_settle_steps),
	num_record_steps_(num_record_steps),
	tolerance_(0.2),
	p_(p),
	steps_since_reset_(0),
	total_error_(0.0),
	best_error_(std::numeric_limits<double>::infinity()) {

	dp_.clear();
	for(size_t ii=0;ii<p.size();++ii) {
		dp_.push_back(0.001);
	}


}


void Twiddle::updateError(const double error) {

	++steps_since_reset_;

	if(steps_since_reset_>num_record_steps_+num_record_steps_) {
		std::cout << "adjusting coefficients ..." << std::endl;
		std::cout << "total_error : " << total_error_ << std::endl;




		steps_since_reset_ = 0;
		total_error_ = 0.0;
	}

	if(steps_since_reset_<num_settle_steps_) {
		std::cout << "settling ..." << std::endl;
	}
	else {
		std::cout << "recording ..." << std::endl;
		total_error_ += error;
	}



}

// void Twiddle::twiddle(): 
    

//     it = 0
//     while sum(dp) > tol:
        
//         for i in range(len(p)):
//             p[i] += dp[i]
//             robot = make_robot()
//             x_trajectory, y_trajectory, err = run(robot, p)

//             if err < best_err:
//                 best_err = err
//                 dp[i] *= 1.1
//             else:
//                 p[i] -= 2 * dp[i]
//                 robot = make_robot()
//                 x_trajectory, y_trajectory, err = run(robot, p)

//                 if err < best_err:
//                     best_err = err
//                     dp[i] *= 1.1
//                 else:
//                     p[i] += dp[i]
//                     dp[i] *= 0.9
//         it += 1
//     return p

