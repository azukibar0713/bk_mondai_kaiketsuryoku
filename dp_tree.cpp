// 安定化集合（隣り合うどの２頂点間も選ばない）のなかでノードに書かれた数値の和の最大値
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using Graph = vector<vector<int>>;

int N;
vector<long long> w;
Graph G;

vector<int> dp1, dp2;

void dfs(int v, int p = -1) {
    // 最初に子頂点を探索しておく
    for (auto ch : G[v]) {
        if (ch == p) continue;
        dfs(ch, v);
    }

    // 帰りがけに動的計画法
    // この時点でvよりしたのdpの計算は終わっている
    dp1[v] = 0, dp2[v] = w[v];  // 初期条件
    for (auto ch : G[v]) {
        if (ch == p) continue;
        dp1[v] +=
            max(dp1[ch], dp2[ch]);  // 頂点vを根とする各部分木内での安定集合の重みの最大（vを選ばない場合）.
                                    // vを選ばないので、dp1,2どちらでも選べる
        dp2[v] += dp1[ch];  // 頂点vを根とする各部分木内での安定集合の重みの最大（vを選ぶ場合）.
                            // vを選んでいるので、w[v] + sum(dp1)
    }
}

int main() { return 0; }