#include "SConfigManager.h"

SConfigManager::SConfigManager() {}

SConfigManager::~SConfigManager() {}

void SConfigManager::Clear() {
	qDeleteAll(config_list_);
	config_list_.clear();
	id2config_.clear();

	qDeleteAll(schema_list_);
	schema_list_.clear();
	id2schema_.clear();
}

SConfig * SConfigManager::LoadConfig(QString file_path) {
	return nullptr;
}

SConfig * SConfigManager::NewConfig(QString file_path) {
	return nullptr;
}

void SConfigManager::AddConfig(SConfig * cfg) {}
