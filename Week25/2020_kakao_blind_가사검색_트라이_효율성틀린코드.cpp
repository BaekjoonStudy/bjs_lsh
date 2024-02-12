#include <string>
#include <vector>
#include <iostream>

using namespace std;

int c2i (char c) {
    return c - 'a';
}

struct Trie {
    int value = 0;
    bool isFinish = false;
    Trie* Node[26];
    Trie() { // 생성자
        for (int i = 0; i < 26; i++)
            Node[i] = NULL;
    }
    
    void insert(string word, int idx) {
        this->value++;
        if (idx == word.size()-1) {
            this->isFinish = true;
            return;
        }
        int cur = c2i(word[idx]);
        if (this->Node[cur] == NULL)
            this->Node[cur] = new Trie();
        this->Node[cur]->insert(word, idx+1);
    }
    
    int find(string query, int idx) {
        int cur = c2i(query[idx]);      
        if (query[idx] == '?') {
            return this->value;
        }
        if (this->Node[cur] == NULL) // 단어없음
            return 0;
        
        return this->Node[cur]->find(query, idx+1);
    }
};

Trie* forwardTrie[10001];
Trie* backwardTrie[10001];

string reverse(string s) {
    string ret = "";
    for (int i = s.size()-1; i >= 0; i--) {
        ret += s[i];
    }
    return ret;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    
    for (auto w : words) {
        int wSize = w.size();
        if (forwardTrie[wSize] == NULL)
            forwardTrie[wSize] = new Trie();
        forwardTrie[wSize]->insert(w,0);
        
        w = reverse(w);
        if (backwardTrie[wSize] == NULL)
            backwardTrie[wSize] = new Trie();
        backwardTrie[wSize]->insert(w,0);
    }
    
    // cout << forwardTrie[5]->value << "\n";
    // cout << forwardTrie[5]->Node[c2i('f')]->Node[c2i('r')]->Node[c2i('o')]->value << "\n";
    // cout << backwardTrie[5]->value << "\n";
    // cout << backwardTrie[5]->Node[c2i('t')]->value << "\n";
    
    for (auto q : queries) {
        int qSize = q.size();
        if (forwardTrie[qSize] == NULL)
            answer.push_back(0);
        else if (q[0] == '?' && q[qSize-1] == '?') { // 전부 ?인 경우
            answer.push_back(forwardTrie[qSize]->value);
        }
        else if (q[0] == '?') { // 접두사가 ?인 경우
            q = reverse(q);
            answer.push_back(backwardTrie[qSize]->find(q,0));
        }
        else { // 접미사가 ?인 경우
            answer.push_back(forwardTrie[qSize]->find(q,0));
        }
    }
    
    return answer;
}
