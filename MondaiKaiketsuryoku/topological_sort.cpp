// 問題解決力を鍛える！アルゴリズムとデータ構造
// P.234
// トポロジカルソート
// 　トポロジカルソート可能であるためには、有向サイクルを持たないことが必要かつ十分条件
//   そのようなグラフをDAG(Directed Acyclic Graph)と呼ぶ
//   一般にトポロジカルソート順は複数存在する
// アルゴリズム
//   深さ優先探索を再帰関数の抜けた順に並べて、それを逆順に並び替えなおす

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

vector<bool> seen;
vector<int> order;
void dfs(const Graph &G, int v) {
    seen[v] = true;
    for (auto next_v : G[v]) {
        if (seen[next_v]) continue;
        dfs(G, next_v);
    }
    order.push_back(v);
}

int main() {
    int n, m;
    Graph G(n);

    // *************
    // グラフ入力処理
    // *************

    seen.assign(n, false);
    order.clear();
    for (int v = 0; v < n; v++) {
        if (seen[v] != -1) continue;
        dfs(G, v);
    }
    reverse(order.begin(), order.end());
    return 0;
}