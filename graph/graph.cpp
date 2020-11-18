#include <algorithm>
#include <queue>
#include "graph.h"

using namespace std;

namespace graphs {

	bool graph::add_node(int n)
	{
		return edges.insert({ n, {} }).second;
	}

	bool graph::del_node(int n)
	{
		for (auto itr = edges.begin(); itr != edges.end(); ++itr)
			itr->second.erase(n);
		return edges.erase(n) != 0;
	}

	bool graph::add_edge(int n1, int n2)
	{
		auto itr1 = edges.find(n1);
		auto itr2 = edges.find(n2);
		if (itr1 != edges.end() and itr2 != edges.end()) {
			bool is_added = edges[n1].insert(n2).second;
			if (is_added)
				++ecount;
			return is_added;
		}
		return false;
	}

	bool graph::del_edge(int n1, int n2)
	{
		bool is_deleted = edges[n1].erase(n2) != 0;
		if (is_deleted)
			--ecount;
		return is_deleted;
	}

	vector<int> graph::nodes()
	{
		vector<int> vertices;
		for (auto itr = edges.begin(); itr != edges.end(); ++itr)
			vertices.push_back(itr->first);
		return vertices;
	}

	vector<pair<int, int>> graph::out_edges(int n)
	{
		vector<pair<int, int>> arrows;
		auto itr1 = edges.find(n);
		if (itr1 != edges.end()) {
			for (auto itr = edges[n].begin(); itr != edges[n].end(); ++itr)
				arrows.push_back({ n, *itr });
		}
		return arrows;
	}

	int graph::nodes_count() const
	{
		return edges.size();
	}

	int graph::edges_count() const
	{
		return ecount;
	}

	ostream& operator<<(ostream& out, const graph& g)
	{
		for (auto itr1 = g.edges.begin(); itr1 != g.edges.end(); ++itr1) {
			out << itr1->first << " : ";
			for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2)
				out << *itr2 << ' ';
			out << ';' << endl;
		}
		return out;
	}

	istream& operator>>(istream& in, graph& g)
	{
		graph temp;

		while (true) {
			int source;
			char colon;
			if (!(in >> source >> colon) or colon != ':')
				break;
			unordered_set<int> targets;
			for (int target; in >> target; targets.insert(target);)
				in.clear();
			char semicolon;
			if (!(in >> semicolon) or semicolon != ';')
				break;

			temp.edges[source] = targets;
		}

		if (in.eof())
			g = temp;
		else
			in.clear(ios_base::failbit);
		return in;
	}

	graph graph::reverse(const graph& g)
	{
		graph temp;
		for (auto itr1 = g.edges.begin(); itr1 != g.edges.end(); ++itr1) {
			for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2) {
				temp.edges[*itr2].insert(itr1->first);
			}
		}
		return temp;
	}

	vector<int> graph::shortest_path(graph& g, int n1, int n2)
	{
		vector<int> path;
		auto itr1 = g.edges.find(n1);
		auto itr2 = g.edges.find(n2);

		if (itr1 == g.edges.end() or itr2 == g.edges.end())
			return path;

		unordered_map<int, bool> discovered;
		unordered_map<int, int> inverted_arrows;
		queue<int> sources;
		for (auto itr3 = g.edges.begin(); itr3 != g.edges.end(); ++itr3)
			discovered[itr3->first] = false;
		discovered[n1] = true;
		sources.push(n1);

		while (!sources.empty()) {
			int source = sources.front();
			sources.pop();
			for (auto itr4 = g.edges[source].begin(); itr4 != g.edges[source].end(); ++itr4) {
				if (discovered[*itr4] == false) {
					discovered[*itr4] = true;
					inverted_arrows[*itr4] = source;
					sources.push(*itr4);

					if (*itr4 == n2) {
						for (int target = n2; target != n1; target = inverted_arrows[target])
							path.push_back(target);
						path.push_back(n1);
						std::reverse(path.begin(), path.end());
						return path;
					}
				}
			}
		}
		return path;
	}

}
