#include "SWorkspace.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

SWorkspace::SWorkspace() {}

SWorkspace::~SWorkspace() {}

bool SWorkspace::Open(QString file_path) {
	QFile json_file(file_path);
	if (!json_file.open(QIODevice::ReadOnly)) {
		qWarning() << "Couldn't open workspace file:" << file_path;
		return false;
	}

	QByteArray json_data = json_file.readAll();
	QJsonParseError parse_error;
	QJsonDocument json_doc = QJsonDocument::fromJson(json_data, &parse_error);
	if (json_doc.isNull()) {
		qWarning("Workspace file %s parse error", file_path);
		qWarning() << parse_error.errorString();
		return false;
	}

	QJsonObject jo = json_doc.object();
	if (jo.isEmpty()) {
		qWarning("Workspace file %s format error", file_path);
		return false;
	}

	// 读取工作区数据
	QFileInfo file_info(file_path);
	QString file_folder = file_info.absolutePath();

	QString name;
	if (QJsonValue jv = jo.value(QLatin1String("name")); jv.isString()) {
		name = jv.toString();
	}
	if (name.isEmpty()) {
		name = file_path;
	}

	QStringList schema_folders;
	if (QJsonValue jv = jo.value(QLatin1String("schemas")); jv.isArray()) {
		for (auto v : jv.toArray()) {
			QString schema_path = v.toString();
			if (QDir::isRelativePath(schema_path)) {
				schema_path.prepend("/").prepend(file_folder);
			}
			if (QDir schema_dir(schema_path); schema_dir.exists()) {
				schema_folders << schema_dir.absolutePath();
			}
		}
	}

	QStringList config_folders;
	if (QJsonValue jv = jo.value(QLatin1String("configs")); jv.isArray()) {
		for (auto v : jv.toArray()) {
			QString config_path = v.toString();
			if (QDir::isRelativePath(config_path)) {
				config_path.prepend("/").prepend(file_folder);
			}
			if (QDir config_dir(config_path); config_dir.exists()) {
				config_folders << config_dir.absolutePath();
			}
		}
	}

	// 销毁原有数据
	if (IsValid()) {
	}

	// 更新数据
	valid_ = true;
	file_path_ = file_path;
	name_ = name;
	schema_folder_list_ = schema_folders;
	config_folder_list_ = config_folders;

	return true;
}
