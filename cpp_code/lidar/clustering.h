#ifndef CLUSTERING_H
#define CLUSTERING_H

namespace lidar
{
    /**
     * @class ClusteringEngine
     * @brief Handles point clustering for the C-UAS LiDAR system.
     *
     * The ClusteringEngine is responsible for grouping preprocessed points into clusters, where each cluster represents a candidate object
     * in the scene.
     */
    class ClusteringEngine
    {
    public:
        ClusteringEngine();
        ClusteringEngine(const ClusteringEngine&) = delete;

        ClusteringEngine& operator=(const ClusteringEngine&) = delete;
    private:
    };
}

#endif
