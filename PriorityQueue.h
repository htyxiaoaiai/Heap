#pragma once
#include"Heap.h"

//堆实现优先级队列
template<class T>
class PriorityQueue
{
public:
	//插入
	void Push(const T& d)
	{
		_q.Push();
	}
	//删除
	void Pop()
	{
		_q.Pop();
	}
private:
	BigHeap<T> _q;//
};

插入和删除的算法复杂度均为O(lgN);
对于较大的数据，远远由于数组实现的优先级队列
数组实现
插入：push  O(1)
删除：pop   O(N)
