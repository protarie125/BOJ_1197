#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using Edges = vector<tuple<ll, ll, ll>>;

ll v, e;
Edges edges;
vl par;
ll cte;
ll ans;

ll getRoot(const ll x) {
	if (x != par[x]) {
		par[x] = getRoot(par[x]);
	}

	return par[x];
}

void updateRoot(const ll x, const ll y) {
	const auto& rx = getRoot(x);
	const auto& ry = getRoot(y);

	par[ry] = rx;
}

void solve() {
	cte = 0;
	ans = 0;
	for (const auto& [cost, x, y] : edges) {
		if (getRoot(x) == getRoot(y)) {
			continue;
		}

		++cte;
		ans += cost;

		updateRoot(x, y);

		if (v - 1 == cte) {
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> v >> e;

	edges = Edges(v + 1);
	while (0 < (e--))
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges.push_back({ c, a, b });
	}
	sort(edges.begin(), edges.end());

	par = vl(v + 1);
	for (const auto& i : ranges::iota_view{ 0, v + 1 }) {
		par[i] = i;
	}

	solve();
	cout << ans;

	return 0;
}