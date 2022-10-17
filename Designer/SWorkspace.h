#pragma once

#include <QString>
#include <QList>

struct SWorkspaceSettings
{
	QString setting_file_;
	QString name_;
	QString config_folder_;
	QString schema_folder_;
	QString script_folder_;
	QString schema_suffix_{QLatin1String(".json")};
	QString config_suffix_{QLatin1String(".xml")};

	bool IsValid() const { return setting_file_.isEmpty() == false; }
	
	static SWorkspaceSettings Parse(QString setting_file);
};

class SWorkspace {
public:
	SWorkspace();
	~SWorkspace();

public:
	bool IsValid() const { return settings_.IsValid(); }
	QString GetName() const { return settings_.name_; }

	void SetupSettings(const SWorkspaceSettings& settings);

private:
	SWorkspaceSettings settings_;
};

