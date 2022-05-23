#include "feature.hpp"

namespace cuislam {
    Feature::Feature(std::shared_ptr<Frame> frame, const cv::KeyPoint &kp, const cv::Mat &descriptor)
    :frame_(frame), kp_(kp), descriptor_(descriptor) {

    }

    std::shared_ptr<MapPoint> Feature::GetMapPoint() {
        return map_point_.lock();
    }

    cv::Point2f Feature::GetFixelXY() {
        return kp_.pt;
    }

    void Feature::SetMapPoint(std::shared_ptr<MapPoint> pMapPoint) {
        map_point_ = pMapPoint;
        is_map_point_ = true;
    }
} 
