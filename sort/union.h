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

	class UnionFind2
	{
	public:
		UnionFind2(int size) {
			_count		= size;
			_parent		= new int[size];

			for (size_t i = 0; i < size; i++) {
				_parent[i] = i;
			}
		}

		~UnionFind2() {
			delete[] _parent;
		}

		// 查找过程，查找元素p所对应的集合编号
		// 返回的就是父节点ID
		int find(int p) {
			assert(p >= 0 && p < _count);

			while (p != _parent[p]) {
				p = _parent[p];	
			}

			return p;
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

			int q_root = find(q);
			int p_root = find(p);

			// 已经在连接
			if (q_root == p_root) { return; }

			// 将其中的一个父节点的父节点设置另外一个父节点
			_parent[p_root] = q_root;

		}

	private:
		int *_parent;	// 这一版本的union的本质就是一个数组
		int _count; // 数据个数
	};

	// 测试第一种方案的union find，测试元素为size
	// 这种算法中isConnected只需要O(1)时间，但是由于union操作需要O(n)时间
	// 总体测试过程的算法复杂度是O(n^2)
	void test_uf1(int size) {
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

	void test_uf2(int size) {
		srand(time(nullptr));

		UnionFind2 uf2(size);
		time_t start_time = clock();

		// 进行size次操作，随机选择两个元素进行合并
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			uf2.unionElements(a, b);
		}

		// 在进行size操作，随机选择两个元素，查询他们是否属于同一个集合
		// 注意这里的复杂度为n^2
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			uf2.isConnected(a, b);
		}
		time_t end_time = clock();
		
		cout << "UF2, " << 2*size << " time:" << double(end_time-start_time)/CLOCKS_PER_SEC << " s" << endl;
	}

	
	void test_uf(int size) {
		// 注意在union find 1和union find 2的时候
		// 我是用了100000数据作为模拟，实际上却发现uf1使用了48S，而uf2却使用了58S
		// 这是个很奇怪的现象，我目前无法解释为什么
		// 按照理论来说unionfind2的复杂度为O(n*log n)，要比unionfind1要低很多
		// log n 为树的高度
		test_uf1(size);
		test_uf2(size);
	}

}
}


#endif // union_h
