class Solution {
public:
    int minDistance(string word1, string word2) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        int len1 = word1.size();
        int len2 = word2.size();

        vector<vector<int> > table(len1+1,vector<int>(len2+1,0));

        for (int i=1;i<=len1;i++){
            table[i][0]=i;
        }

        for (int i=1;i<=len2;i++){
            table[0][i]=i;
        }

        for(int i=0;i<len1;i++){
            for (int j=0;j<len2;j++){
                table[i+1][j+1]=min(table[i+1][j],table[i][j+1])+1;
                if (word1[i]==word2[j]){
                    table[i+1][j+1]=min(table[i+1][j+1],table[i][j]);
                }else{
                    table[i+1][j+1]=min(table[i+1][j+1],table[i][j]+1);
                }
            }
        }

        return table[len1][len2];
    }
};
