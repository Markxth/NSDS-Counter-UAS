#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_

namespace gnc {

/**
  * @class GuidanceEngine
  * @brief Handles the guidance logic for the C-UAS GNC system.
  * 
  * The GuidanceEngine is responsible for receiving target packages and determining what the turret should aim at. The GuidanceEngine
  * must also determine what the ballistic effects of the current projectile package will be, and calculate the necessary offsets
  * to hit the chosen target.
  */
class GuidanceEngine {
  public:
    GuidanceEngine() = default;
    GuidanceEngine(const GuidanceEngine&) = delete;
    ~GuidanceEngine() = default;
    GuidanceEngine& operator=(const GuidanceEngine&) = delete;
};

}  // namespace gnc

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_GUIDANCE_H_