#ifndef DETECTION_H
#define DETECTION_H

namespace lidar
{
    /**
     * @class DetectionEngine
     * @brief Handles target detection for the C-UAS LiDAR system.
     *
     * The DetectionEngine is responsible for evaluating candidate clusters, rejecting those unlikely to be UAS, and converting the remainder
     * into target measurements (position, extent, and timestamp) for sensor fusion.
     */
    class DetectionEngine
    {
    public:
        DetectionEngine();
        DetectionEngine(const DetectionEngine&) = delete;

        DetectionEngine& operator=(const DetectionEngine&) = delete;
    private:
    };
}

#endif
