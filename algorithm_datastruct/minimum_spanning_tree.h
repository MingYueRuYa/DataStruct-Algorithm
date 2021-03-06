// 最小生成树实例

#ifndef minimum_spanning_tree_h
#define minimum_spanning_tree_h

// 使用prim算法生成最小树

// #include "edge.h"
#include "union.h"
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


namespace DSA {

namespace Graph {

// 使用prim算法生成最小树
// 1.遍历一个起始顶点所有相关联的边，放到小顶堆中
// 2.在小顶堆中弹出最小边的值，判断当前的边所对应的点是否已经遍历过，
//   且这条边的两个顶点是否都已经遍历过，如果没有遍历过则加入最小生成树边
//	 接着上面的点，是否已经遍历过。如果没有，则再把与之相关联的边，加入到小顶堆中。
// 3.如此反复操作，直到所有的点和边都已经遍历过，则结束.
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

// Kruskal 算法
// 1.遍历所有的边，加入到堆中
// 2.从对中弹出权值最小的边，判断和已有的边顶点是否形成圈
// 3.如果没有形成圈，则就是最小生成树的一条边，否则就不是
// 4.不断的从最小堆中弹出权值最小的边，重复1-3步骤，直到堆中的数据为空 且 最小生成树的边=vertex_count-1
template <typename Graph, typename Weight>
class KruskalMST {

using GraphData = Edge<Weight>;
using SharedGraphData = shared_ptr<GraphData>;

private:
	vector<GraphData> _mst;	// 最小生成树包含的所有边
	Weight _mstWeight;			// 最小生成树的权值
	int _count = 0;

public:
	KruskalMST(Graph &graph) {
		// 1.遍历所有的边，放到最小堆中	
		MinHeap<GraphData> minHeap(graph.GetEdgeCount());
		for (int i = 0; i < graph.GetVertexCount(); ++i) {
			typename Graph::adjIterator adj(graph, i);
			for (SharedGraphData data = adj.begin(); !adj.end(); data = adj.next()) {
				// 如果这里不进行判断的话，(a, b)会插入一条数据到堆中，(b, a)也会插入一条数据到堆中
				// 这样就会插入两条数据到堆中，这是没有必要的。所以就采取插入一条顶点较小的数据
				++_count;
				if (data->vertex1() > data->vertex2()) { continue; }
				minHeap.insert(*data);

			} // for data
		} // for i
		// 2.从堆中弹出最小边，并判断是否形成了环
		Union::UnionFind1 uf = Union::UnionFind1(graph.GetVertexCount());
		while (! minHeap.isEmpty() && _mst.size() < graph.GetVertexCount()-1) {
			// 3.从堆中取出最小边
			Edge<Weight> edge = minHeap.extractMin();

			// 看该边的两个端点连通的，说明这条边将产生环，需要丢弃
			if (uf.isConnected(edge.vertex1(), edge.vertex2())) {
				continue;
			}

			// 否则，将这条边加入到最小生成树中
			_mst.push_back(edge);
			// 同时需要维护union，将边加入到union中
			uf.unionElements(edge.vertex1(), edge.vertex2());
		}

		_mstWeight = _mst[0].weight();
		for (int i = 1; i < _mst.size(); i++) {
			_mstWeight += _mst[i].weight();
		}

	}

	vector<GraphData> AllEdges() { return _mst; }

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

		cout << "Test Kruskal MST:" << endl;
		WeightSparseGraph<double> g3 = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph3(g3, file_name);

		KruskalMST<WeightSparseGraph<double>, double> KruskalMST(g3);
		vector<Edge<double>> mst3 = KruskalMST.AllEdges();
		for (int i = 0; i < mst3.size(); i++)
			cout << "(" << mst3[i].vertex1() << "," << mst3[i].vertex2() << ") "<< mst3[i].weight() << endl;
		cout << "The MST weight is: " << KruskalMST.result() << endl;

	}

