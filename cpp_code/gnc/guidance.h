// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_

#include <vector>

#include "utility/datatypes/TargetPackage.h"
#include "utility/math/Math.h"

#include "gnc/Heuristic.h"

namespace gnc {

/**
  * @class GuidanceEngine
  * @brief Handles the guidance logic for the C-UAS GNC system.
  * 
  * The GuidanceEngine is responsible for receiving target packages and determining what the turret should aim at. The GuidanceEngine
  * must also determine what the ballistic effects of the current projectile package will be, and calculate the necessary offsets
  * to hit the chosen target.
  */
class GuidanceEngine {
  public:
    GuidanceEngine() = default;
    GuidanceEngine(const GuidanceEngine&) = delete;
    ~GuidanceEngine() = default;
    GuidanceEngine& operator=(const GuidanceEngine&) = delete;

    /**
     * @brief Applies a weighted heuristic to determine the priority of each target in the provided list of target packages.
     * @param target_packages A vector of target packages to sort by priority.
     * @return A priority queue of targets.
     */
    [[nodiscard]] heuristics::TargetPriorityQueue determine_target_priorities(const std::vector<util::datatypes::TargetPackage>& target_packages) const noexcept;

    /**
     * @brief Guidance engine entry and exit point. Receives a list of target packages and the current statevector of the sentry and determines
     * a desired aim statevector.
     * @param target_packages A vector of target packages for processing.
     * @return The AE statevector that the sentry should aim at.
     */
    [[nodiscard]] util::math::Vector2d determine_desired_statevector(const std::vector<util::datatypes::TargetPackage>& target_packages) const noexcept;

    /**
     * @brief Sets the heuristic ruleset used by the targeting system.
     * @param rules The heuristic ruleset to use for targeting.
     */
    void set_targeting_heuristic_ruleset(heuristics::HeuristicRuleset ruleset) noexcept;

  private:
    heuristics::HeuristicRuleset targeting_heuristic_rules;

    /**
     * @brief Applies the active heuristic rules to the given target package. Returns 0 and warns if there are no rules.
     * @param target_package The target package to apply the rules to.
     * @return The weighted output of the weighted heuristic function.
     */
    [[nodiscard]] double apply_targeting_heuristic(const util::datatypes::TargetPackage& target_package) const noexcept;

    /**
     * @brief Calculates the absolute AE rotation needed to track a moving target.
     * @param target_package The target package to calculate aim for.
     * @param dt_s The capture time interval in seconds.
     * @return The aim statevector in AE coordinates.
     */
    [[nodiscard]] util::math::Vector2d calculate_aim_statevector(const util::datatypes::TargetPackage& target_package, const double dt_s) const noexcept;
};

}  // namespace gnc

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_
