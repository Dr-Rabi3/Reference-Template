class binary_trie {
    struct Node {
        Node* child[2];
        Node() { child[0] = child[1] = NULL; }
    };
    Node* root;
    int LOG;
public:
    binary_trie(int _LOG) :LOG(_LOG) { root = new Node(); }
    void insert(int x) {
        Node* v = root;
        for (int bit = LOG - 1; bit >= 0; --bit) {
            int to = ((1 << bit) & x ? 1 : 0);
            if (v->child[to] == NULL)
                v->child[to] = new Node();
            v = v->child[to];
        }
    }
    int query_max(int x) {
        Node* v = root; int sum = 0;
        for (int bit = LOG - 1; bit >= 0; bit--) {
            int to = ((1 << bit) & x ? 0 : 1);
            if (v->child[to] == NULL) to = 1 - to;
            v = v->child[to], sum += to * (1 << bit);
        }
        return x ^ sum;
    }
    int query_min(int x) {
        return INT_MAX ^ query_max(INT_MAX ^ x);
    }
};
