// Copyright [2026] Purdue National Security and Defense Society
#include <chrono>

#include "gnc/controls.h"

namespace gnc {

namespace {

// Seconds from a monotonic origin, the counterpart of Python's
// time.monotonic(): it never steps when the wall clock is corrected.
double NowSeconds() noexcept {
  const auto elapsed = std::chrono::steady_clock::now().time_since_epoch();
  return std::chrono::duration<double>(elapsed).count();
}

}  // namespace

// A prev_time of 0 means "unseeded", not "started at time zero". Stamping
// here keeps the first dt at one control period, not the whole uptime.
ControlEngine::ControlEngine(double kp, double ki, double kd, double integral,
                             double prev_error, double prev_time)
  : kp_(kp),
    ki_(ki),
    kd_(kd),
    integral_(integral),
    prev_error_(prev_error),
    prev_time_((prev_time == 0.0) ? NowSeconds() : prev_time) {}

double ControlEngine::get_kp() const noexcept { return kp_; }
double ControlEngine::get_ki() const noexcept { return ki_; }
double ControlEngine::get_kd() const noexcept { return kd_; }
double ControlEngine::get_integral() const noexcept { return integral_; }
double ControlEngine::get_prev_error() const noexcept { return prev_error_; }
double ControlEngine::get_prev_time() const noexcept { return prev_time_; }

double ControlEngine::PID(const double error) noexcept {
  const double current_time = NowSeconds();
  const double dt = current_time - prev_time_;
  prev_time_ = current_time;

  const double proportional_term = kp_ * error;

  // Removes steady state error from a constant disturbance such as wind,
  // which kp alone cannot cancel.
  integral_ += error * dt;
  const double integral_term = ki_ * integral_;

  // Guards the divide: the first frame, or two calls inside one clock tick,
  // can give dt <= 0.
  double derivative_term = 0.0;
  if (dt > 0.0) derivative_term = (error - prev_error_) / dt;
  derivative_term *= kd_;
  prev_error_ = error;

  return proportional_term + integral_term + derivative_term;
}

void ControlEngine::aim_at_desired_statevector(const util::math::Vector2d& current_statevector_ae, const util::math::Vector2d& desired_statevector_ae) noexcept {
  // Determine necessary commands

  // Issue commands
}

}  // namespace gnc
