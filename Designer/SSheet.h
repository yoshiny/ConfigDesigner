#pragma once

#include <QString>
#include <QList>
#include <QHash>

#include "SProperty.h"
#include "SEnumMeta.h"

class SConfig;
class SField;
class SEntry;
class SPropertyManager;

class SSheet {
public:
	enum class EType {
		kTable = 0,
		kForm = 1,
	};
private:
	static SEnumMeta& TypeMeta() {
		static SEnumMeta mt = SEnumMeta()
			.Add((int)EType::kTable, QLatin1String("Table"), QObject::tr("表格"))
			.Add((int)EType::kForm, QLatin1String("Form"), QObject::tr("表单"))
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
	SSheet(SConfig *config, EType type);
	~SSheet();

public:
	SPropertyManager &GetPropertyManager();
	EType GetType() const { return type_; }
	SConfig *GetConfig() const { return config_; }
	QString GetGuid() const;

	QString GetName() const;
	void SetName(QString name);

	QString GetTitle() const;
	void SetTitle(QString title);

	int GetIndex() const;
	void SetIndex(int index);

	QHash<QString, QVariant> GetProps() const;
	void SetProps(QHash<QString, QVariant> props);

	SField *GetField(QString field) const;
private:
	const EType type_;
	SConfig *config_{ nullptr };
	mutable QString guid_;

	SProperty *name_{ nullptr };
	SProperty *title_{ nullptr };
	SProperty *index_{ nullptr };
	SProperty *props_{ nullptr };

	QList<SField *>field_list_;
	QList<SEntry *>entry_list_;
};

