// Copyright [2026] Purdue National Security and Defense Society
#include <iostream>

#include "gnc/gnc.h"
#include "lidar/lidar.h"

int main()
{
  std::cout << "Hello, Sentry!" << std::endl;

  // TOOD(LeoZhang): enforce MISRA and Google CPP Style on cv.cpp, then include here

  lidar::LidarEngine lidar;
  gnc::GNCEngine gnc;

  while (false) {
	// Run CV

	// Run LiDAR

	// Combine with Fusion

	// Pass off to GNC
  }

  return 0;
}
