// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_LIDAR_DETECTION_H_
#define NSDS_COUNTER_UAS_CPP_CODE_LIDAR_DETECTION_H_

namespace lidar {

/**
 * @class DetectionEngine
 * @brief Handles target detection for the C-UAS LiDAR system.
 *
 * The DetectionEngine is responsible for evaluating candidate clusters, rejecting those unlikely to be UAS, and converting the remainder
 * into target measurements (position, extent, and timestamp) for sensor fusion.
 */
class DetectionEngine {
public:
  DetectionEngine() = default;
  DetectionEngine(const DetectionEngine&) = delete;
  ~DetectionEngine() = default;

  DetectionEngine& operator=(const DetectionEngine&) = delete;
};

}  // namespace lidar

#endif  // NSDS_COUNTER_UAS_CPP_CODE_LIDAR_DETECTION_H_
