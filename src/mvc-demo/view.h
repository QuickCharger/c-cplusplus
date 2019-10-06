#pragma once

#include "model.h"

class View
{
public:
	View();
	View(const Model& model);
	~View();

	void SetModel(const Model& model);
	void Render();

private:
	Model model;
};
