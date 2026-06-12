#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int t;
    int a, b, x;
    cin >> t;
    while (t--) {
        cin >> a >> b >> x;

        ll ans = abs(a - b);
        ll ops_a = 0;
        ll ops_b = 0;

        while (a != b) {
            if (a < b) {
                swap(a, b);
                swap(ops_a, ops_b);
            }
            ll next = a / x;
            if (next == a) {
                break;
            }
            ops_a++;
            a = next;
            ans = min(ans, ops_a + ops_b + abs(a-b));
        }

        cout << ans << "\n";
    }
}