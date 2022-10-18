#pragma once

#include <QList>
#include <QHash>
#include <QSet>
#include <QString>

class SConfig;
class SSchema;

class SConfigManager {
public:
	SConfigManager();
	~SConfigManager();

public:
	void Clear();
	SConfig *LoadConfig(QString file_path);
	SConfig *NewConfig(QString file_path);
	void AddConfig(SConfig *cfg);

private:
	QList<SConfig *> config_list_;
	QHash<QString, SConfig *>id2config_;

	QList<SSchema *> schema_list_;
	QHash<QString, SSchema *>id2schema_;
};

