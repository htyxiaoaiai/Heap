#pragma once
#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

template<class T>
class BigHeap
{
public:
	//无参构造函数
	BigHeap()
	{}
	//有参构造函数
	BigHeap(const T* a, size_t size);
public:
	//插入
	void Push(const T& d);
	//删除最大的节点
	void Pop();
	//打印
	void Print();
protected:
	//向下调整
	void _AdjustDown(size_t parent);
	//向上调整
	void _AdjustUp(size_t child);
protected:
	vector<T> _a;//顺序表
};

template<class T>
BigHeap<T>::BigHeap(const T* a, size_t size)
{
	//断言
	assert(a);
	//将数组里面的内容拷贝到顺序表内
	for (size_t i = 0; i < size; i++)
	{
		_a.push_back(a[i]);
	}

	//从下往上构建堆

	//找到第一个非叶子结点并从后往前开始逐步调整
	for (int i = (_a.size() - 2) / 2; i >= 0; i--)
	{
		_AdjustDown(i);
	}

}

//向下调整
template<class T>
void BigHeap<T>::_AdjustDown(size_t parent)
{
	size_t child = parent * 2 + 1;//左孩子
	while (child < _a.size())//判断左孩子是否存在
	{
		//找到左右孩子中较大的
		if (child + 1 < _a.size() && _a[child + 1] > _a[child])
		{
			child++;
		}

		//孩子节点比父亲节点大，交换并且再次调整
		if (_a[child]>_a[parent])
		{
			swap(_a[child], _a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		//孩子节点比父亲节点小，不需要调整
		else
		{
			break;
		}
	}

}

//向上调整
template<class T>
void BigHeap<T>::_AdjustUp(size_t child)
{
	size_t parent = (child - 1) / 2;
	while (parent<_a.size() && parent>=0)//当父亲节点为根节点时不再调整
	{
		//如果孩子节点比父亲节点大，则交换位置，并继续向上调整
		if (_a[child] > _a[parent])
		{
			swap(_a[child], _a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		//孩子节点比父亲节点小不需要调整
		else
		{
			break;
		}
	}
}

//插入
template<class T>
void BigHeap<T>::Push(const T& d)
{
	//插入到顺序表中
	_a.push_back(d);

	//向上调整
	_AdjustUp(_a.size() - 1);
}

//删除最大的节点
template<class T>
void BigHeap<T> ::Pop()
{
	//断言顺序表不为空
	assert(!_a.empty());

	//交换第一个节点和最后一个节点
	swap(_a[0], _a[_a.size() - 1]);

	//删除最后一个节点
	_a.pop_back();

	//从第一个节点开始向下调整
	_AdjustDown(0);
}

//打印
template<class T>
void BigHeap<T>::Print()
{
	for (size_t i = 0; i < _a.size(); i++)
	{
		cout << _a[i] << " ";
	}
	cout << endl;
}

void TestBigHeap()
{
	int a[] = { 10 ,11, 13, 12, 16, 18, 15 ,17 ,14, 19 };
	BigHeap<int> hp1(a, sizeof(a) / sizeof(a[0]));
	hp1.Print();
	cout << "Push:" << endl;
	hp1.Push(20);
	hp1.Print();
	hp1.Push(9);
	hp1.Print();
	cout << "Pop:" << endl;
	hp1.Pop();
	hp1.Print();
	hp1.Pop();
	hp1.Print();
}