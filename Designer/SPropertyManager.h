#pragma once

#include <functional>

#include <QSet>
#include <QVariant>

#include "SProperty.h"

class SPropertyManager : public QObject {
	Q_OBJECT
public:
	SPropertyManager(QObject *parent = nullptr);
	~SPropertyManager();

public:
	SProperty *AssignProperty(SProperty::ERole prop_role, SProperty::EType prop_type = SProperty::kStringType);
	void RecoverProperty(SProperty *prop);
	void RecoverProperty(std::initializer_list<SProperty*> list);

	void SetBackValue(SProperty *prop, QVariant value, bool force = false);
	QVariant GetBackValue(SProperty *prop);
	void ClearBackValue(SProperty *prop);
	void ClearBackValues();

signals:
	void OnPropertyBackValueChanged(SProperty *);

private:
	QHash<SProperty *, QVariant> back_values_;
	QSet<SProperty *> properties_;
};

