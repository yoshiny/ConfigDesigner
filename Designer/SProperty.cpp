#include "SProperty.h"

#include "SConstraint.h"
#include "SPropertyManager.h"
#include "SApplication.h"

SProperty::SProperty(SPropertyManager *prop_manager, ERole role)
	: prop_manager_(prop_manager)
	, role_(role)
{}

bool SProperty::ChangeValue(QVariant value) {
	return false;
}

bool SProperty::IsDirty() const {
	return prop_manager_->GetBackValue(const_cast<SProperty*>(this)).isValid();
}

QString SProperty::GetStringValue() const {
	return QVariant2QString(value_);
}

QJsonValue SProperty::GetJsonValue() const {
	return QVariant2QJsonValue(value_);
}

void SProperty::ClearDirty() {
	prop_manager_->ClearBackValue(this);
}

