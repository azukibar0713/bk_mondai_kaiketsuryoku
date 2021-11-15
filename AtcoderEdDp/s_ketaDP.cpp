/* - 問題
 *   - https://atcoder.jp/contests/dp/tasks/dp_s
 * - 解説ページ
 *   - https://kyopro-friends.hatenablog.com/entry/2019/01/12/231035
*/
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repi(i, a, b) for (int i = int(a); i < int(b); ++i)
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    std::ifstream in("input.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    string k;
    cin >> k;
    int n = k.size();
    int d;
    cin >> d;

    using mint = modint1000000007;
    using mintd = modint;
    mintd::set_mod(d);

    using Type = mint;
    vector<vector<vector<Type>>> dp(
        k.size() + 1, vector<vector<Type>>(2, vector<Type>(d, 0)));

    // 0文字目, k未満確定していない, dで割ったあまり0は1通り(kの前に"0"がついているイメージ)
    dp[0][0][0] = 1;

    // ポイント
    // - k「未満」確定の2次元目はループで回さない.
    rep(i, k.size()) rep(j, d) {
        int num = k[i] - '0';
        rep(dig, 10) {
            // k未満が確定しているので、0-9までどの値でも取れる
            dp[i + 1][1][(j + dig) % d] += dp[i][1][j];
        }

        rep(dig, num) {
            // k未満が確定していないが、num未満であれば確定に遷移できる
            //   ※k未満は確定していなくてもkを超えてはいない
            dp[i + 1][1][(j + dig) % d] += dp[i][0][j];
            ;
        }
        // numを取ればk未満確定していない（ kとずっと同じ値）に遷移
        dp[i + 1][0][(j + num) % d] += dp[i][0][j];
    }

    // 答えに0が含まれるので1引く
    cout << (dp[n][0][0] + dp[n][1][0].val() - 1).val();

    return 0;
}
