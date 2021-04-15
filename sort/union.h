/****************************************************************************
**
** Copyright (C) 2021 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef union_h
#define union_h

#include <ctime>
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

namespace DSA {
namespace Union {
	class UnionFind1
	{
	public:
		UnionFind1(int size) {
			_count	= size;
			_id		= new int[size];

			for (size_t i = 0; i < size; i++)
			{
				_id[i] = i;
			}
		}

		~UnionFind1() {
			delete[] _id;
		}

		// 查找过程，查找元素p所对应的集合编号
		int find(int p) {
			assert(p >= 0 && p < _count);

			return _id[p];
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			int qID = find(q);
			int pID = find(p);

			if (qID == pID) { return; }

			// 在合并过程中需要遍历一遍所有元素，将两个元素所属集合合并起来
			for (size_t i = 0; i < _count; i++) {
				if (_id[i] == qID) {
					_id[i] = pID;
				} // if
			} // for i

		}

	private:
		int *_id;	// 这一版本的union的本质就是一个数组
		int _count; // 数据个数

	};

	// 测试第一种方案的union find，测试元素为size
	void test_uf1() {
		int size = 1000000;

		srand(time(nullptr));

		UnionFind1 uf1(size);
		time_t start_time = clock();

		// 进行size次操作，随机选择两个元素进行合并
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			uf1.unionElements(a, b);
		}

		// 在进行size操作，随机选择两个元素，查询他们是否属于同一个集合
		// 注意这里的复杂度为n^2
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			uf1.isConnected(a, b);
		}
		time_t end_time = clock();
		
		cout << "UF1, " << 2*size << " time:" << double(end_time-start_time)/CLOCKS_PER_SEC << " s" << endl;

	}

	
}
}


#endif // union_h
