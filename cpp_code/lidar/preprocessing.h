#ifndef NSDS_COUNTER_UAS_CPP_CODE_LIDAR_PREPROCESSING_H_
#define NSDS_COUNTER_UAS_CPP_CODE_LIDAR_PREPROCESSING_H_

namespace lidar {

/**
 * @class PreprocessingEngine
 * @brief Handles point cloud preprocessing for the C-UAS LiDAR system.
 *
 * The PreprocessingEngine is responsible for cleaning raw point clouds before further processing. This includes range and region-of-interest
 * filtering, downsampling, outlier removal, and ground removal.
 */
class PreprocessingEngine {
public:
  PreprocessingEngine() = default;
  PreprocessingEngine(const PreprocessingEngine&) = delete;
  ~PreprocessingEngine() = default;

  PreprocessingEngine& operator=(const PreprocessingEngine&) = delete;
};

}  // namespace lidar

#endif  // NSDS_COUNTER_UAS_CPP_CODE_LIDAR_PREPROCESSING_H_
