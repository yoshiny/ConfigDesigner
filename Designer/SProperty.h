#pragma once

#include <QVariant>
#include <QString>
#include <QHash>

#include "SEnumMeta.h"

class SPropertyManager;

class SProperty {
public:
	enum class EMode {
		kString = 0,
		kText,
		kInteger,
		kDouble,
		kBool,
		kDate,
		kTime,
		kDateTime,
		kCombo,
		kFlag,
		kReference,
		kTableFold,
		kDependSelector,
	};

private:
	static SEnumMeta& ModeMeta() {
		static SEnumMeta mt = SEnumMeta()
			.Add((int)EMode::kString, QLatin1String("String"), QObject::tr("字符串"))
			.Add((int)EMode::kText, QLatin1String("Text"), QObject::tr("文本段"))
			.Add((int)EMode::kInteger, QLatin1String("Integer"), QObject::tr("整型"))
			.Add((int)EMode::kDouble, QLatin1String("Double"), QObject::tr("浮点型"))
			.Add((int)EMode::kBool, QLatin1String("Bool"), QObject::tr("布尔"))
			.Add((int)EMode::kDate, QLatin1String("Date"), QObject::tr("日期"))
			.Add((int)EMode::kTime, QLatin1String("Time"), QObject::tr("时间"))
			.Add((int)EMode::kDateTime, QLatin1String("DateTime"), QObject::tr("日期时间"))
			.Add((int)EMode::kCombo, QLatin1String("Combo"), QObject::tr("下拉选择"))
			.Add((int)EMode::kFlag, QLatin1String("Flag"), QObject::tr("标志位"))
			.Add((int)EMode::kReference, QLatin1String("Reference"), QObject::tr("外键引用"))
			.Add((int)EMode::kTableFold, QLatin1String("TableFold"), QObject::tr("表聚合"))
			.Add((int)EMode::kDependSelector, QLatin1String("DependSelector"), QObject::tr("依赖选择"))
			;
		return mt;
	}

public:
	static QLatin1String ModeName(EMode mode) {
		return ModeMeta().Value2Name((int)mode);
	}
	
	static QString ModeTitle(EMode mode) {
		return ModeMeta().Value2Title((int)mode);
	}

	static int ModeValue(QLatin1String name) {
		return ModeMeta().Name2Value(name);
	}

	enum class EType {
		kName = 0,
		kTitle,
		kGroup,
		kDesc,
		kReadOnly,
		kUnique,

		kValue,
		kMode,
		kDefault,
		kConstraint,
		kEnableCond,
	};

private:
	static SEnumMeta& TypeMeta() {
		static SEnumMeta mt = SEnumMeta()
			.Add((int)EType::kName, QLatin1String("Name"), QObject::tr("名称"))
			.Add((int)EType::kTitle, QLatin1String("Title"), QObject::tr("标题"))
			.Add((int)EType::kGroup, QLatin1String("Group"), QObject::tr("分组"))
			.Add((int)EType::kDesc, QLatin1String("Desc"), QObject::tr("描述"))
			.Add((int)EType::kReadOnly, QLatin1String("ReadOnly"), QObject::tr("只读"))
			.Add((int)EType::kUnique, QLatin1String("Unique"), QObject::tr("唯一"))
			.Add((int)EType::kValue, QLatin1String("Value"), QObject::tr("值"))
			.Add((int)EType::kMode, QLatin1String("Mode"), QObject::tr("模式"))
			.Add((int)EType::kDefault, QLatin1String("Default"), QObject::tr("默认值"))
			.Add((int)EType::kConstraint, QLatin1String("Constraint"), QObject::tr("约束"))
			.Add((int)EType::kEnableCond, QLatin1String("EnableCond"), QObject::tr("启用条件"))
			;
		return mt;
	}

public:
	static QLatin1String TypeName(EType type) {
		return TypeMeta().Value2Name((int)type);
	}

	static QString TypeTitle(EType type) {
		return TypeMeta().Value2Title((int)type);
	}

	static int TypeValue(QLatin1String name) {
		return TypeMeta().Name2Value(name);
	}
public:
	SProperty(EType prop_type, int value_type )
		: prop_type_(prop_type)
		, value_type_(value_type)
	{}

public:
	EType GetPropType() const { return prop_type_; }
	int GetValueType() const { return value_type_; }

	QString GetValueDisplay() const { return value_display_; }
	QString GetValueText() const { return value_.toString(); }
	QVariant GetValue() const { return value_; }
	void SetValue(QVariant value) { value_ = value; }
	bool ChangeValue(QVariant value);

	bool IsDirty() const;
	void ClearDirty() const;

	bool IsValid() const { return value_valid_; }
	void SetValid(bool valid) { value_valid_ = valid; }

	bool IsInvalidate() const { return value_invalidate_; }
	bool SetInvalidate(bool invalidate) { value_invalidate_ = invalidate; }

private:
	EType prop_type_{EType::kValue};
	int value_type_{0};
	QVariant value_;
	QString value_display_;
	QString value_tips_;
	bool value_invalidate_{true};
	bool value_valid_{false};
	SPropertyManager *prop_manager_{ nullptr };
};

