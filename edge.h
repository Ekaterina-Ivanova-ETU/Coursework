#pragma once
class edge
{
public:
	int vertex_from, vertex_to, capacity, flow;

	edge() {}
	edge(int vertex_from, int vertex_to, int capacity) : vertex_from(vertex_from), vertex_to(vertex_to), capacity(capacity), flow(0) {}
	int other(int vertex) const
	{
		return vertex == vertex_from ? vertex_to : vertex_from;
	}
	int capacity_to(int vertex) const 
	{
		return vertex == vertex_to ? capacity - flow : flow;
	}
	void add_flow_to(int vertex, int f) 
	{
		flow += (vertex == vertex_to ? f : -f);
	}
};