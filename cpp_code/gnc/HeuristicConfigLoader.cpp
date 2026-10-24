// Copyright [2026] Purdue National Security and Defense Society
#include <iostream>

#include "ext/toml.h"

#include "gnc/HeuristicConfigLoader.h"

namespace gnc::heuristics {

HeuristicRuleset HeuristicConfigLoader::load_ruleset_from_file(const std::string file_path) const {
  HeuristicRuleset ruleset;

  try {
	toml::table table = toml::parse_file(file_path);

	auto* rules_array = table["rules"].as_array();
	if (rules_array) {
	  for (const auto& rule_node : *rules_array) {
		auto* rule_table = rule_node.as_table();
		if (!rule_table) continue;

		auto id = rule_table->get_as<std::string>("id");
		auto weight = rule_table->get_as<double>("weight");

		if (!id || !weight) continue;

		HeuristicRule rule;
		try {
		  rule = registry.get_rule_from_id(id->get());
		}
		catch (const std::runtime_error& err) {
		  // Unknown heuristic rule id; skip
		  continue;
		}

		ruleset.emplace_back(*weight, rule);
	  }
	}
  }
  catch (const toml::parse_error& err) {
	std::cerr << "Parsing failed with error:\n" << err << std::endl;
  }

  return ruleset;
}

}  // namespace gnc::heuristics
