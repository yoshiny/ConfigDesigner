#pragma once

#include <QVariant>
#include <QString>
#include <QDateTime>

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
			return reg;
		}();
	}

	// 定义QVariant转换操作符
	operator QVariant() const {
		auto impl = static_cast<const T *>(this);
		return QVariant::fromValue<T>(*impl);
	}

	// 子类必须自定定义QString转换操作符

	// 定义比较运算符
	bool operator< (const T &that) const { return QString(*static_cast<const T *>(this)) < QString(that); }
	bool operator==(const T &that) const { return QString(*static_cast<const T *>(this)) == QString(that); }
};

//////////////////////////////////////////////////////////////////////////
// 常规值定义
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 约束值定义
//////////////////////////////////////////////////////////////////////////

