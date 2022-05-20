#pragma once
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "common_include.hpp"
#include "mappoint.hpp"

namespace cuislam {
    class Frame;
    class Feature {
        public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
        Feature() = default;

        Feature(std::shared_ptr<Frame> frame, const cv::KeyPoint &kp, const cv::Mat& descriptor);
        
    };
}
#endif