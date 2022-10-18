#include "SConfig.h"

SConfig::~SConfig() {}

SConfig::SConfig(QString file_path, EConfigType type)
	: type_(type)
	, file_path_(file_path)
{}

bool SNormalConfig::Load() {
	return false;
}

bool SNormalConfig::Save() {
	return false;
}
