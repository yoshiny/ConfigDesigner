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
    QTimer::singleShot(0, this, &SMainWindow::tryOpenWorkspaceFromArguments);
}

SMainWindow::~SMainWindow()
{}

void SMainWindow::tryOpenWorkspaceFromArguments() {
    QStringList arguments = SApp()->GetArguments();
    QString workspace_file = arguments.value(0);
    
    if (QFileInfo fileInfo(workspace_file); fileInfo.exists()) {
        bool suc = SApp()->GetWorkspace().Open(fileInfo.absoluteFilePath());
        qDebug() << "open result:" << suc;
        if (suc) {
            setWindowTitle(SApp()->GetWorkspace().GetName());
        }
    }
}
