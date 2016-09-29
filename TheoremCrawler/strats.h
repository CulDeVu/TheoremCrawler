#pragma once

#include "assumpt.h"
#include "exprNode.h"
#include "exprNodeOps.h"

exprNode* I_and(exprNode* a, exprNode* b)
{
	exprNode* ret = new exprNode();
	ret->expr = "and";

	exprNode* a_new = copy(a);
	exprNode* b_new = copy(b);

	ret->args.push_back(a_new);
	ret->args.push_back(b_new);
	return ret;
}

exprNode* E_forall(exprNode* n, exprNode* free)
{
	bool b = isFree(n, free);
	if (!b)
	{
		printf("not valid substitution\n");
		return n;
	}

	exprNode* ret = copy(n->args[1]);
	replace(ret, n->args[0], free);

	return ret;
}

exprNode* I_forall(exprNode* n, exprNode* free)
{
	return n;
}

exprNode* randomVictim(assumptStack* global)
{
	assumptStack* last = global;
	int numFacts = 0;
	while (last != 0)
	{
		numFacts += last->facts.size();
		last = last->subAssumpt;
	}

	int r = rand() % numFacts;

	last = global;
	while (true)
	{
		if (r < last->facts.size())
		{
			return last->facts[r];
		}

		r -= last->facts.size();
		last = last->subAssumpt;
	}
}

void strat_I_and(assumptStack* global)
{
	assumptStack* last = global;
	while (last->subAssumpt != 0)
		last = last->subAssumpt;

	exprNode* v1 = randomVictim(global);
	exprNode* v2 = randomVictim(global);

	exprNode* result = I_and(v1, v2);
	last->facts.push_back(result);
}

void strat_E_forall(assumptStack* global)
{
	assumptStack* last = global;
	while (last->subAssumpt != 0)
		last = last->subAssumpt;

	// grab some random victim to apply the strat to
	exprNode* victim = 0;
	while (true)
	{
		victim = randomVictim(global);
		if (victim->expr != "forall")
			continue;
		break;
	}

	// create the variable to replace with
	int r = rand() % 100 + 100;
	exprNode* f = new exprNode();
	f->varId = r;

	exprNode* next = E_forall(victim, f);

	assumptStack* nextStack = new assumptStack();
	nextStack->localVarid = r;
	nextStack->facts.push_back(next);

	last->subAssumpt = nextStack;
}

void pickStrat(assumptStack* global)
{
	int r = rand() % 2;

	if (r == 0)
		strat_E_forall(global);
	else if (r == 1)
		strat_I_and(global);
}