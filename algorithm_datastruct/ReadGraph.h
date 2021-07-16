/****************************************************************************
**
** Copyright (C) 2021 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef read_graph_
#define read_graph_

#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>

using std::string;
using std::ifstream;
using std::stringstream;

// 读取图算法
template <typename Graph>
class ReadGraph {
public:
	ReadGraph(Graph &graph, const string &filename) {
		ifstream file(filename);
		string line;
		int vertex, edge;

		assert(file.is_open());
		// 第一行读取图中的节点个数和边的个数
		assert(getline(file, line));
		stringstream ss(line);
		ss >> vertex >> edge;	

		assert(vertex == graph.GetVertexCount());

		for (int i = 0; i < edge; ++i) {
			assert(getline(file, line));
			stringstream ss(line);

			int left_vertex = 0, right_vertex = 0;
			ss >> left_vertex >> right_vertex;

			assert(left_vertex >= 0 && left_vertex < vertex);
			assert(right_vertex >= 0 && right_vertex < vertex);
			
			graph.addEdge(left_vertex, right_vertex);
			
		} // for i

	}
};

// 读取待权图
template <typename Graph, typename Weight>
class ReadGraph2 {
public:
	ReadGraph2(Graph &graph, const string &filename) {
		ifstream file(filename);
		string line;
		int vertex, edge;

		assert(file.is_open());
		// 第一行读取图中的节点个数和边的个数
		assert(getline(file, line));
		stringstream ss(line);
		ss >> vertex >> edge;	

		assert(vertex == graph.GetVertexCount());

		for (int i = 0; i < edge; ++i) {
			assert(getline(file, line));
			stringstream ss(line);

			int left_vertex = 0, right_vertex = 0;
			Weight weight;
			ss >> left_vertex >> right_vertex >> weight;

			assert(left_vertex >= 0 && left_vertex < vertex);
			assert(right_vertex >= 0 && right_vertex < vertex);
			
			graph.addEdge(left_vertex, right_vertex, weight);
			
		} // for i
	}
};

#endif // !read_graph_

