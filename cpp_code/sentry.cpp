// Copyright [2026] Purdue National Security and Defense Society
#include <iostream>

#include "gnc/gnc.h"
#include "lidar/lidar.h"

#include "utility/datatypes/TargetPackage.h"
#include "utility/math/Math.h"

int main()
{
  std::cout << "Hello, Sentry!" << std::endl;

  // TOOD(LeoZhang): enforce MISRA and Google CPP Style on cv.cpp, then include here

  lidar::LidarEngine lidar;
  gnc::GNCEngine gnc;

  // TEST
  std::vector<util::datatypes::TargetPackage> targets{
	util::datatypes::TargetPackage{
	  0,
	  10.0,
	  util::math::Vector3d{0.0, 1.0, 2.0},
	  util::math::Vector3d{3.0, 4.0, 5.0},
	  0.0,
	  10.0
	}
  };

  gnc.receive_target_packages(targets);
  // END TEST

  while (false) {
	// Run CV

	// Run LiDAR

	// Combine with Fusion

	// Pass off to GNC
  }

  return 0;
}
