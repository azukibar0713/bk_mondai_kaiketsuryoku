// Dijkstra法(O(VV))
//   各辺が非負であるときには最短距離d[v]の値を動的に更新していく過程で緩和順序が決まる

#include <iostream>
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
    dist[s] = 0;
    for (int iter = 0; iter < n; ++iter) {
        // 使用済でない頂点のうち、dist値が最小のものを探す
        long long min_dist = INF;
        int min_v = -1;
        for (int v = 0; v < n; v++) {
            if (!used[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                min_v = v;
            }
        }
        // もしそのような点が見つからなければ終了する
        if (min_v == -1) break;

        // min_vを始点とした各頂点を緩和する
        for (auto e : G[min_v]) {
            chmin(dist[e.to], dist[min_v] + e.w);
        }
        used[min_v] = true;
    }


    return 0;
}