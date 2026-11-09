#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <opencv2/videoio.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    cv::VideoCapture cap(0, cv::CAP_DSHOW);
    if (cap.isOpened()) {
        cv::Mat frame;
        cap >> frame;
        qDebug() << "Camera:" << frame.cols << "x" << frame.rows;
    }
    else {
        qDebug() << "Not camera :(";
    }

    QLabel ventana("Face Tracking System");
    ventana.resize(640, 480);
    ventana.show();

    return app.exec();
}