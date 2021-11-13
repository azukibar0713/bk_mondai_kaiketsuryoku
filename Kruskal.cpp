// クラスカル法
//   - 辺集合Tを空集合とする
//   - 各辺を重みが小さい順にソートして、e0,e1,...とおく
//   - Tにeiを追加したときにサイクルが形成されるのであればeiは破棄する
//   - サイクルが形成されないのであればTにeiを追加する
//   - Tが最小全域木となる
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct UnionFind {
    vector<int> par, siz;
    UnionFind(int n) : par(n, -1), siz(n, 1) {}
    int root(int x) {
        if (par[x] == -1)
            // xが根の場合はxを返す
            return x;
        else
            // 経路圧縮（途中に通ったノードの親はrootにつなげる）
            return par[x] = root(par[x]);
    }

    bool issame(int x, int y) { return root(x) == root(y); }

    // xを含むグループと、yを含むグループを併合する
    bool unite(int x, int y) {
        // x, yをそれぞれ根まで移動させる
        x = root(x);
        y = root(y);
        // すでに同じグループのときには何もしない
        if (x == y) return false;
        // union by size (y側のサイズが小さくなるようにする)
        if (siz[x] < siz[y]) swap(x, y);
        // yをxの子にする
        par[y] = x;
        siz[x] += siz[y];
    }
    // xを含むサイズ
    int size(int x) { return siz[root(x)]; }
};

// 辺e=(u,v)を {w(e), {e,v}}で表す
using Edge = pair<int, pair<int, int>>;

int main(void) {
    int n = 2, m = 1;
    vector<Edge> edges(m);  // 辺集合
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = Edge(w, make_pair(u, v));
    }

    sort(edges.begin(), edges.end());

    long long res = 0;
    UnionFind uf(n);
    for (int i = 0; i < m; i++) {
        int w = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;

        // 辺u, vの追加によってサイクルが形成されるときは追加しない
        if (uf.issame(u, v)) continue;

        // 辺(u, v)を追加する
        res += w;
        uf.unite(u, v);
    }

    cout << res;
}