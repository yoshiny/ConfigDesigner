#pragma once

#include <QHash>
#include <QString>

#include "SProperty.h"

class SSheet;
class SPropertyManager;

class SField {
public:
	SField(SSheet *sheet);
	~SField();

public:
	SPropertyManager &GetPropertyManager() const;
	void AddProperty(SProperty *prop);

	QString GetName() const {return GetPropertyValue(SProperty::ERole::kName).toString();}
	QString GetTitle() const {return GetPropertyValue(SProperty::ERole::kTitle).toString();}
	QString GetDesc() const {return GetPropertyValue(SProperty::ERole::kDesc).toString();}
	QString GetGroup() const {return GetPropertyValue(SProperty::ERole::kGroup).toString();}
	QString GetDefault() const {return GetPropertyValue(SProperty::ERole::kDefault).toString();}
	QString GetEnableCond() const {return GetPropertyValue(SProperty::ERole::kEnableCond).toString();}
	SProperty::EMode GetMode() const;
	bool IsUnique() const { return GetPropertyValue(SProperty::ERole::kUnique).toBool(); }
	bool IsReadOnly() const { return GetPropertyValue(SProperty::ERole::kReadOnly).toBool(); }
	QVariant GetConstraint() const { return GetPropertyValue(SProperty::ERole::kConstraint); }

	SProperty *GetProperty(SProperty::ERole role) const;
	QVariant GetPropertyValue(SProperty::ERole role) const;
	bool ChangePropertyValue(SProperty::ERole role, QVariant value);

	bool IsPropertyDirty(SProperty::ERole role) const;

private:
	SSheet *sheet_;

	QHash<SProperty::ERole, SProperty*> properties_;
};

