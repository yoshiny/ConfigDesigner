#pragma once

#include <QHash>
#include <QString>
#include <QJsonValue>

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

	QString GetName() const {return GetPropertyStringValue(SProperty::kNameRole);}
	QString GetTitle() const { return GetPropertyStringValue(SProperty::kTitleRole); }
	QString GetDesc() const { return GetPropertyStringValue(SProperty::kDescRole); }
	QString GetGroup() const { return GetPropertyStringValue(SProperty::kGroupRole); }
	QString GetEnableCond() const { return GetPropertyStringValue(SProperty::kEnableCondRole); }
	SProperty::EType GetType() const;
	bool IsUnique() const { return GetPropertyValue(SProperty::kUniqueRole).toBool(); }
	bool IsReadOnly() const { return GetPropertyValue(SProperty::kReadOnlyRole).toBool(); }
	QVariant GetConstraint() const { return GetPropertyValue(SProperty::kConstraintRole); }

	SProperty *GetProperty(SProperty::ERole role) const;
	QVariant GetPropertyValue(SProperty::ERole role) const;
	QString GetPropertyStringValue(SProperty::ERole role) const;
	QJsonValue GetPropertyJsonValue(SProperty::ERole role) const;
	bool ChangePropertyValue(SProperty::ERole role, QVariant value);

	bool IsPropertyDirty(SProperty::ERole role) const;

private:
	SSheet *sheet_;

	QHash<SProperty::ERole, SProperty*> properties_;
};

