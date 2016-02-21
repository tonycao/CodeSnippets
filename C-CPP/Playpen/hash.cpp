class Hash {
public:
    Hash(): seed_(131), size_(0) {
        memset(head_, 0, sizeof(head_));
    }
    
    void Insert(const char* str) {
        unsigned int id = hash(str);
        char *dst = (char*)node_[size_].word;
        while(*dst++ = *str++);
        node_[size_].next = head_[id];
        head_[id] = &node_[size_];
        ++size_;
    }

    bool Find(const char* str) {
        unsigned int id = hash(str);
        for(Node* p=head_[id]; p; p=p->next) {
            char* dst = (char*)p->word;
            int i = 0;
            for(; *(str+i) && *(str+i)==*(dst+i); ++i);
            if(!*(str+i) && !*(dst+i)) return true;
        }
        return false;
    }
    
private:
    unsigned int hash(const char* str) {// BKDR Hash Function
        unsigned int hash = 0;
        while(*str) {
            hash = hash * seed_ + (*str++);
        }
        return (hash & 0x7FFFFFFF) % kHashSize;
    }
    
private:
    unsigned int seed_;
    unsigned int size_;
    static const int kWordSize = 26 + 1;
    static const int kNodeSize = 20000;
    static const int kHashSize = 10001;
    struct Node {
        char word[kWordSize];
        Node *next;
    };
    Node node_[kNodeSize];
    Node* head_[kHashSize];
};