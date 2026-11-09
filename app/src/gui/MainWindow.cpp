#include "MainWindow.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

// First initialize base class QMainWindow
MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    setupUI();
}

MainWindow::~MainWindow() = default;

MainWindow::setupUI() {

    setWindowTitle("PERRETE Face Tracker");
    resize(1280, 720);

    auto* central_widget = new QWidget(this);
    auto* layout = new QVBoxLayout(central_widget);

    auto* label = new QLabel("PERRETE Face Tracking", central_widget);
    auto* button = new QPushButton("Start Camera", central_widget);

    layout->addWidget(label);
    layout->addWidget(button);

    setCentralWidget(central_widget);

}