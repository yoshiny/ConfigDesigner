#include "SPropertyManager.h"

SPropertyManager::SPropertyManager(QObject *parent)
	: QObject(parent)
{}

SPropertyManager::~SPropertyManager() {
	qDeleteAll(properties_);
	properties_.clear();
	back_values_.clear();
}

SProperty * SPropertyManager::AssignProperty(SProperty::ERole prop_role) {
	SProperty *prop = new SProperty(this, prop_role);
	properties_.insert(prop);
	return prop;
}

void SPropertyManager::RecoverProperty(SProperty * prop) {
	ClearBackValue(prop);
	if (properties_.remove(prop)) {
		delete prop;
	}
}

void SPropertyManager::RecoverProperty(std::initializer_list<SProperty*> list) {
	for (auto it : list) {
		RecoverProperty(it);
	}
}

void SPropertyManager::SetBackValue(SProperty * prop, QVariant value, bool force) {
	if (force || !back_values_.contains(prop)) {
		back_values_.insert(prop, value);
		emit OnPropertyBackValueChanged(prop);
	}
}

QVariant SPropertyManager::GetBackValue(SProperty * prop) {
	return back_values_.value(prop);
}

void SPropertyManager::ClearBackValue(SProperty * prop) {
	back_values_.remove(prop);
	emit OnPropertyBackValueChanged(prop);
}

void SPropertyManager::ClearBackValues() {
	back_values_.clear();
	emit OnPropertyBackValueChanged(nullptr);
}

