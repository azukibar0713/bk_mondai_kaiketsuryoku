// フロイド・ワーシャル法
// O(V^3)
// dp[k][i][j] :
// 頂点0,1,...,k-1のみを中継店として通ってよい場合の、頂点iから頂点jへの最短距離
// 初期条件
//   d[0][i][j] : 0 (i == j)
//              : l(e) (辺e(i,j)が存在する)
//              : INF (それ以外)
// dp[k+1][i][j]の更新
//   新たに使用する頂点をkを使用しない場合：dp[k][i][j]
//   使用する場合：dp[k][i][k] + dp[k][k][j]
// dpは2次元でなくin-placeで2次元で良い
// dp[v][v] < 0となる頂点がある場合は負閉路が存在する

// Dijkstra法(O(VV))
//   各辺が非負であるときには最短距離d[v]の値を動的に更新していく過程で緩和順序が決まる

#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1LL << 60;

int main() {
    int n = 10, m = 9, s = 0;  // 頂点数、辺数、始点

    vector<vector<long long>> dp(n, vector<long long>(n, INF));

    // dp初期条件
    for (int e = 0; e < m; e++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        dp[a][b] = w;
    }
    for (int v = 0; v < n; v++) dp[v][v] = 0;

    // dp遷移（ワーシャルフロイド）
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
            }
        }
    }

    bool exist_negative_cycle = false;
    // dp[v][v] < 0なら負閉路が存在する
    for (int v = 0; v < n; ++v) {
        if (dp[v][v] < 0) exist_negative_cycle = true;
    }
    return 0;
}