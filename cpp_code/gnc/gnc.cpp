// Copyright [2026] Purdue National Security and Defense Society
#include "utility/datatypes/TargetPackage.h"

#include "gnc/gnc.h"

namespace gnc {

const std::string DEFAULT_HEURISTIC_CONFIG_PATH = "config/gnc/default_ruleset.toml";

using TargetPackage = util::datatypes::TargetPackage;

GNCEngine::GNCEngine()
  : control_engine(0, 0, 0) {
  heuristics::HeuristicRuleset default_ruleset = heuristic_config_loader.load_ruleset_from_file(DEFAULT_HEURISTIC_CONFIG_PATH);
  guidance_engine.set_targeting_heuristic_ruleset(default_ruleset);
}

void GNCEngine::receive_target_packages(const std::vector<TargetPackage>& target_packages) noexcept {
  util::math::Vector2d current_statevector_ae = navigation_engine.get_current_statevector();
  util::math::Vector2d desired_statevector_ae = guidance_engine.determine_desired_statevector(target_packages);

  control_engine.aim_at_desired_statevector(current_statevector_ae, desired_statevector_ae);
}

}  // namespace gnc
