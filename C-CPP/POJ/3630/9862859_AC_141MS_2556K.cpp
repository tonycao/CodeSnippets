#include<iostream>
using namespace std;
int cases, icount;
int nodenum;

struct Trie_node
{
    bool isExist;
    Trie_node * branch[10];
}Node[100000];

class Trie
{
    private:
    Trie_node root;
    public:
    Trie(){root = Node[0];}
    bool insert(char num[])
    {
        Trie_node *location = &root;
        int i = 0;
        int len = strlen(num);
        while(num[i])
        {
            if(i==len-1 && location->branch[num[i]-'0'] != NULL) //
            {
                return false;
            }
            if(location->branch[num[i]-'0']==NULL)//
            {
                location->branch[num[i]-'0'] = &Node[nodenum];
                Node[nodenum].isExist = false;
                memset(Node[nodenum].branch,NULL,sizeof(Node[nodenum].branch));
                nodenum++;
            }
            if(location->branch[num[i]-'0']->isExist == true)
            {
                return false;
            }
            location = location->branch[num[i]-'0'];
            i++;
        }
        location->isExist = true;
        return true;
    }
};
int main()
{
    scanf("%d",&cases);
    while(cases--)
    {
        nodenum = 1;
        bool flag = true;
        scanf("%d",&icount);
        char tel[11];
        Trie t;
        while(icount--)
        {
            scanf("%s",tel);
            if(!t.insert(tel))
            {
                flag = false;
            }
        }
        if(flag)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}