#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define inf INT64_MAX
#define FIO                                                                    \
	ios_base::sync_with_stdio(0);                                              \
	cin.tie(0);                                                                \
	cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using vi = vector<int>;
using vvi = vector<vi>;

/**
 * Edmonds Karp Max Flow
 * Time Complexity: O(V E^2)
 * NOTE: if u->v has multiple edge then do
 * NOTE: adj.pb[u].pb(v) only once, but capacity[u][v]+=edge_capacity for the
 * NOTE: other occurences. If directed graph u->v then add the reverse edge
 * NOTE: (adj[v].pb(u)) and set capacity to 0.
 * NOTE: See in main function for sample use
 * SOURCE: https://cp-algorithms.com/graph/edmonds_karp.html
 *
 *
 */

vvi adj, capacity;
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
			capacity[prev][cur] -= new_flow;
			capacity[cur][prev] += new_flow;
			cur = prev;
		}
	}

	return flow;
}
signed main()
{
	FIO;
	int n, m;
	cin >> n >> m;
	adj.resize(n + 1);
	capacity.resize(n + 1, vi(n + 1));
	int u, v, w;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v >> w;
		adj[u].pb(v), adj[v].pb(u);
		capacity[u][v] += w;
	}
	int ans = maxflow(1, n, n);
	cout << ans << "\n";
	return 0;
}
