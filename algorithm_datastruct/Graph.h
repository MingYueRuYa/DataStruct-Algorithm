/****************************************************************************
**
** Copyright (C) 2021 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef SparseGraph_
#define SparseGraph_

#include "edge.h"
#include "ReadGraph.h"

#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::string;
using std::shared_ptr;
using std::make_shared;

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

	~Component() {
		delete[] visited_;
		delete[] id_;
	}

	int GetCount() { return ccount_; }

};

template <typename Graph>
class Path {
private:
	Graph &graph_;
	int vertex_;
	shared_ptr<bool []> visited_;	// 记录DFS过程中节点是否被访问过
	shared_ptr<int []> from_;	// 记录路径，from[i]表示查找路径的之前的一个节点
								// from[2] = 1 from[3] = 2 from[4] = 3

	void DFS(int vertex) {
		visited_[vertex] = true;
		typename Graph::GraphIterator itr(graph_, vertex);
		for (int temp_vertex = itr.begin(); !itr.end(); temp_vertex = itr.next()) {
			if (visited_[temp_vertex]) { continue; }

			// 注意这里的复制操作
			// 1	2	3	4
			// -1	1	2	3
			// 这个节点从上vertex过来的，可以理解为temp_vertex父亲是vertex
			from_[temp_vertex] = vertex;
			DFS(temp_vertex);
		}
	}

public:
	Path(Graph &graph, int vertex) :graph_(graph), vertex_(vertex) {
		visited_ = shared_ptr<bool []>(new bool[graph_.GetVertexCount()]);
		from_	 = shared_ptr<int []>(new int[graph_.GetVertexCount()]);

		for (int i = 0; i < graph_.GetVertexCount(); ++i) {
			visited_[i] = false;
			// 先初始化为为-1
			from_[i]	= -1;
		}

		DFS(vertex_);
	}

	~Path() {}

	// 如果当前节点已经访问过了，则表示存在路径
	bool HasPath(int vertex) {
		return visited_[vertex];
	}

	// 返回路径
	void GetPath(int vertex, vector<int> &pathVec) {
		assert(HasPath(vertex));

		stack<int> pathstack;
		int temp_vertex = vertex;
		// 以逆序的方式，回溯到source 顶点
		// 比如刚开始的时候：1 2 3 4 5
		// 此时以逆序的方式加入到stack中 5 4 3 2 1 
		// 然后在倒叙出来就是1 2 3 4 5 
		while (-1 != temp_vertex) {
			pathstack.push(temp_vertex);
			temp_vertex = from_[temp_vertex];
		}

		pathVec.clear();

		while (!pathstack.empty()) {
			pathVec.push_back(pathstack.top());
			pathstack.pop();
		}
	}

	void ShowPath(int vertex) {

		assert(HasPath(vertex));

		vector<int> pathVec;
		GetPath(vertex, pathVec);

		for (int i = 0 ; i < pathVec.size(); ++i) {
			cout << pathVec[i];
			if (i == pathVec.size()-1) {
				cout << endl;
			} else {
				cout << " --> ";
			}
		}
	}

};

// BFS 广度优先遍历
// 寻找无向图的最短路径:本质和树的层序遍历思想一致
template <typename Graph>
class ShortestPath {
private:
	Graph &graph_;	// 图的引用
	int start_;		// 起始点
	shared_ptr<bool []> visited_;	// 记录BFS过程中节点是否被访问过
	shared_ptr<int []> from_;		// 记录路径，from[i]表示查找路径i的上一个节点
	shared_ptr<int []> ord_;		// 记录路径中节点的次序.ord_[i]表示i节点在路径中的次序

public:
	// 构造函数，寻找无权图graph从S点到其他点的最短路径
	ShortestPath(Graph &graph, int start): graph_(graph), start_(start){
		assert(start_ >= 0 && start_ < graph.GetVertexCount());

		int vertex_count = graph.GetVertexCount();
		// visited_	= make_shared<bool []>(vertex_count);
		visited_	= shared_ptr<bool []>(new bool[vertex_count]());
		from_	= shared_ptr<int []>(new int[vertex_count]());
		ord_	= shared_ptr<int []>(new int[vertex_count]());

		for (int i = 0; i < vertex_count ; ++i) {
			visited_[i] = false;
			from_[i] = -1;
			ord_[i] = -1;
		}

		std::queue<int> graph_queue;
		graph_queue.push(start_);

		visited_[start_] = true;
		ord_[start_] = 0;

		while (! graph_queue.empty()) {
			int vertex = graph_queue.front();
			graph_queue.pop();

			typename Graph::GraphIterator itr(graph_, vertex);
			for (int temp_vertex = itr.begin(); !itr.end(); temp_vertex = itr.next()) {
				// 如果已经访问过的点，则不需要在访问
				if (visited_[temp_vertex]) { continue; }

				graph_queue.push(temp_vertex);

				// 设置已经访问过
				visited_[temp_vertex] = true;
				// 路径+1
				ord_[temp_vertex] = ord_[vertex] + 1;
				from_[temp_vertex] = vertex;

			} // for temp_vertex
		} // while graph_queue.emtpy
	}

	~ShortestPath() {}

	// 从start到vertex是否有路径
	bool HasPath(int vertex)
	{
		return visited_[vertex];
	}

	void Path(int end, vector<int> &pathVec) {
		assert(end > 0 && graph_.GetVertexCount());	

		stack<int> graph_stack;
		// 从from数组逆向查找从s到w的路径，存放到栈中
		int temp_end = end;
		while (temp_end != -1) {
			graph_stack.push(temp_end);	
			temp_end = from_[temp_end];
		}

		// 从栈中依次取出元素，获得顺序的从s到w的路径
		pathVec.clear();

		while (!graph_stack.empty()) {
			pathVec.push_back(graph_stack.top());
			graph_stack.pop();
		}

	}

	void ShowPath(int vertex) {
		assert(HasPath(vertex));
		assert(vertex > 0 && graph_.GetVertexCount());

		vector<int> path_vec;
		Path(vertex, path_vec);
		for (int i = 0; i < path_vec.size(); ++i) {
			cout << path_vec[i];	
			if (i == path_vec.size()-1) { cout << endl; }
			else { cout << "--> "; }
		} // for i
	}

	// 获取最短路径的长度
	int Length(int vertex) {
		assert(vertex > 0 && graph_.GetVertexCount());

		return ord_[vertex];
	}

};

// 稠密图 - 邻接矩阵
template<typename Weight>
class WeightDenseGraph {

using GraphData = Edge<Weight>;
using SharedGraphData = shared_ptr<GraphData>;

private:
	int _vertexs, _edges;	// 点和边数量
	bool _directed;			// 是否为有向图
	vector<vector<SharedGraphData>> _data;	// 图的具体数据

public:	
	WeightDenseGraph(int vertexs, bool directed) : _vertexs(vertexs), 
													_edges(0),
													_directed(directed) {
		_data = vector<vector<SharedGraphData>>(_vertexs, vector<SharedGraphData>(_vertexs, nullptr));
	}

	~WeightDenseGraph() {
	}

	int GetVertexCount() { return _vertexs; }
	int GetEdgeCount() { return _edges; }

	// 添加一条边
	void addEdge(int vertex1, int vertex2, Weight weight) {
		assert(vertex1 >= 0 && vertex1 < _vertexs);
		assert(vertex2 >= 0 && vertex2 < _vertexs);

		//1.先要将原来的边删除，在添加新的边
		if (hasEdge(vertex1, vertex2)) {

			_data[vertex1][vertex2].reset();
			// _data[vertex1][vertex2] = nullptr;
			--_edges;

			if (vertex1 != vertex2 && !_directed) {
				_data[vertex2][vertex1].reset();
				--_edges;
			}
		}

		 _data[vertex1][vertex2] = SharedGraphData(new GraphData(vertex1, vertex1, weight));

		if (vertex1 != vertex2 && !_directed) {
			 _data[vertex2][vertex1] = SharedGraphData(new GraphData(vertex2, vertex1, weight));
			++_edges;
		}

		++_edges;
	}

	// 检查vertex1和vertex2是否有边
	bool hasEdge(int vertex1, int vertex2) {
		assert(vertex1 >= 0 && vertex1 < _vertexs);
		assert(vertex2 >= 0 && vertex2 < _vertexs);

		return _data[vertex1][vertex2].use_count() != 0;

		// return _data[vertex1][vertex2] != nullptr;
	}

	// 显示图的信息
	void show() {
		for (int i = 0; i < _vertexs; ++i) {
			for (int j = 0; j < _data[i].size(); ++j) {
				// cout << "(to: " << _data[i][j]->vertex2() << ", weight:" << _data[i][j]->weight() << ")\t";
				if (0 == _data[i][j].use_count()) { cout << "NULL\t"; }
				else { cout << _data[i][j]->weight() << "\t"; }
			}	// for j
			cout << "\n";
		} // for i
	}

	// 邻边迭代器, 传入一个图和一个顶点,
	 // 迭代在这个图中和这个顶点向连的所有边
	class adjIterator {
	private:
		WeightDenseGraph& G; // 图G的引用
		int _vertex;
		int _index;

	public:
		// 构造函数
		adjIterator(SparseGraph& graph, int v) : G(graph) {
			this->_vertex = v;
			this->_index = -1;
		}

		~adjIterator() {}

		// 返回图G中与顶点v相连接的第一个边
		SharedGraphData begin() {
			_index = -1;
			return next();
		}

		// 返回图G中与顶点v相连接的下一个边
		SharedGraphData next() {
			_index += 1;
			if (_index < G.g[_vertex].size()) {
				return G.g[_vertex][_index].use_count() == 0 ? SharedGraphData() : G.g[_vertex][_index];
			}
			return SharedGraphData();
		}

		// 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
		bool end() {
			return _index >= G.g[_vertex].size();
		}
	};

};


// 稀疏图 - 邻接表
template<typename Weight>
class WeightSparseGraph {

using GraphData = Edge<Weight>;
using SharedGraphData = shared_ptr<GraphData>;

private:
	int _vertexs, _edges;	// 点和边数量
	bool _directed;			// 是否为有向图
	vector<vector<SharedGraphData>> _data;	// 图的具体数据

public:	
	WeightSparseGraph(int vertexs, bool directed) : _vertexs(vertexs), 
													_edges(0),
													_directed(directed) {
		_data = vector<vector<SharedGraphData>>(_vertexs, vector<SharedGraphData>(0, nullptr));
	}

	~WeightSparseGraph() {
	}

	int GetVertexCount() { return _vertexs; }
	int GetEdgeCount() { return _edges; }

	// 添加一条边
	void addEdge(int vertex1, int vertex2, Weight weight) {
		assert(vertex1 >= 0 && vertex1 < _vertexs);
		assert(vertex2 >= 0 && vertex2 < _vertexs);

		// 注意：由于在邻接表的情况，查找是否有重边需要遍历整个链表	
		// 这里我们允许出现重复的边
		_data[vertex1].push_back(SharedGraphData(new GraphData(vertex1, vertex2, weight)));
		if (vertex1 != vertex2 && !_directed) {
			_data[vertex2].push_back(SharedGraphData(new GraphData(vertex2, vertex1, weight)));
		}
		// 维护边的数据
		_edges++;
	}

	// 检查vertex1和vertex2是否有边
	bool hasEdge(int vertex1, int vertex2) {
		assert(vertex1 >= 0 && vertex1 < _vertexs);
		assert(vertex2 >= 0 && vertex2 < _vertexs);

		for (int i = 0; i < _data[vertex1].size(); ++i) {
			if (vertex2 == _data[vertex1][i]->other(vertex1)) { return true; }
		}
		return false;
	}

	// 显示图的信息
	void show() {
		for (int i = 0; i < _vertexs; ++i) {
			cout << "vertex " << i << "\t";
			for (int j = 0; j < _data[i].size(); ++j) {
				cout << "(to: " << _data[i][j]->vertex2() << ", weight:" << _data[i][j]->weight() << ")\t";
			}	// for j
			cout << "\n";
		} // for i
	}

	// 邻边迭代器, 传入一个图和一个顶点,
	 // 迭代在这个图中和这个顶点向连的所有边
	class adjIterator {
	private:
		WeightSparseGraph& G; // 图G的引用
		int _vertex;
		int _index;

	public:
		// 构造函数
		adjIterator(WeightSparseGraph& graph, int v) : G(graph) {
			this->_vertex = v;
			this->_index = 0;
		}

		~adjIterator() {}

		// 返回图G中与顶点v相连接的第一个边
		SharedGraphData begin() {
			_index = 0;
			if (!G._data[_vertex].empty())
				return G._data[_vertex][_index];
			// 若没有顶点和v相连接, 则返回NULL
			return NULL;
		}

		// 返回图G中与顶点v相连接的下一个边
		SharedGraphData next() {
			_index += 1;
			if (_index < G._data[_vertex].size())
				return G._data[_vertex][_index];
			return NULL;
		}

		// 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
		bool end() {
			return _index >= G._data[_vertex].size();
		}
	};

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

	void test_graph_show_path() {
		string file_name = "../test_files/testG2.txt";
		DenseGraph dense_graph(6, false);
		ReadGraph<DenseGraph> read_graph_2(dense_graph, file_name);
		cout << "test G2 in Dense Graph:" << endl;

		Path<DenseGraph> dense_path(dense_graph, 0);
		// 节点6不存在
		dense_path.ShowPath(6);

	}

	// 测试无权图最短路径算法
	void test_shortest_path_graph() {
		string file_name = "../test_files/testG2.txt";
		SparseGraph sparse_graph(6, false);
		ReadGraph<SparseGraph> read_graph_2(sparse_graph, file_name);
		cout << "test G2 in Sparse Graph:" << endl;
		sparse_graph.show();

		// 比较使用深度优先遍历和广度优先遍历获得路径的不同
		// 广度优先遍历获得的是无权图的最短路径
		Path<SparseGraph> dfs(sparse_graph, 0);
		cout << "DFS : ";
		dfs.ShowPath(5);

		ShortestPath<SparseGraph> bfs(sparse_graph, 0);
		cout << "BFS : ";
		bfs.ShowPath(5);
		cout << "BFS shortest length: " << bfs.Length(5) << endl;

		// 测试testG1文件
		file_name = "../test_files/testG1.txt";
		SparseGraph g2 = SparseGraph(13, false);
		ReadGraph<SparseGraph> readGraph2(g2, file_name);
		g2.show();

		// 比较使用深度优先遍历和广度优先遍历获得路径的不同
		// 广度优先遍历获得的是无权图的最短路径
		Path<SparseGraph> dfs2(g2, 0);
		cout << "DFS : ";
		dfs2.ShowPath(3);

		ShortestPath<SparseGraph> bfs2(g2, 0);
		cout << "BFS : ";
		bfs2.ShowPath(3);
	}

	// 测试有权图
	void test_weight_graph() {
		int vertexs = 8;
		string file_name = R"(../test_files/testWeightGraph.txt)";
		cout << std::fixed << std::setprecision(2);

		cout << "weight sparse graph:\n";
		WeightSparseGraph<double> weight_sparse_graph(vertexs, false);
		ReadGraph2<WeightSparseGraph<double>, double> read2(weight_sparse_graph, file_name);
		weight_sparse_graph.show();	

		cout << "\n";
		cout << "weight dense graph:\n";
		WeightDenseGraph<double> weight_dense_graph(vertexs, false);
		ReadGraph2<WeightDenseGraph<double>, double> read3(weight_dense_graph, file_name);
		weight_dense_graph.show();	

		cout << "\n";
	}
}
}

#endif // SparseGraph_
