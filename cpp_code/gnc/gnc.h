#ifndef GNC_H
#define GNC_H

#include <vector>

#include "controls.h"
#include "guidance.h"
#include "navigation.h"

// TODO: forward until a decision is reached about how to actually handle this
class TargetPackage;

namespace gnc
{
    /**
     * @class GNCEngine
     * @brief Handles GNC engine orchestration.
     *
     * GNCEngine is responsible for orchestrating the execution of various components of the Guidance, Navigation, and Control code.
     * GNCEngine's primary public interface is the receive_target_packages method which receives a list of target packages and then makes choices
     * about which target to prioritize and executes the necessary code to acquire that target.
     */
    class GNCEngine
    {
    public:
        GNCEngine();
        GNCEngine(const GNCEngine&) = delete;

        GNCEngine& operator=(const GNCEngine&) = delete;

        /**
         * @brief Public interface for delivering target packages to the GNC engine.
         * @param target_packages a vector of target packages for processing.
         */
        void receive_target_packages(std::vector<TargetPackage> target_packages);
    private:
        GuidanceEngine guidance_engine;
        NavigationEngine navigation_engine;
        ControlEngine control_engine;
    }
}

#endif