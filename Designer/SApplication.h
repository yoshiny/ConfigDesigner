#pragma once
#include <QApplication.h>
class SApplication : public QApplication {
	Q_OBJECT

public:
	SApplication(int &argc, char **argv);
	~SApplication();
private:

};

inline SApplication *SApp() {
	return static_cast<SApplication *>(QCoreApplication::instance());
}
