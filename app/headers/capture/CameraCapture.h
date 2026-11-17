#pragma once

#include <iostream> 
#include <thread>
#include <atomic>
#include <mutex>

#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>


class CameraCapture {

public:

    CameraCapture(): running_(false) {}
    ~CameraCapture();

    CameraCapture(const CameraCapture&) = delete;
    CameraCapture& operator=(const CameraCapture&) = delete;

    void start();
    void stop();

    bool getLastFrame(cv::Mat& out);

private:

    std::thread running_thread_;
    std::atomic<bool> running_;
    std::mutex mut_;

    cv::VideoCapture cap_;
    cv::Mat last_frame_;

    void capture();

};


