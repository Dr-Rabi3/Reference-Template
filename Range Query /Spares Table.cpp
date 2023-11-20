template < typename T > class SparesTable {
    vector<vector<T>>st;
    vector<int> LOG;
    int n;
    T(*operation)(T, T);
    int P;
public:
    SparesTable(vector<T>& v, T(*func)(T, T)) {
        operation = func;
        n = v.size();
        P = __lg(n) + 1;
        st = vector<vector<T>>(P, vector<T>(n));
        LOG = vector<int>(n + 1);
        for (int i = 2;i <= n;i++) LOG[i] = LOG[i / 2] + 1;
        for (int i = 0;i < n;i++) st[0][i] = v[i];
        for (int p = 1;(1 << p) <= n;p++) {
            for (int i = 0;i + (1 << p) <= n;i++) {
                st[p][i] = operation(st[p - 1][i], st[p - 1][i + (1 << (p - 1))]);
            }
        }
    }
    T query(int l, int r) {
        T ans;
        for (int p = P - 1;p >= 0;p--) {
            if ((1 << p) <= r - l + 1) {
                ans = operation(ans, st[p][l]);
                l += (1 << p);
            }
        }
        return ans;
    }
    T FQuery(int l, int r) {
        int p2 = LOG[r - l + 1];
        return operation(st[p2][l], st[p2][r - (1 << p2) + 1]);
    }
};
