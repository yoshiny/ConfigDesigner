#include "SMainWindow.h"

#include <QTimer>
#include <QFileInfo>
#include <QDebug>

#include "SApplication.h"

SMainWindow::SMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // 尝试从命令行参数中打开工作区
    QTimer::singleShot(0, this, &SMainWindow::TryOpenWorkspaceFromArguments);
}

SMainWindow::~SMainWindow()
{}

void SMainWindow::TryOpenWorkspaceFromArguments() {
    // 确保主窗体完全显示
    SApp()->processEvents(QEventLoop::ExcludeUserInputEvents);

    QStringList arguments = SApp()->GetArguments();
    QString workspace_file = arguments.value(0);
    
    if (QFileInfo fileInfo(workspace_file); fileInfo.exists()) {
        bool suc = SApp()->OpenWorkspace(fileInfo.absoluteFilePath());
        qDebug() << "open result:" << suc;
        if (suc) {
            setWindowTitle(SApp()->GetWorkspace().GetName());
            LoadWorkspace();
        }
    }
}

void SMainWindow::LoadWorkspace() {
    SApp()->processEvents(QEventLoop::ExcludeUserInputEvents);

}

void SMainWindow::on_action_about_Qt_triggered() {
    SApp()->aboutQt();
}

void SMainWindow::on_action_exit_triggered() {
    SApp()->closeAllWindows();
}
