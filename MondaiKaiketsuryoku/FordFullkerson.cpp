// フォードファルカーソン法
// アイデア
//   -
//   残余グラフ上で見つけたs-tパス上にフローを流せるだけ流す、を残余グラフにs-tパスがなくなるまで繰り返す

#include <iostream>
#include <vector>>
using namespace std;

struct Graph {
    // rev : 逆辺 (to, from) がG[to]の中で何番目の要素か
    // cap : 辺 (from, to) の容量
    struct Edge {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
    };

    // 隣接リスト
    vector<vector<Edge>> list;

    // n: 頂点数
    Graph(int n = 0) : list(n) {}

    size_t size() { return list.size(); }

    // GraphインスタンスをGとして、
    // G.list[v]をG[v]と書けるようにしておく
    vector<Edge> &operator[](int i) { return list[i]; }

    // 辺e=(u,v)の逆辺(v,u)取得する
    Edge &redge(const Edge &e) { return list[e.to][e.rev]; }

    // 辺e=(u, v)に流量fのフローを流す
    // e = (u,v)の流量がfだけ減少する
    // 逆辺(v,u)の流量は増える
    void run_flow(Edge &e, int f) {
        e.cap -= f;
        redge(e).cap += f;
    }

    // 頂点fromから頂点toへ容量capの辺を張る
    // このときtoからfromも容量0の辺を張っておく
    void addedge(int from, int to, int cap) {
        int fromrev = (int)list[from].size();
        int torev = (int)list[to].size();
        list[from].push_back(Edge(torev, from, to, cap));
        list[to].push_back(Edge(fromrev, to, from, 0));
    }
};

struct FordFulkerson {
    static const int INF = 1 << 30;
    vector<int> seen;

    FordFulkerson() {}

    // 残余グラフ上でs-tパスを見つける（深さ優先探索）
    // 返り値はs-tパス上の容量の最小値（見つからない場合は0）
    // f: sからvへ到達した過程の各辺の容量の最小値
    int fodfs(Graph &G, int v, int t, int f) {
        // 終端tに到達したらreturn
        if (v == t) {
            return f;
        }

        seen[v] = true;
        for (auto &e : G[v]) {
            if (seen[e.to]) continue;
            // 容量0の辺は実際には存在しない
            if (e.cap == 0) continue;
            // s-tパスを探す
            // 見つかったらflowはパス上の最小容量
            // 見つからなかったらf=0
            int flow = fodfs(G, e.to, t, min(f, e.cap));
            // s-tパスが見つからなかったら次辺を探す
            if (flow == 0) continue;
            // 辺eに容量flowのフローを流す
            G.run_flow(e, flow);
            // s-tパスを見つけたらパス上最小容量を返す
            return flow;
        }
        // s-tパスが見つからなかったら0を返す
        return 0;
    }

    // グラフGのs-t間の最大流量を求める
    // ただしリターン時にGは残余グラフとなる
    int solve(Graph &G, int s, int t) {
        int res = 0;

        // 残余グラフにs-tパスがなくなるまで反復
        while (true) {
            seen.assign((int)G.size(), 0);
            int flow = fodfs(G, s, t, INF);
            // s-tパスが見つからなかったら終了
            if (flow == 0) return res;
            res += flow;
        }
        // no reach
        return 0;
    }
};

int main() {
    int n = 6;
    int m = 9;
    int A[] = {0, 0, 1, 1, 2, 2, 3, 3, 4};
    int B[] = {1, 3, 2, 3, 4, 5, 2, 4, 5};
    int C[] = {5, 5, 4, 37, 56, 7, 3, 9, 2};

    Graph G(n);
    for (int i = 0; i < m; i++) {
        int u = A[i];
        int v = B[i];
        int c = C[i];
        G.addedge(u, v, c);
    }

    FordFulkerson ff;
    int s = 0, t = n - 1;
    cout << ff.solve(G, s, t) << endl;
    return 0;
}
