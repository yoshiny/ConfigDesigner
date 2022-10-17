#include "SApplication.h"

#include <qt_windows.h>
#include <dbghelp.h>

#include <QMutex>
#include <QDebug>
#include <QDateTime>
#include <QFile>

SApplication::SApplication(int & argc, char ** argv)
	: QApplication(argc, argv)
{
	// 安装日志过滤器
	qInstallMessageHandler(&SApplication::messageHandler);

	// 增大可打开文件句柄数量
	if (_getmaxstdio() < 1024) {
		_setmaxstdio(4096);
	}

	qDebug() << "launched";
}

SApplication::~SApplication() {
}

void SApplication::messageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg) {
	QString prefix = QLatin1String("Unknown");
	switch (type) {
	case QtDebugMsg:
		prefix = QLatin1String("Debug");
		break;
	case QtInfoMsg:
		prefix = QLatin1String("Info");
		break;
	case QtWarningMsg:
		prefix = QLatin1String("Warn");
		break;
	case QtCriticalMsg:
		prefix = QLatin1String("Critical");
		break;
	case QtFatalMsg:
		prefix = QLatin1String("Fatal");
		break;
	default:
		break;
	}

	QString log_message = QString("[%1][%2][%3:%4:%5]\n%6")
		.arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
		.arg(prefix)
		.arg(context.file ? context.file : "")
		.arg(context.function ? context.function : "")
		.arg(context.line)
		.arg(msg);

	QFile log_file("log.log");

	static QMutex mutex;
	QMutexLocker _guard(&mutex);

	log_file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream writer(&log_file);
	writer << log_message << '\n';
	log_file.flush();
	log_file.close();
}
