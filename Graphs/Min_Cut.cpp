// time-limit: 1000
// problem-url: https://cses.fi/problemset/task/1695
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define pb push_back
#define inf 1e18
#define FIO                                                                    \
	ios_base::sync_with_stdio(0);                                              \
	cin.tie(0);                                                                \
	cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using pii = pair<int, int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using mii = map<int, int>;
using pqb = priority_queue<int>;
using pqs = priority_queue<int, vi, greater<int>>;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
vvi adj, capacity, adj_matrix;

int bfs(int s, int t, vector<int> &parent)
{
	fill(parent.begin(), parent.end(), -1), parent[s] = -2;
	queue<pair<int, int>> q;
	q.push({s, inf});

	while (!q.empty())
	{
		auto [cur, flow] = q.front();
		q.pop();
		for (int next : adj[cur])
		{
			if (parent[next] == -1 && capacity[cur][next])
			{
				parent[next] = cur;
				int new_flow = min(flow, capacity[cur][next]);
				if (next == t) return new_flow;
				q.push({next, new_flow});
			}
		}
	}
	return 0;
}

int maxflow(int s, int t, int n)
{
	int flow = 0;
	vector<int> parent(n + 1);
	int new_flow;
	while ((new_flow = bfs(s, t, parent)))
	{
		flow += new_flow;
		int cur = t;
		while (cur != s)
		{
			int prev = parent[cur];
			capacity[prev][cur] -= new_flow, capacity[cur][prev] += new_flow;
			cur = prev;
		}
	}

	return flow;
}
void dfs(int cur, vb &vis)
{
	vis[cur] = true;
	for (int i = 1; i < capacity.at(cur).size(); i++)
		if (capacity[cur][i] && !vis[i]) dfs(i, vis);
}
vector<pii> mincut(const int &n, int s, int t)
{
	vb vis(n + 1, false);
	vector<pii> cut_edges;
	maxflow(1, n, n);
	dfs(1, vis);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (vis.at(i) && !vis.at(j) && adj_matrix.at(i).at(j))
				cut_edges.pb({i, j});
	return cut_edges;
}
signed main()
{
	FIO;
	int n, m;
	cin >> n >> m;
	adj.resize(n + 1);
	capacity.resize(n + 1, vi(n + 1));
	int u, v;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
		capacity[u][v]++;
		capacity[v][u]++;
	}
	adj_matrix = capacity;
	vector<pii> ans = mincut(n, 1, n);
	cout << ans.size() << "\n";
	for (auto &[u, v] : ans)
	{
		cout << u << " " << v << "\n";
	}
	return 0;
}
