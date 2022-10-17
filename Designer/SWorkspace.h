#pragma once

#include <QString>
#include <QList>

class SWorkspace {
public:
	SWorkspace();
	~SWorkspace();

public:
	bool Open(QString file_path);
	bool IsValid() const { return valid_; }
	QString GetName() const { return name_; }

private:
	bool valid_{false};
	QString file_path_;
	QString name_;
	QList<QString> config_folder_list_;
	QList<QString> schema_folder_list_;
};

