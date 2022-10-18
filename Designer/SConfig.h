#pragma once

#include <QString>
#include <QList>
#include <QFileInfo>

class SSheet;

class SConfig {
public:
	enum class EConfigType {
		kNormal = 0,
		kProxy = 1,
	};

public:
	virtual ~SConfig();

public:
	virtual bool Load() = 0;
	virtual bool Save() = 0;

public:
	EConfigType GetType() const { return type_; }
	QString GetTitle() const { return title_; }
	QString GetName() const { return QFileInfo(file_path_).fileName(); }

protected:
	SConfig(QString file_path, EConfigType type);

private:
	const EConfigType type_;
	const QString file_path_;
	QString title_;
	QList<SSheet *> sheet_list_;
};

class SNormalConfig : public SConfig {
public:
	SNormalConfig(QString file_path)
		: SConfig(file_path, SConfig::EConfigType::kNormal)
	{}

	~SNormalConfig() {}

public:
	virtual bool Load() override;
	virtual bool Save() override;
};

