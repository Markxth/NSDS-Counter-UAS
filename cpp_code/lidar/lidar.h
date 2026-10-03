#ifndef LIDAR_H
#define LIDAR_H

#include "clustering.h"
#include "detection.h"
#include "preprocessing.h"

namespace lidar
{
    /**
     * @class LidarEngine
     * @brief Handles LiDAR engine orchestration.
     *
     * LidarEngine is responsible for orchestrating the execution of the LiDAR processing pipeline. Raw point clouds received from the
     * sensor are passed through preprocessing, clustering, and detection to produce target measurements for sensor fusion.
     */
    class LidarEngine
    {
    public:
        LidarEngine();
        LidarEngine(const LidarEngine&) = delete;

        LidarEngine& operator=(const LidarEngine&) = delete;
    private:
        PreprocessingEngine preprocessing_engine;
        ClusteringEngine clustering_engine;
        DetectionEngine detection_engine;
    };
}

#endif
