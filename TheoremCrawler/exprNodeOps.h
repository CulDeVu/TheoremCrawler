#pragma once

#include "exprNode.h"

int highestVarid(exprNode* n)
{
	if (n->varId != -1)
	{
		return n->varId;
	}

	int highest = -1;
	for (int i = 0; i < n->args.size(); ++i)
	{
		int a = highestVarid(n->args[i]);
		if (a > highest)
			highest = a;
	}

	return highest;
}

bool isFree(exprNode* n, int free)
{
	if (n->varId != -1)
	{
		return (n->varId != free);
	}

	bool ret = true;
	for (int i = 0; i < n->args.size(); ++i)
	{
		ret = ret && isFree(n->args[i], free);
	}

	return ret;
}
bool isFree(exprNode* n, exprNode* free)
{
	if (free->varId != -1)
	{
		return isFree(n, free->varId);
	}

	bool ret = true;
	for (int i = 0; i < free->args.size(); ++i)
	{
		ret = ret && isFree(n, free->args[i]);
	}

	return ret;
}

bool isEqual(exprNode* a, exprNode* b)
{
	if (a->expr != b->expr)
		return false;

	if (a->varId != b->varId)
		return false;

	if (a->args.size() != b->args.size())
		return false;

	for (int i = 0; i < a->args.size(); ++i)
	{
		if (!isEqual(a->args[i], b->args[i]))
			return false;
	}

	return true;
}

exprNode* copy(exprNode* n)
{
	exprNode* ret = new exprNode();

	ret->expr = n->expr;
	ret->varId = n->varId;

	for (int i = 0; i < n->args.size(); ++i)
	{
		exprNode* a = copy(n->args[i]);
		ret->args.push_back(a);
	}

	return ret;
}

void replace(exprNode* n, exprNode* old, exprNode* add)
{
	for (int i = 0; i < n->args.size(); ++i)
	{
		if (isEqual(n->args[i], old))
		{
			exprNode* a = copy(add);
			delete n->args[0];
			n->args[0] = a;
		}
		else
		{
			replace(n->args[i], old, add);
		}
	}
}