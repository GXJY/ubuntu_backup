#pragma once
#ifndef MAPPOINT_HPP
#define MAPPOINT_HPP

#include "common_include.hpp"

namespace cuislam {
    struct Frame;

    struct Feature;
    
    // lu biao dian lei, te zheng dian zai san jao hua hou xing cheng lu biao dian
    struct MapPoint
    {
        public:
        // ???  EIGEN_MAKE_ALIGENED_OPERATOR_NEW;
        typedef std::shared_ptr<MapPoint> Ptr;
        unsigned long id = 0;  //ID
        bool is_bad_point = false;
        bool is_putlier = false;
        Vec3 pos_ = Vec3::Zero();  // Position in world
        std::mutex data_mutex_;
        int observed_times_ = 0;  // being observed by feature matching algo.
        std::list<std::weak_ptr<Feature>> observations_;

        cv::Mat descriptor_;  //di tu dian de miao shi zi 

        MapPoint() {}

        MapPoint(long id, Vec3 position);

        Vec3 Pos() {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return pos_;
        }

        void setPose(const Vec3 &pos) {
            std::unique_lock<std::mutex> lck(data_mutex_);
            pos_ = pos;
        }

        void setDescriptor(const cv::Mat& descriptor) {
            std::unique_lock<std::mutex> lck(data_mutex_);
            descriptor_ = descriptor;
        }

        void AddObservation(std::shared_ptr<Feature> feature) {
            std::unique_lock<std::mutex> lck(data_mutex_);
            observations_.push_back(feature);
            observed_times_++;
        }

        void RemoveObservation(std::shared_ptr<Feature> feature);

        std::list<std::weak_ptr<Feature>> GetObs() {
            std::unique_lock<std::mutex> lck(data_mutex_);
            return observations_;
        }

        static std::shared_ptr<MapPoint> CreatNewMappoint();
    }; 
}

#endif