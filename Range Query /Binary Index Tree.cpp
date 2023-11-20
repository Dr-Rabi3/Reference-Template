struct BIT {
    int size;
    vector<int> bit;
    BIT(int n) : size(n), bit(n + 1) {}
    void update(int x, int v) {
        x++;
        for (; x <= size; x += x & (-x)) { bit[x] += v; }
    }
    int query(int b) {
        b++;
        int result = 0;
        for (; b > 0; b -= b & (-b)) { result += bit[b]; }
        return result;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
};
