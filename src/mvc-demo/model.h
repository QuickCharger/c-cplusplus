#pragma once

#include <common.h>

class Model
{
public:
	Model();
	Model(const string& data);
	~Model();

	string Data();
	void SetData(const string& data);

	void RegisterDataChangeHandler(DataChangeHandler handler);

private:
	string data = "";
	DataChangeHandler event = nullptr;
};
