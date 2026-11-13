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

    while (running) {

        cap >> frame;

        if (frame.empty())
            continue;

        std::lock_guard<std::mutex> lock(mut);
        last_frame = frame.clone();

    }

}

void CameraCapture::start() {

    if (running)
        return;

    cap.open(0);

    if (!cap.isOpened())
        throw std::runtime_error("Couldn't open the camera");

    running = true;
    running_thread = std::thread(&CameraCapture::capture, this);

}

void CameraCapture::stop() {
    
    running = false;

    if (running_thread.joinable())
        running_thread.join();

    cap.release();

}

bool CameraCapture::getLastFrame(cv::Mat& out) {

    std::lock_guard<std::mutex> lock(mut);

    if (last_frame.empty())
        return false;
    else {

        out = last_frame.clone();
        return true;

    }

} 