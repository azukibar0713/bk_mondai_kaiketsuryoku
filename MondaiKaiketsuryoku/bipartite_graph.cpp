// 問題解決力を鍛える！アルゴリズムとデータ構造
// P.233
// 2部グラフ判定
// 各頂点を隣同士が同じ色にならないように、白、黒で塗分けできるか？
#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> color;
bool dfs(const Graph &G, int v, int cur = 0) {
    color[v] = cur;
    for (auto next_v : G[v]) {
        // 頂点の色がすでに確定してる場合
        if (color[next_v] != -1) {
            // 同じ色が隣接している場合は２部グラフではない
            if (color[next_v] == cur) return false;
            // 色が確定していた場合は探索しない
            continue;
        }
        // 隣接頂点の色を変えて再帰的に探索
        // falseが返ってきたらfalseを返す
        if (!dfs(G, next_v, 1 - cur)) return false;
    }
    return true;
}

int main() {
    int n, m;
    Graph G(n);

    // *************
    // グラフ入力処理
    // *************

    color.assign(n, -1);
    bool is_bipartile = true;
    for (int v = 0; v < n; v++) {
        // 探索済の場合は探索しない
        if (color[v] != -1) continue;
        if (!dfs(G, v)) is_bipartile = false;
    }
    return 0;
}
