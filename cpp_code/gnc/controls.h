// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_CONTROLS_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_CONTROLS_H_

#include "utility/math/Math.h"

namespace gnc {

/**
 * @class ControlEngine
 * @brief Handles the control logic for the C-UAS GNC system.
 *
 * The ControlEngine receives a target location and emits hardware signals to
 * align the turret to it. Internally it runs a PID loop that estimates and
 * corrects aiming error from external forces such as wind and recoil. Error
 * is in radians of turret deflection. Ported from pycode/gnc/controls.py.
 */
class ControlEngine {
 public:
  /**
   * @brief Builds the loop from its gains and a resumable seed state, so a
   *        running loop survives a restart without resetting the integral.
   * @param kp proportional multiplier.
   * @param ki integral multiplier.
   * @param kd derivative multiplier.
   * @param integral integral accumulator for PID calculations.
   * @param prev_error a seed error to use for PID calculations.
   * @param prev_time a seed time in seconds; 0 means "not yet seeded".
   */
  ControlEngine(double kp, double ki, double kd, double integral = 0,
                double prev_error = 0, double prev_time = 0);
  ControlEngine(const ControlEngine&) = delete;
  ~ControlEngine() = default;
  ControlEngine& operator=(const ControlEngine&) = delete;

  [[nodiscard]] double get_kp() const noexcept;
  [[nodiscard]] double get_ki() const noexcept;
  [[nodiscard]] double get_kd() const noexcept;
  [[nodiscard]] double get_integral() const noexcept;
  [[nodiscard]] double get_prev_error() const noexcept;
  [[nodiscard]] double get_prev_time() const noexcept;

  /**
   * @brief Estimates and corrects the aiming error for one control step.
   *
   * u = kp*e + ki*integral(e*dt) + kd*(de/dt). Advances loop state, so this
   * runs at the control rate rather than once per received measurement.
   *
   * @param error the instantaneous error, in radians of turret deflection.
   * @return the correction signal for the actuator.
   */
  [[nodiscard]] double PID(double error) noexcept;

  /**
   * @brief Aims the sentry at the target statevector given the current state vector of the sentry.
   * @param current_statevector_ae The absolute AE statevector the sentry is currently aiming at.
   * @param desired_statevector_ae The absolute AE statevector to aim it.
   */
  void aim_at_desired_statevector(const util::math::Vector2d& current_statevector_ae, const util::math::Vector2d& desired_statevector_ae) noexcept;

 private:
  double kp_;
  double ki_;
  double kd_;
  double integral_;
  double prev_error_;
  // Seconds on the monotonic clock, matching Python's time.monotonic().
  double prev_time_;
};

}  // namespace gnc

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_CONTROLS_H_
