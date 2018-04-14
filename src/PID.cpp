#include <iostream>
#include <iomanip>
#include "PID.h"

PID::PID(const std::vector<double>& K) :
	K_(K), 
	integrated_error_(0.0), 
	previous_error_(0.0),
	twiddler_(50,50,K)  {

}

double PID::getControl(const double error) {

	twiddler_.updateError(error);

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

void PID::initialize(const std::vector<double>& K) {

	K_ = K;

	integrated_error_ = 0.0;
	previous_error_ = 0.0;

}



