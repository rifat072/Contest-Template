const int Node=5000;

struct Trie
{
    int root,curNodeId;
    struct node
    {
        int val;
        int endcnt;
        int child[27];
        bool endmark;
        vector<int> endlist;
        void clear(){
            memset(child,0,sizeof child);
            val=endcnt=0;
            endlist.clear();
            endmark=false;
        }
    }trie[Node];

    void clear(){
        trie[root].clear();
        root=curNodeId=0;
    }

    void addTrie(string str,int id){
        int len=str.length();
        int cur=root;
        for(ll i=0;i<len;i++){
            int c = str[i]-'a';
            if(trie[cur].child[c]==0){
                curNodeId++;
                trie[curNodeId].clear();
                trie[curNodeId].val=c;
                trie[cur].child[c]=curNodeId;
            }
            cur=trie[cur].child[c];
        }
        trie[cur].endlist.push_back(id);
        trie[cur].endmark=true;
    }
    bool searchTrie (string str){
        int len=str.length();
        int cur=root;
        for (int i = 0; i < len; i++){
            int c = str[i] - 'a';
            if(trie[cur].child[c] == 0)return false;
            cur=trie[cur].child[c];
        }
        return trie[cur].endmark;
    }

};
