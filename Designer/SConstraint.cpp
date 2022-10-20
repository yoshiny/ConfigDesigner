#include "SConstraint.h"

#include <QChar>

QJsonValue QVariant2QJsonValue(QVariant variant) {
	int vt = variant.userType();
	switch (vt) {
	case QMetaType::QTime:
		return QJsonValue(variant.toTime().toString(Qt::ISODate));
	case QMetaType::QDate:
		return QJsonValue(variant.toDate().toString(Qt::ISODate));
	case QMetaType::QDateTime:
		return QJsonValue(variant.toDateTime().toString(Qt::ISODate));
	default:
		break;
	}
	// 内置类型按照默认处理，自定义类型会调用自定义的转换运算符
	return variant.toJsonValue();
}

QString QVariant2QString(QVariant variant) {
	int vt = variant.userType();
	switch (vt) {
	case QMetaType::QTime:
		return variant.toTime().toString(Qt::ISODate);
	case QMetaType::QDate:
		return variant.toDate().toString(Qt::ISODate);
	case QMetaType::QDateTime:
		return variant.toDateTime().toString(Qt::ISODate);
	default:
		break;
	}
	// 内置类型按照默认处理，自定义类型会调用自定义的转换运算符
	return variant.toString();
}

QVariant SConstraint::QJsonValue2SConstraint(QJsonValue value) {
	if (QJsonObject jo = value.toObject(); !jo.isEmpty()) {
		EConstraintType type = (EConstraintType)jo[QLatin1String("type")].toInt();
		switch (type) {
		case SConstraint::kStringType:
			break;
		case SConstraint::kTextType:
			break;
		case SConstraint::kIntegerType:
			return SIntegerConstraint::FromJsonValue(value);
		case SConstraint::kDoubleType:
			break;
		case SConstraint::kBoolType:
			break;
		case SConstraint::kDateType:
			break;
		case SConstraint::kTimeType:
			break;
		case SConstraint::kDateTimeType:
			break;
		case SConstraint::kComboType:
			break;
		case SConstraint::kFlagType:
			break;
		case SConstraint::kReferenceType:
			break;
		case SConstraint::kDependSelectorType:
			break;
		default:
			Q_ASSERT(false);
			break;
		}
	}
	Q_ASSERT(false);
	return QVariant();
}

QJsonValue SConstraint::QVariant2QJsonValue(QVariant variant, EConstraintType type) {
	switch (type) {
	case SConstraint::kStringType:
		return variant.toString();
	case SConstraint::kTextType:
		return QJsonArray::fromStringList(variant.toStringList());
	case SConstraint::kIntegerType:
		return variant.toString();
	case SConstraint::kDoubleType:
		return variant.toString();
	case SConstraint::kBoolType:
		return variant.toString();
	case SConstraint::kDateType:
		return variant.toDate().toString(Qt::ISODate);
	case SConstraint::kTimeType:
		return variant.toTime().toString(Qt::ISODate);
	case SConstraint::kDateTimeType:
		return variant.toDateTime().toString(Qt::ISODate);
	case SConstraint::kComboType:
		return variant.toStringList().join(QLatin1Char(','));
	case SConstraint::kFlagType:
		return QString("0x%1").arg(variant.toULongLong(), 8, 16, QLatin1Char('0'));
	case SConstraint::kReferenceType:
		return variant.toStringList().join(QLatin1Char(','));
	case SConstraint::kDependSelectorType:
		Q_ASSERT(false); // 不应该走到这里，约束为“依赖选择”字段的值，应该传入其依赖字段的约束类型
		break;
	default:
		Q_ASSERT(false);
		break;
	}
	return QJsonValue();
}

QVariant SConstraint::QJsonValue2QVariant(QJsonValue value, EConstraintType type) {
	
	return QVariant();
}




