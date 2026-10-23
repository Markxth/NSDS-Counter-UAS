// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_DATATYPES_TARGET_PACKAGE_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_DATATYPES_TARGET_PACKAGE_H_

#include <cstddef>

#include "utility/math/Math.h"

namespace util::datatypes {

/**
 * @struct TargetPackage
 * @brief Contains data about a single possible target as determined by the sensor systems.
 *
 * The TargetPackage stores vectors in rotated xyz coordinates. These rotated vectors are found by takeing the screen space coordinates (and range) of a target
 * and converting them into xyz coordinates with the camera assumed to be at the origin with no rotation. In actuality, the camera likely has some rotation, which
 * means the 'rotated' vectors are not the same in the fixed frame. 'Rotated' vectors can be converted into fixed frame vectors using the known orientation of the
 * camera.
 */
struct TargetPackage {
	std::size_t target_id;
	double time;
	util::math::Vector3d rotated_position_xyz;
	util::math::Vector3d rotated_velocity_xyz;
	double measurement_uncertainty;
	double target_confidence;
};

}  // namespace util::datatypes

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_DATATYPES_TARGET_PACKAGE_H_
