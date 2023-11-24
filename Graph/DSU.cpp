struct dsu {
    vector<int>par, siz;
    dsu(int n) {
        par = vector<int>(n + 1);
        siz = vector<int>(n + 1, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int u) { return par[u] = (par[u] == u ? u : find(par[u])); }
    bool connect(int u, int v) { return find(u) == find(v); }
    void marge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)return;
        if (siz[u] < siz[v]) swap(u, v);
        siz[u] += siz[v];
        par[v] = u;
    }
};
