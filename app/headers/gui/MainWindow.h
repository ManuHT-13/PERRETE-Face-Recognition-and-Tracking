#pragma once

#include <QMainWindow>

class MainWindow: public QMainWindow {

    Q_OBJECT;

private:

    void setupUI();

public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

};