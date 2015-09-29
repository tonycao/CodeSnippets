class Solution {
public:

    struct node{
        string str;
        int lev;
        node(string s, int l):str(s), lev(l){}
    };

vector<string> findDict(string str, unordered_set<string> &dict){
        vector<string> res;
        int sz = str.size();
        string s = str;
        for (int i=0;i<sz;i++){
            s = str;
            for (char j = 'a'; j<='z'; j++){
                s[i]=j;
                if (dict.find(s)!=dict.end()){
                    res.push_back(s);
                }
            }

        }
        return res;
    }
 bool valid(string s1,string s2){
        bool flag=false;
        for (int i=0;i<s1.size();i++){
            if (s1[i]!=s2[i]){
                if (flag==true){return false;}
                else{flag=true;}
            }
        }
        return true;
    }

    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if (valid(start, end)) return 2;
        queue<node> q;
        queue<node> rq;
        map<string, bool> mark;
        map<string, bool> rmark;
        for(auto it=dict.begin(); it!= dict.end(); it++){
            mark[*it] = false;
            rmark[*it] = false;
        }

        int level = 1;
        int rlevel = 1;
        q.push(node(start,1));
        rq.push(node(end,1));

        while(!q.empty() & !rq.empty()){
            if (q.size()<rq.size()){
            while (!q.empty() && q.front().lev==level){

                vector<string> l = findDict(q.front().str,dict);
                for (auto it=l.begin();it!=l.end();it++){
                    if (!mark[*it]){
                        mark[*it]=true;
                        if (rmark[*it]){return q.front().lev+rq.back().lev;}
                        q.push(node(*it,level+1));
                    }
                }
                q.pop();
            }
            level++;
            }else{

                while (!rq.empty() && rq.front().lev==rlevel){

                    vector<string> lr = findDict(rq.front().str,dict);
                    for (auto it=lr.begin();it!=lr.end();it++){
                        if (!rmark[*it]){
                            rmark[*it]=true;
                            if (mark[*it]){return rq.front().lev+q.back().lev;}
                            rq.push(node(*it,rlevel+1));
                        }
                    }
                    rq.pop();
                }

                rlevel++;
            }
        }
        return 0;
    }
};
