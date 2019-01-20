#include <map>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "func.h"

using namespace std;

int main(int argc, char **argv)
{
	string context;
	string newContext;
	getLines(200, context);

	//context += "{}";
	int type = parseType(context);
	if (type == TYPE::eJson)
	{
		parseJson(context, newContext);
	}
	else if (type == TYPE::eXML)
	{
		parseXML(context, newContext);
	}
	else
	{
		newContext = context;
	}

	cout << newContext;

	cout << endl;
}
