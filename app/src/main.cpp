#include <iostream>
#include <stdexcept>

#include <QApplication>
#include <QLabel>
#include <QDebug>

#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "MainWindow.h"
#include "CameraCapture.h"


int main(int argc, char* argv[]) {

    CameraCapture camera_capture;

    try {

        camera_capture.start();
        cv::Mat frame;

        while (true) {

            if (camera_capture.getLastFrame(frame))
                cv::imshow("Camera Capture", frame);

            if (cv::waitKey(1) == 'q') break;

        }

        camera_capture.stop();
        cv::destroyAllWindows();


    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Camera: " << e.what() << '\n';
        return 1;
    }
    
    
    return 0;

}