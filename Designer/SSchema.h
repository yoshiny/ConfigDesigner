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
	QString GetName() const { return name_->GetValue().toString(); }
	QString GetTitle() const { return title_->GetValue().toString(); }
	QString GetDesc() const { return desc_->GetValue().toString(); }

	const QList<SField*>& GetFields() const { return field_list_; }

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

