#include <vector>
#include <list>
using namespace std;

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable(int size = 101);

    void makeEmpty()
    {
        for(int i = 0; i < theLists.size(); i++)
            theLists[i].clear();
    }

    bool contains(const HashedObj & x) const
    {
        const list<HashedObj> & whichList = theLists[myhash(x)];
        return find(whichList.begin(), whichList.end(), x) != whichList.end();
    }

    bool remove(const HashedObj & x)
    {
        list<HashedObj> & whichList = theLists[myhash(x)];
        typename list<HashedObj>::iterator itr = find(whichList.begin(), whichList.end(), x);
        if(itr == whichList.end())
            return false;
        whichList.erase(itr);
        --currentSize;
        return true;
    }

    bool insert(const HashedObj & x)
    {
        list<HashedObj> & whichList = theLists[myhash(x)];
        if(find(whichList.begin(), whichList.end(), x) != whichList.end())
            return false;
        whichList.push_back(x);
        if(++currentSize > theLists.size())
            rehash();
        return true;
    }

  private:
    vector<list<HashedObj> > theLists;   // The array of Lists
    int  currentSize;

    void rehash()
    {
        vector<list<HashedObj> > oldLists = theLists;

        // Create new double-sized, empty table
        theLists.resize(2 * theLists.size());
        for(int j = 0; j < theLists.size(); j++)
            theLists[j].clear();

        // Copy table over
        currentSize = 0;
        for(int i = 0; i < oldLists.size(); i++)
        {
            typename list<HashedObj>::iterator itr = oldLists[i].begin();
            while(itr != oldLists[i].end())
                insert(*itr++);
        }
    }

    int myhash(const HashedObj & x) const
    {
        int hashVal = hash(x);

        hashVal %= theLists.size();
        if(hashVal < 0)
            hashVal += theLists.size();

        return hashVal;
    }
};

int main(){
    return 0;
}
