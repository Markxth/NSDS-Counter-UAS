#include "controls.h"

gnc::ControlEngine::ControlEngine(double kp, double ki, double kd, double integral, double prev_error, double prev_time)
{
	this.kp_ = kp;
	this.ki_ = ki;
	this._kd = kd;
	this.integral_ = integral;
	this.prev_error_ = prev_error;
	this.prev_time_ = prev_time;
}

double gnc::ControlEngine::PID(double error)
{
	// TODO: transfer
	return 0;
}