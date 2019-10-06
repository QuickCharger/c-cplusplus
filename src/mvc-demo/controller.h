#pragma once

#include "model.h"
#include "view.h"

class Controller
{
public:
	Controller();
	Controller(const Model &model, const View& view);
	~Controller();

	void SetModel(const Model& model);
	void SetView(const View& view);
	void OnLoad();

private:
	Model model;
	View view;
};
