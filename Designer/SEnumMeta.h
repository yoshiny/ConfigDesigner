#pragma once

#include <QHash>
#include <QString>

class SEnumMeta {
public:
	SEnumMeta &Add(int value, QLatin1String name, QString title);
	QLatin1String Value2Name(int value) const;
	QString Value2Title(int value) const;
	int Name2Value(QLatin1String name) const;

private:
	QHash<int, QLatin1String> value2name_;
	QHash<int, QString> value2title_;
	QHash<QLatin1String, int> name2value_;
};

