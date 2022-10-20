#include "SSheet.h"

#include <QDebug>
#include <QUuid>

#include "SConfig.h"
#include "SField.h"
#include "SValue.h"

SSheet::SSheet(SConfig * config, EType type)
	: config_(config)
	, type_(type)
{
	auto &prop_manager = GetPropertyManager();
	name_ = prop_manager.AssignProperty(SProperty::kValueRole);
	title_ = prop_manager.AssignProperty(SProperty::kValueRole);
	index_ = prop_manager.AssignProperty(SProperty::kValueRole);
	props_ = prop_manager.AssignProperty(SProperty::kValueRole);
}

SSheet::~SSheet() {
	auto &prop_manager = GetPropertyManager();
	prop_manager.RecoverProperty({name_, title_, index_, props_});

	qDeleteAll(field_list_);
	field_list_.clear();

	qDeleteAll(entry_list_);
	entry_list_.clear();
}

SPropertyManager & SSheet::GetPropertyManager() {
	return config_->GetPropertyManager();
}

QString SSheet::GetGuid() const {
	if (guid_.isEmpty()) {
		guid_ = QUuid::createUuid().toString(QUuid::Id128);
	}
	return guid_;
}

QString SSheet::GetName() const {
	return name_->GetValue().toString();
}

void SSheet::SetName(QString name) {
	name_->ChangeValue(name);
}

QString SSheet::GetTitle() const {
	return title_->GetValue().toString();
}

void SSheet::SetTitle(QString title) {
	title_->ChangeValue(title);
}

int SSheet::GetIndex() const {
	return index_->GetValue().toString().toInt();
}

void SSheet::SetIndex(int index) {
	index_->ChangeValue(index);
}

QHash<QString, QVariant> SSheet::GetProps() const {
	return props_->GetValue().toHash();
}

void SSheet::SetProps(QHash<QString, QVariant> props) {
	props_->ChangeValue(props);
}

SField * SSheet::GetField(QString field) const {
	for (auto it = field_list_.begin(); it != field_list_.end(); ++it) {
		if ((*it)->GetName() == field) {
			return *it;
		}
	}
	return nullptr;
}
