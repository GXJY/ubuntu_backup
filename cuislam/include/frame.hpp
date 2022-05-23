# ifndef FRAME_HPP
# define FRAME_HPP

# include "common_include.hpp"
# include "feature.hpp"
# include "mappoint.hpp"
# include "camera.hpp"

namespace cuislam {
    class Frame {
        public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
        typedef std::shared_ptr<Frame> Ptr;
        Frame() = default;

        SE3 Pose() {return pose_;}

        void SetPose(const SE3 &pose) {pose_ = pose;}
        void SetImage(cv::Mat &img) {img_ = img;}
        cv::Mat GetImage() {return img_;}

        void SetKeyPointAndDescriptor(std::shared_ptr<Frame> frame, const std::vector<cv::KeyPoint> &KeyPoint, const cv::Mat &descriptor);

        void GetKeyPoint(std::vector<cv::KeyPoint> &vKeyPoint);

        void GetKeyPointPt(std::vector<cv::Point2f> &vPoint2f);
        
        void GetNotMapPointPoint(std::vector<cv::Point2f> &vPoint2f, cv::Mat &descriptor);

        int GetNUmberKeyPoint();

        void SetFeature(std::shared_ptr<Feature> pfeature);

        void GetFeatures(std::vector<std::shared_ptr<Feature>> &feature);

        std::vector<std::shared_ptr<Feature>> GetFeatures() const;

        void GetMapPointMatches(std::vector<std::shared_ptr<MapPoint>> &vMapPoint);

        void GetMatchKeyPoint(std::vector<cv::Point2f> &vPoint2f);

        static std::shared_ptr<Frame> CreateFrame();

    public:
        long int id_;
        long keyframe_id;

    private:
        SE3 pose_;
        cv::Mat img_;

        std::vector<std::shared_ptr<Feature>> features_;
        
        int numkeypoints_ = 0;


    };
}


# endif