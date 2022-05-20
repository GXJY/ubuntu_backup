#include "camera.hpp"

namespace cuislam
{
    Camera::Camera(Mat33 K) {
        fx_ = K(0, 0);
        fy_ = K(1, 1);
        cx_ = K(0, 2);
        cy_ = K(1, 2);
    }

    Camera::Camera(double fx, double fy, double cx, double cy, const SE3 & pose) {
        fx_ = fx;
        fy_ = fy;
        cx_ = cx;
        cy_ = cy;
        pose_ = pose;

        pose_inv_ = pose_.inverse();
    }
    
    Eigen::Vector3d Camera::world2camera(const Eigen::Vector3d &p_w, const SE3 & T_c_w)
    {
        return pose_ * T_c_w * p_w;
    }

    Eigen::Vector3d Camera::camera2world(const Eigen::Vector3d &p_c, const SE3 & T_c_w)
    {
        return T_c_w.inverse() * p_c;
    }
    
    Eigen::Vector2d Camera::camera2pixel(const Eigen::Vector3d &p_c)
    {
        Eigen::Vector2d vec(fx_ * p_c(0, 0) / p_c(2, 0) + cx_, fy_ * p_c(1, 0) / p_c(2, 0) + cy_);
        return vec;
    }

    Eigen::Vector3d Camera::pixel2camera(const Eigen::Vector2d &p_p, double depth)
    {
        Eigen::Vector3d vec;
        vec[0] = (p_p[0] - cx_) * depth / fx_;
        vec[1] = (p_p[1] - cy_) * depth / fy_;
        vec[2] = depth;

        return vec;
    }

    Eigen::Vector3d Camera::pixel2world(const Eigen::Vector2d &p_p, const SE3 &T_c_w, double depth)
    {
        return camera2world(pixel2camera(p_p, depth), T_c_w);
    }

    Eigen::Vector2d Camera::world2pixel(const Eigen::Vector3d &p_w, const SE3 &T_c_w)
    {
        return camera2pixel(world2camera(p_w, T_c_w));
    }
} // namespace cuislam
