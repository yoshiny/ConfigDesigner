#include "SValue.h"

const int SStringValue::meta_type_id_ = SPropertyValue::RegisterMetaType<SStringValue>(SValueType::kStringType);
const int SIntegerValue::meta_type_id_ = SPropertyValue::RegisterMetaType<SIntegerValue>(SValueType::kIntegerType);
const int SDoubleValue::meta_type_id_ = SPropertyValue::RegisterMetaType<SDoubleValue>(SValueType::kDoubleType);
