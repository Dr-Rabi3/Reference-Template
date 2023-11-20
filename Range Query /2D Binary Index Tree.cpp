struct BIT2D { // 1-based
    int n, m;
    vector<vector<int>> bit;
    BIT2D(int n, int m) : n(n), m(m) {
        bit = vector<vector<int>>(n + 1, vector<int>(m + 1));
    }
    void update(int x, int y, int val) {
        for (; x <= n; x += (x & (-x))) {
            for (int i = y; i <= n; i += (i & (-i))) { bit[x][i] += val; }
        }
    }
    int query(int x1, int y1, int x2, int y2) {
        int ans = 0;
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        return ans;
    }
    int query(int x, int y) {
        return query(x, y, x, y);
    }
};
