/****************************************************************************
**
** Copyright (C) 2021 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include <iostream>

using std::ostream;

template<typename Weight>
class Edge
{
private:
	int _vertex1, _vertex2;	// 边的两个端点
	Weight _weight;			// 边的权值

public:
	// 构造函数
	Edge(int vertex1, int vertex2, Weight weight): _vertex1(vertex1), 
												   _vertex2(vertex2), 
												   _weight(weight)
	{}

	// 空的构造函数	
	Edge() {}
	~Edge() {}

	// 返回第一个顶点
	int vertex1() { return _vertex1; }

	// 返回第二个顶点
	int vertex2() { return _vertex2; }

	Weight weight() { return _weight; }

	// 给定一个顶点，返回另外一个顶点
	int other(int vertex) {
		return vertex == _vertex1 ? _vertex2 : _vertex1;
	}

	// 输出边的信息
	friend ostream& operator<<(ostream &os, const Edge &edge)
	{
		os << edge._vertex1 << "-" << edge._vertex2 << ": " << edge._weight;

		return os;
	}

	bool operator<(const Edge<Weight> &edge)
	{
		return _weight < edge._weight;
	}

	bool operator<=(const Edge<Weight> &edge)
	{
		return _weight <= edge._weight;
	}

	bool operator==(const Edge<Weight> &edge)
	{
		return _weight == edge._weight;
	}

};
