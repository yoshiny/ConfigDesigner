#include "SSchema.h"

#include <QUuid>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "SField.h"
#include "SValue.h"

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

		auto roles = {SProperty::kNameRole
					 ,SProperty::kTitleRole
					 ,SProperty::kGroupRole
					 ,SProperty::kReadOnlyRole
					 ,SProperty::kUniqueRole
					 ,SProperty::kDescRole
					 ,SProperty::kTypeRole
					 ,SProperty::kDefaultRole
					 ,SProperty::kEnableCondRole
					 ,SProperty::kConstraintRole
		};

		for (auto role : roles) {
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
