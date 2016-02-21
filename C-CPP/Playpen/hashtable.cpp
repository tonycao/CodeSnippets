#include <iostream>


using namespace std;

const int sz = 5;

struct data {
  int id;
  int val;
};

class Hashtable {
  data dt[sz];
  int numel;
public:
  Hashtable();
  int hash(int &id);
  int rehash(int &id);
  int insert(data &d);
  int remove(data &d);
  int retrieve(int &id);
  void output();
};


Hashtable::Hashtable() {
  for (int i = 0; i < sz; i++) {
    dt[i].id = -1;
    dt[i].val = 0;
  }
  numel = 0;
}

int Hashtable::hash(int &id) {
  return id % sz;
}

int Hashtable::rehash(int &id) {
  return (id + 1) % sz;
}

int Hashtable::insert(data &d) {
  if (numel < sz) {
    int hashid = hash(d.id);
    if (hashid >= 0 && hashid < sz) {
      if (dt[hashid].id == -1 || dt[hashid].id == -2) {
        dt[hashid].id = d.id;
        dt[hashid].val = d.val;
        numel++;
        return 0;
      } else {
        cout << "collision! rehashing..." << endl;
        int i = 0;
        while (i < sz) {
          hashid = rehash(hashid);
          if (dt[hashid].id == -1 || dt[hashid].id == -2) {
            dt[hashid].id = d.id;
            dt[hashid].val = d.val;
            numel++;
            return 0;
          }
          if (i == sz) {return -1;}
          i++;
        }
      }
    }
  } else {return -1;}
}

int Hashtable::remove(data &d) {
  int hashid = hash(d.id);
  if (hashid >= 0 && hashid < sz) {
    if (dt[hashid].id == d.id) {
      dt[hashid].id = -2;
      dt[hashid].val = 0;
      numel--;
      return 0;
    } else {
      int i = 0;
      while (i < sz) {
        hashid = rehash(hashid);
        if (dt[hashid].id == d.id) {
          dt[hashid].id = -2;
          dt[hashid].val = 0;
          numel--;
          return 0;
        }
        if (i == sz) {return -1;}
        i++;
      }
    }
  }
}

int Hashtable::retrieve(int &id) {
  int hashid = hash(id);
  if (hashid >= 0 && hashid < sz) {
    if (dt[hashid].id == id) {
      return dt[hashid].val;
    } else {
      int i = 0;
      while (i < sz) {
        hashid = rehash(hashid);
        if (dt[hashid].id == id) {
          return dt[hashid].val;
        }
        if (i == sz) {return 0;}
        i++;
      }
    }
  }
}

void Hashtable::output() {
  cout << "idx  id  val" << endl;
  for (int i = 0; i < sz; i++) {
    cout << i << "    " << dt[i].id << "    " << dt[i].val << endl;
  }
}


int main() {
  Hashtable hashtable;
  data d;
  d.id = 27;
  d.val = 27;
  hashtable.insert(d);
  hashtable.output();


  d.id = 99;
  d.val = 99;
  hashtable.insert(d);
  hashtable.output();

  d.id = 32;
  d.val = 32;
  hashtable.insert(d);
  hashtable.output();

  d.id = 77;
  d.val = 77;
  hashtable.insert(d);
  hashtable.output();

//retrieve data
  int id = 77;
  int val = hashtable.retrieve(id);
  cout << endl;
  cout << "Retrieving ... " << endl;
  cout << "hashtable[" << id << "]=" << val << endl;
  cout << endl;


//delete element
  d.id = 32;
  d.val = 32;
  hashtable.remove(d);
  hashtable.output();

  d.id = 77;
  d.val = 77;
  hashtable.remove(d);
  hashtable.output();


  return 0;
}