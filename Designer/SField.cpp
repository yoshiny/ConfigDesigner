#include "SField.h"

#include "SSheet.h"
#include "SPropertyManager.h"
#include "SValue.h"

SField::SField(SSheet * sheet)
    : sheet_(sheet)
{
    auto &prop_manager = GetPropertyManager();
    for (auto role : {SProperty::ERole::kName
                    , SProperty::ERole::kTitle
                    , SProperty::ERole::kGroup
                    , SProperty::ERole::kDesc
                    , SProperty::ERole::kReadOnly
                    , SProperty::ERole::kUnique
                    , SProperty::ERole::kMode
                    , SProperty::ERole::kDefault
                    , SProperty::ERole::kConstraint
                    , SProperty::ERole::kEnableCond
                    }
        )
    {
        AddProperty(prop_manager.AssignProperty(role));
    }

    ChangePropertyValue(SProperty::ERole::kReadOnly, false);
    ChangePropertyValue(SProperty::ERole::kUnique, false);
    ChangePropertyValue(SProperty::ERole::kMode, (int)SProperty::EMode::kString);
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

SProperty::EMode SField::GetMode() const {
    return (SProperty::EMode)GetPropertyValue(SProperty::ERole::kMode).toInt();
}

SProperty * SField::GetProperty(SProperty::ERole role) const {
    return properties_.value(role, nullptr);
}

QVariant SField::GetPropertyValue(SProperty::ERole role) const {
    auto prop = properties_.value(role, nullptr);
    return prop ? prop->GetValue() : QVariant();
}

bool SField::ChangePropertyValue(SProperty::ERole role, QVariant value) {
    if (auto prop = properties_.value(role, nullptr)) {
        if (prop->ChangeValue(value)) {
            if (role == SProperty::ERole::kMode) {
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
