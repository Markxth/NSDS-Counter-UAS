// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULEREGISTRY_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULEREGISTRY_H_

#include <string>
#include <unordered_map>

#include "gnc/Heuristic.h"

namespace gnc::heuristics {

class HeuristicRuleRegistry {
  public:
	HeuristicRuleRegistry();
	~HeuristicRuleRegistry() = default;

	/**
	 * @brief Gets a heuristic rule from its.
	 * @param id The string that identifies the rule.
	 * @return The associated heuristic rule, if one exists.
	 * @throws When the requested rule does not exist.
	 */
	[[nodiscard]] HeuristicRule get_rule_from_id(std::string id) const;

  private:
	std::unordered_map<std::string, HeuristicRule> registry;
};

}  // namespace gnc::heuristics

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULEREGISTRY_H_
