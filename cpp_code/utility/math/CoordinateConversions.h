// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_

#include "utility/math/Math.h"

namespace util::math {


nodiscard inline Vector3d ScreenToRelativeXyz(const Vector2d& screen_xy, const double range, const double screen_width, const double screen_height, const double theta, const double f, const double n) noexcept {
 
  const double aspect_ratio = screen_width / screen_height;
  const double a = 1 / (aspect_ratio * std::tan(theta / 2));
  const double b = 1 / (std::tan(theta / 2));
  
  Matrixd<4, 4> projection_matrix{a, 0.0, 0.0, 0.0, 
    0.0, b, 0.0, 0.0, 
    0.0, 0.0, -(f + n) / (f - n), -2 * n * f / (f - n), 
    0.0, 0.0, -1.0, 0.0};
  
  const double x_ndc = 2 * screen_xy[0] / screen_width - 1.0;
  const double y_ndc = 1.0 - 2 * screen_xy[1] / screen_height;
  const double w_ndc = range / std::sqrt(std::pow((x_ndc/a), 2) + std::pow((y_ndc/b), 2) + 1.0);
  const double z_ndc = -1.0 * (f + n) / (f - n) * w_ndc - 2 * f * n / (f - n);
  
  Vector4d p_screen{x_ndc * w_ndc, y_ndc * w_ndc, z_ndc * w_ndc, w_ndc};

  Vector4d direction = projection_matrix.Inverse() * p_screen;

  Vector3d direction_xyz{direction[0], direction[1], direction[2]};

  return direction_xyz.Normalized() * range;
} 


nodiscard inline Vector3d RelativeToAbsoluteXyz(const Vector3d& relative_xyz, const Matrixd<3, 3>& turret_rotation, const Matrixd<3, 3>& sensor_rotation) noexcept {

  return turret_rotation * sensor_rotation * relative_xyz;

}

}

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_COORDINATE_CONVERSIONS_H_
