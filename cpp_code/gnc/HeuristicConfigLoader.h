// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICCONFIGLOADER_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICCONFIGLOADER_H_

#include <string>

#include "gnc/Heuristic.h"
#include "gnc/HeuristicRuleRegistry.h"

namespace gnc::heuristics {

class HeuristicConfigLoader {
  public:
	HeuristicConfigLoader() = default;
	~HeuristicConfigLoader() = default;

	/**
	 * @brief Loads a heuristic rule config from a provided file.
	 * @param file_path The config file path to load.
	 * @return The ruleset loaded from the file.
	 * @throws When the file cannot be found.
	 */
	[[nodiscard]] HeuristicRuleset load_ruleset_from_file(const std::string file_path) const;

  private:
	HeuristicRuleRegistry registry;
};

}

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICCONFIGLOADER_H_
