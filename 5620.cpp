#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef pair < ll, ll > P;
vector<P> points;

ll dist(const P& a, const P& b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

ll closest_pair(int l, int r, vector<P>& sorted_by_y) {
    if (r - l <= 3) {
        ll min_dist = LLONG_MAX;
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j < r; ++j)
                min_dist = min(min_dist, dist(points[i], points[j]));
        sort(points.begin() + l, points.begin() + r, [](P a, P b) { return a.second < b.second; });
        return min_dist;
    }

    int mid = (l + r) / 2;
    ll x_mid = points[mid].first;

    vector<P> y_left, y_right;
    for (auto& p : sorted_by_y) {
        if (p.first < x_mid) y_left.push_back(p);
        else y_right.push_back(p);
    }

    ll d = min(closest_pair(l, mid, y_left), closest_pair(mid, r, y_right));

    vector<P> strip;
    for (auto& p : sorted_by_y)
        if (abs(p.first - x_mid) < sqrt(d))
            strip.push_back(p);

    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size() && j - i < 8; ++j) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    return d;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    points.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> points[i].first >> points[i].second;

    sort(points.begin(), points.end()); // sort by x
    vector<P> sorted_by_y = points;
    sort(sorted_by_y.begin(), sorted_by_y.end(), [](P a, P b) {
        return a.second < b.second;
    });

    cout << closest_pair(0, n, sorted_by_y) << '\n';
    return 0;
}
