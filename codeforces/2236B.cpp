#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string bin;
        cin >> bin;

        // odd number of 1's == fail
        bool failed = false;
        int sz = bin.size();
        for (int i = 0; i < sz; i++) {
            if (bin[i] == '1') {
                if (i + k < sz) {
                    bin[i] = '0';
                    if (bin[i+k] == '1') {
                        bin[i+k]='0';
                    } else {
                        bin[i+k] = '1';
                    }
                } else {
                    failed = true;
                    break;
                }
            }
        }

        if (failed) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }   
}