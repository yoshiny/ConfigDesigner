#pragma once

#include <QHash>
#include <QList>
#include <QString>
#include <QJsonValue>

#include "SProperty.h"
#include "SConstraint.h"

class SSchema;
class SPropertyManager;

class SField {
public:
	SField(SSchema *schema);
	~SField();

public:
	static const QList<SProperty::ERole>& GetFieldPropertyRoles();

public:
	SPropertyManager &GetPropertyManager() const;
	void AddProperty(SProperty *prop);

	bool ChangePropertyValue(SProperty::ERole role, QVariant value);
	bool IsPropertyDirty(SProperty::ERole role) const;

	SProperty *GetProperty(SProperty::ERole role) const;
	QVariant GetPropertyValue(SProperty::ERole role) const;
	QString GetPropertyDisplayValue(SProperty::ERole role) const;
	QString GetPropertyStringValue(SProperty::ERole role) const;
	QJsonValue GetPropertyJsonValue(SProperty::ERole role) const;

	QString GetName() const {return GetPropertyStringValue(SProperty::kNameRole);}
	QString GetTitle() const { return GetPropertyStringValue(SProperty::kTitleRole); }
	QString GetDesc() const { return GetPropertyStringValue(SProperty::kDescRole); }
	QString GetGroup() const { return GetPropertyStringValue(SProperty::kGroupRole); }
	bool IsUnique() const { return GetPropertyValue(SProperty::kUniqueRole).toBool(); }
	bool IsReadOnly() const { return GetPropertyValue(SProperty::kReadOnlyRole).toBool(); }
	QVariant GetConstraint() const { return GetPropertyValue(SProperty::kConstraintRole); }
	SConstraint::EConstraintType GetConstraintType() const;

private:
	SSchema *schema_;
	QHash<SProperty::ERole, SProperty*> properties_;
};

