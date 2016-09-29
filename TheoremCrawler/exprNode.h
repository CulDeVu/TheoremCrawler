#pragma once

#include <string>
#include <vector>

using namespace std;

string binaryOps[] = {
	"or", "v",
	"and", "^",
	"=>", "=>",
	"in", "in",
	"=", "="
};
int findOp(string s)
{
	for (int i = 0; i < 5; ++i)
	{
		if (s == binaryOps[2 * i])
			return 2 * i + 1;
	}
	return -1;
}

struct exprNode
{
	string expr;
	int varId;
	vector<exprNode*> args;

	exprNode()
	{
		expr = "";
		varId = -1;
	}

	~exprNode()
	{
		for (int i = 0; i < args.size(); ++i)
			delete args[i];
	}
};

exprNode* recursiveParse(string n, int& i)
{
	exprNode* ret = new exprNode();

	// search parse name of expression
	int b = 0;
	bool isFunc = false;
	while (i + b < n.length())
	{
		if (n[i + b] == ',' || n[i + b] == ')')
			break;
		if (n[i + b] == '(')
		{
			isFunc = true;
			break;
		}
		++b;
	}

	if (n[i] == '_') // variable
	{
		string s = n.substr(i + 1, b - 1);
		ret->varId = atoi(s.c_str());
		i = i + b;
		return ret;
	}
	else if (isFunc) // function that has args
	{
		ret->expr = n.substr(i, b);
		i = i + b + 1;

		while (true)
		{
			if (n[i - 1] == ')')
				break;
			ret->args.push_back(recursiveParse(n, i));
			i = i + 1;
		}

		return ret;
	}
	else
	{
		ret->expr = n.substr(i, b);
		i = i + b;
		return ret;
	}
}

void printExprNode(exprNode* n)
{
	if (n->args.size() == 0)
	{
		if (n->varId == -1)
			printf("%s", n->expr.c_str());
		else
			printf("a%d", n->varId);
		return;
	}

	int binaryIndex = findOp(n->expr);
	if (binaryIndex != -1)
	{
		printf("(");
		printExprNode(n->args[0]);
		printf(" %s ", binaryOps[binaryIndex].c_str());
		printExprNode(n->args[1]);
		printf(")");
	}
	else if (n->expr == "forall" || n->expr == "exists")
	{
		printf("%s ", n->expr.c_str());
		printExprNode(n->args[0]);
		printf(" ");
		printExprNode(n->args[1]);
	}
	else
	{
		printf("%s(", n->expr.c_str());
		for (int i = 0; i < n->args.size(); ++i)
		{
			printExprNode(n->args[i]);

			if (i < n->args.size() - 1)
				printf(",");
		}
		printf(")");
	}

	return;
}