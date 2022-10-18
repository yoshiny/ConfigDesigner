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

	QChar sep_slice_{QChar(0x00A6)};	// 片分割：¦
	QChar sep_section_{QChar(0x00A7)};	// 节分割：§
	QChar sep_fragment_{QChar(0x00B6)};	// 段分割：¶

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
	QChar GetSepSlice() const { return settings_.sep_slice_; }
	QChar GetSepSection() const { return settings_.sep_section_; }
	QChar GetSepFragment() const { return settings_.sep_fragment_; }

	void SetupSettings(const SWorkspaceSettings& settings);

private:
	SWorkspaceSettings settings_;
};

