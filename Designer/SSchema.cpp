#include "SSchema.h"

#include <QUuid>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "SField.h"

SSchema::SSchema(QString file_path)
	: file_path_(file_path)
{
	name_ = property_manager_.AssignProperty(SProperty::ERole::kValue);
	title_ = property_manager_.AssignProperty(SProperty::ERole::kValue);
	desc_ = property_manager_.AssignProperty(SProperty::ERole::kValue);
}

SSchema::~SSchema() {
	property_manager_.RecoverProperty({name_, title_, desc_});
	qDeleteAll(field_list_);
	field_list_.clear();
}

QString SSchema::GetGuid() const {
	if (guid_.isEmpty()) {
		guid_ = QUuid::createUuid().toString(QUuid::Id128);
	}
	return guid_;
}

bool SSchema::Load() {
	return false;
}

bool SSchema::Save() {
	QFile file(file_path_);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		// TODO log error
		return false;
	}

	QJsonObject jo_root;
	jo_root[QLatin1String("Guid")] = GetGuid();
	jo_root[QLatin1String("Name")] = GetName();
	jo_root[QLatin1String("Title")] = GetTitle();
	jo_root[QLatin1String("Desc")] = GetDesc();

	QJsonArray ja_fields;
	for (auto field : field_list_) {
		QJsonObject jo_field;

		jo_field[QLatin1String("Name")] = field->GetName();
		jo_field[QLatin1String("Title")] = field->GetTitle();
		jo_field[QLatin1String("Group")] = field->GetGroup();
		jo_field[QLatin1String("ReadOnly")] = field->IsReadOnly();
		jo_field[QLatin1String("Unique")] = field->IsUnique();
		jo_field[QLatin1String("Desc")] = field->GetDesc();
		jo_field[QLatin1String("Mode")] = SProperty::ModeName(field->GetMode());
		jo_field[QLatin1String("Default")] = field->GetDefault();
		jo_field[QLatin1String("EnableCond")] = field->GetEnableCond();
		jo_field[QLatin1String("Constraint")] = field->GetProperty(SProperty::ERole::kConstraint)->GetValueText();

		ja_fields << jo_field;
	}

	jo_root[QLatin1String("Fields")] = ja_fields;

	QJsonDocument jd(jo_root);
	file.write(jd.toJson(QJsonDocument::Indented));
	bool suc = file.flush();
	file.close();
	return suc;
}
