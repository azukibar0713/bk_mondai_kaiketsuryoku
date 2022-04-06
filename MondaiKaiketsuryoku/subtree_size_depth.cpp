// 問題解決力を鍛える！アルゴリズムとデータ構造
// P.238
//  部分木のサイズ = 1 + 子頂点の部分木サイズの和　（帰りがけ時に求める）
//  深さ（行きがけ時に求める）

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> depth;
vector<int> subtree_size;

void dfs(const Graph &G, int v, int p = -1, int d = 0) {
    depth[v] = d;
    for (auto c : G[v]) {
        // 親への逆流を防ぐ
        if (c == p) continue;
        dfs(G, c, v, d + 1);
    }
    // 帰りがけ時に部分木のサイズを求める
    subtree_size[v] = 1;  // 自分自身
    for (auto c : G[v]) {
        if (c == p) continue;
        subtree_size[c] += subtree_size[c];
    }
}

int main() {
    int n, m;
    Graph G(n);

    // *************
    // グラフ入力処理
    // *************

    depth.assign(n, 0);
    subtree_size.assign(n, 0);
    dfs(G, 0);

    return 0;
}