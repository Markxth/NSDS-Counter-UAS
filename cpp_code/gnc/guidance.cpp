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

util::math::Vector3d GuidanceEngine::determine_target_statevector(const std::vector<TargetPackage>& target_packages) const noexcept {
  util::math::Vector3d target_statevector;

  heuristics::TargetPriorityQueue target_priorities = determine_target_priorities(target_packages);

  return target_statevector;
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

}  // namespace gnc
