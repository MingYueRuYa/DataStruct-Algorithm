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
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;

namespace DSA {
namespace Union {
	class UnionFind 
	{
	public:
		UnionFind() {}
		virtual ~UnionFind() { cout << "~UnionFind" << endl; }

		virtual int find(int p) = 0;
		virtual int isConnected(int p, int q) = 0;
		virtual void unionElements(int p, int q) = 0;
		virtual void printData() = 0;
	};

	class UnionFind1 : public UnionFind
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
			cout << "~UnionFind1" << endl; 
		}

		// 查找过程，查找元素p所对应的集合编号
		int find(int p) override {
			assert(p >= 0 && p < _count);

			return _id[p];
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) override {
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

		void printData() override {

		}

	private:
		int *_id;	// 这一版本的union的本质就是一个数组
		int _count; // 数据个数

	};

	// 第二种优化方案：采用树形结构
	// 如果两个节点有共同的根节点，则认为是连通的。
	class UnionFind2: public UnionFind
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
			cout << "~UnionFind2" << endl; 
		}

		// 查找过程，查找元素p所对应的集合编号
		// 返回的就是父节点ID
		int find(int p) override {
			assert(p >= 0 && p < _count);

			// 根节点的特征p = _parent[p]
			while (p != _parent[p]) {
				p = _parent[p];	
			}

			return p;
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			int q_root = find(q);
			int p_root = find(p);

			// 已经在连接
			if (q_root == p_root) { return; }

			// 将其中的一个父节点的父节点设置另外一个父节点
			_parent[p_root] = q_root;
		}

		void printData() override {}

	private:
		int *_parent;	// 这一版本的union的本质就是一个数组
		int _count; // 数据个数
	};

	// 第三种优化方案：采用树形结构，优化union操作，将子节点数目多的根节点设置为子节点，其本质是为了降低数据的高度
	// 如果两个节点有共同的根节点，则认为是连通的。
	class UnionFind3 : public UnionFind
	{
	public:
		UnionFind3(int size) {
			_count		= size;
			_parent		= new int[size];
			_size		= new int[size];

			for (size_t i = 0; i < size; i++) {
				_parent[i] = i;
				// 默认都是一个，表示自己和自己连通
				_size[i] = 1;
			}
		}

		~UnionFind3() {
			delete[] _parent;
			delete[] _size;
			cout << "~UnionFind3" << endl; 
		}

		// 查找过程，查找元素p所对应的集合编号
		// 返回的就是父节点ID
		int find(int p) override {
			assert(p >= 0 && p < _count);

			// 根节点的特征p = _parent[p]
			while (p != _parent[p]) {
				p = _parent[p];	
			}

			return p;
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			int q_root = find(q);
			int p_root = find(p);

			// 已经在连接
			if (q_root == p_root) { return; }

			// 如果q_root给根节点元素个数<p_root
			// 则将q_root设置为子节点
			if (_size[q_root] < _size[p_root]) {
				_parent[q_root] = p_root;
				_size[p_root] += _size[q_root];
			} else {
				_parent[p_root] = q_root;
				_size[q_root] += _size[p_root];
			}
		}

		void printData() override {}

	private:
		int *_parent;	// 这一版本的union的本质就是一个数组
		int _count;		// 数据个数
		int *_size;		// _size[i]表示以i为根集合中元素个数
	};

	// 第四种优化方案：采用树形结构，
	// 同样是优化union操作，采用的是那个根节点的层数少，就作为新的根节点
	// 如果两个节点有共同的根节点，则认为是连通的。
	class UnionFind4 : public UnionFind
	{
	public:
		UnionFind4(int size) {
			_count		= size;
			_parent		= new int[size];
			_rank		= new int[size];

			for (size_t i = 0; i < size; i++) {
				_parent[i] = i;
				// 默认都是一个，表示自己和自己连通
				_rank[i] = 1;
			}
		}

		~UnionFind4() {
			delete[] _parent;
			delete[] _rank;
			cout << "~UnionFind4" << endl; 
		}

		// 查找过程，查找元素p所对应的集合编号
		// 返回的就是父节点ID
		int find(int p) override {
			assert(p >= 0 && p < _count);

			// 根节点的特征p = _parent[p]
			while (p != _parent[p]) {
				p = _parent[p];	
			}

			return p;
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			int q_root = find(q);
			int p_root = find(p);

			// 已经是连接
			if (q_root == p_root) { return; }

			if (_rank[q_root] < _rank[p_root]) {
				_parent[q_root] = p_root;
			} else if (_rank[q_root] > _rank[p_root]) {
				_parent[p_root] = q_root;
			} else { // _rank[q_root] = _rank[p_root]
				_parent[q_root] = p_root;
				_rank[p_root]++;
			}
		}

		void printData() override {}

	private:
		int *_parent;	// 这一版本的union的本质就是一个数组
		int _count;		// 数据个数
		int *_rank;		// _size[i]表示以i为根集合中元素个数
	};


	// TODO 需要做个试验验证下
	// 第五种优化方案：采用树形结构，
	// 优化find操作，采用的是路径压缩，其本质就是还是减少树的高度
	// 比如：							经过路径压缩之后
	//			 1								1
	//			/							   / \
	//		   2							  2	  3
	//		  /									 / \
	//		 3									4   5
	//		/
	//	   4
	//	  /
	//   5
	// 
	class UnionFind5 : public UnionFind
	{
	public:
		UnionFind5(int size) {
			_count		= size;
			_parent		= new int[size];
			_rank		= new int[size];

			for (size_t i = 0; i < size; i++) {
				_parent[i] = i;
				// 默认都是一个，表示自己和自己连通
				_rank[i] = 1;
			}
		}

		~UnionFind5() {
			delete[] _parent;
			delete[] _rank;
			cout << "~UnionFind5" << endl; 
		}

		// 查找过程，查找元素p所对应的集合编号
		// 返回的就是父节点ID
		int find(int p) override {
			assert(p >= 0 && p < _count);

			// 根节点的特征p = _parent[p]
			// 隔一个父节点，设置父节点
			while (p != _parent[p]) {
				// 设置p的父节点为为p的第二个父节点
				// 如上图所示：设置5的父节点为3
				_parent[p] = _parent[_parent[p]];
				p = _parent[p];
			}

			return p;
		}

		// 查看p，q是否属于一个集合里面
		int isConnected(int p, int q) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			return find(q) == find(p);
		}

		// 合并元素q和元素p所属的集合
		void unionElements(int q, int p) override {
			assert(p >= 0 && p < _count);
			assert(q >= 0 && q < _count);

			int q_root = find(q);
			int p_root = find(p);

			// 已经是连接
			if (q_root == p_root) { return; }

			if (_rank[q_root] < _rank[p_root]) {
				_parent[q_root] = p_root;
			} else if (_rank[q_root] > _rank[p_root]) {
				_parent[p_root] = q_root;
			} else { // _rank[q_root] = _rank[p_root]
				_parent[q_root] = p_root;
				_rank[p_root]++;
			}
		}

		void printData() override {
			for (size_t i = 0; i < _count; i++) {
				cout << _parent[i] << " ";
			}
			cout << endl;
		}

	private:
		int *_parent;	// 这一版本的union的本质就是一个数组
		int _count;		// 数据个数
		int *_rank;		// _size[i]表示以i为根集合中元素个数
	};

	// 这种算法中isConnected只需要O(1)时间
	// union find 1 算法复杂度是O(n^2)
	// union find 2 算法复杂度是O(n * log h)
	// union find 3 算法复杂度是O(n * log h)
	// union find 4 算法复杂度是O(n * log h)
	// union find 5 算法复杂度是O(n * log h)
	void test_uf(int unionFindType, int size) {
		srand(time(nullptr));

		shared_ptr<UnionFind> union_find;

		switch (unionFindType)
		{
		case 1:
			union_find.reset(new UnionFind1(size));
			break;
		case 2:
			union_find.reset(new UnionFind2(size));
			break;
		case 3:
			union_find.reset(new UnionFind3(size));
			break;
		case 4:
			union_find.reset(new UnionFind4(size));
			break;
		case 5:
			union_find.reset(new UnionFind5(size));
			break;
		default:
			assert(false);
			break;
		}

		time_t start_time = clock();

		// 进行size次操作，随机选择两个元素进行合并
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			union_find->unionElements(a, b);
		}

		// 在进行size操作，随机选择两个元素，查询他们是否属于同一个集合
		// 注意这里的复杂度为n^2
		for (size_t i = 0; i < size; i++) {
			int a = rand()%size;
			int b = rand()%size;
			union_find->isConnected(a, b);
		}
		time_t end_time = clock();
		
		cout << "UF" << unionFindType << ", " << 2*size << " time:" << double(end_time-start_time)/CLOCKS_PER_SEC << " s" << endl;

		union_find->printData();

	}

	void test_uf(int size) {
		// 注意在union find 1和union find 2的时候
		// 我是用了100000数据作为模拟，实际上却发现uf1使用了48S，而uf2却使用了58S
		// 这是个很奇怪的现象，我目前无法解释为什么
		// 按照理论来说unionfind2的复杂度为O(n*log n)，要比unionfind1要低很多
		// log n 为树的高度
		// test_uf(1, size);
		// test_uf(2, size);
		test_uf(3, size);
		test_uf(4, size);
		test_uf(5, size);
	}

}
}

#endif // union_h