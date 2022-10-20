#include "SField.h"

#include "SSheet.h"
#include "SPropertyManager.h"
#include "SValue.h"

SField::SField(SSheet * sheet)
    : sheet_(sheet)
{
    auto &prop_manager = GetPropertyManager();
    for (auto role : {SProperty::kNameRole
                    , SProperty::kTitleRole
                    , SProperty::kGroupRole
                    , SProperty::kDescRole
                    , SProperty::kReadOnlyRole
                    , SProperty::kUniqueRole
                    , SProperty::kTypeRole
                    , SProperty::kDefaultRole
                    , SProperty::kConstraintRole
                    , SProperty::kEnableCondRole
                    }
        )
    {
        AddProperty(prop_manager.AssignProperty(role));
    }

    ChangePropertyValue(SProperty::kReadOnlyRole, false);
    ChangePropertyValue(SProperty::kUniqueRole, false);
    ChangePropertyValue(SProperty::kTypeRole, SProperty::kStringType);
}

SField::~SField() {
    auto &prop_manager = GetPropertyManager();
    for (auto it = properties_.constBegin(); it != properties_.constEnd(); ++it) {
        prop_manager.RecoverProperty(it.value());
    }
    properties_.clear();
}

SPropertyManager & SField::GetPropertyManager() const {
    return sheet_->GetPropertyManager();
}

SProperty::EType SField::GetType() const {
    return (SProperty::EType)GetPropertyValue(SProperty::kTypeRole).toInt();
}

SProperty * SField::GetProperty(SProperty::ERole role) const {
    return properties_.value(role, nullptr);
}

QVariant SField::GetPropertyValue(SProperty::ERole role) const {
    auto prop = properties_.value(role, nullptr);
    return prop ? prop->GetValue() : QVariant();
}

QString SField::GetPropertyStringValue(SProperty::ERole role) const {
    return QVariant2QString(GetPropertyValue(role));
}

QJsonValue SField::GetPropertyJsonValue(SProperty::ERole role) const {
    return QVariant2QJsonValue(GetPropertyValue(role));
}

bool SField::ChangePropertyValue(SProperty::ERole role, QVariant value) {
    if (auto prop = properties_.value(role, nullptr)) {
        if (prop->ChangeValue(value)) {
            if (role == SProperty::kTypeRole) {
                // 刷新默认值和约束属性
            }
            return true;
        }
    }
    return false;
}

bool SField::IsPropertyDirty(SProperty::ERole role) const {
    if (auto prop = properties_.value(role, nullptr)) {
        return prop->IsDirty();
    }
    return false;
}

void SField::AddProperty(SProperty * prop) {
    properties_.insert(prop->GetRole(), prop);
}
