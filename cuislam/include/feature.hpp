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
        
        std::shared_ptr<MapPoint> GetMapPoint();

        cv::KeyPoint GetKeyPoint() {return kp_;}

        cv::Point2f GetFixelXY();

        void SetMapPoint(std::shared_ptr<MapPoint> pMapPoint);

        bool MatchPoint() {return matchflag;}

        void SetMatchPoint() {matchflag =true;}

        bool OutlierPoint() {return is_outlier_;}
        
        bool isMatchPoint() {return is_map_point_;}

        void SetDescriptor(cv::Mat &descriptor) {descriptor_ = descriptor;}

        cv::Mat GetDescriptor(void) {return descriptor_;}

    private:
        std::weak_ptr<MapPoint> map_point_;
        std::weak_ptr<Frame> frame_;
        cv::KeyPoint kp_;
        cv::Mat descriptor_;
        bool matchflag = false;
        bool is_map_point_ = false;
        bool is_outlier_ = false;        
    };
}
#endif