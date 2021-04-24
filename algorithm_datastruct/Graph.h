/****************************************************************************
**
** Copyright (C) 2021 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef SparseGraph_
#define SparseGraph_

#include <vector>
#include <cassert>
#include <string>
#include <iostream>

#include "ReadGraph.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace DSA {
namespace Graph {
// test G1 in Sparse Graph:
// vertex 0:       5       1       2       6
// vertex 1:       0
// vertex 2:       0
// vertex 3:       4       5
// vertex 4:       3       6       5
// vertex 5:       0       4       3
// vertex 6:       4       0
// vertex 7:       8
// vertex 8:       7
// vertex 9:       12      10      11
// vertex 10:      9
// vertex 11:      12      9
// vertex 12:      9       11
	// 稀疏图，邻接表结构
class SparseGraph {
private:
	int vertex_count_, edge_count_;	// 点数，边数
	bool directed_;					// 是否为有向图
	vector<vector<int>> data_;		// 具体数据

public:
	SparseGraph(int vertex_count, bool directed) {
		assert(vertex_count > 0);

		this->vertex_count_	= vertex_count;
		this->edge_count_	= 0;
		this->directed_		= directed;

		// 初始化空数据
		this->data_ = vector<vector<int>>(vertex_count_, vector<int>());
	}

	~SparseGraph() {}

	int GetVertexCount() const { return vertex_count_; }
	int GetEdgeCount() const { return edge_count_; }

	// 向图中添加一个边
	void addEdge(int left_vertex, int right_vertex) {
		assert(left_vertex >= 0 && left_vertex < vertex_count_);
		assert(right_vertex >= 0 && right_vertex < vertex_count_);

		if (hasEdge(left_vertex, right_vertex)) { return; }

		data_[left_vertex].push_back(right_vertex);

		// 如果两个节点不相同且不是有向图
		if (left_vertex != right_vertex && !directed_) {
			data_[right_vertex].push_back(left_vertex);
		}

		++edge_count_;	
	}

	// 判断两个节点是否相连
	bool hasEdge(int left_vertex, int right_vertex) {
		assert(left_vertex >= 0 && left_vertex < vertex_count_);
		assert(right_vertex >= 0 && right_vertex < vertex_count_);

		if (data_.empty()) { return false; }

		for (const int vertex : data_[left_vertex]) {
			if (vertex == right_vertex) { return true; }
		}

		return false;	
	}

	// 显示图的信息
	void show() {
		for (int i = 0; i < vertex_count_; ++i) {
			cout << "vertex " << i << ":\t";
			for (int vertex : data_[i]) {
				cout << vertex << "\t";
			} // for vertex
			cout << endl;
		} // for i
	}
};

// 稠密图 - 邻接矩阵
class DenseGraph {
private:
	int vertex_count_, edge_count_;	// 点数，边数
	bool directed_;					// 是否为有向图
	vector<vector<bool>> data_;		// 具体数据

public:
	DenseGraph(int vertex_count, bool directed) {
		assert(vertex_count>0);

		this->vertex_count_		= vertex_count;
		this->edge_count_	= 0;
		this->directed_		= directed;
		// data_初始化为n*n矩阵，每一个data_[i][j]都为false， 表示没有任何的边
		this->data_ = vector<vector<bool>>(vertex_count_, vector<bool>(vertex_count_, false));	// 初始化空数据
	}

	~DenseGraph() {}

	int GetVertexCount() const { return vertex_count_; }
	int GetEdgeCount() const { return edge_count_; }

	// 向图中添加一个边
	void addEdge(int left_vertex, int right_vertex) {
		assert(left_vertex > 0 && left_vertex < vertex_count_);
		assert(right_vertex > 0 && right_vertex < vertex_count_);

		if (hasEdge(left_vertex, right_vertex)) { return; }

		data_[left_vertex][right_vertex] = true;

		// 注意并不判断left_vertex_ == right_vertex_
		if (!directed_) {
			data_[right_vertex][left_vertex] = true;
		}

		++edge_count_;	
	}

	// 判断两个节点是否相连
	bool hasEdge(int left_vertex, int right_vertex) {
		assert(left_vertex > 0 && left_vertex < vertex_count_);
		assert(right_vertex > 0 && right_vertex < vertex_count_);


		return data_[left_vertex][right_vertex];	
	}

	// 显示图的信息
	void show() {
		for (int i = 0; i < vertex_count_; ++i) {
			cout << "vertex " << i << ":\t";
			for (int vertex : data_[i]) {
				cout << vertex << "\t";
			} // for vertex
			cout << endl;
		} // for i
	}
};

	void test_graph() {
		// 测试sparse,dense graph
		string file_name = "../test_files/testG1.txt";
		SparseGraph sparse_graph(13, false);
		ReadGraph<SparseGraph> read_graph_1(sparse_graph, file_name);
		cout << "test G1 in Sparse Graph:" << endl;
		sparse_graph.show();
	}

}
}


#endif // SparseGraph_

