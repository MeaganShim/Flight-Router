/*
 * mstprimtest.h
 *
 *  Created on: Apr 7, 2021
 *      Author: Meagan
 */

#ifndef MSTPRIMTEST_H_
#define MSTPRIMTEST_H_

#include <iostream>
#include <vector>
using namespace std;

class illegalArgumentException: public exception
{
	virtual const char* what() const throw()
	{
		return "illegal argument";
	}
} myex;

class edge{
private:
	double weight;
	double paired_node;
public:
	edge();
	~edge();
	double get_paired_node();
	double get_weight();
	void create_edge(int node, double w);
	bool find_node(int wanted_node);
	bool compare_weight(double wanted_weight);
	void change_weight(double new_weight);
};

class graph{
private:
	int graph_size;
	int edge_count;
	vector<vector<edge>> adjacency_list;
public:
	graph();
	~graph();
	void initialize_graph(int node_num);
	void insert_edge(int u, int v, double w);
	void print_test();
	void erase_edge(int u, int v);
	void adjacent(int u, int v, double w);
	void degree(int u);
	void get_edge_count();
	void clear();
	int get_size();
	double mst(int root);
};

class Node{
private:
	int node_val;
	double key;

public:
	Node();
	~Node();
	void set_key(double k);
	void set_node_val(int val);
	double get_key();
	int get_node_val();
};

class PQ{
private:
	int size;
	int capacity;
	Node* node_list;
	int* index_list;
public:
	PQ();
	~PQ();
	void init_pq(int size);
	bool is_empty();
	Node extract_min();
	void modify_pq(int node, double new_key);
	void heapify(int index);
	int get_left(int index);
	int get_right(int index);
	int get_parent(int index);
	double get_key_val(int index);
	bool in_pq(int node);
};

#endif /* MSTPRIMTEST_H_ */
