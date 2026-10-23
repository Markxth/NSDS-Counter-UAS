// Copyright [2026] Purdue National Security and Defense Society
#include "utility/datatypes/TargetPackage.h"

#include "gnc/gnc.h"

namespace gnc {

using TargetPackage = util::datatypes::TargetPackage;

GNCEngine::GNCEngine()
  : control_engine(0, 0, 0) {}

void GNCEngine::receive_target_packages(const std::vector<TargetPackage>& target_packages) noexcept {
  util::math::Vector3d target_statevector_xyz = guidance_engine.determine_target_statevector(target_packages);
  util::math::Vector2d current_statevector_ae = navigation_engine.get_current_statevector();
  control_engine.aim_at_target(target_statevector_xyz, current_statevector_ae);
}

}  // namespace gnc
