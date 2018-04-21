#include <iostream>
#include <iomanip>
#include "PID.h"

PID::PID(const std::vector<double>& K, const bool use_twiddler) :
	K_(K), 
	use_twiddler_(use_twiddler),
	integrated_error_(0.0), 
	previous_error_(0.0),
	twiddler_(100,500,K)  {

}

double PID::getControl(const double error) {

	if(use_twiddler_) {
		const bool KisUpdated = twiddler_.updateError(error,K_);
	
		if(KisUpdated) {
			std::cout << "\nNEW COEFF : " << K_[0] << "  " << K_[1]  << "   " << K_[2]  << std::endl;
			integrated_error_ = 0.0;
		}
	}

	const double Derror = (error - previous_error_);
	
	integrated_error_ += error;
	previous_error_ = error;

	const double u =  -K_[0] * error - K_[2] * Derror - K_[1] * integrated_error_;

	if(u>1.0) {
		return 1.0;
	}
	else if(u<-1.0) {
		return -1.0;
	}
	
	return u;


}


