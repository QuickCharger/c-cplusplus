#include "model.h"

Model::Model()
{

}

Model::Model(const string &data)
{
	this->SetData(data);
}

Model::~Model()
{

}

string Model::Data()
{
	return data;
}

void Model::SetData(const string& data)
{
	this->data = data;
	if (this->event != nullptr)
		this->event(data);
}

void Model::RegisterDataChangeHandler(DataChangeHandler handler)
{
	this->event = handler;
}
