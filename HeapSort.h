#pragma once
#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

//向下调整
void AdjustDown(int *a, int size, int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && a[child] < a[child + 1])
		{
			child++;
		}

		if (a[child] > a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//堆排序
void HeapSort(int *a, int size)
{
	assert(a);
	//创建堆
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, size, i);
	}

	//将大根堆的第一个节点和最后一个互换，并将剩余的元素调整为一个堆
	for (int i = 0; i < size; i++)
	{
		swap(a[0], a[size - i - 1]);
		AdjustDown(a, size - i - 1, 0);
	}

}

//测试函数
void TestHeapSort()
{
	int a[10] = { 1,0,4,8,3,5,7,6,2,9 };
	HeapSort(a, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
