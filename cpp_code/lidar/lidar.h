// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_LIDAR_LIDAR_H_
#define NSDS_COUNTER_UAS_CPP_CODE_LIDAR_LIDAR_H_

#include "clustering.h"
#include "detection.h"
#include "preprocessing.h"

namespace lidar {

/**
 * @class LidarEngine
 * @brief Handles LiDAR engine orchestration.
 *
 * LidarEngine is responsible for orchestrating the execution of the LiDAR processing pipeline. Raw point clouds received from the
 * sensor are passed through preprocessing, clustering, and detection to produce target measurements for sensor fusion.
 */
class LidarEngine {
public:
  LidarEngine() = default;
  LidarEngine(const LidarEngine&) = delete;
  ~LidarEngine() = default;

  LidarEngine& operator=(const LidarEngine&) = delete;
private:
  PreprocessingEngine preprocessing_engine;
  ClusteringEngine clustering_engine;
  DetectionEngine detection_engine;
};

}  // namespace lidar

#endif  // NSDS_COUNTER_UAS_CPP_CODE_LIDAR_LIDAR_H_
