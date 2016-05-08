题目描述

2015年春节期间，A公司的支付软件某宝和T公司某信红包大乱战。春节后高峰以后，公司Leader要求后台的工程师对后台的海量数据进行分析。
先要求分析出各地区发红包金额最多的前100用户。现在知道人数最多的s地区大约有1000w用户。要求写一个算法实现。【扩展：海量数据处理】

思路分析：
由于数据量太大，内存中根本不可能放下那么多的数据，所以只能将部分的数据加入内存，现在假设将前K个数据放入内存中，并将其构建成小根堆
（因为需要找出最大的K个，所以需要留小较大的元素，而堆只能从最上边的元素出去，所以采用小根堆，将较大的都留下来）

如果数据小根堆的堆顶元素要大，则直接覆盖,并重新构建成小根堆

#pragma once
#include<iostream>
#include<assert.h>
#include<time.h>

using namespace std;

//使用long long 是防止数据个数太大越界
//在实际中由于数据量比较大可能需要从磁盘读写，而不是直接从数组中读取，这里为了方便所以建立一个数组模拟

const long long N = 10000;//所有红包的个数
const long long K = 100;//需要查找最大的个数

//向下调整
void AjustDown(int* a, long long parent)
{
	int child = parent * 2 + 1;
	while (child < K)
	{
		//寻找较小的孩子
		if (child + 1 < K&&a[child + 1] < a[child])
		{
			child++;
		}

		//孩子节点小于根节点，则交换并再次调整
		if (a[child] < a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		//孩子节点大于根节点，已经是小根堆不需要处理
		else
		{
			break;
		}
	}
}

//找到最大的K个元素
void FindTopK(int a[], int topK[])
{
	assert(a && topK);
	assert(K < N);
	//首先将前K个放入数组
	for (long long i = 0; i < K; i++)
	{
		topK[i] = a[i];
	}

	//将topK构建成小根堆,(因为需要保留比跟节点要大的元素)
	for (long long i = (K - 2) / 2; i >= 0; i--)
	{
		AjustDown(topK, i);
	}

	//遍历大的数据，如果元素比小根堆的顶点大，则修改，并重新调整为小根堆
	for (long long i = K; i < N; i++)
	{
		if (a[i] > topK[0])
		{
			topK[0]=a[i];
			AjustDown(topK, 0);
		}
	}
}


void TestRedPacket()
{
	int a[N] = { 0 };
	int b[K] = { 0 };
	//产生随机的种子
	srand(time(0));
	for (long long i = 0; i < N; i++)
	{
		a[i] =( rand()%10000);//将数据控制在10000以内
	}

	//将后边的数据控制在10000以上
	for (long long i = K; i < N; i++)
	{
		a[i] += 10000;
	}
	//数据对比明显

	//查找
	FindTopK(a, b);

	for (long long i = 0; i < K; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;

}
