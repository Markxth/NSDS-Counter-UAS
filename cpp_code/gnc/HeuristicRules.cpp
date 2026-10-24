// Copyright [2026] Purdue National Security and Defense Society

#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULES_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULES_H_

#include "utility/datatypes/TargetPackage.h"

namespace gnc::heuristics {

double target_distance(const util::datatypes::TargetPackage& target) {
	return target.absolute_position_xyz.Magnitude();
}

double target_velocity(const util::datatypes::TargetPackage& target) {
	return target.absolute_velocity_xyz.Magnitude();
}

double target_confidence(const util::datatypes::TargetPackage& target) {
	return target.target_confidence;
}

}  // namespace gnc::heuristics

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTICRULES_H_
