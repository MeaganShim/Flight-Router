//============================================================================
// Name        : mstprimtest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include "create_graph.h"
using namespace std;

// EDGE IMPLEMENTATION
edge::edge(){
	weight = 0.0;
	paired_node = std::numeric_limits<double>::infinity();
}

edge::~edge(){
	weight = 0.0;
	paired_node = std::numeric_limits<double>::infinity();
}

double edge::get_paired_node(){
	return paired_node;
}

void edge::create_edge(int node, double w){
	weight = w;
	paired_node = node;
}

bool edge::find_node(int node_wanted){
	if(paired_node == node_wanted){
		return true;
	}
	else{
		return false;
	}
}

void edge::change_weight(double new_weight){
	weight = new_weight;
}

double edge::get_weight(){
	return weight;
}

bool edge::compare_weight(double wanted_weight){
	if(wanted_weight == weight){
		return true;
	}
	else{
		return false;
	}
}

// GRAPH IMPLEMENTATION
graph::graph(){
	edge_count = 0;
	graph_size = 0;
}

graph::~graph(){
	edge_count = 0;
	graph_size = 0;
}

void graph::initialize_graph(int node_num){
	graph_size = node_num;
	// initialize size of adjacency_list
	adjacency_list.resize(node_num);
	cout << "success" << endl;
}

void graph::insert_edge(int u, int v, double w){
	bool exists = false;
	// check if illegal argument
	if(u >= graph_size || v >= graph_size || w <= 0.00 || u == v){
		throw myex;
	}
	// within vector at u check if edge has corresponding node v
	for(int i = 0; i < adjacency_list[u].size(); i++){
		if(adjacency_list[u][i].find_node(v) == true){
			// change weight of edge at that index
			adjacency_list[u][i].change_weight(w);
			exists = true;
			break;
		}
	}
	// if we find vector v in u then we need to change weight of vector u in v
	if(exists == true){
		// loop through vector v and check if edge has corresponding node u
		for(int i = 0; i < adjacency_list[v].size(); i++){
			if(adjacency_list[v][i].find_node(u) == true){
				// change weight of edge at that index
				adjacency_list[v][i].change_weight(w);
				exists = true;
				break;
			}
		}
	}

	// if edge DNE then push back vector and create edge and increase edge count
	if(exists == false){
		edge forward;
		forward.create_edge(v, w);
		edge reverse;
		reverse.create_edge(u,w);
		adjacency_list[u].push_back(forward);
		adjacency_list[v].push_back(reverse);
		edge_count = edge_count + 2;
	}
	cout << "success" <<endl;
}

void graph::erase_edge(int u, int v){
	bool exists = false;
	// check if u or v are outside the bounds
	if(u >= graph_size || v >= graph_size || u == v){
		throw myex;
	}

	// search for edge v in vector u
	for(int i = 0; i < adjacency_list[u].size(); i++){
		if(adjacency_list[u][i].find_node(v) == true){
			//if an edge does exist then remove edge v from vector u
			exists = true;
			adjacency_list[u].erase(adjacency_list[u].begin() + i);
			break;
		}
	}

	// if exists = true then there is a corresponding edge u in vector v
	if(exists == true){
		for(int i = 0; i < adjacency_list[v].size(); i++){
			if(adjacency_list[v][i].find_node(u) == true){
				//remove edge u from vector v
				adjacency_list[v].erase(adjacency_list[v].begin() + i);
				break;
			}
		}
		// decrement edge count by 2
		edge_count = edge_count - 2;
		cout << "success" << endl;
	}
	else{
		// there is no edge between u and v
		cout << "failure" << endl;
	}
}


void graph::adjacent(int u, int v, double w){
	// check if u or v are outside of bounds
	if(u >= graph_size || v >= graph_size || w <= 0.00 || u == v){
		throw myex;
	}

	// check if edge v exists  in vector u of weight w
	for(int i = 0; i < adjacency_list[u].size(); i++){
		if(adjacency_list[u][i].find_node(v) == true && adjacency_list[u][i].compare_weight(w) == true){
			//if an edge with correct weight does exist then return
			cout << "adjacent " << u << " " << v << " ";
			std::cout << std::fixed << std::setprecision(2) << w << std::endl;
			return;
		}
	}
	cout << "not adjacent " << u << " " << v << " ";
	std::cout << std::fixed << std::setprecision(2) << w << std::endl;
}

void graph::degree(int u){
	// check if u is outside of bounds
	if(u >= graph_size){
		throw myex;
	}
	int degree = adjacency_list[u].size();
	cout << "degree of " << u << " is " << degree << endl;
}

void graph::get_edge_count(){
	cout << "edge count is " << edge_count << endl;
}

void graph::clear(){
	// reset the edge count to be zero
	edge_count = 0;
	for(int i = 0; i < graph_size; i++){
		adjacency_list[i].clear();
	}
	cout << "success" << endl;
}

void graph::print_test(){
	for(int i = 0; i < graph_size; i++){
		cout << i << ": ";
		for(int j = 0; j < adjacency_list[i].size(); j++){
			cout << adjacency_list[i][j].get_paired_node() << " ";
		}
		cout << endl;
	}
}

