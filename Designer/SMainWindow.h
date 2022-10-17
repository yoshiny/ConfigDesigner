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
    void TryOpenWorkspaceFromArguments();
    void LoadWorkspace();

private slots:
    void on_action_about_Qt_triggered();
    void on_action_exit_triggered();

private:
    Ui::SMainWindowClass ui;
};
