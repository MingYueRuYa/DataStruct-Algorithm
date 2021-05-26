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

	// 迭代器，统一遍历的接口
	// 迭代器，传入一个图和一个顶点
	// 迭代在这个图中和这个顶点相连的所有顶点
	class GraphIterator {
	private:
		SparseGraph &graph_;	// 图的引用
		int vertex_;				// 顶点
		int index_;				// 索引

	public:
		GraphIterator(SparseGraph &graph, int vertex): graph_(graph) {
			this->graph_ = graph;
			this->vertex_ = vertex;
		}

		~GraphIterator() = default;

		// 返回图中graph中与顶点vertex相连接的第一个顶点
		int begin() {

			index_ = 0;

			if (graph_.data_[vertex_].size()) {
				return graph_.data_[vertex_][index_];
			}

			// 若是没有顶点和v相连接，则返回-1
			return -1;
		}

		// 返回图中G与顶点vertex相连接的下一个顶点
		int next() {
			index_++;
			if (index_ < graph_.data_[vertex_].size()) {
				return graph_.data_[vertex_][index_];
			}

			return -1;
		}

		// 查看是否已经迭代完与图G中与顶点vertex相连接的所有顶点
		bool end() {
			return index_ >= graph_.data_[vertex_].size();
		}

	};
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
		assert(left_vertex >= 0 && left_vertex < vertex_count_);
		assert(right_vertex >= 0 && right_vertex < vertex_count_);

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
		assert(left_vertex >= 0 && left_vertex < vertex_count_);
		assert(right_vertex >= 0 && right_vertex < vertex_count_);


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

	// 迭代器，统一遍历的接口
	// 迭代器，传入一个图和一个顶点
	// 迭代在这个图中和这个顶点相连的所有顶点
	class GraphIterator {
	private:
		DenseGraph &graph_;	// 图的引用
		int vertex_;				// 顶点
		int index_;				// 索引

	public:
		GraphIterator(DenseGraph &graph, int vertex): graph_(graph) {
			this->graph_	= graph;
			this->vertex_	= vertex;
			this->index_	= -1;	// 索引从-1开始，因为每次遍历都需要调用一次next
		}

		~GraphIterator() = default;

		// 返回图中graph中与顶点vertex相连接的第一个顶点
		int begin() {

			index_ = -1;

			return next();
		}

		// 返回图中G与顶点vertex相连接的下一个顶点
		int next() {

			// 从当前index_开始向后搜索，直到找到一个graph_.data_[vertex_][index]为true
			for (index_ += 1; index_ < graph_.data_[vertex_].size(); ++index_) {
				if (graph_.data_[vertex_][index_]) {
					return index_;
				}
			} // index_

			return -1;
		}

		// 查看是否已经迭代完与图G中与顶点vertex相连接的所有顶点
		bool end() {
			return index_ >= graph_.GetVertexCount();
		}
	};

};

template <typename Graph>
class Component {
private:
	Graph graph_;	// 图的引用
	bool *visited_ = nullptr;	// 记录DFS的过程中是否被访问
	int ccount_	   = 0;	// 记录连通分量个数
	int *id_	   = nullptr;		// 每个节点所对应的连通分量标记

	void DFS(int vertex) {
		// 设置当前的点已经遍历过
		visited_[vertex] = true;
		// 设置当前的点属于哪个图
		id_[vertex] = ccount_;

		//遍历当前的点与之相关联的点
		typename Graph::GraphIterator itr(graph_, vertex);
		for (int tmp_vertex = itr.begin(); !itr.end(); tmp_vertex = itr.next()) {
			if (visited_[tmp_vertex]) { continue; }

			DFS(tmp_vertex);
		}
	}

public:
	// 构造函数，求出无权图的连通分量
	Component(Graph	&graph) : graph_(graph) {
		visited_	= new bool[graph_.GetVertexCount()];
		id_			= new int[graph_.GetVertexCount()];

		ccount_ = 0;

		for (int i = 0; i < graph_.GetVertexCount(); ++i) {
			visited_[i] = false;
			id_[i]		= -1;
		} // for i

		// 注意这里使用了i作为vertex的点，就需要图中的实际的点也是从0开始
		for (int i = 0; i < graph_.GetVertexCount(); ++i) {
			if (visited_[i]) { continue; }
			DFS(i);
			// 如果发现还有点没有遍历到，就说明存在2个以上的连通分量
			ccount_++;
		}

	}

	int GetCount() { return ccount_; }

};


	void test_graph() {
		// 测试sparse,dense graph
		string file_name = "../test_files/testG1.txt";
		SparseGraph sparse_graph(13, false);
		ReadGraph<SparseGraph> read_graph_1(sparse_graph, file_name);
		cout << "test G1 in Sparse Graph:" << endl;
		sparse_graph.show();

		cout << endl;
		
		DenseGraph dense_graph(13, false);
		ReadGraph<DenseGraph> read_graph_2(dense_graph, file_name);
		cout << "test G1 in Dense Graph:" << endl;
		dense_graph.show();
	}

	void test_graph_iterator() {
		// 测试sparse,dense graph
		string file_name = "../test_files/testG1.txt";
		SparseGraph sparse_graph(13, false);
		ReadGraph<SparseGraph> read_graph_1(sparse_graph, file_name);
		cout << "test G1 in Sparse Graph:" << endl;
		sparse_graph.show();

		for (size_t vertex = 0; vertex < 13; vertex++) {
			cout << vertex << " : ";

			SparseGraph::GraphIterator iterator(sparse_graph, vertex);
			for (int w = iterator.begin(); !iterator.end(); w = iterator.next()) {
				cout << w << " ";
			}

			cout << endl;
		}

		cout << endl;
		
		DenseGraph dense_graph(13, false);
		ReadGraph<DenseGraph> read_graph_2(dense_graph, file_name);
		cout << "test G1 in Dense Graph:" << endl;
		dense_graph.show();
		cout << endl;

		for (size_t vertex = 0; vertex < 13; vertex++) {
			cout << vertex << " : ";

			DenseGraph::GraphIterator iterator(dense_graph, vertex);
			for (int w = iterator.begin(); !iterator.end(); w = iterator.next()) {
				cout << w << " ";
			}

			cout << endl;
		}
	}

	void test_graph_dfs() {
		string file_name = "../test_files/testG1.txt";
		SparseGraph sparse_graph(13, false);
		ReadGraph<SparseGraph> read_graph_1(sparse_graph, file_name);
		cout << "test G1 in Sparse Graph:" << endl;

		Component<SparseGraph> sparse_component(sparse_graph);
		cout <<  "graph count:" << sparse_component.GetCount() << endl;

		file_name = "../test_files/testG2.txt";
		DenseGraph dense_graph(6, false);
		ReadGraph<DenseGraph> read_graph_2(dense_graph, file_name);
		cout << "test G2 in Dense Graph:" << endl;

		Component<DenseGraph> dense_component(dense_graph);
		cout <<  "graph count:" << dense_component.GetCount() << endl;
		
	}
}
}

#endif // SparseGraph_
