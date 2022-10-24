#pragma once

#include <QVariant>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QHash>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "SProperty.h"

struct STypeParam {
	static QVariant QJsonValue2STypeParam(SProperty::EType type, QJsonValue value);
};

QJsonValue QVariant2QJsonValue(QVariant variant);
QVariant QString2QVariant(SProperty::EType type, QString value);

template <typename T>
struct STypeParamBasic {
	// 注册类型元数据
	STypeParamBasic() {
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
struct SComboParam : public STypeParamBasic<SComboParam>
{
	bool multi_{ false };
	QList<QPair<QString, QString>> pair_list_;

	static SComboParam FromJsonValue(QJsonValue jv) {
		SComboParam param;
		if (QJsonObject jo = jv.toObject(); !jo.isEmpty()) {
			param.multi_ = jo[QLatin1String("multi")].toBool();
			if (QJsonArray ja_pairs = jo[QLatin1String("pairs")].toArray(); !ja_pairs.isEmpty()) {
				for (auto it = ja_pairs.constBegin(); it != ja_pairs.constEnd(); ++it) {
					if (QJsonObject jo_pair = it->toObject(); !jo_pair.isEmpty()) {
						QString key = jo_pair[QLatin1String("key")].toString();
						QString val = jo_pair[QLatin1String("val")].toString();
						if (!key.isEmpty()) {
							param.pair_list_.push_back(QPair<QString, QString>(key, val));
						}
					}
				}
			}
		}
		return param;
	}

	QString ToString() const {
		return QString();
	}

	QJsonValue ToJsonValue() const {
		QJsonArray ja;
		for (auto it = pair_list_.constBegin(); it != pair_list_.constEnd(); ++it) {
			ja.append(QJsonObject{{QLatin1String("key"), it->first}, {QLatin1String("val"), it->second} });
		}
		QJsonObject jo{
			{QLatin1String("multi"), multi_},
			{QLatin1String("pairs"), ja}
		};
		return jo;
	}
};
Q_DECLARE_METATYPE(SComboParam)

struct SFlagParam : public STypeParamBasic<SFlagParam>
{
	QList<QPair<QString, qulonglong>> pair_list_;

	static SFlagParam FromJsonValue(QJsonValue jv) {
		SFlagParam param;
		if (QJsonArray ja = jv.toArray(); !ja.isEmpty()) {
			for (auto it = ja.constBegin(); it != ja.constEnd(); ++it) {
				QJsonObject jo = it->toObject();
				QString key = jo[QLatin1String("key")].toString();
				qulonglong val = jo[QLatin1String("val")].toString().toULongLong(nullptr, 16);
				param.pair_list_.append(QPair<QString, qulonglong>(key, val));
			}
		}
		return param;
	}

	QString ToString() const {
		return QString();
	}

	QJsonValue ToJsonValue() const {
		QJsonArray ja;
		for (auto it = pair_list_.constBegin(); it != pair_list_.constEnd(); ++it) {
			ja.append(QJsonObject{{QLatin1String("key"), it->first}, {QLatin1String("val"), QString("0x%1").arg(it->second, 8, 16, QLatin1Char('0'))}});
		}
		return ja;
	}
};
Q_DECLARE_METATYPE(SFlagParam)

struct SReferenceParam : public STypeParamBasic<SReferenceParam>
{
	bool multi_{ false };
	QString config_;
	QString sheet_;
	QString field_;
	QString display_;

	static SReferenceParam FromJsonValue(QJsonValue jv) {
		SReferenceParam param;
		QJsonObject jo = jv.toObject();
		param.multi_ = jo[QLatin1String("multi")].toBool();
		param.config_ = jo[QLatin1String("config")].toString();
		param.sheet_ = jo[QLatin1String("sheet")].toString();
		param.field_ = jo[QLatin1String("field")].toString();
		param.display_ = jo[QLatin1String("display")].toString();
		return param;
	}

	QString ToString() const {
		return QString();
	}

	QJsonValue ToJsonValue() const {
		QJsonObject jo{
			{QLatin1String("multi"), multi_},
			{QLatin1String("config"), config_},
			{QLatin1String("sheet"), sheet_},
			{QLatin1String("field"), field_},
			{QLatin1String("display"), display_},
		};
		return jo;
	}
};
Q_DECLARE_METATYPE(SReferenceParam)
