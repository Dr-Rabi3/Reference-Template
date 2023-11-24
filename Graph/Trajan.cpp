// trajan implementation (SCC, Bridges, Art point)
class Trajan {
private:
    vector<int>inStack;  // know node component
    stack<int> sk; // nodes component
    int n, id, numComp;
    vector<vector<int>>adj;
    vector<vector<int>>comps;
    vector<pair<int, int>>bridges;
    bool root;
    set<int> artPoint;
    stack<pair<int, int>>BiCompo;
    vector<pair<int, int>>BiConnComp;
    vector<int>heads;
public:
    vector<int>dfn;  // depth first number 
    vector<int>lowLink; // lowest link number of dfn to connected nodes
    vector<int>comp; // every node store number of its compo..
    Trajan(vector<vector<int>>& adj, int n, int base = 1) {
        this->n = n;
        id = 1;
        numComp = 0;
        root = false;
        dfn = vector<int>(n + 1, -1);
        lowLink = vector<int>(n + 1);
        inStack = vector<int>(n + 1);
        comp = vector<int>(n + 1);
        this->adj = adj;
    }
    void SCC(int node) {
        lowLink[node] = dfn[node] = id++;
        inStack[node] = 1;
        sk.push(node);
        for (auto& child : adj[node]) {
            if (dfn[child] == -1) {
                SCC(child);
                lowLink[node] = min(lowLink[node], lowLink[child]);
            }
            else if (inStack[child])
                lowLink[node] = min(lowLink[node], dfn[child]);
        }
        if (lowLink[node] == dfn[node]) {
            comps.push_back(vector<int>());
            int x = -1;
            while (x != node) {
                x = sk.top(), sk.pop();
                inStack[x] = 0;
                comps.back().push_back(x);
                comp[x] = comps.size();
            }
            numComp++;
        }
    }
    vector<vector<int>> getCompos() {
        return comps;
    }
    int NumOfSCC() {
        return numComp;
    }
    vector<int>getHeads() {
        for (int i = 1;i <= n;i++) {
            if (dfn[i] == lowLink[i])
                heads.push_back(i);
        }
        return heads;
    }
    void Bridges(int node, int par) {
        lowLink[node] = dfn[node] = id++;
        for (auto& child : adj[node]) {
            if (dfn[child] == -1) {
                Bridges(child, node);
                lowLink[node] = min(lowLink[node], lowLink[child]);
                if (lowLink[child] == dfn[child])
                    bridges.push_back({ node, child });
            }
            else if (child != par)
                lowLink[node] = min(lowLink[node], dfn[child]);
        }
    }
    vector<pair<int, int>>getBridges() {
        return bridges;
    }
    void ArticulationPoint(int node, int par = -1) {
        lowLink[node] = dfn[node] = id++;
        for (auto& child : adj[node]) {
            if (dfn[child] == -1) {
                ArticulationPoint(child, node);
                lowLink[node] = min(lowLink[node], lowLink[child]);
                if (lowLink[child] >= dfn[node]) {
                    if (par != -1)
                        artPoint.insert(node);
                }
            }
            else if (child != par)
                lowLink[node] = min(lowLink[node], dfn[child]);
        }
    }
    set<int>getArtPoint() {
        return artPoint;
    }
    void BiConnectedComp(int node, int par) {
        lowLink[node] = dfn[node] = id++;
        for (auto& child : adj[node]) {
            if (node != child && dfn[child] < dfn[node])
                BiCompo.push({ node,child });
            if (dfn[child] == -1) {
                BiConnectedComp(child, node);
                lowLink[node] = min(lowLink[node], lowLink[child]);
                if (lowLink[child] >= dfn[node]) {
                    pair<int, int>edge;
                    do {
                        edge = BiCompo.top();
                        BiCompo.pop();
                        BiConnComp.push_back(edge);
                    } while (edge.first != node || edge.second != node);
                }
            }
            else if (child != par)
                lowLink[node] = min(lowLink[node], dfn[child]);
        }
    }
    vector<pair<int, int>>getBiComps() {
        return BiConnComp;
    }
};
