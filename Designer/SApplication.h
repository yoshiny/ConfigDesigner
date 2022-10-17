#pragma once
#include <QApplication.h>

class SApplication : public QApplication {
	Q_OBJECT

public:
	SApplication(int &argc, char **argv);
	~SApplication();

private:
	static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

inline SApplication *SApp() {
	return static_cast<SApplication *>(QCoreApplication::instance());
}
