// ベルマンフォード法
// アイデア
//   DAGの最短経路問題とは異なって辺緩和順序がわからない
//     ->各辺に対して一通り順序不問で緩和する操作を最短距離が更新されなくなるまで行う
//   到達可能な負閉路を持たないのであれば|V|回目の反復を行っても最短距離は更新されない
//   更新されるのであれば負経路を持つ

// 問題解決力を鍛える！アルゴリズムとデータ構造
// P.238
//  部分木のサイズ = 1 + 子頂点の部分木サイズの和　（帰りがけ時に求める）
//  深さ（行きがけ時に求める）

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

    bool exist_negative_cycle = false;
    vector<long long> dist(n, INF);
    dist[s] = 0;
    for (int iter = 0; iter < n; ++iter) {
        bool update = false;
        for (int v = 0; v < n; ++v) {
            if (dist[v] == INF) continue;  // まだ到達していないので緩和しない
            for (auto e : G[v]) {
                if (chmin(dist[e.to], dist[v] + e.w)) {
                    update = true;
                }
            }
        }
        // 更新が行われなかったら、最短経路が確定している
        if (!update) break;
        // n回目の反復で更新されたら、負経路を持つ
        if (iter == n - 1 && update) exist_negative_cycle = true;
    }

    if (exist_negative_cycle)
        cout << "Negative Cycle" << endl;
    else {
        for (int v = 0; v < n; ++v) {
            if (dist[v] < INF)
                cout << dist[v] << endl;
            else
                cout << "INF" << endl;  // 到達不可能
        }
    }
    return 0;
}