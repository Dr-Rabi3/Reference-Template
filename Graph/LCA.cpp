template < typename T > class LCA {
private:
    vector<vector<T>>up;
    vector<int>preorder;
    int n, L, id;
public:
    vector<int>depth;
    LCA(vector<vector<T>>& adj, T src = 1) {
        n = adj.size();
        L = __lg(n) + 1;
        id = 1;
        up = vector<vector<T>>(L, vector<T>(n + 5));
        depth = vector<int>(n + 1);
        preorder = vector<int>(n + 1);
        dfs(src, 0, adj);
    }
    void dfs(T u, T p, vector<vector<T>>& adj) {
        preorder[u] = id++;
        up[0][u] = p;
        for (int i = 1;i < L;i++)
            up[i][u] = up[i - 1][up[i - 1][u]];
        for (auto& i : adj[u]) {
            if (i != p) {
                depth[i] = depth[u] + 1;
                dfs(i, u, adj);
            }
        }
    }
    T query(T u, int k) {
        for (int p = 0;p < L;++p) {
            if (k & (1 << p))
                u = up[p][u];
        }
        return u;
    }
    T kthNode(T u, int level) {
        int lg = log2(depth[u]);
        for (int i = lg; i >= 0; i--)
            if (depth[u] - (1 << i) >= level)
                u = up[i][u];
        return u;
    }
    T lca(T u, T v) {
        if (depth[u] < depth[v])
            swap(u, v);
        u = query(u, depth[u] - depth[v]);
        if (u == v)return u;
        for (int i = L - 1;i >= 0;i--) {
            if (up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        }
        return up[0][u];
    }
    // dest rood between some nodes
    int destBetweenNodes(vector<int>& root) {
        sort(all(root), [&](int a, int b) {
            return preorder[a] < preorder[b];
            });
        int ans = depth[root[0]] + 1;
        for (int j = 1;j < root.size();j++) {
            int u = root[j - 1];
            int v = root[j];
            int x = lca(u, v);
            ans += depth[v] - depth[x];
        }
        return ans;
    }
};
