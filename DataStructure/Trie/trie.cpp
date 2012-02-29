/*
 * Trie
 * by Tian Cao
 * */

#include <iostream>
#include <stack>
using namespace std;

const int sonNum = 26, base = 'a';

typedef struct _Trie_node
{
    bool isStr; //
    _Trie_node *next[sonNum]; //following node
    _Trie_node():isStr(false)
    {
        memset(next, NULL, sizeof(next));
    }

}Trie_node;

class Trie
{
public:
    Trie();
    void insert(const char* word);
    bool search(char* word);
    void deleteTrie(Trie_node *root);
    bool deleteWord(const char *word);
private:
    Trie_node* root;
};

Trie::Trie()
{
    root = new Trie_node;
}

void Trie::insert(const char *word)
{
    Trie_node *location = root;
    while(*word)
    {
        if(location->next[*word-base]==NULL)
        {
            Trie_node *tmp = new Trie_node;
            location->next[*word-base] = tmp;
        }
        location = location->next[*word-base];
        word++;
    }
    location->isStr = true; //label a string
}

bool Trie::search(char *word)
{
    Trie_node *location = root;
    while(*word && location)
    {
        location = location->next[*word-base];
        word++;
    }
    return (location!=NULL && location->isStr);
}

void Trie::deleteTrie(Trie_node *root)
{
    //if(root != NULL)
    //{
    for(int i = 0; i < sonNum; i++)
    {
        if(root->next[i] != NULL)
        {
            deleteTrie(root->next[i]);
        }
    }
    delete root;
    //}
}

bool Trie::deleteWord(const char* word)
{
    Trie_node *current = root;
    stack<Trie_node*> nodes; // save internal nodes
    while(*word != '\0' && current != 0)
    {
        nodes.push(current);
        current = current->next[*word - base];
        word++;
    }

    if(current && current->isStr)
    {
        current->isStr = false; //current is point to the leaf node
        while(nodes.size() != 0)
        {
            char c = *(--word);
            current = nodes.top()->next[c-base]; //get current node for processing

            bool invalid = true;
            for(int i = 0; i < 26; i++)
            {
                if(current->next[i] != 0 ) //&& i != (c-base))
                {
                    invalid = false;
                }
            }
            if(current->isStr == 0 && invalid)
            {
                delete current;
            }
            else
            {
                break;
            }
            nodes.top()->next[c-base] = 0;
            nodes.pop();
        }
        return true;
    }
    else
      return false;
}

int main()
{
    /*
    Trie t;
    t.insert("a");
    t.insert("abandon");
    char *c = "abandon";
    t.insert(c);
    t.insert("abashed");
    if(t.search("abashed"))
      printf("true\n");
      */
    Trie t;
    t.insert("abc");         
    t.insert("d");
    char * c = "dda";
    t.insert(c);
    t.insert("da");
    if(t.search("da"))
    {
        printf("find\n");
    }
    t.deleteWord("dda");
    if(!t.search("dda"))
    {
        printf("not find\n");
    }
    t.deleteWord("d");
    if(!t.search("d"))
    {
        printf("not find\n");
    }
    if(t.search("da"))
    {
        printf("find\n");
    }       
    //t.deleteTrie(t.root);
    return 0;
}
