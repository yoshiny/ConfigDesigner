#pragma once

#include <QString>
#include <QHash>
#include <QList>
#include <QFileInfo>

#include "SPropertyManager.h"

class SProperty;
class SSheet;

class SConfig {
public:
	enum class EType {
		kNormal = 0,
		kProxy = 1,
	};

public:
	virtual ~SConfig();

public:
	virtual bool Load() = 0;
	virtual bool Save() = 0;

public:
	EType GetType() const { return type_; }
	QString GetName() const { return QFileInfo(file_path_).fileName(); }
	QString GetGuid() const;

	QString GetTitle() const;
	void SetTitle(QString title);

	QString GetDocLink() const;
	void SetDocLink(QString link);

	QString GetTag() const;
	void SetTag(QString tag);

	QHash<QString, QVariant> GetProps() const;
	void SetProps(QHash<QString, QVariant> props);

	QStringList GetActions() const;
	void SetActions(QStringList actions);

	SPropertyManager& GetPropertyManager() { return property_manager_; }
protected:
	SConfig(QString file_path, EType type);

private:
	const EType type_;
	const QString file_path_;
	mutable QString guid_;

	SProperty *title_{nullptr};
	SProperty *doc_link_{nullptr};
	SProperty *tag_{nullptr};
	SProperty *props_{nullptr};
	SProperty *actions_{nullptr};
	
	QList<SSheet *> sheet_list_;
	SPropertyManager property_manager_;
};

class SNormalConfig : public SConfig {
public:
	SNormalConfig(QString file_path)
		: SConfig(file_path, EType::kNormal)
	{}

	~SNormalConfig() {}

public:
	virtual bool Load() override;
	virtual bool Save() override;
};

