/**
 * 1258. Synonymous Sentences
 * 
 * Intuition
 * 
 * credits votrubac
 * we are given a list of pairs of strings that are synonyms
 * we need to return all possible sentences we can form using the synonyms
 * 
 * Approach
 * 
 * we can use union find to group the synonyms
 * Then we can use dfs to form all possible sentences
 * 
 * Complexity
 * 
 * Time complexity: O(n^2)
 * 
 * Space complexity: O(n)
 */
class dsu {
    vector<int> f;
public:
    dsu(int n) {
        f.resize(n);
        for(int i = 0; i < n; ++i)
            f[i] = i;
    }
    void merge(int a, int b) {
        int fa = find(a);
        int fb = find(b);
        f[fa] = fb;
    }
    int find(int a) {
        int origin = a;
        while(a != f[a])
            a = f[a];
        return f[origin] = a;
    }
};

class Solution {
    unordered_map<string, int> w_id;              // word -> id
    unordered_map<int, string> id_w;              // id -> word
    unordered_map<int, vector<string>> f_words;   // root id -> sorted synonym list
    vector<string> ans;                            // result storage

public:
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        int id = 0;
        // 1. assign unique ids to all words appearing in synonyms
        for(auto& s : synonyms) {
            if(!w_id.count(s[0])) {
                w_id[s[0]] = id;
                id_w[id++] = s[0];
            }
            if(!w_id.count(s[1])) {
                w_id[s[1]] = id;
                id_w[id++] = s[1];
            }
        }
        int n = w_id.size();
        dsu u(n);
        // 2. union synonym pairs
        for(auto& s : synonyms) {
            int i1 = w_id[s[0]];
            int i2 = w_id[s[1]];
            u.merge(i1, i2);
        }
        // 3. group words by their root id
        for(int i = 0; i < n; ++i) {
            int root = u.find(i);
            f_words[root].push_back(id_w[i]);
        }
        // 4. sort each group lexicographically
        for(auto& fw : f_words)
            sort(fw.second.begin(), fw.second.end());
        
        // 5. split input text into words
        vector<string> sentenceWords;
        string w;
        for(char c : text) {
            if(c == ' ') {
                sentenceWords.push_back(w);
                w.clear();
            } else {
                w += c;
            }
        }
        if(!w.empty()) sentenceWords.push_back(w);
        
        // 6. backtrack to generate all possible sentences
        string path;
        bt(sentenceWords, 0, path, u);
        sort(ans.begin(), ans.end());   // final lexicographic order
        return ans;
    }
    
    void bt(vector<string>& sentenceWords, int i, string& path, dsu& u) {
        if(i == sentenceWords.size()) {
            path.pop_back();            // remove trailing space
            ans.push_back(path);
            path += ' ';                // restore for backtracking (optional)
            return;
        }
        int originalSize = path.size();
        if(!w_id.count(sentenceWords[i])) {
            // word has no synonyms – keep as is
            path += sentenceWords[i] + " ";
            bt(sentenceWords, i + 1, path, u);
            path.resize(originalSize);
        } else {
            int root = u.find(w_id[sentenceWords[i]]);
            for(const string& syn : f_words[root]) {
                path += syn + " ";
                bt(sentenceWords, i + 1, path, u);
                path.resize(originalSize);
            }
        }
    }
};