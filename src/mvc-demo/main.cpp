/*
* Õª×Ô£º https://helloacm.com/model-view-controller-explained-in-c/
* Models for maintaining data
* Views for display
* Controllers for handling events that affect the model or views
*/

#include <iostream>
#include "view.h"
#include "model.h"
#include "controller.h"
#include "common.h"

using namespace std;

void DataChange(string data)
{
	cout << "Data Changes: " << data << endl;
}

int main()
{
	Model model("Model");
	View view(model);
	model.RegisterDataChangeHandler(DataChange);
	Controller controller(model, view);
	controller.OnLoad();

	model.SetData("Changes");

	cout << "over." << endl;
	getchar();

	return 0;
}
