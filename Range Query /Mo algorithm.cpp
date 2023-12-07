template < typename T > class MO { // 1-based
    struct Query { int l, r, id; };
    const int M = 450;
    vector <Query> queries;
    vector<T> nums, ans;
    int n, q, curAns;
    void add(int x) { }
    void rem(int x) { }
public:
    MO(int _n, int _q) : n(_n), q(_q) {
        nums = vector<T>(n + 1);
        ans = vector<T>(n + 1);
        queries = vector<Query>(q);
    }
    void getArr() {
        for (int i = 1; i <= n;++i)
            cin >> nums[i];
    }
    void getQuery() {
        for (int i = 1; i <= q;++i) {
            int l, r;cin >> l >> r;
            queries[i] = { l,r,i };
        }
    }
    vector<T> mo_process() {
        sort(all(queries), [&](Query& a, Query& b) {
            int A = a.l / M;
            int B = b.l / M;
            return make_pair(A, a.r) < make_pair(B, b.r);
            });
        int l = queries[0].l, r = l - 1;
        for (auto& query : queries) {
            while (l > query.l) add(nums[--l]);
            while (r < query.r) add(nums[++r]);
            while (l < query.l) rem(nums[l++]);
            while (r > query.r) rem(nums[r--]);
            ans[query.id] = curAns;
        }
        return ans;
    }
};
