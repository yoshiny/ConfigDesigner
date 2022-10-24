#pragma once

#include <functional>

#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QHash>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

struct SValueType {
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
};

template <typename Impl>
struct SValueBasic {
	template <typename VT>
	static int RegisterMetaType(SValueType::EType type) {
		int metaTypeId = qRegisterMetaType<VT>();
		QMetaType::registerComparators<VT>();
		QMetaType::registerConverter<VT, QVariant>();
		QMetaType::registerConverter<VT, QString>();
		QMetaType::registerConverter<VT, QJsonValue>();

		Impl::factory_.insert(type, []() -> QVariant { return VT(); });
		return metaTypeId;
	}

	static QVariant Create(SValueType::EType type) {
		auto fac = Impl::factory_.value(type, nullptr);
		return fac ? fac() : QVariant();
	}

	inline static QHash<SValueType::EType, std::function<QVariant()>> factory_{};
};

struct SPropertyValue : public SValueBasic<SPropertyValue> {
};

struct SValueConstraint : public SValueBasic<SValueConstraint> {
	
};

//////////////////////////////////////////////////////////////////////////
// 属性值
//////////////////////////////////////////////////////////////////////////
struct SStringValue : SPropertyValue {
	static const int meta_type_id_;

	QString value_;

	operator QVariant() const { return QVariant::fromValue<SStringValue>(*this); }
	operator QString() const { return value_; }
	operator QJsonValue() const { return value_; }
};
Q_DECLARE_METATYPE(SStringValue)

struct SIntegerValue : SPropertyValue {
	static const int meta_type_id_;

	qlonglong value_{ 0 };

	operator QVariant() const { return QVariant::fromValue<SIntegerValue>(*this); }
	operator QString() const { return QString::number(value_); }
	operator QJsonValue() const { return this->operator QString(); }
};
Q_DECLARE_METATYPE(SIntegerValue)

struct SDoubleValue : SPropertyValue {
	static const int meta_type_id_;

	double value_{ 0.0 };

	operator QVariant() const { return QVariant::fromValue<SDoubleValue>(*this); }
	operator QString() const { return QString::number(value_, 'f', 3); }
	operator QJsonValue() const { return this->operator QString(); }
};
Q_DECLARE_METATYPE(SDoubleValue)

//////////////////////////////////////////////////////////////////////////
// 值约束
//////////////////////////////////////////////////////////////////////////

