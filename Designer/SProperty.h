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
		kTypeRole,
		kDefaultRole,
		kConstraintRole,
		kEnableCondRole,
		kValidCheckRole,
	};

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
			.Add(kTypeRole, QLatin1String("Type"), QObject::tr("类型"))
			.Add(kDefaultRole, QLatin1String("Default"), QObject::tr("默认值"))
			.Add(kConstraintRole, QLatin1String("Constraint"), QObject::tr("约束"))
			.Add(kEnableCondRole, QLatin1String("EnableCond"), QObject::tr("启用条件"))
			.Add(kValidCheckRole, QLatin1String("ValidCheck"), QObject::tr("合法检校"))
			;
		return mt;
	}

public:
	enum EType {
		kStringType = 0,
		kTextType,
		kIntegerType,
		kDoubleType,
		kBoolType,
		kDateType,
		kTimeType,
		kDateTimeType,
		kComboType,
		kFlagType,
		kReferenceType,
		kDependSelectorType,
	};

	static QLatin1String TypeName(EType type) {
		return TypeMeta().Value2Name(type);
	}

	static QString TypeTitle(EType type) {
		return TypeMeta().Value2Title(type);
	}

	static int TypeValue(QLatin1String name) {
		return TypeMeta().Name2Value(name);
	}

private:
	static SEnumMeta& TypeMeta() {
		static SEnumMeta mt = SEnumMeta()
			.Add(kStringType, QLatin1String("String"), QObject::tr("字符串"))
			.Add(kTextType, QLatin1String("Text"), QObject::tr("文本段"))
			.Add(kIntegerType, QLatin1String("Integer"), QObject::tr("整型"))
			.Add(kDoubleType, QLatin1String("Double"), QObject::tr("浮点型"))
			.Add(kBoolType, QLatin1String("Bool"), QObject::tr("布尔"))
			.Add(kDateType, QLatin1String("Date"), QObject::tr("日期"))
			.Add(kTimeType, QLatin1String("Time"), QObject::tr("时间"))
			.Add(kDateTimeType, QLatin1String("DateTime"), QObject::tr("日期时间"))
			.Add(kComboType, QLatin1String("Combo"), QObject::tr("下拉选择"))
			.Add(kFlagType, QLatin1String("Flag"), QObject::tr("标志位"))
			.Add(kReferenceType, QLatin1String("Reference"), QObject::tr("外键引用"))
			.Add(kDependSelectorType, QLatin1String("DependSelector"), QObject::tr("依赖选择"))
			;
		return mt;
	}

public:
	SProperty(SPropertyManager *prop_manager, ERole prop_role, EType prop_type);

public:
	ERole GetRole() const { return role_; }
	EType GetType() const { return type_; }

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
	const EType type_;
	QVariant value_;
	QString value_display_;
	QString value_tips_;
	bool value_invalidate_{true};
	bool value_valid_{false};
};

