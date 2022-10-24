#include "SProperty.h"

#include "SConstraint.h"
#include "SPropertyManager.h"
#include "SApplication.h"

SProperty::SProperty(SPropertyManager *prop_manager, ERole prop_role, EType prop_type)
	: prop_manager_(prop_manager)
	, role_(prop_role)
	, type_(prop_type)
{}

bool SProperty::ChangeValue(QVariant value) {
	return false;
}

bool SProperty::IsDirty() const {
	return prop_manager_->GetBackValue(const_cast<SProperty*>(this)).isValid();
}

QString SProperty::GetStringValue() const {
	return value_.toString();
}

QJsonValue SProperty::GetJsonValue() const {
	return QJsonValue();
}

void SProperty::ClearDirty() {
	prop_manager_->ClearBackValue(this);
}

