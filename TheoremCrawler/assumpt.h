#pragma once

#include "blockBuffer.h"
#include "exprNode.h"

//typedef blockBuffer<assumptNode*> assumptBuffer;

struct assumptNode
{
	static blockBuffer<assumptNode*> assumpts;
	static blockBuffer<exprNode*> facts;
	static blockBuffer<exprNode*> constants;

	blockBuffer<exprNode*>* factsNode;

	exprNode* assumpt;
	int localVarid;
};

struct assumptStack
{
	static blockBuffer<assumptNode*> assumpts;
	static blockBuffer<exprNode*> factsB;
	static blockBuffer<exprNode*> constants;

	blockBuffer<exprNode*>* factsNode;
	
	vector<exprNode*> facts;

	exprNode* ass;
	int localVarid;

	assumptStack* subAssumpt;

	assumptStack()
	{
		factsNode = 0;
		
		ass = 0;
		localVarid = -1;
		subAssumpt = 0;
	}
};

