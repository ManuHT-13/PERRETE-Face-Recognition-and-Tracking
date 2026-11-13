#pragma once

#include <iostream> 
#include <thread>
#include <atomic>
#include <mutex>

#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>


class CameraCapture {

private:

    std::thread running_thread;
    std::atomic<bool> running; 
    std::mutex mut;

    cv::VideoCapture cap;
    cv::Mat last_frame;

    void capture();

public:

    CameraCapture(): running(false) {}
    ~CameraCapture();

    CameraCapture(const CameraCapture&) = delete;
    CameraCapture& operator=(const CameraCapture&) = delete;

    void start();
    void stop();

    bool getLastFrame(cv::Mat& out);

};


