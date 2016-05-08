#pragma once
#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;


//仿函数重载()
template<class T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template <class T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

//注意模板参数
template<class T, class compare = Greater<T>>
class Heap
{
public:
	//无参构造函数
	Heap()
	{}
	//有参构造函数
	Heap(const T* a, size_t size)
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
public:
	//插入
	void Push(const T& d)
	{
		//插入到顺序表中
		_a.push_back(d);

		//向上调整
		_AdjustUp(_a.size() - 1);
	}
	//删除最大的节点
	void Pop()
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
	void Print()
	{
		for (size_t i = 0; i < _a.size(); i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
	}

protected:
	//向下调整
	void _AdjustDown(size_t parent)
	{
		size_t child = parent * 2 + 1;
		//左孩子
		while (child < _a.size())//判断左孩子是否存在
		{
			//找到左右孩子中较大的
			compare com;
			/*if (child + 1 < _a.size() && _a[child + 1] > _a[child])*/
			if (child + 1 < _a.size() && com(_a[child + 1], _a[child]))
			{
				child++;
			}

			//孩子节点比父亲节点大，交换并且再次调整
			/*if (_a[child]>_a[parent])*/
			if (com(_a[child], _a[parent]))
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
	void _AdjustUp(size_t child)
	{
		size_t parent = (child - 1) / 2;
		while (parent<_a.size() && parent >= 0)//当父亲节点为根节点时不再调整
		{
			//如果孩子节点比父亲节点大，则交换位置，并继续向上调整
			/*if (_a[child] > _a[parent])*/
			compare com;
			if (com(_a[child], _a[parent]))
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
protected:
	vector<T> _a;//顺序表
};
