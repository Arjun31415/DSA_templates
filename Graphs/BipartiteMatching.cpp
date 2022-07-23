// time-limit: 1000
// problem-url: https://cses.fi/problemset/task/1696
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
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
#define debugging
bool bfs(int n, vi &pair_u, vi &pair_v, vi &dist, vvi &adj, const int &NIL)
{

	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (pair_u.at(i) == NIL) dist.at(i) = 0, q.push(i);
		else dist.at(i) = inf;
	dist.at(NIL) = inf;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (dist.at(u) < dist[NIL])
			for (auto &v : adj[u])
				if (dist.at(pair_v.at(v)) == inf)
					dist[pair_v[v]] = dist[u] + 1, q.push(pair_v[v]);
	}
	return dist[NIL] != inf;
}
bool dfs(const int u, vi &pair_u, vi &pair_v, vi &dist, const vvi &adj,
		 const int &NIL)
{
	if (u != NIL)
	{
		for (auto &v : adj[u])
		{
			if (dist[pair_v[v]] == dist[u] + 1)
				if (dfs(pair_v[v], pair_u, pair_v, dist, adj, NIL))
				{
					pair_u[u] = v, pair_v[v] = u;
					return true;
				}
		}
		dist[u] = inf;
		return false;
	}
	return true;
}
int Hopcroft_Karp(const int &n, const int &m, vvi &adj, vector<pii> &matches)
{
	const int NIL = 0;
	vi dist(n + 1);
	vi pair_u(n + 1, NIL), pair_v(m + 1, NIL);
	int matching = 0;
	while (bfs(n, pair_u, pair_v, dist, adj, NIL))
		for (int i = 1; i <= n; i++)
			if (pair_u[i] == NIL && (dfs(i, pair_u, pair_v, dist, adj, NIL)))
				matching++;
	for (int i = 1; i <= n; i++)
		if (pair_u[i] != NIL) matches.pb({i, pair_u[i]});
	return matching;
}
signed main()
{
	FIO;
	int n, m, k;
	cin >> n >> m >> k;
	vvi adj(n + 1);
	int u, v;
	for (int i = 0; i < k; i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
	}
	vector<pii> matches;
	int ans = Hopcroft_Karp(n, m, adj, matches);
	cout << ans << "\n";
	for (auto &x : matches)
		cout << x.first << " " << x.second << "\n";
	return 0;
}

