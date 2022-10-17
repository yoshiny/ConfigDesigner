#pragma once
#include <QApplication.h>

#include "SWorkspace.h"

class SApplication : public QApplication {
	Q_OBJECT

public:
	SApplication(int &argc, char **argv);
	~SApplication();

public:
	QStringList GetArguments();
	SWorkspace &GetWorkspace() { return workspace_; }

private:
	static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
	SWorkspace workspace_;
};

inline SApplication *SApp() {
	return static_cast<SApplication *>(QCoreApplication::instance());
}
