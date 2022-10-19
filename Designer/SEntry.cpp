#include "SEntry.h"

#include "SSheet.h"
#include "SPropertyManager.h"

SEntry::SEntry(SSheet * sheet)
    : sheet_(sheet)
{}

SEntry::~SEntry() {
	auto &prop_manager = sheet_->GetPropertyManager();
	for (auto it = properties_.constBegin(); it != properties_.constEnd(); ++it) {
		prop_manager.RecoverProperty(it.value());
	}
	properties_.clear();
}

SProperty * SEntry::GetProperty(SField * field) {
	return properties_.value(field, nullptr);
}

SProperty * SEntry::GetProperty(QString field) {
	return GetProperty(sheet_->GetField(field));
}

void SEntry::SetProperty(SField * field, SProperty * prop) {
	if (auto cur = properties_.value(field, nullptr)) {
		sheet_->GetPropertyManager().RecoverProperty(cur);
	}
	properties_.insert(field, prop);
}
