#pragma once

#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QJsonValue>

QJsonValue QVariant2QJsonValue(QVariant variant);
QString QVariant2QString(QVariant variant);

struct SBooleanBox {
	static bool FromString(QString str) {
		return str.toLower() == QLatin1String("true");
	}
	static bool FromString(QStringRef str) {
		return FromString(str.toString());
	}
	static QLatin1String ToString(bool val) {
		return val ? QLatin1String("True") : QLatin1String("False");
	}
};

struct SValue {
};

template <typename T>
struct SValueBasic : public SValue {
	// 注册类型元数据
	SValueBasic() {
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
	operator QJsonValue() const{
		auto impl = static_cast<const T *>(this);
		return impl->ToJsonValue();
	}

	// 定义比较运算符，子类可根据需要重写
	bool operator< (const T &that) const { return QString(*static_cast<const T *>(this)) < QString(that); }
	bool operator==(const T &that) const { return QString(*static_cast<const T *>(this)) == QString(that); }
};

//////////////////////////////////////////////////////////////////////////
// 常规值定义
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 约束值定义
//////////////////////////////////////////////////////////////////////////

