// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_GNC_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_GNC_H_

#include <vector>

namespace util::datatypes {
struct TargetPackage;
}

#include "gnc/controls.h"
#include "gnc/guidance.h"
#include "gnc/navigation.h"

namespace gnc {

/**
 * @class GNCEngine
 * @brief Handles GNC engine orchestration.
 *
 * GNCEngine is responsible for orchestrating the execution of various components of the Guidance, Navigation, and Control code.
 * GNCEngine's primary public interface is the receive_target_packages method which receives a list of target packages and then makes choices
 * about which target to prioritize and executes the necessary code to acquire that target.
 */
class GNCEngine {
  public:
    GNCEngine();
    GNCEngine(const GNCEngine&) = delete;
    ~GNCEngine() = default;
    GNCEngine& operator=(const GNCEngine&) = delete;

    /**
    * @brief Public interface for delivering target packages to the GNC engine.
    * @param target_packages a vector of target packages for processing.
    */
    void receive_target_packages(const std::vector<util::datatypes::TargetPackage>& target_packages) noexcept;

  private:
    GuidanceEngine guidance_engine;
    NavigationEngine navigation_engine;
    ControlEngine control_engine;
};

}  // namespace gnc

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_GNC_H_
