# include "frame.hpp"

namespace cuislam {
    std::shared_ptr<Frame> Frame::CreateFrame() {
        static long factory_id = 0;
        std::shared_ptr<Frame> new_frame(new Frame);
        new_frame->id_ = factory_id++;
        return new_frame;
    }

    void Frame::GetMapPointMatches(std::vector<std::shared_ptr<MapPoint>> &vMapPoint) {
        for(auto mp : features_) {
            if(mp->GetMapPoint()) {
                vMapPoint.push_back(mp->GetMapPoint());
            }
        }
    }

    void Frame::GetMatchKeyPoint(std::vector<cv::Point2f> &vPoint2f) {
        for(size_t start = 0, end = features_.size(); start != end; start++) {
            if(features_[start]->GetMapPoint()) {
                vPoint2f.push_back(features_[start]->GetKeyPoint().pt);
            }
        }
    }

    void Frame::GetFeatures(std::vector<std::shared_ptr<Feature>> &features) {
        features_ = features;
    }

    std::vector<std::shared_ptr<Feature>> Frame::GetFeatures() const {
        std::vector<std::shared_ptr<Feature>> features;
        features = features_;
        return features;
    }

    void Frame::SetFeature(std::shared_ptr<Feature> pfeature) {
        features_.push_back(pfeature);
    }

    void Frame::SetKeyPointAndDescriptor(std::shared_ptr<Frame> frame, const std::vector<cv::KeyPoint> &vKeyPoint, const cv::Mat &descriptor) {
        numkeypoints_ = vKeyPoint.size();
        features_.clear();
        for(int i = 0; i != numkeypoints_; i++) {
            std::shared_ptr<Feature> feature = std::make_shared<Feature>(frame, vKeyPoint[i], descriptor.row(i));
            features_.push_back(feature);
        }
    }

    void Frame::GetKeyPoint(std::vector<cv::KeyPoint> &vKeyPoint) {
        for(auto a:features_) {
            vKeyPoint.push_back(a->GetKeyPoint());
        }
    }

    void Frame::GetKeyPointPt(std::vector<cv::Point2f> &vPoint2f) {
        for(auto a:features_) {
            vPoint2f.push_back(a->GetKeyPoint().pt);
        }
    }

    void Frame::GetNotMapPointPoint(std::vector<cv::Point2f> &vPoint2f, cv::Mat &descriptor) {
        for(auto a:features_) {
            if(a->isMatchPoint()) {
                continue;
            }
            vPoint2f.push_back(a->GetFixelXY());
            descriptor.push_back(a->GetDescriptor());
        }
    }

    int Frame::GetNumberKeyPoint() {
        return numkeypoints_;
    }
}