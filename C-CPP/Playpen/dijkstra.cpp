#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using std::vector;
using std::priority_queue;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

//https://ronzii.wordpress.com/2011/07/07/dijkstras-algorithm-using-stl/

typedef pair<int, int> pp;

class cmp {
	public:
	int operator() (const pair<int, int> &p1, const pair<int, int> &p2) {
		return p1.second < p2.second;
	}
};


int main() {
	priority_queue<pp, vector<pp>, cmp> Q;
	int n;
	cin >> n;
	vector<vector<pp> >G(n + 1);
	int e, u, v, w;
	cin >> e;

	for (int i = 0; i < e; ++i) {
		cin >> u >> v >> w;
		G[u].push_back(pp(v, w));
		G[v].push_back(pp(u, w));
	}

	// start point
	int s;
	cin >> s;
	int d[n + 1];
	for (int i = 1; i <= n; ++i) {
		d[i] = INT_MAX;
	}

	d[s] = 0;
	Q.push(pp(s, d[s]));

	while(!Q.empty()) {
		u = Q.top().first;
		Q.pop();
		int size = G[u].size();
		for (int i = 0; i < size; ++i) {
			v = G[u][i].first;
			w = G[u][i].second;
			cout << u << " " << v << " " << w << endl;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				Q.push(pp(v, d[v]));
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << "Node " << i << ", min weight = " << d[i] << endl;
	}
	return 0;
}