int graph::get_size(){
	return graph_size;
}

double graph::mst(int root){
	// check if root is valid
	if(root >= graph_size){
		throw myex;
	}
	PQ min_heap;
	min_heap.init_pq(graph_size);
//	cout << "-----------------------------------------" << endl;
//	cout << "NEW MST CALL" << endl;
	double mst_count = 0.00;
	// initialize root
	min_heap.modify_pq(root, 0.00);

	while(!min_heap.is_empty()){
//		cout << "extract min from heap" << endl;
		Node current = min_heap.extract_min();
		// get node value
		int node = current.get_node_val();
		// add associated weight to mst count
		mst_count = mst_count + current.get_key();
//		cout << "current min node: " << node << endl;;
//		cout << "updated mst count: " << mst_count << endl;

		// loop through adjacent nodes
		for(int i = 0; i < adjacency_list[node].size(); i++){
			// get adjacent edge from adjacency list
			edge tmp_edge = adjacency_list[node][i];
//			cout << "at adjacent node " << tmp_edge.get_paired_node() << endl;
			// check if i is in PQ and if weight is smaller than current key in min_heap

			bool in_pq = min_heap.in_pq(tmp_edge.get_paired_node());
//			cout << "we are in the min heap " << in_pq << endl;
//			cout << "edge weight: " << tmp_edge.get_weight() << endl;
//			cout << "key val in min heap: " << min_heap.get_key_val(tmp_edge.get_paired_node()) << endl;

			if(min_heap.in_pq(tmp_edge.get_paired_node()) && tmp_edge.get_weight() < min_heap.get_key_val(tmp_edge.get_paired_node())){
//				min_heap.modify_pq(tmp_edge.get_weight(), tmp_edge.get_paired_node());
				min_heap.modify_pq(tmp_edge.get_paired_node(),tmp_edge.get_weight());
			}
		}
	}
	return mst_count;
}


// NODE IMPLEMENTATION
Node::Node(){
	key = std::numeric_limits<double>::infinity();
	node_val = 0;
}

Node::~Node(){

}
void Node::set_key(double k){
	key = k;
}

double Node::get_key(){
	return key;
}

void Node::set_node_val(int val){
	node_val = val;
}

int Node::get_node_val(){
	return node_val;
}

// PQ IMPLEMENTATION
PQ::PQ(){
	size = 0;
	capacity = 0;
	node_list = NULL;
	// indicates the position wrt to weight
	// ex at index 0 of PQ we hold weight 4 then in index list at index 4 we set it to be 0
	index_list = NULL;
}

PQ::~PQ(){
	// deallocate node list
	delete[] node_list;
	node_list = NULL;
	delete [] index_list;
	index_list = NULL;
}

void PQ::init_pq(int graph_size){
	capacity = graph_size;
	size = graph_size;
	node_list = new Node[graph_size];
	index_list = new int[graph_size];
	// initialize values of node in PQ
	for(int i = 0; i < size; i++){
		node_list[i].set_node_val(i);
		index_list[i] = i;
	}
}

bool PQ::is_empty(){
	if(size == 0){
		return true;
	}
	else{
		return false;
	}
}

void PQ::heapify(int index){
	// get invoked in the modify key function
	int left = get_left(index);
	int right = get_right(index);
	int min_val = index;
	if(left < size && node_list[left].get_key() < node_list[index].get_key()){
		min_val = left;
	}
//	if(right < size && node_list[right].get_key() < node_list[index].get_key()){
//		min_val = right;
//	}
	// change comparision of right to smallest instead of index
	if(right < size && node_list[right].get_key() < node_list[min_val].get_key()){
		min_val = right;
	}
	if(min_val != index){
//		cout << "min value is one of the children" << endl;
//		cout << min_val << endl;
		// swap positions in node list
		// swap positions between two nodes in node list
		Node tmp = node_list[index];
		node_list[index] = node_list[min_val];
		node_list[min_val] = tmp;
		// swap positions in index_list to account for new switch
//		int index_tmp = index_list[index];
//		index_list[index] = index_list[min_val];
//		index_list[min_val] = index_tmp;

		// new index logic
		int new_index = node_list[min_val].get_node_val();
		int new_min = node_list[index].get_node_val();
//		int index_tmp = new_index;
		index_list[new_index] = min_val;
		index_list[new_min] = index;


		// recursively call heapify
		// get parent of index
		int parent = get_parent(index);
		heapify(parent);
	}

	// print for debug
//	cout << "______________________" << endl;
//	cout << endl;
//	for(int i = 0; i < capacity; i++){
//		cout << i << ": " << node_list[i].get_node_val() << "   " << index_list[i] << endl;
//	}
}

void PQ::modify_pq(int node, double new_key){
	int position = index_list[node];
//	cout << "updating key at node " << node_list[position].get_node_val() << " from " << node_list[position].get_key() << " to " << new_key << endl;
	node_list[position].set_key(new_key);
	int parent_index = get_parent(position);
	// try starting at zero
	heapify(parent_index);
}

