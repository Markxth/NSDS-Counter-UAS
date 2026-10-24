// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTIC_H_
#define NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTIC_H_

#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "utility/datatypes/TargetPackage.h"

namespace gnc::heuristics {

using HeuristicRule = std::function<double(const util::datatypes::TargetPackage&)>;
using WeightedHeuristicRule = std::pair<double, HeuristicRule>;
using HeuristicRuleset = std::vector<WeightedHeuristicRule>;
using WeightedTarget = std::pair<double, std::reference_wrapper<const util::datatypes::TargetPackage>>;

/**
 * @brief A comparator for WeightedTargets. Compares the priorties associated with each target.
 */
struct WeightedTargetCompare {
  /**
   * @brief Compares two weighted targets.
   * @param lhs The left target.
   * @param rhs The right target.
   * @return True if the left hand is smaller than the right hand.
   */
  bool operator()(const WeightedTarget& lhs, const WeightedTarget& rhs) const {
    return lhs.first < rhs.first;
  }
};

using TargetPriorityQueue = std::priority_queue<WeightedTarget, std::vector<WeightedTarget>, WeightedTargetCompare>;

}

#endif  // NSDS_COUNTER_UAS_CPP_CODE_GNC_HEURISTIC_H_