// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_

#include "utility/math/Math.h"

namespace util::math {


inline Vector3d ScreenToRelativeXyz(const Vector2d& screen_xy, double range, double screen_width, double screen_height, double theta, double f, double n) {
 
  double aspect_ratio = screen_width / screen_height;
  double a = 1 / (aspect_ratio * std::tan(theta / 2));
  double b = 1 / (std::tan(theta / 2));
  
  Matrixd<4, 4> projection_matrix{a, 0.0, 0.0, 0.0, 0.0, b, 0.0, 0.0, 0.0, 0.0, -(f + n) / (f - n), -2 * n * f / (f - n), 0.0, 0.0, -1.0, 0.0};

  Vector4d pixel_4d{2*screen_xy[0]/screen_width - 1.0, 1.0 - 2*screen_xy[1]/screen_height, -1.0, 1.0};

  Matrixd<4, 4> inverse_projection_matrix = projection_matrix.Inverse();

  Vector4d direction = inverse_projection_matrix * pixel_4d;

  Vector3d direction_xyz{direction[0] / direction[3], direction[1] / direction[3], direction[2] / direction[3]};

  return direction_xyz.Normalized() * range;
} 


inline Vector3d RelativeToAbsoluteXyz(const Vector3d& relative_xyz, const Matrixd<3, 3>& turret_rotation, const Matrixd<3, 3>& sensor_rotation) {

  return turret_rotation * sensor_rotation * relative_xyz;

}

}

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_
