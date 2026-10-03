#ifndef PREPROCESSING_H
#define PREPROCESSING_H

namespace lidar
{
    /**
     * @class PreprocessingEngine
     * @brief Handles point cloud preprocessing for the C-UAS LiDAR system.
     *
     * The PreprocessingEngine is responsible for cleaning raw point clouds before further processing. This includes range and region-of-interest
     * filtering, downsampling, outlier removal, and ground removal.
     */
    class PreprocessingEngine
    {
    public:
        PreprocessingEngine();
        PreprocessingEngine(const PreprocessingEngine&) = delete;

        PreprocessingEngine& operator=(const PreprocessingEngine&) = delete;
    private:
    };
}

#endif
