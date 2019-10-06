#include "controller.h"

Controller::Controller()
{
}

Controller::Controller(const Model &model, const View& view)
{
	this->SetModel(model);
	this->SetView(view);
}

Controller::~Controller()
{

}

void Controller::SetModel(const Model& model)
{
	this->model = model;
}

void Controller::SetView(const View& view)
{
	this->view;
}

void Controller::OnLoad()
{
	this->view.Render();
}
