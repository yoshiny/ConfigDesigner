#pragma once

#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "SEnumMeta.h"

struct SConstraint {
	enum EConstraintType {
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

	static QLatin1String ConstraintTypeName(EConstraintType type) {
		return ConstraintTypeMeta().Value2Name(type);
	}

	static QString ConstraintTypeTitle(EConstraintType type) {
		return ConstraintTypeMeta().Value2Title(type);
	}

	static int ConstraintTypeValue(QLatin1String name) {
		return ConstraintTypeMeta().Name2Value(name);
	}

	// 从QJsonValue中创建具体约束对象
	static QVariant QJsonValue2SConstraint(QJsonValue value);

	// 将具体值根据约束类型转化为QJsonValue
	static QJsonValue QVariant2QJsonValue(QVariant variant, EConstraintType type);

	// 从QJsonValue中根据约束类型创建具体值
	static QVariant QJsonValue2QVariant(QJsonValue value, EConstraintType type);

private:
	static SEnumMeta& ConstraintTypeMeta() {
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
};

QJsonValue QVariant2QJsonValue(QVariant variant);
QString QVariant2QString(QVariant variant);

template <typename T>
struct SConstraintBasic {
	// 注册类型元数据
	SConstraintBasic() {
		static int _reg = []() {
			int reg = qRegisterMetaType<T>();
			bool suc = QMetaType::registerComparators<T>();
			Q_ASSERT(suc);

			suc = QMetaType::registerConverter<T, QVariant>();
			Q_ASSERT(suc);

			suc = QMetaType::registerConverter<T, QString>();
			Q_ASSERT(suc);

			suc = QMetaType::registerConverter<T, QJsonValue>();
			Q_ASSERT(suc);
			return reg;
		}();
	}

	// 定义QVariant转换运算符，子类无需重写
	operator QVariant() const {
		auto impl = static_cast<const T *>(this);
		return QVariant::fromValue<T>(*impl);
	}

	// 定义QString转换运算符，子类必须实现ToStirng方法
	operator QString() const {
		auto impl = static_cast<const T *>(this);
		return impl->ToString();
	}

	// 定义QJsonValue转换运算符，子类必须实现ToJsonValue方法
	operator QJsonValue() const {
		auto impl = static_cast<const T *>(this);
		return impl->ToJsonValue();
	}

	// 定义比较运算符，子类可根据需要重写
	bool operator< (const T &that) const { return QString(*static_cast<const T *>(this)) < QString(that); }
	bool operator==(const T &that) const { return QString(*static_cast<const T *>(this)) == QString(that); }
};

//////////////////////////////////////////////////////////////////////////
// 约束值定义
//////////////////////////////////////////////////////////////////////////
struct SIntegerConstraint : public SConstraintBasic<SIntegerConstraint>
{
	static constexpr SConstraint::EConstraintType type_{SConstraint::kIntegerType};
	qlonglong default_{ 0 };
	qlonglong min_{ 0 };
	qlonglong max_{ 0 };

	static SIntegerConstraint FromJsonValue(QJsonValue jv) {
		SIntegerConstraint ic;
		if (QJsonObject jo = jv.toObject(); !jo.isEmpty()) {
			ic.default_ = jo[QLatin1String("default")].toString().toLongLong();
			ic.min_ = jo[QLatin1String("min")].toString().toLongLong();
			ic.max_ = jo[QLatin1String("max")].toString().toLongLong();
		}
		return ic;
	}

	QString ToString() const {
		if (min_ == max_) {
			return QObject::tr("默认值：%1").arg(default_);
		} else {
			return QObject::tr("默认值：%1，最小值：%2，最大值：%3").arg(default_).arg(min_).arg(max_);
		}
	}

	QJsonValue ToJsonValue() const {
		QJsonObject jo{
			{QLatin1String("type"), type_},
			{QLatin1String("default"), QString::number(default_)},
			{QLatin1String("min"), QString::number(min_)},
			{QLatin1String("max"), QString::number(max_)},
		};
		return jo;
	}
};
Q_DECLARE_METATYPE(SIntegerConstraint)
