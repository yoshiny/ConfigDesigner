#include "SSchema.h"

#include <QUuid>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "SField.h"

SSchema::SSchema(QString file_path)
	: file_path_(file_path)
{
	name_ = property_manager_.AssignProperty(SProperty::kValueRole);
	title_ = property_manager_.AssignProperty(SProperty::kValueRole);
	desc_ = property_manager_.AssignProperty(SProperty::kValueRole);
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

QString SSchema::GetName() const {
	return name_->GetStringValue();
}

QString SSchema::GetTitle() const {
	return title_->GetStringValue();
}

QString SSchema::GetDesc() const {
	return desc_->GetStringValue();
}

bool SSchema::Load() {
	QFile file(file_path_);
	if (!file.open(QIODevice::ReadOnly)) {
		// TODO log error
		return false;
	}

	QByteArray json_data = file.readAll();
	QJsonParseError parse_error;
	QJsonDocument json_doc = QJsonDocument::fromJson(json_data, &parse_error);
	if (json_doc.isNull()) {
		qCritical("%s parse error:", file_path_);
		qCritical() << parse_error.errorString();
		return false;
	}

	QJsonObject jo_root = json_doc.object();
	if (jo_root.isEmpty()) {
		qCritical("%s content error", file_path_);
		return false;
	}

	guid_ = jo_root[QLatin1String("Guid")].toString();
	name_->SetValue(jo_root[QLatin1String("Name")].toString());
	title_->SetValue(jo_root[QLatin1String("Title")].toString());
	desc_->SetValue(jo_root[QLatin1String("Desc")].toString());

	QJsonArray ja_fields = jo_root[QLatin1String("Fields")].toArray();
	for (auto it : ja_fields) {
		QJsonObject jo_field = it.toObject();
		auto field = new SField(this);
		for (auto role : SField::GetFieldPropertyRoles()) {
			auto prop = field->GetProperty(role);
			prop->SetValue(jo_field[SProperty::RoleName(role)].toVariant());
		}

		field_list_ << field;
	}

	property_manager_.ClearBackValues();
	return true;
}

bool SSchema::Save() {
	QFile file(file_path_);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		// TODO log error
		return false;
	}

	QJsonObject jo_root;
	jo_root[QLatin1String("Guid")] = GetGuid();
	jo_root[QLatin1String("Name")] = name_->GetJsonValue();
	jo_root[QLatin1String("Title")] = title_->GetJsonValue();
	jo_root[QLatin1String("Desc")] = desc_->GetJsonValue();

	QJsonArray ja_fields;
	for (auto field : field_list_) {
		QJsonObject jo_field;

		for (auto role : SField::GetFieldPropertyRoles()) {
			jo_field[SProperty::RoleName(role)] = field->GetPropertyJsonValue(role);
		}

		ja_fields << jo_field;
	}

	jo_root[QLatin1String("Fields")] = ja_fields;

	QJsonDocument jd(jo_root);
	file.write(jd.toJson(QJsonDocument::Indented));
	bool suc = file.flush();
	file.close();
	return suc;
}
