#include "SProperty.h"

bool SProperty::ChangeValue(QVariant value) {
	return false;
}

bool SProperty::IsDirty() const {
	return false;
}

void SProperty::ClearDirty() const {}
