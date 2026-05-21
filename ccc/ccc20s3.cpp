// https://dmoj.ca/problem/ccc20s3

// uses frequency table and sliding window to check
// all matches are hashed and then stored in an unordered_set
// the hashing part is interesting 

#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

typedef long long ll;

string n, h;
int freq[26];
int window[26];

ll mod = 4000004479;
ll p = 53;

unordered_set<ll> s;

bool equal() {
    for (int i = 0; i < 26; i++) {
        if (freq[i] != window[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> h;

    if (n.length() > h.length()) {
        cout << "0\n";
        return 0;
    }

    ll power = 1;

    ll hash = 0;

    for (int i = 0; i < n.length(); i++) {
        freq[n[i] - 'a']++;
        window[h[i] - 'a']++;

        hash = ((h[i] - 'a') + p * hash) % mod;
        power = power * p % mod;
    }

    if (equal()) {
        s.insert(hash);
    }

    for (int i = 0; i < h.length() - n.length(); i++) {
        int a = h[i] - 'a';
        int b = h[i + n.length()] - 'a';
        window[b]++;
        window[a]--;

        // h_old = aB^n-1 + c1^B^n-2 + ... + c_n-1
        // h_new = c1B^n-1 + ... + c^n-1B + b
        // h_new from old = h * B - a * B^n + b
        // we have: -a * B^n = a * (M - B^n) (mod M)
        // h_new = h * B + a(M - pow) + b
        // calculating the new string hash removing first letter and adding last

        hash = (hash * p + a * (mod - power) + b )% mod;

        if (equal()) {
            s.insert(hash);
        }
    }
    cout << s.size() << "\n";
}