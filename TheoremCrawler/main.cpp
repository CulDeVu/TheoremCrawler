#include <fstream>
#include <iostream>
#include <stdio.h>

#include <io.h>
#include <fcntl.h>

#include "exprNode.h"
#include "strats.h"

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

vector<exprNode*> theorems;

exprNode* recursiveRead(nlohmann::basic_json<>::value_type root)
{
	exprNode* a = new exprNode();

	a->expr = root["expr"].get<string>();

	a->varId = root["varid"].get<int>();

	int size = root["args"].size();
	for (int i = 0; i < size; ++i)
	{
		a->args.push_back(recursiveRead(root["args"][i]));
	}

	return a;
}

int main()
{
	//_setmode(_fileno(stdout), _O_U16TEXT);
	//std::wcout << L"Hello, \u0444!\n";

	assumptStack* globalStack = new assumptStack();
	
	json root;

	std::ifstream file("theorems.json");
	file >> root;

	int size = root["longform"].size();
	for (int i = 0; i < size; ++i)
	{
		string str = root["longform"][i].get<string>();
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
		int a = 0;
		globalStack->facts.push_back(recursiveParse(str, a));
	}

	for (int i = 0; i < globalStack->facts.size(); ++i)
	{
		printExprNode(globalStack->facts[i]);
		printf("\n");
	}

	for (int i = 0; i < 5; ++i)
	{
		pickStrat(globalStack);

		assumptStack* a = globalStack;
		while (a->subAssumpt != 0)
		{
			a = a->subAssumpt;
			printf("|");
		}

		printExprNode(a->facts[a->facts.size() - 1]);
		printf("\n");
	}

	/*exprNode* f = new exprNode();
	f->varId = 100;
	exprNode* a = E_forall(theorems[0], f);
	printExprNode(a);*/
		
	//printf("asdf");
	getchar();
}