// 最小生成树实例

#ifndef minimum_spanning_tree_h
#define minimum_spanning_tree_h

// 使用prim算法生成最小树

// #include "edge.h"
#include "heap.h"
#include "Graph.h"

#include <vector>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

using DSA::Heap::MinHeap;
using DSA::Heap::IndexMinHeap;
using DSA::Graph::WeightSparseGraph;

// 使用prim算法生成最小树
// 1.遍历一个起始顶点所有相关联的边，放到小顶堆中
// 2.在小顶堆中弹出最小边的值，判断当前的边所对应的点是否已经遍历过，
//   且这条边是否已经组成环,如果没有组成环，则是最小生成树的一条边。
//	 接着上面的点，是否已经遍历过。如果没有，则再把与之相关联的边，加入到小顶堆中。
// 3.如此反复操作，直到所有的点和边都已经遍历过，则结束.

namespace DSA {

namespace Graph {

template<typename Graph, typename Weight>
class LazyPrimMST {

using GraphData = Edge<Weight>;
using SharedGraphData = shared_ptr<GraphData>;

private:
	Graph &_graph;									// 图的引用
	MinHeap<GraphData> _minHeap;					// 最小堆，算法辅助结构
	bool *_marked;									// 标记数据，是遍历过程中是否已经被访问过
	vector<Edge<Weight>> _mstEdges;					// 最小生成树包含的所有边
	Weight _mstWeight;								// 最小生成树的权值

	void visited(int vertex) {
		assert(!_marked[vertex]);

		_marked[vertex] = true;

		// 将和顶点vertex所有链接的边都加入到最小堆中
		typename Graph::adjIterator adj(_graph, vertex);
		for (shared_ptr<Edge<Weight>> edge = adj.begin(); !adj.end(); edge = adj.next()) {
			// 如果另个顶点已经被访问到了，则不需要加入堆中
			if (_marked[edge->other(vertex)]) { continue; }

			_minHeap.insert(*edge);
		}
	}
public:
	LazyPrimMST(Graph &graph): _graph(graph), 
							  _minHeap(MinHeap<GraphData>(_graph.GetEdgeCount()+1)) {

		_marked = new bool[_graph.GetVertexCount()+1];

		for (int i = 0; i < _graph.GetVertexCount(); ++i) {
			_marked[i] = false;
		}

		_mstEdges.clear();

		// lazy prim
		visited(0);

		while (!_minHeap.isEmpty()) {
			Edge<Weight> min_edge = _minHeap.extractMin();
			// 此边的两个顶点都已经访问过了，不需要
			if (_marked[min_edge.vertex1()] && _marked[min_edge.vertex2()]) { continue; }

			_mstEdges.push_back(min_edge);

			// 再访问这条边连接的还没有访问的节点
			if (!_marked[min_edge.vertex1()]) {
				visited(min_edge.vertex1());
			} else {
				visited(min_edge.vertex2());
			}
		}

		// 计算最小生成树的权值
		_mstWeight = _mstEdges[0].weight();
		for (int i = 1; i < _mstEdges.size(); ++i) {
			_mstWeight += _mstEdges[i].weight();
		}
	}

	vector<Edge<Weight>> AllEdges() { return _mstEdges; }

	Weight result() {
		return _mstWeight;
	}

};

// 优化的prim算法：
// 优化点：
// 1.采用优化的堆结构
// 2.未优化的Prim算法，是遍历了所有的边，放到堆结构中。优化的算法：是判断是否比已经加入的边小。如果小，才加入到堆中。
template<typename Graph, typename Weight>
class PrimMST {

using GraphData = Edge<Weight>;
using SharedGraphData = shared_ptr<GraphData>;

private:
	Graph &_graph;									// 图的引用
	IndexMinHeap<GraphData> _minHeap;					// 最小堆，算法辅助结构
	bool *_marked;									// 标记数据，是遍历过程中是否已经被访问过
	vector<Edge<Weight>> _mstEdges;					// 最小生成树包含的所有边
	Weight _mstWeight;								// 最小生成树的权值
	vector<SharedGraphData>_EdgeTo;					// 访问的点所对应的边

	void visited(int vertex) {
		assert(!_marked[vertex]);

		_marked[vertex] = true;

		// 将和顶点vertex所有链接的边都加入到最小堆中
		typename Graph::adjIterator adj(_graph, vertex);
		for (shared_ptr<Edge<Weight>> edge = adj.begin(); !adj.end(); edge = adj.next()) {
			// 如果另个顶点已经被访问到了，则不需要加入堆中
			if (_marked[edge->other(vertex)]) { continue; }

			int other_vertex = edge->other(vertex);

			// 如果这条边没有，则表示新加入的
			if (nullptr == _EdgeTo[other_vertex] ) {
				_EdgeTo[other_vertex] = edge;				
				_minHeap.insert(other_vertex, *edge);
			}
			else if ( _EdgeTo[other_vertex]->weight() > edge->weight()) { 
				// 已经有了边，需要判断新的边是否比原来的边小。如果比原来的小，则需要更新边的信息
				_EdgeTo[other_vertex] = (edge);
				_minHeap.change(other_vertex, *edge);
			}
		}
	}
public:
	PrimMST(Graph &graph): _graph(graph), 
						  _minHeap(IndexMinHeap<GraphData>(_graph.GetEdgeCount()+1)){
		_marked = new bool[_graph.GetVertexCount()+1];
		_EdgeTo.resize(_graph.GetEdgeCount());

		for (int i = 0; i < _graph.GetVertexCount(); ++i) {
			_marked[i] = false;
		}

		for (int i = 0; i < _graph.GetEdgeCount(); ++i) {
			_EdgeTo[i] = nullptr;
		}

		_mstEdges.clear();

		// prim
		visited(0);

		while (!_minHeap.isEmpty()) {
			int vertex = _minHeap.extractMinIndex();
			assert(_EdgeTo[vertex]);
			_mstEdges.push_back(*(_EdgeTo[vertex]));
			visited(vertex);
		}

		// 计算最小生成树的权值
		_mstWeight = _mstEdges[0].weight();
		for (int i = 1; i < _mstEdges.size(); ++i) {
			_mstWeight += _mstEdges[i].weight();
		}
	}

	vector<Edge<Weight>> AllEdges() { return _mstEdges; }

	Weight result() { return _mstWeight; }

};

	void test_min_spanning_tree() {
		string file_name = R"(../test_files/testWeightGraph.txt)";
		int V = 8;

		WeightSparseGraph<double> g = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph(g, file_name);

		// Test Lazy Prim MST
		cout << "Test Lazy Prim MST:" << endl;
		LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST(g);
		vector<Edge<double>> mst = lazyPrimMST.AllEdges();
		for (int i = 0; i < mst.size(); i++)
			cout << "(" << mst[i].vertex1() << "," << mst[i].vertex2() << ") "<< mst[i].weight() << endl;
		cout << "The MST weight is: " << lazyPrimMST.result() << endl;

		WeightSparseGraph<double> g2 = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph2(g2, file_name);

		// Test Lazy Prim MST
		cout << "Test Prim MST:" << endl;
		PrimMST<WeightSparseGraph<double>, double> PrimMST(g2);
		vector<Edge<double>> mst2 = PrimMST.AllEdges();
		for (int i = 0; i < mst2.size(); i++)
			cout << "(" << mst2[i].vertex1() << "," << mst2[i].vertex2() << ") "<< mst2[i].weight() << endl;
		cout << "The MST weight is: " << PrimMST.result() << endl;

	}
}
}

#endif // minimum_spanning_tree_h

