#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SMainWindow.h"

class SMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SMainWindow(QWidget *parent = nullptr);
    ~SMainWindow();

private:
    Ui::SMainWindowClass ui;
};