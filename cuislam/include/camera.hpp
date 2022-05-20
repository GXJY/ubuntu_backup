#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common_include.hpp"

namespace cuislam
{
    struct Camera {
        public:
            EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
            typedef std::shared_ptr<Camera> Ptr;

            double fx_ = 0, fy_ = 0, cx_ = 0, cy_ = 0;

            SE3 pose_;
            SE3 pose_inv_;

            Camera() = default; // mo ren gou zao han shu

            Camera(Mat33 K);

            Camera(double fx, double fy, double cx, double cy, const SE3 & pose);

            SE3 pose() const {return pose_;}

            // nei can ju zhen
            Eigen::Matrix3d K() const {
                Eigen::Matrix3d K;
                K << fx_, 0, cx_, 0 , fy_, cy_, 0 ,0 ,1;
                return K;
            }

            Vec2 PrincipalPoint() const {
                return Vec2(cx_, cy_);
            }

            double FocalLength() const {
                return fx_;
            }

            // coordinate transform: world camera pixel
            Eigen::Vector3d world2camera(const Eigen::Vector3d &p_w, const SE3 &T_c_w);

            Eigen::Vector3d camera2world(const Eigen::Vector3d &p_c, const SE3 &T_c_w);

            Eigen::Vector2d camera2pixel(const Eigen::Vector3d &p_c);
            
            Eigen::Vector3d pixel2camera(const Eigen::Vector2d &p_p, double depth = 1);

            Eigen::Vector3d pixel2world(const Eigen::Vector2d &p_p, const SE3 &T_c_w, double depth = 1);

            Eigen::Vector2d world2pixel(const Eigen::Vector3d &p_w, const SE3 &T_c_w);
    };
}


#endif