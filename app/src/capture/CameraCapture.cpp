#include <iostream> 
#include <thread>
#include <atomic>
#include <mutex>
#include <stdexcept>

#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

#include "capture/CameraCapture.h"


CameraCapture::~CameraCapture() {
    stop();
}

void CameraCapture::capture() {

    cv::Mat frame;

    while (running_) {

        cap_ >> frame;

        if (frame.empty())
            continue;

        std::lock_guard<std::mutex> lock(mut_);
        last_frame_ = frame.clone();

    }

}

void CameraCapture::start() {

    if (running_)
        return;

    cap_.open(0);

    if (!cap_.isOpened())
        throw std::runtime_error("Couldn't open the camera");

    running_ = true;
    running_thread_ = std::thread(&CameraCapture::capture, this);

}

void CameraCapture::stop() {
    
    running_ = false;

    if (running_thread_.joinable())
        running_thread_.join();

    cap_.release();

}

bool CameraCapture::getLastFrame(cv::Mat& out) {

    std::lock_guard<std::mutex> lock(mut_);

    if (last_frame_.empty())
        return false;
    else {
        out = last_frame_.clone();
        return true;
    }

} 