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

int main(void) {
    UnionFind uf(7);

    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(5, 6);

    cout << uf.issame(1, 3) << endl;  // true
    cout << uf.issame(2, 5) << endl;  // false

    uf.unite(1, 6);
    cout << uf.issame(2, 5) << endl;  // true;
    return 0;
}
