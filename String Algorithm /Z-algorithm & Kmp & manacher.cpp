namespace str {
    // Computes the Z-array of s
    vector<int> Z(const string& s) {
        int n = (int)s.size();
        vector<int> z_S(n);
        z_S[0] = n;
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r) { z_S[i] = min(z_S[i - l], r - i + 1); }
            while (i + z_S[i] < n && s[z_S[i]] == s[i + z_S[i]]) { z_S[i]++; }
            if (i + z_S[i] - 1 > r) {
                l = i;
                r = i + z_S[i] - 1;
            }
        }
        return z_S;
    }
    // Computes the KMP of s 
    vector<int>KMP(const string& s) {
        int n = s.size();
        vector<int>fail(n);
        for (int i = 1;i < n;i++) {
            int j = fail[i - 1];
            while (j > 0 && s[i] != s[j])j = fail[j - 1];
            if (s[i] == s[j])
                j++;
            fail[i] = j;
        }
        return fail;
    }
    // compute Longest Palindrome substring in o(n)
    string manacher(const string& p) {
        string s = "#"; for (char c : p) s += c, s += '#';
        vector<int> man(s.size());
        int mx = 0;
        for (int i = 1, l = 0, r = 1; i + 1 < s.size(); i++) {
            if (i < r) man[i] = min(r - i, man[l + r - i]);
            while (i - man[i] >= 0 && i + man[i] < s.size() && s[i - man[i]] == s[i + man[i]]) man[i]++;
            if (i + man[i] > r) l = i - man[i], r = i + man[i];
            if (man[i] - 1 > man[mx] - 1) mx = i;
        }
        string res = "";
        for (int i = mx - man[mx] + 1; i < mx + man[mx]; i++) if (s[i] != '#') res += s[i];
        return res;
    }
};
