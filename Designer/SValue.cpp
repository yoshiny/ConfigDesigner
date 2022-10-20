#include "SValue.h"

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