// get index of left child at input index
int PQ::get_left(int index){
	return (2*index) +1;
}

// get index of right child at input index
int PQ::get_right(int index){
	return (2*index) +2;
}

int PQ::get_parent(int index){
	return (index-1)/2;
}

Node PQ::extract_min(){
	if(size == 1){
		size = size -1;
		return node_list[0];
	}
	// extract root and swap first and last indicies of array
	Node root = node_list[0];
	node_list[0] = node_list[size-1];
	node_list[size-1] = root;
	// update index array
//	index_list[root.get_node_val()] = index_list[size-1];
//	index_list[size-1] = 0;

	// new index array update
	int extract_index = 0;
	int new_root = node_list[size-1].get_node_val();
	int new_swap = node_list[extract_index].get_node_val();
	index_list[new_root] = size-1;
	index_list[new_swap] = extract_index;

	size = size -1;
	heapify(0);

	return root;
}

double PQ::get_key_val(int index){
	int position = index_list[index];
	return node_list[position].get_key();
}

bool PQ::in_pq(int node){
	if(index_list[node] < size){
		return true;
	}
	else{
		return false;
	}
}

int main() {
	string input;
	bool continue_input = true;
	graph graph1;
	while(continue_input == true){
		getline(cin,input);
		string command = input.substr(0, input.find(" "));

		char last_char = command.back();
		if(isspace(last_char)){
			command = command.substr(0, command.size() - 1);
		}

		if(command == "n"){
			// initialize graph with the number of nodes passed in
			// the way we are extracting string locally will not have impact when running it on server
			string str_node_num = input.substr(input.find(" ")+ 1, input.find(" ") + 1);
			int node_num = std::stoi(str_node_num);
			// call init function
			graph1.initialize_graph(node_num);
//			graph1.print_test();
		}
		else if(command == "i"){
			//string manipulations
			string params = input.substr(input.find(" ") + 1);
			int semi_colon1 = params.find(";");
			string str_u = params.substr(0, semi_colon1);
			string second_param = params.substr(semi_colon1 +1);
			int semi_colon_2 = second_param.find(";");
			string str_v = second_param.substr(0, semi_colon_2);
			string str_w = second_param.substr(semi_colon_2 +1);

			// convert string to ints
			int u = std::stoi(str_u);
			int v = std::stoi(str_v);
			double w = std::stod(str_w);

			try{
				graph1.insert_edge(u,v,w);
			}
			catch(exception& ex){
				cout << ex.what() << endl;
			}

//			graph1.print_test();
		}
		else if(command == "e"){
			// new string manipulations
			string params = input.substr(input.find(" ") + 1);
			int semi_colon1 = params.find(";");
			string str_u = params.substr(0, semi_colon1);
			string second_param = params.substr(semi_colon1 +1);
			int semi_colon_2 = second_param.find(";");
			string str_v = second_param.substr(0, semi_colon_2);


			int u = std::stoi(str_u);
			int v = std::stoi(str_v);
			try{
				graph1.erase_edge(u,v);
			}
			catch(exception& ex){
				cout << ex.what() << endl;
			}
//			graph1.print_test();
		}
		else if(command == "adjacent"){
			//checks if there is an edge between nodes u and v of weight w
			// string commands
			string params = input.substr(input.find(" ") + 1);
			int semi_colon1 = params.find(";");
			string str_u = params.substr(0, semi_colon1);
			string second_param = params.substr(semi_colon1 +1);
			int semi_colon_2 = second_param.find(";");
			string str_v = second_param.substr(0, semi_colon_2);
			string str_w = second_param.substr(semi_colon_2 +1);

			// convert string to ints
			int u = std::stoi(str_u);
			int v = std::stoi(str_v);
			double w = std::stod(str_w);

			try{
				graph1.adjacent(u,v,w);
			}
			catch(exception& ex){
				cout << ex.what() << endl;
			}

		}
		else if(command == "degree"){
			// returns degree of node u
			string str_u = input.substr(input.find(" ")+ 1, input.find(" ") +1);
			int u = std::stoi(str_u);
			try{
				graph1.degree(u);
			}
			catch(exception& ex){
				cout << ex.what() << endl;
			}
		}
		else if(command == "edge_count"){
			// return total number of edges in the graph
			graph1.get_edge_count();
		}
		else if(command == "clear"){
			// removes all edges from the graph
			graph1.clear();
//			graph1.print_test();
		}
		else if(command == "mst"){
			// calculate MST starting at node u
			string str_u = input.substr(input.find(" ")+ 1, input.find(" ") +1);
			int u = std::stoi(str_u);
			try{
				double count = graph1.mst(u);
				if(count != std::numeric_limits<double>::infinity()){
					cout << "mst ";
					std::cout << std::fixed << std::setprecision(2) << count << std::endl;
				}
				else{
					cout << "not connected" << endl;
				}
			}
			catch(exception& ex){
				cout << ex.what() << endl;
			}

		}
		else if(command == "exit"){
			continue_input = false;
			break;
		}

	}
	return 0;
}
