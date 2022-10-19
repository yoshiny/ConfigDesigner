#pragma once

#include <QString>
#include <QHash>

class SSheet;
class SField;
class SProperty;

class SEntry {
public:
	SEntry(SSheet *sheet);
	~SEntry();

public:
	void SetProperty(SField *field, SProperty *prop);
	SProperty *GetProperty(SField *field);
	SProperty *GetProperty(QString field);

private:
	SSheet *sheet_;
	QHash<SField*, SProperty*> properties_;
};

