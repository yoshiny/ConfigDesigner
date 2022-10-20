#pragma once

#include <QString>
#include <QList>

#include "SPropertyManager.h"

class SField;

class SSchema {
public:
	SSchema(QString file_path);
	~SSchema();

public:
	QString GetGuid() const;
	QString GetName() const;
	QString GetTitle() const;
	QString GetDesc() const;

	const QList<SField*>& GetFields() const { return field_list_; }
	SPropertyManager &GetPropertyManager() { return property_manager_; }

public:
	bool Load();
	bool Save();

private:
	const QString file_path_;
	mutable QString guid_;
	SProperty *name_;
	SProperty *title_;
	SProperty *desc_;

	QList<SField *>field_list_;
	SPropertyManager property_manager_;
};

