#include "SProperty.h"

#include "SValue.h"
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

void SProperty::ClearDirty() {
	prop_manager_->ClearBackValue(this);
}

