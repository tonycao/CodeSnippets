//hash.h 
//2011/11/13   By Adoo
#ifndef  HASH_H
#define HASH_H
template<typename type,typename long (*count_key)(type)>
class hash{
public:
     hash(std::size_t size, const type empty, const type deleted):_size(size),  
        _ref_count(new std::size_t (1)),table(NULL),_empty(empty),_deleted(deleted)
    {
        //get the adjacency prime with the size;
        do{
            if(is_prime(_size))
                break;
            else
                ++_size;
        }while(true);
        //allocate the memoey
        table=new type[_size]();
        for(std::size_t i=0 ; i!=_size; ++i)
        {
            table[i]=_empty;
        }
    }
    ~hash()
    {
        decr_cout();
    }
    bool insert(const type& k)
    {//insert an element k to hash table
        long a=std::abs(count_key(k));
        for(size_t i=0; i!=_size; ++i)
        {
            long index=hash_function(count_key(k),i);
            if(table[index]==_empty || table[index]==_deleted)
            {
                table[index]=k;
                return true;
            }
        }
        return false;
    }
    const type& search(const type& k)
    {
        long key=std::abs(count_key(k));
        for(std::size_t i=0; i!=_size; ++i)
        {
            type ty=table[hash_function(key,i)] ;
            if( ty== k )
                return  table[hash_function(key,i)] ;
            if(ty=_empty)
                break;
        }
        return _empty;
    }
    hash(const type& t)
    {
        ++*t.ref_count;
        decr_count();
        ref_count=t.ref_count;
        table=t.table;
    }
    hash& operator=(const hash& t){
        ++*t.ref_count;
        decr_count();
        ref_count=t.ref_count;
        table=t.table;
        return *this;
    }
    const type& operator[](const type& t){
        return search(t);
    }
    const hash& operator=(const hash& t) const{
        ++*t.ref_count;
        decr_count();
        ref_count=t.ref_count;
        table=t.table;
        _empty=t._empty;
        _deleted=t._deleted;
        return *this;
    };
private:
    void decr_cout()
    {
        if(!--*_ref_count)
        {
            delete _ref_count;
            delete [] table;
        }
    }
    long hash_function(long key,std::size_t count)
    {
        return (key%_size + count* (1 + key%(_size - 1)) % _size);
    }
    bool  is_prime(std::size_t l)
    {
            bool prime=true;
            std::size_t sqrt=std::sqrtl( l )+1;
            for(int i=2; i!=sqrt; ++i)
            {
                if(l%i ==0 )
                {
                    prime=false;
                    break;
                }
            }
            return prime;
    }
private:
    std::size_t  _size;
    std::size_t  *_ref_count;
    type   *table;
    const type _empty;
    const type _deleted;
};
#endif