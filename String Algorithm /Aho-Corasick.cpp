class Aho {
    struct node {
        node* child[26];
        node* fail;
        vector<int>patIdx;
        node() { for (int c = 0;c < 26;c++) child[c] = NULL; }
    };
    node* root;
    int numPtr;
    void move(node*& kmp, int c) {
        while (!kmp->child[c])
            kmp = kmp->fail;
        kmp = kmp->child[c];
    }

public:
    Aho(int n) :numPtr(n) { root = new node(); }

    void insert(const string& s, int idx) {
        node* temp = root;
        for (auto& i : s) {
            int c = i - 'a';
            if (temp->child[c] == NULL)
                temp->child[c] = new node();
            temp = temp->child[c];
        }
        temp->patIdx.push_back(idx);
    }
    void build() {
        node* temp = root;

        queue<node*>q;
        for (int c = 0;c < 26;c++) {
            if (temp->child[c]) {
                q.push(temp->child[c]);
                temp->child[c]->fail = root;
            }
            else temp->child[c] = root;
        }

        node* cur;

        while (!q.empty()) {
            cur = q.front();
            q.pop();
            for (int c = 0;c < 26;c++) {
                if (cur->child[c] == NULL)continue;

                q.push(cur->child[c]);

                node* kmp = cur->fail;

                move(kmp, c);

                cur->child[c]->fail = kmp;
                cur->child[c]->patIdx.insert(cur->child[c]->patIdx.end(),
                    kmp->patIdx.begin(), kmp->patIdx.end());
            }
        }
    }

    vector<vector<int>> match(const string& s) {
        vector<vector<int>>res(numPtr);
        node* temp = root;
        for (int i = 0;i < s.size();++i) {
            int c = s[i] - 'a';
            move(temp, c);
            for (auto j : temp->patIdx) {
                res[j].push_back(i);
            }
        }
        return res;
    }
};
