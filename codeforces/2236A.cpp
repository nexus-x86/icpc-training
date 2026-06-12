#include <iostream>
using namespace std;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int max = 0;
        int min = 7;

        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (a > max) {
                max = a;
            }
            if (a < min) {
                min = a;
            }
        
        }
        cout << max + 1 - min << "\n";
    }
}