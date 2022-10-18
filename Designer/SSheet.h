#pragma once

#include <QString>

class SConfig;

class SSheet {
public:
	enum class ESheetType {
		kTable = 0,
		kForm = 1,
	};

public:


private:
	SConfig *config_{nullptr};

};

