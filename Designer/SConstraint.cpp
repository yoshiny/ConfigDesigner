#include "SConstraint.h"

#include <QChar>

QVariant STypeParam::QJsonValue2STypeParam(SProperty::EType type, QJsonValue value) {
	switch (type) {
	case SProperty::kComboType:
		return SComboParam::FromJsonValue(value);
	case SProperty::kFlagType:
		return SFlagParam::FromJsonValue(value);
	case SProperty::kReferenceType:
		return SReferenceParam::FromJsonValue(value);
	case SProperty::kDependSelectorType:
		break;
	default:
		break;
	}
	Q_ASSERT(false);
	return QVariant();
}

QJsonValue QVariant2QJsonValue(QVariant variant) {
	QVariant::Type type = variant.type();
	if (type >= QVariant::UserType) {
		return variant.toJsonValue();
	}

	switch (type) {
	case QMetaType::Bool:
		return variant.toBool() ? QLatin1String("true") : QLatin1String("false");
	case QMetaType::QDate:
		return variant.toDate().toString(Qt::ISODate);
	case QMetaType::QTime:
		return variant.toTime().toString(Qt::ISODate);
	case QMetaType::QDateTime:
		return variant.toDateTime().toString(Qt::ISODate);
	case QMetaType::Double:
	case QMetaType::Float:
		return QString::number(variant.toDouble(), 'f', 3);
	case QMetaType::QStringList:
		return variant.toStringList().join(QLatin1Char(','));
	default:
		break;
	}
	Q_ASSERT(false);
	return variant.toString();
}

QVariant QString2QVariant(SProperty::EType type, QString value) {
	switch (type) {
	case SProperty::kStringType:
		return value;
	case SProperty::kTextType:
		return value;
	case SProperty::kIntegerType:
		return value.toLongLong();
	case SProperty::kDoubleType:
		return value.toDouble();
	case SProperty::kBoolType:
		return value.toLower() == QLatin1String("true");
	case SProperty::kDateType:
		return QDate::fromString(value, Qt::ISODate);
	case SProperty::kTimeType:
		return QTime::fromString(value, Qt::ISODate);
	case SProperty::kDateTimeType:
		return QDateTime::fromString(value, Qt::ISODate);
	case SProperty::kComboType:
	case SProperty::kFlagType:
	case SProperty::kReferenceType:
		return value.split(QLatin1Char(','), Qt::SkipEmptyParts);
	case SProperty::kDependSelectorType:
		Q_ASSERT(false); // 不应该走到这里，类型为“依赖选择”的值，应该传入其依赖字段的类型
		break;
	default:
		break;
	}
	Q_ASSERT(false);
	return value;
}
