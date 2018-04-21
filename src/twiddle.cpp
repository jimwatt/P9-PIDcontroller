#include <iostream>
#include <limits>
#include <cmath>
#include "twiddle.hpp"

Twiddle::Twiddle(const int num_settle_steps, const int num_record_steps, 
	const std::vector<double>& p) :
	num_settle_steps_(num_settle_steps),
	num_record_steps_(num_record_steps),
	tolerance_(0.01),
	p_(p),
	steps_since_reset_(0),
	total_error_(0.0),
	best_error_(std::numeric_limits<double>::infinity()),
	status_(1),
	current_twiddle_dimension_(0) {

	dp_.clear();
	dp_.push_back(0.2);
	dp_.push_back(0.003);
	dp_.push_back(2.9);


}

double sum(std::vector<double>& v) {
	double s = 0.0;
	for(size_t ii=0;ii<v.size();++ii) {
		s+=v[ii];
	}
	return s;
}


bool Twiddle::updateError(const double error, std::vector<double>& Kvals) {

	bool KisUpdated = false;

	++steps_since_reset_;

	if(steps_since_reset_>num_record_steps_+num_record_steps_) {
		// std::cout << "adjusting coefficients ..." << std::endl;
		std::cout << "total_error : " << total_error_ << std::endl;

		KisUpdated = doTwiddle(Kvals);

		steps_since_reset_ = 0;
		total_error_ = 0.0;
	}

	if(steps_since_reset_<num_settle_steps_) {
		// std::cout << "settling ..." << std::endl;
	}
	else {
		// std::cout << "recording ..." << std::endl;
		total_error_ += fabs(error);
	}

	return KisUpdated;

}

bool Twiddle::doTwiddle(std::vector<double>& Kvals) {

	const int numdim = Kvals.size();
    
    if(status_== 0) {  // We are already done
    	return false;
    }

    if(sum(dp_)<tolerance_) {  // Hooray, we are done!
		status_ = 0;
		return false;
	}
    

    if(status_==1) {		// we just finished the first call to robot
    	
    	if(total_error_ < best_error_) {
        	best_error_ = total_error_;
            dp_[current_twiddle_dimension_] *= 1.1;
            current_twiddle_dimension_ = (current_twiddle_dimension_+1) % numdim;
            p_[current_twiddle_dimension_] += dp_[current_twiddle_dimension_];
            status_ = 1;		//just for readibility
            std::cout << "BEST ERROR : " << best_error_ << std::endl;
        }
        else {
            p_[current_twiddle_dimension_] -= 2 * dp_[current_twiddle_dimension_];
            status_ = 2;
        }
    }
    else if(status_==2) {	// we just finished the second call to robot
		if(total_error_ < best_error_) {
			best_error_ = total_error_;
			dp_[current_twiddle_dimension_] *= 1.1;
			std::cout << "BEST ERROR : " << best_error_ << std::endl;
		}
		else {
			p_[current_twiddle_dimension_] += dp_[current_twiddle_dimension_];
			dp_[current_twiddle_dimension_] *= 0.9;
		}
		current_twiddle_dimension_ = (current_twiddle_dimension_+1) % numdim;
		p_[current_twiddle_dimension_] += dp_[current_twiddle_dimension_];
        status_ = 1;
    }
    
    Kvals = p_;

    std::cout << current_twiddle_dimension_ << " \tsum(dp) : " << sum(dp_) << std::endl;
    std::cout << "dp : " << dp_[0] << " \t" << dp_[1] << " \t" << dp_[2] << std::endl;
    return true;

}



// while sum(dp) > tol:
//         print("Iteration {}, best error = {}".format(it, best_err))
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
