struct node {
  // write your data
  int lazy = 0;
  int sum;
  void operator = (int val) {
    lazy = 0;
    sum = val;
  }

  node operator + (const node& right) { // current node is in lift side 
    node cur;// is the parent node
    cur.sum = sum + right.sum;
    return cur;
  }

};
template<typename T = node> class segment_tree { // 1 based
#define LEFT (idx << 1)
#define RIGHT (idx << 1 | 1)
#define MID ((start + end) >> 1)
  int n;
  vector<T> tree;

  void is_lazy(int idx, int val) {
    tree[idx].lazy += val;
  }

  inline void pushdown(int idx, int start, int end) {
    if (tree[idx].lazy == 0) return;
    is_lazy(idx, tree[idx].lazy);
    if (start != end) {
      tree[LEFT].lazy += tree[idx].lazy;
      tree[RIGHT].lazy += tree[idx].lazy;
    }
    tree[idx].lazy = 0;
  }
  inline void pushup(int idx) {
    tree[idx] = tree[LEFT] + tree[RIGHT];
  }

  void build(int idx, int start, int end, const string& arr) {
    if (start == end) {
      tree[idx] = arr[start];
      return;
    }
    build(LEFT, start, MID, arr);
    build(RIGHT, MID + 1, end, arr);
    pushup(idx);
  }
  T query(int idx, int start, int end, int from, int to) {
    pushdown(idx, start, end);
    if (from <= start && end <= to)
      return tree[idx];
    if (to <= MID)
      return query(LEFT, start, MID, from, to);
    if (MID < from)
      return query(RIGHT, MID + 1, end, from, to);
    return query(LEFT, start, MID, from, to) +
      query(RIGHT, MID + 1, end, from, to);
  }
  void updatePos(int idx2, int newVal, int idx, int start, int end) {
    if (start == end) {
      tree[idx] = newVal;
    }
    else {
      pushdown(idx, start, end);
      if (idx2 <= MID) updatePos(idx2, newVal, LEFT, start, MID);
      else updatePos(idx2, newVal, RIGHT, MID + 1, end);
      pushup(idx);
    }
  }

  void update(int idx, int start, int end, int lq, int rq, const int& val)
  {
    pushdown(idx, start, end);
    if (rq < start || end < lq)
      return;
    if (lq <= start && end <= rq) {
      tree[idx].lazy += val;
      pushdown(idx, start, end);
      return;
    }
    update(LEFT, start, MID, lq, rq, val);
    update(RIGHT, MID + 1, end, lq, rq, val);
    pushup(idx);
  }
public:
  segment_tree(int n) :n(n), tree(n << 2) {}
  segment_tree(const string& s) {
    n = s.size() - 1;
    tree = vector<T>(n << 2);
    build(1, 1, n, s);
  }
  int get(int l, int r) {
    return query(1, 1, n, l, r).sum;
  }
  void update(int l, int r, const int& val) {
    update(1, 1, n, l, r, val);
  }
  void update(int idx, int val) {
    updatePos(idx, val, 1, 1, n);
  }
#undef LEFT
#undef RIGHT
#undef MID
};
