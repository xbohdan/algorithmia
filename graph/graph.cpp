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
		auto it1 = edges.find(n);
		if (it1 != edges.end()) {
			ecount -= it1->second.size();
			edges.erase(it1);
			for (auto it2 = edges.begin(); it2 != edges.end(); ++it2)
				ecount -= it2->second.erase(n);
			return true;
		}
		return false;
	}

	bool graph::add_edge(int n1, int n2)
	{
		auto it1 = edges.find(n1);
		auto it2 = edges.find(n2);
		if (it1 != edges.end() and it2 != edges.end()) {
			bool is_added = it1->second.insert(n2).second;
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
		for (auto it = edges.begin(); it != edges.end(); ++it)
			vertices.push_back(it->first);
		return vertices;
	}

	vector<pair<int, int>> graph::out_edges(int n)
	{
		vector<pair<int, int>> arrows;
		auto it1 = edges.find(n);
		if (it1 != edges.end()) {
			for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
				arrows.push_back({ n, *it2 });
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
		for (auto it1 = g.edges.begin(); it1 != g.edges.end(); ++it1) {
			out << it1->first << " : ";
			for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
				out << *it2 << ' ';
			out << ';' << endl;
		}
		return out;
	}

	istream& operator>>(istream& in, graph& g)
	{
		graph temp;

		for (;;) {
			int source;
			char colon;
			if (!(in >> source >> colon) or colon != ':')
				break;
			unordered_set<int> targets;
			for (int target; in >> target; targets.insert(target));
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
		for (auto it1 = g.edges.begin(); it1 != g.edges.end(); ++it1) {
			for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
				temp.edges[*it2].insert(it1->first);
			}
		}
		return temp;
	}

	vector<int> graph::shortest_path(graph& g, int n1, int n2)
	{
		vector<int> path;
		auto it1 = g.edges.find(n1);
		auto it2 = g.edges.find(n2);

		if (it1 == g.edges.end() or it2 == g.edges.end())
			return path;

		unordered_map<int, int> inverted_arrows;
		queue<int> sources;
		sources.push(n1);

		while (!sources.empty()) {
			int source = sources.front();
			sources.pop();
			for (auto it4 = g.edges[source].begin(); it4 != g.edges[source].end(); ++it4) {
				if (!inverted_arrows.count(*it4)) {
					inverted_arrows[*it4] = source;
					sources.push(*it4);

					if (*it4 == n2) {
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
