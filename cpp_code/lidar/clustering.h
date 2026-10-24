// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_LIDAR_CLUSTERING_H_
#define NSDS_COUNTER_UAS_CPP_CODE_LIDAR_CLUSTERING_H_

namespace lidar {
    
/**
 * @class ClusteringEngine
 * @brief Handles point clustering for the C-UAS LiDAR system.
 *
 * The ClusteringEngine is responsible for grouping preprocessed points into clusters, where each cluster represents a candidate object
 * in the scene.
 */
class ClusteringEngine {
public:
  ClusteringEngine() = default;
  ClusteringEngine(const ClusteringEngine&) = delete;
  ~ClusteringEngine() = default;

  ClusteringEngine& operator=(const ClusteringEngine&) = delete;
};

}  // namespace lidar

#endif  // NSDS_COUNTER_UAS_CPP_CODE_LIDAR_CLUSTERING_H_
