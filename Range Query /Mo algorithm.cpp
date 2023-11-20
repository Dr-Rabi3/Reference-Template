struct Query {
  int l, r, id;
};
int curAns = 0;
void add(int x) {

}
void rem(int x) {

}
const int M = 450;
int n, q;
int nums[N], ans[N];
vector <Query> queries;
void Mo() {
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
}
