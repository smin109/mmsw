#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Event {
    int x, y1, y2, type;
    bool operator<(const Event &e) const { return x < e.x; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    cin >> N;

    vector<Event> events;
    vector<int> y_coords;

    for (int i = 0; i < N; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        events.push_back({x1, y1, y2, 1});  // 시작
        events.push_back({x2, y1, y2, -1}); // 끝
        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    // 좌표 압축
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());
    auto get_idx = [&](int y) {
        return lower_bound(y_coords.begin(), y_coords.end(), y) - y_coords.begin();
    };

    int M = y_coords.size();
    vector<int> count(4 * M), len(4 * M);

    auto update = [&](int node, int l, int r, int ul, int ur, int val, auto &&update_ref) -> void {
        if (r <= ul || ur <= l) return;
        if (ul <= l && r <= ur) {
            count[node] += val;
        } else {
            int m = (l + r) / 2;
            update_ref(node * 2, l, m, ul, ur, val, update_ref);
            update_ref(node * 2 + 1, m, r, ul, ur, val, update_ref);
        }
        if (count[node]) {
            len[node] = y_coords[r] - y_coords[l];
        } else if (r - l == 1) {
            len[node] = 0;
        } else {
            len[node] = len[node * 2] + len[node * 2 + 1];
        }
    };

    sort(events.begin(), events.end());

    ll area = 0;
    for (int i = 0; i < events.size() - 1; i++) {
        int l = get_idx(events[i].y1);
        int r = get_idx(events[i].y2);
        update(1, 0, M - 1, l, r, events[i].type, update);
        area += 1LL * len[1] * (events[i + 1].x - events[i].x);
    }

    cout << area << '\n';
    return 0;
}
