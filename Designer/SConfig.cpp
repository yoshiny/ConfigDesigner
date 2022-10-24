#include "SConfig.h"

#include <QDebug>
#include <QUuid>


SConfig::SConfig(QString file_path, EType type)
	: type_(type)
	, file_path_(file_path)
{
	title_ = property_manager_.AssignProperty(SProperty::kValueRole, SProperty::kStringType);
	doc_link_ = property_manager_.AssignProperty(SProperty::kValueRole, SProperty::kStringType);
	tag_ = property_manager_.AssignProperty(SProperty::kValueRole, SProperty::kStringType);
	props_ = property_manager_.AssignProperty(SProperty::kValueRole, SProperty::kStringType);
	actions_ = property_manager_.AssignProperty(SProperty::kValueRole, SProperty::kStringType);
}

SConfig::~SConfig() {
	property_manager_.RecoverProperty({title_, doc_link_, tag_, props_, actions_});
	qDeleteAll(sheet_list_);
	sheet_list_.clear();
}

QString SConfig::GetGuid() const {
	if (guid_.isEmpty()) {
		guid_ = QUuid::createUuid().toString(QUuid::Id128);
	}
	return guid_;
}

QString SConfig::GetTitle() const {
	return title_->GetValue().toString();
}

void SConfig::SetTitle(QString title) {
	title_->ChangeValue(title);
}

QString SConfig::GetDocLink() const {
	return doc_link_->GetValue().toString();
}

void SConfig::SetDocLink(QString link) {
	doc_link_->ChangeValue(link);
}

QString SConfig::GetTag() const {
	return tag_->GetValue().toString();
}

void SConfig::SetTag(QString tag) {
	tag_->ChangeValue(tag);
}

QHash<QString, QVariant> SConfig::GetProps() const {
	return props_->GetValue().toHash();
}

void SConfig::SetProps(QHash<QString, QVariant> props) {
	props_->ChangeValue(props);
}

QStringList SConfig::GetActions() const {
	return actions_->GetValue().toStringList();
}

void SConfig::SetActions(QStringList actions) {
	actions_->ChangeValue(actions);
}

bool SNormalConfig::Load() {
	return false;
}

bool SNormalConfig::Save() {
	return false;
}
