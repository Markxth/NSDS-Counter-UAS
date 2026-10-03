#ifndef CONTROLS_H
#define CONTROLS_H

namespace gnc
{
    /**
     * @class ControlEngine
     * @brief Handles the control logic for the C-UAS GNC system.
     *
     * The ControlEngine is responsible for receiving a target location and emitting hardware signals to align the turret to the target location.
     * Internaly the ControlEngine runs a PID loop to estimate and correct aiming error from external forces (wind, recoil, etc.).
     */
    class ControlEngine
    {
    public:
        ControlEngine(double kp, double ki, double kd, double integral = 0, double prev_error = 0, double prev_time = 0);
        ControlEngine(const ControlEngine&) = delete;

        ControlEngine& operator=(const ControlEngine&) = delete;

        /// Accessors for constants and accumulator
        double get_kp();
        double get_ki();
        double get_kd();
        double get_integral();
        double get_prev_error();
        double get_prev_time();

        /**
         * @brief A PID loop that estimates and corrects aiming error.
         * @param error the instantaneously measured error.
         */
        double PID(double error);
    private:
        double kp_;
        double ki_;
        double kd_;
        double integral_;
        double prev_error_;
        double prev_time_;
    }
}

#endif