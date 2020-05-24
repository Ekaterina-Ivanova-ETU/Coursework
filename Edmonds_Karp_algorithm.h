#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "C:\Users\Екатерина Иванова\source\repos\шаблон List\List.h"
#include "C:\Users\Екатерина Иванова\source\repos\шаблон List\List_iterator.h"
#include "edge.h"
using namespace std;


class EdmondsKarp_algorithm
{
private:
	List<char> vertexes;
	List<edge> edges;
	List<int> edges_parent;
	List<bool> used;
	List<int>* connectivity_list;
	bool connectivity_list_exists;
	const int INF = 1000000000;

	
	// Algorithm of breadth-first search.
	void bfs(int vertex) 
	{
		int current_vertex, vertex_to, k;

		List<int> queue;
	
		used.set(vertex, true);
		queue.push_back(vertex);

		while (!queue.isEmpty())
		{
			current_vertex = queue.front();
			queue.pop_front();
			for (int i = 0; i < connectivity_list[current_vertex].get_size(); i++)
			{
				k = connectivity_list[current_vertex].at(i);
				vertex_to = edges.at(k).other(current_vertex);
				if (!used.at(vertex_to) && edges.at(k).capacity_to(vertex_to))
				{
					edges_parent.set(vertex_to, k);
					used.set(vertex_to, true);
					queue.push_back(vertex_to);
				}
			}
		}
	}

	// Function for checking whether there is a path from one vertex to another.
	bool has_path(int from, int to)
	{
		for (int i = 0; i < vertexes.get_size(); i++)
			used.set(i, false);
		bfs(from);
		return used.at(to);
	}

	// Function for searching for an edge with the minimum capacity (c_min) in the found path.
	int bottleneck_capacity(int from, int to)
	{
		int delta_flow = INF;
		for (int i = to; i != from; i = edges.at(edges_parent.at(i)).other(i))
			delta_flow = min(delta_flow, edges.at(edges_parent.at(i)).capacity_to(i));
		return delta_flow;
	}

	// Function that increases flow by c_min for each edge on the found path, and reduces it by c_min for the opposite edge.
	void add_flow(int from, int to, int flow)
	{
		for (int i = to; i != from; i = edges.at(edges_parent.at(i)).other(i))
			edges[edges_parent.at(i)].add_flow_to(i, flow);
	}

	// Function returns the minimum argument.
	int min(int value1, int value2)
	{
		return value1 <= value2 ? value1 : value2;
	}

public:
	EdmondsKarp_algorithm() 
	{
		connectivity_list_exists = false;
	};

	~EdmondsKarp_algorithm()
	{
		if (connectivity_list_exists)
		{
			for (int i = 0; i < vertexes.get_size(); i++)
				if (!connectivity_list[i].isEmpty())
					connectivity_list[i].clear();
		}
		delete[] connectivity_list;

		if (!vertexes.isEmpty())
			vertexes.clear();
		if (!edges.isEmpty())
			edges.clear();
		if (!edges_parent.isEmpty())
			edges_parent.clear();
		if (!used.isEmpty())
			used.clear();
	};

	// Reading data from a file.
	void input(string info_file)
	{
		ifstream file(info_file);
		if (!file.is_open())
			throw invalid_argument("File is not found.");
	
		char current_vertex_from, current_vertex_to, symbol;
		int vertex_from, vertex_to, capacity;
		string current_capacity = "";

		while (!file.eof())
		{
			file >> noskipws >> symbol;
			if (file.eof()) break;
			
			current_vertex_from = symbol;
			if (!vertexes.contains(current_vertex_from))
				vertexes.push_back(current_vertex_from);
			file >> symbol;
			if (symbol != ' ')
				throw invalid_argument("The data in the file is incorrect.");

			file >> symbol;
			current_vertex_to = symbol;
			if (!vertexes.contains(current_vertex_to))
				vertexes.push_back(current_vertex_to);
			file >> symbol;
			if (symbol != ' ')
				throw invalid_argument("The data in the file is incorrect.");

			if (current_vertex_from == current_vertex_to)
				throw invalid_argument("A stream coming out of a vertex cannot enter this same vertex.");

			do
			{
				file >> symbol;
				if (symbol == '\n' || file.eof())
					break;
				if (isdigit(symbol))
					current_capacity += symbol;
				else if (symbol != '\n' && !file.eof())
					throw invalid_argument("The data in the file is incorrect.");
			} while (symbol != '\n' && !file.eof());
			if (current_capacity.empty())
				throw invalid_argument("The data in the file is incorrect.");
			else
			{
				capacity = atoi(current_capacity.c_str());
				current_capacity.clear();
			}

			vertex_from = vertexes.get_index(current_vertex_from);
			vertex_to = vertexes.get_index(current_vertex_to);

			edges.push_back(edge(vertex_from, vertex_to, capacity));
		}

		if (vertexes.isEmpty())
			throw invalid_argument("The file is empty.");

		if (vertexes.at(0) != 'S' || vertexes.at(vertexes.get_size() - 1) != 'T')
			throw invalid_argument("Input should begin with 'S' and end with 'T'.");

		file.close();

		connectivity_list = new List<int>[vertexes.get_size()];
		connectivity_list_exists = true;
		edge current_edge;
		int i = 0;
		Iterator<edge> *iter = edges.create_iterator();
		while (iter->has_next())
		{
			current_edge = iter->next();
			connectivity_list[current_edge.vertex_from].push_back(i);
			connectivity_list[current_edge.vertex_to].push_back(i);
			i++;
		}
		delete iter;
	}

	// Function for searching for the maximum flow in the network using the Edmonds-Karp algorithm.
	int max_flow()
	{
		if (vertexes.isEmpty())
			throw invalid_argument("Data is not set.");

		for (int i = 0; i < vertexes.get_size(); i++)
			edges_parent.push_back(0);
		for (int i = 0; i < vertexes.get_size(); i++)
			used.push_back(false);

		int max_flow = 0, delta_flow, from = 0, to = vertexes.get_size() - 1;

		while (has_path(from, to))
		{			
			delta_flow = bottleneck_capacity(from, to);
			add_flow(from, to, delta_flow);
			max_flow += delta_flow;
		}

		return max_flow;
	}
};