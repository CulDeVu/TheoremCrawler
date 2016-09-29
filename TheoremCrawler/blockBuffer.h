#pragma once

template <typename T>
struct blockBuffer
{
	vector<T> data;

	blockBuffer* prev;
	blockBuffer* next;

	blockBuffer()
	{
		next = prev = 0;
	}
	~blockBuffer()
	{
		delete next;
	}

	blockBuffer* getLast()
	{
		if (next == 0)
			return this;
		return next->getLast();
	}

	void push(T d)
	{
		blockBuffer* a = getLast();
		a->data.push_back(d);
	}

	blockBuffer* createNewBlock()
	{
		blockBuffer* n = new blockBuffer();
		
		blockBuffer* a = getLast();
		a->next = n;

		return n;
	}

	void destroy()
	{
		prev->next = 0;
		data.clear();
		next->destroy();
	}
	void destroyDelete()
	{
		prev->next = 0;
		for (int i = 0; i < data.size(); ++i)
			delete data[i];
		data.clear();
		next->destroyDelete();
	}
};