	void test_compare_min_spanning_tree() {
		string file_name = R"(../test_files/testWeightGraph.txt)";
		string file_name2 = R"(../test_files/testWeightGraph-250-1273.txt)";
		string file_name3 = R"(../test_files/testWeightGraph-1000-8433.txt)";
		string file_name4 = R"(../test_files/testWeightGraph-10000-61731.txt)";

		int V = 8, V2 = 250, V3 = 1000, V4 = 10000;

		vector<std::pair<double, double>> time_weight_vc;

		clock_t start_time, end_time;
		// Test Lazy Prim MST
		// cout << "-----------------Test Lazy Prim MST:-----------------" << endl;
		WeightSparseGraph<double> g = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph(g, file_name);
		start_time = clock();
		LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST(g);
		end_time = clock();
		// cout << "The MST weight is: " << lazyPrimMST.result() << endl;
		time_weight_vc.push_back(std::pair<double, double>(lazyPrimMST.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g2 = WeightSparseGraph<double>(V2, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph2(g2, file_name2);
		start_time = clock();
		LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST2(g2);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(lazyPrimMST2.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));
		// cout << "The MST weight is: " << lazyPrimMST2.result() << endl;

		WeightSparseGraph<double> g3 = WeightSparseGraph<double>(V3, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph3(g3, file_name3);
		start_time = clock();
		LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST3(g3);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(lazyPrimMST3.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g4 = WeightSparseGraph<double>(V4, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph4(g4, file_name4);
		start_time = clock();
		LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST4(g4);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(lazyPrimMST4.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		// cout << "----------------Test Prim MST:-----------------" << endl;
		WeightSparseGraph<double> g5 = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph5(g5, file_name);
		start_time = clock();
		PrimMST<WeightSparseGraph<double>, double> PrimMST1(g5);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(PrimMST1.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g6 = WeightSparseGraph<double>(V2, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph6(g6, file_name2);
		start_time = clock();
		PrimMST<WeightSparseGraph<double>, double> PrimMST2(g6);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(PrimMST2.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g7 = WeightSparseGraph<double>(V3, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph7(g7, file_name3);
		start_time = clock();
		PrimMST<WeightSparseGraph<double>, double> PrimMST3(g7);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(PrimMST3.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g8 = WeightSparseGraph<double>(V4, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph8(g8, file_name4);
		start_time = clock();
		PrimMST<WeightSparseGraph<double>, double> PrimMST4(g8);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(PrimMST4.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		// cout << "----------------Test Kruskal MST:-----------------" << endl;
		WeightSparseGraph<double> g9 = WeightSparseGraph<double>(V, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph9(g9, file_name);
		start_time = clock();
		KruskalMST<WeightSparseGraph<double>, double> KurskalMST1(g9);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(KurskalMST1.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g10 = WeightSparseGraph<double>(V2, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph10(g10, file_name2);
		start_time = clock();
		KruskalMST<WeightSparseGraph<double>, double> KurskalMST2(g10);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(KurskalMST2.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g11 = WeightSparseGraph<double>(V3, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph11(g11, file_name3);
		start_time = clock();
		KruskalMST<WeightSparseGraph<double>, double> KurskalMST3(g11);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(KurskalMST3.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		WeightSparseGraph<double> g12 = WeightSparseGraph<double>(V4, false);
		ReadGraph2<WeightSparseGraph<double>, double> readGraph12(g12, file_name4);
		start_time = clock();
		KruskalMST<WeightSparseGraph<double>, double> KruskalMST4(g12);
		end_time = clock();
		time_weight_vc.push_back(std::pair<double, double>(KruskalMST4.result(), (double)(end_time-start_time)/CLOCKS_PER_SEC));

		cout << "\t\t" << V << "\t\t\t" << V2 << "\t\t\t\t" << V3 << "\t\t\t\t" << V4 << "\t\t\t" << "\n";
		cout << "Lazy Prim\t";
		for (int i = 0; i < 4; ++i) {
			cout << "weight:" << time_weight_vc[i].first << " time:" << time_weight_vc[i].second << "s\t";
		}
		cout << endl;
		
		cout << "Prim     \t";
		for (int i = 4; i < 8; ++i) {
			cout << "weight:" << time_weight_vc[i].first << " time:" << time_weight_vc[i].second << "s\t";
		}
		cout << endl;

		cout << "Kruskal   \t";
		for (int i = 8; i < 12; ++i) {
			cout << "weight:" << time_weight_vc[i].first << " time:" << time_weight_vc[i].second << "s\t";
		}
		cout << endl;
	}
}
}


#endif // minimum_spanning_tree_h

