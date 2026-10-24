// Copyright [2026] Purdue National Security and Defense Society
#include "gnc/HeuristicRuleRegistry.h"

#include "gnc/HeuristicRules.cpp"

namespace gnc::heuristics {

HeuristicRuleRegistry::HeuristicRuleRegistry() {
  // TOOD(ChristopherStackpole): auto populate
  registry.emplace(
	"target_distance",
	target_distance
  );

  registry.emplace(
	"target_velocity",
	target_velocity
  );

  registry.emplace(
	"target_confidence",
	target_confidence
  );
}

HeuristicRule HeuristicRuleRegistry::get_rule_from_id(std::string id) const {
  if (registry.contains(id)) {
	return registry.at(id);
  }
  else {
	throw std::runtime_error("Requested rule does not exist.");
  }
}

}  // namespace gnc::heuristics
