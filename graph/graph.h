#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace graphs {

	class graph {
	public:
		bool add_node(int n);
		bool del_node(int n);
		bool add_edge(int n1, int n2);
		bool del_edge(int n1, int n2);
		vector<int> nodes();
		vector<pair<int, int>> out_edges(int n);
		int nodes_count() const;
		int edges_count() const;

		friend ostream& operator<<(ostream& out, const graph& g);
		friend istream& operator>>(istream& in, graph& g);

		static graph reverse(const graph& g);
		static vector<int> shortest_path(graph& g, int n1, int n2);

	private:
		map<int, set<int>> edges;
		int ecount = 0;
	};

}
