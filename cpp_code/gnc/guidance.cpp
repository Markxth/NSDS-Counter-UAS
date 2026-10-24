// Copyright [2026] Purdue National Security and Defense Society
#include "gnc/guidance.h"

namespace gnc {

using TargetPackage = util::datatypes::TargetPackage;

heuristics::TargetPriorityQueue GuidanceEngine::determine_target_priorities(const std::vector<TargetPackage>& target_packages) const noexcept {
  heuristics::TargetPriorityQueue priorities;

  for (const util::datatypes::TargetPackage target : target_packages) {
	double priority = apply_targeting_heuristic(target);
	priorities.emplace(heuristics::WeightedTarget{priority, std::cref(target)});
  }

  return priorities;
}

util::math::Vector2d GuidanceEngine::determine_desired_statevector(const std::vector<TargetPackage>& target_packages) const noexcept {
  util::math::Vector2d desired_statevector_ae;

  heuristics::TargetPriorityQueue target_priorities = determine_target_priorities(target_packages);
  while (!target_priorities.empty()) {
	// Pull Target Package
	const heuristics::WeightedTarget target = target_priorities.top();
	target_priorities.pop();

	double weight = target.first;
	const util::datatypes::TargetPackage& target_package = target.second;

	// Determine Aim Statevector
	// TODO(ChristopherStackpole): REMOVE HARDCODING
	// NOTE: Assumed 60 FPS
	util::math::Vector2d aim_statevector_ae = calculate_aim_statevector(target_package, 0.016);
  }

  return desired_statevector_ae;
}

void GuidanceEngine::set_targeting_heuristic_ruleset(heuristics::HeuristicRuleset rules) noexcept {
  targeting_heuristic_rules = rules;
}

double GuidanceEngine::apply_targeting_heuristic(const TargetPackage& target_package) const noexcept {
  double score = 0.0;
  
  for (heuristics::WeightedHeuristicRule rule : targeting_heuristic_rules) {
	double weight = rule.first;
	double rule_value = rule.second(target_package);

	score += weight * rule_value;
  }

  return score;
}

util::math::Vector2d GuidanceEngine::calculate_aim_statevector(const util::datatypes::TargetPackage& target_package, const double dt_s) const noexcept {
  util::math::Vector2d aim_statevector;

  return aim_statevector;
}

}  // namespace gnc
