

class LRUCache{
private:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v):key(k), value(v){}
    };
    
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        else {
            // move the current visited node to the beginning of the list, update the address of the node
            //cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            CacheNode tmp = *cacheMap[key];
            cacheList.erase(cacheMap[key]);
            cacheList.push_front(tmp);
            cacheMap[key] = cacheList.begin();
            return cacheMap[key]->value;
        }
    }
    
    void set(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (cacheList.size() == capacity) {
                // delete end node of the list (least visited node)
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            // insert new node in teh beginning of the list, update map
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        } else {
            // update node value, move the current visited node to the beginning of the list, update the address of the node
            cacheMap[key]->value = value;
            //cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            CacheNode tmp = *cacheMap[key];
            cacheList.erase(cacheMap[key]);
            cacheList.push_front(tmp);
            cacheMap[key] = cacheList.begin();
        }
    }
private:
    int capacity;
    list<CacheNode> cacheList;
    unordered_map<int, list<CacheNode>::iterator> cacheMap;
};
