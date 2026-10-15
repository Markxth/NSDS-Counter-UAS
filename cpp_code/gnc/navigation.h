#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_NAVIGATION_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_NAVIGATION_H_

namespace gnc {

/**
  * @class NavigationEngine
  * @brief Handles the navigation logic for the C-UAS GNC system.
  * 
  * The NavigationEngine is responsible for determine the current state of the turret relative to its base state and surroundings.
  * Internally the NavigationEngine listens to IMUs and rotary encoders in the turret structure to determine the current state, and may use GIS information
  * to augment state measurements.
  */
class NavigationEngine {
  public:
    NavigationEngine() = default;
    NavigationEngine(const NavigationEngine&) = delete;
    ~NavigationEngine() = default;
    NavigationEngine& operator=(const NavigationEngine&) = delete;
};

}  // namespace gnc

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_NAVIGATION_H_