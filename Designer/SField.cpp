#include "SField.h"

#include "SPropertyManager.h"
#include "SSchema.h"

SField::SField(SSchema *schema)
	: schema_(schema)
{
	auto &prop_manager = GetPropertyManager();
	for (auto role : GetFieldPropertyRoles()) {
		AddProperty(prop_manager.AssignProperty(role, SProperty::kStringType));
	}
}

SField::~SField() {
	auto &prop_manager = GetPropertyManager();
	for (auto it = properties_.constBegin(); it != properties_.constEnd(); ++it) {
		prop_manager.RecoverProperty(it.value());
	}
	properties_.clear();
}

const QList<SProperty::ERole>& SField::GetFieldPropertyRoles() {
	static QList<SProperty::ERole> roles = {
					  SProperty::kNameRole
					, SProperty::kTitleRole
					, SProperty::kGroupRole
					, SProperty::kDescRole
					, SProperty::kReadOnlyRole
					, SProperty::kUniqueRole
					, SProperty::kTypeRole
					, SProperty::kDefaultRole
					, SProperty::kConstraintRole
					, SProperty::kEnableCondRole
	};
	return roles;
}

SPropertyManager & SField::GetPropertyManager() const {
	return schema_->GetPropertyManager();
}

SProperty * SField::GetProperty(SProperty::ERole role) const {
	return properties_.value(role, nullptr);
}

SProperty::EType SField::GetPropertyType(SProperty::ERole role) const {
	auto prop = properties_.value(role, nullptr);
	return prop ? prop->GetType() : SProperty::kStringType;
}

QVariant SField::GetPropertyValue(SProperty::ERole role) const {
	auto prop = properties_.value(role, nullptr);
	return prop ? prop->GetValue() : QVariant();
}

QString SField::GetPropertyDisplayValue(SProperty::ERole role) const {
	auto prop = properties_.value(role, nullptr);
	return prop ? prop->GetDisplayValue() : QString();
}

QString SField::GetPropertyStringValue(SProperty::ERole role) const {
	auto prop = properties_.value(role, nullptr);
	return prop ? prop->GetDisplayValue() : QString();
}

QJsonValue SField::GetPropertyJsonValue(SProperty::ERole role) const {
	auto prop = properties_.value(role, nullptr);
	return prop ? prop->GetJsonValue() : QString();
}

bool SField::ChangePropertyValue(SProperty::ERole role, QVariant value) {
	if (auto prop = properties_.value(role, nullptr)) {
		if (prop->ChangeValue(value)) {
			return true;
		}
	}
	return false;
}

bool SField::IsPropertyDirty(SProperty::ERole role) const {
	if (auto prop = properties_.value(role, nullptr)) {
		return prop->IsDirty();
	}
	return false;
}

void SField::AddProperty(SProperty * prop) {
	properties_.insert(prop->GetRole(), prop);
}
