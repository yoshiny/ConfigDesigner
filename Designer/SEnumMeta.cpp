#include "SEnumMeta.h"

SEnumMeta & SEnumMeta::Add(int value, QLatin1String name, QString title) {
    if (!value2name_.contains(value)) {
        value2name_.insert(value, name);
        value2title_.insert(value, title);
        name2value_.insert(name, value);
    }
    return *this;
}

QLatin1String SEnumMeta::Value2Name(int value) const {
    return value2name_.value(value);
}

QString SEnumMeta::Value2Title(int value) const {
    return value2title_.value(value);
}

int SEnumMeta::Name2Value(QLatin1String name) const {
    return name2value_.value(name, -1);
}
