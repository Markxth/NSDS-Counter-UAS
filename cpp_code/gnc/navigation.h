#ifndef NAVIGATION_H
#define NAVIGATION_H

namespace gnc
{
    /**
     * @class NavigationEngine
     * @brief Handles the navigation logic for the C-UAS GNC system.
     * 
     * The NavigationEngine is responsible for determine the current state of the turret relative to its base state and surroundings.
     * Internally the NavigationEngine listens to IMUs and rotary encoders in the turret structure to determine the current state, and may use GIS information
     * to augment state measurements.
     */
    class NavigationEngine
    {
    public:
        NavigationEngine();
        NavigationEngine(const NavigationEngine&) = delete;

        NavigationEngine& operator=(const NavigationEngine&) = delete;
    private:
    }
}

#endif