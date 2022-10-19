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

QString SProperty::GetValueText() const {
	int vt = value_.userType();
	switch (vt) {
	case QMetaType::Bool:
		return SBooleanBox::ToString(value_.toBool());
	case QMetaType::QStringList:
	{
		QStringList sl = value_.toStringList();
		return sl.join(SApp()->GetWorkspace().GetSepSlice());
	}
	default:
		break;
	}
	return value_.toString();
}

void SProperty::ClearDirty() {
	prop_manager_->ClearBackValue(this);
}

