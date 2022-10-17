#include "SWorkspace.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

SWorkspaceSettings SWorkspaceSettings::Parse(QString setting_file) {
	SWorkspaceSettings settings;

	do
	{
		QFileInfo setting_file_info(setting_file);
		if (!setting_file_info.isFile()) {
			qWarning() << setting_file << "is neither exist or a file";
			break;
		}

		setting_file = setting_file_info.absoluteFilePath();

		QFile json_file(setting_file);
		if (!json_file.open(QIODevice::ReadOnly)) {
			qWarning() << "Couldn't open workspace file:" << setting_file;
			break;
		}

		QByteArray json_data = json_file.readAll();
		QJsonParseError parse_error;
		QJsonDocument json_doc = QJsonDocument::fromJson(json_data, &parse_error);
		if (json_doc.isNull()) {
			qWarning("Workspace file %s parse error", setting_file);
			qWarning() << parse_error.errorString();
			break;
		}

		QJsonObject jo = json_doc.object();
		if (jo.isEmpty()) {
			qWarning("Workspace file %s format error", setting_file);
			break;
		}

		// 工作区名称
		if (QJsonValue jv = jo.value(QLatin1String("name")); jv.isString()) {
			settings.name_ = jv.toString();
		}
		if (settings.name_.isEmpty()) {
			settings.name_ = setting_file;
		}

		// 相关后缀
		auto parse_suffix = [&jo](QString &suffix_setting, QLatin1String json_key) {
			if (QJsonValue jv = jo.value(json_key); jv.isString()) {
				if (QString suffix = jv.toString(); !suffix.isEmpty()) {
					suffix_setting = suffix;
					if (!suffix_setting.startsWith(QLatin1Char('.'))) {
						suffix_setting.prepend(QLatin1Char('.'));
					}
				}
			}
		};
		parse_suffix(settings.schema_suffix_, QLatin1String("schema_suffix"));
		parse_suffix(settings.config_suffix_, QLatin1String("config_suffix"));

		// 相关路径
		QString setting_file_folder = setting_file_info.absolutePath();
		auto parse_folder = [&jo, &setting_file_info](QString &folder_setting, QLatin1String json_key) {
			if (QJsonValue jv = jo.value(json_key); jv.isString()) {
				QString folder_path = jv.toString();
				if (QDir::isRelativePath(folder_path)) {
					folder_path.prepend(QLatin1Char('/')).prepend(setting_file_info.absolutePath());
				}
				if (QDir folder_dir(folder_path); folder_dir.exists()) {
					folder_setting = QDir::cleanPath(folder_dir.absolutePath());
				}
			}
		};
		parse_folder(settings.schema_folder_, QLatin1String("schema"));
		parse_folder(settings.config_folder_, QLatin1String("config"));
		parse_folder(settings.script_folder_, QLatin1String("script"));

		// 标记解析成功
		settings.setting_file_ = setting_file;
	} while (false);

	return settings;
}

SWorkspace::SWorkspace() {}

SWorkspace::~SWorkspace() {}

void SWorkspace::SetupSettings(const SWorkspaceSettings & settings) {
	// 释放旧数据
	if (settings_.IsValid()) {
	}

	// 更新设置
	settings_ = settings;
}



