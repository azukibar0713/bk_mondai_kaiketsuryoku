#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const long long INF = 1LL << 60;

struct Edge {
    int to;       // 隣接頂点番号
    long long w;  // 重み
    Edge(int to, long long w) : w(w), to(to) {}
};
using Graph = vector<vector<Edge>>;

template <class T>
bool chmin(T& a, T b) {
    if (a > b) {
        a = b;
        return true;
    } else
        return false;
}

int main() {
    int n = 10, m = 9, s = 0;  // 頂点数、辺数、始点
    Graph G(n);

    // *************
    // グラフ入力処理
    // *************

    vector<bool> used(n, false);
    vector<long long> dist(n, INF);
    dist[s] = s;

    using P = pair<long long, int>;  // (d[v], d)をpair
    priority_queue<P, vector<P>, greater<P>> que;
    que.push(P(dist[s], s));

    while (!que.empty()) {
        // v: 使用済でない頂点のうち、d[v]が最小の頂点
        // d: vに対するキー値
        int v = que.top().second;
        long long d = que.top().first;
        que.pop();

        // d > dist[v]は, (d, v)がゴミであることを意味する
        if (d > dist[v]) continue;

        for (auto e : G[v]) {
            if (chmin(dist[e.to], dist[v] + e.w)) {
                que.push(P(dist[e.to], e.to));
            }
        }
    }

    return 0;
}