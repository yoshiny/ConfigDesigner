#pragma once

#include <QVariant>
#include <QString>
#include <QHash>
#include <QJsonValue>

#include "SEnumMeta.h"

class SPropertyManager;

class SProperty {
public:
	enum ERole {
		kNameRole = 0,
		kTitleRole,
		kGroupRole,
		kDescRole,
		kReadOnlyRole,
		kUniqueRole,

		kValueRole,
		kConstraintRole,
	};

private:
	static SEnumMeta& RoleMeta() {
		static SEnumMeta mt = SEnumMeta()
			.Add(kNameRole, QLatin1String("Name"), QObject::tr("名称"))
			.Add(kTitleRole, QLatin1String("Title"), QObject::tr("标题"))
			.Add(kGroupRole, QLatin1String("Group"), QObject::tr("分组"))
			.Add(kDescRole, QLatin1String("Desc"), QObject::tr("描述"))
			.Add(kReadOnlyRole, QLatin1String("ReadOnly"), QObject::tr("只读"))
			.Add(kUniqueRole, QLatin1String("Unique"), QObject::tr("唯一"))
			.Add(kValueRole, QLatin1String("Value"), QObject::tr("值"))
			.Add(kConstraintRole, QLatin1String("Constraint"), QObject::tr("约束"))
			;
		return mt;
	}

public:
	static QLatin1String RoleName(ERole role) {
		return RoleMeta().Value2Name(role);
	}

	static QString RoleTitle(ERole role) {
		return RoleMeta().Value2Title(role);
	}

	static int RoleValue(QLatin1String name) {
		return RoleMeta().Name2Value(name);
	}
public:
	SProperty(SPropertyManager *prop_manager, ERole prop_role);

public:
	ERole GetRole() const { return role_; }

	QVariant GetValue() const { return value_; }
	void SetValue(QVariant value) { value_ = value; }
	bool ChangeValue(QVariant value);

	QString GetDisplayValue() const { return value_display_; }
	QString GetStringValue() const;
	QJsonValue GetJsonValue() const;

	bool IsDirty() const;
	void ClearDirty();

	bool IsValid() const { return value_valid_; }
	void SetValid(bool valid) { value_valid_ = valid; }

	bool IsInvalidate() const { return value_invalidate_; }
	bool SetInvalidate(bool invalidate) { value_invalidate_ = invalidate; }

	QString GetValueTips() const { return value_tips_; }
private:
	SPropertyManager *prop_manager_{ nullptr };
	const ERole role_;
	QVariant value_;
	QString value_display_;
	QString value_tips_;
	bool value_invalidate_{true};
	bool value_valid_{false};
};

