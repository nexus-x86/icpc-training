// https://dmoj.ca/problem/ccc05s5

#include <iostream>
#include <algorithm>

using namespace std;

const long long mx = 1e5+1;

long long BIT[mx];
pair<long long, long long> arr[mx];

long long n;
long long a;
long long rankSum = 0;

void update(long long pos, long long val) {
    while (pos <= n) {
        BIT[pos] += val;
        pos += pos & -pos;
    }
}

long long query(long long pos) {
    long long sum = 0;
    while (pos > 0) {
        sum += BIT[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (long long i = 1; i <= n; i++) {
        cin >> a;
        arr[i] = {a, i};
    }
    sort(arr+1, arr+n+1);
    long long total = 0;
    for (long long i = 1; i <= n; i++) {
        long long idx = arr[i].second;
        long long que = query(idx);
        total += idx - que;
        update(idx, 1);
    }

    printf("%.2f\n", (double)total / n);


}