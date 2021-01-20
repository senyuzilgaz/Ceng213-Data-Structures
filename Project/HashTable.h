#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

#define BUCKET_SIZE 2
using namespace std;

template <class K, class T>
class HashTable {
    struct Entry {
        K Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[BUCKET_SIZE];
    };

    int _capacity; // INDICATES THE TOTAL CAPACITY OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket* _table; // THE HASH TABLE


    void insert_Help(const K& key, int& ind, int& b_ind);


public:

    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    // COPY THE WHOLE CONTENT OF RHS INCLUDING THE KEYS THAT WERE SET AS DELETED
    HashTable(const HashTable<K, T>& rhs);
    HashTable<K, T>& operator=(const HashTable<K, T>& rhs);
    ~HashTable();


    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF THE LOAD FACTOR OF THE TABLE IS GREATER THAN 0.6,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(const K& key, const T& value);

    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, THROW ItemNotFoundException()
    void Delete(const K& key);

    // IT RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, RETURN 0
    int Get(const K& key) const;

    // RESIZES THE TABLE, HASH ALL THE TABLE AGAIN, ACCORDING TO THE NEW CAPACITY
    void Resize(int newCapacity);

    int Capacity() const; // RETURN THE TOTAL CAPACITY OF THE TABLE
    int Size() const; // RETURN THE NUMBER OF ACTIVE ITEMS
    void getKeys(K* keys); // PUT THE ACTIVE KEYS TO THE GIVEN INPUT PARAMETER
};


template <class K, class T>
HashTable<K, T>::HashTable() {

    _size = 0;
    _capacity = 1162687;
    _table = new Bucket[_capacity];


}

template <class K, class T>
HashTable<K, T>::HashTable(const HashTable<K, T>& rhs) {

    _size = rhs._size;
    _capacity = rhs._capacity;
    _table = new Bucket[_capacity];

    for (int i = 0; i < _capacity; ++i) {
        _table[i] = rhs._table[i];
    }

}

template <class K, class T>
HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& rhs) {

    delete[] _table;


    _size = rhs._size;
    _capacity = rhs._capacity;
    _table = new Bucket[_capacity];

    for (int i = 0; i < _capacity; ++i) {
        _table[i] = rhs._table[i];
    }

}

template <class K, class T>
HashTable<K, T>::~HashTable() {

    delete[]_table;

}

template <class K, class T>
void HashTable<K, T>::Insert(const K& key, const T& value) {



    int ind = 0, b_ind = 0;
    bool f = true;

    insert_Help(key, ind, b_ind);

    if (_table[ind].entries[b_ind].Active && !(_table[ind].entries[b_ind].Deleted)) {
        f = false;
    }

    _table[ind].entries[b_ind].Key = key;
    _table[ind].entries[b_ind].Value = value;
    _table[ind].entries[b_ind].Active = true;
    _table[ind].entries[b_ind].Deleted = false;


    if (f) {
        ++_size;
    }




    if (_size * 10 >= _capacity * 12) {

        Resize(NextCapacity(_capacity));

    }

}
template <class K, class T>
void HashTable<K, T>::insert_Help(const K& key, int& index, int& b) {

    int h = Hash(key) % _capacity;
    int i = 1;


    while (1) {

        if (!(_table[h].entries[0].Active) || _table[h].entries[0].Deleted || _table[h].entries[0].Key == key) {
            index = h;
            b = 0;

            return;
        }

        else if (!(_table[h].entries[1].Active) || _table[h].entries[1].Deleted || _table[h].entries[1].Key == key) {
            index = h;
            b = 1;

            return;
        }

        else {
            h += (i * i);
            i += 1;

            if (h >= _capacity) {

                while (h >= _capacity) {
                    h -= _capacity;
                }
            }
        }

    }

}

template <class K, class T>
void HashTable<K, T>::Delete(const K& key) {

    int h = Hash(key) % _capacity;
    int i = 1;
    Bucket cur;

    while (1) {

        cur = _table[h];

        if (cur.entries[0].Active == false) {
            return;
        }

        if (cur.entries[0].Key == key) {

            _table[h].entries[0].Deleted = true;

            break;
        }

        if (cur.entries[1].Active == false) {
            return;
        }

        if (cur.entries[1].Key == key) {

            _table[h].entries[1].Deleted = true;

            break;
        }

        h += (i * i);
        i += 1;

        if (h >= _capacity) {

            while (h >= _capacity) {
                h -= _capacity;
            }
        }

    }
    

}

template <class K, class T>
int HashTable<K, T>::Get(const K& key) const {



    int h = Hash(key) % _capacity;
    int i = 1;

    Bucket cur;



    while (1) {
        if (!(_table[h].entries[0].Active)) {
            return 0;
        }

        else if (_table[h].entries[0].Key == key) {


            if ((_table[h].entries[0].Active) && !(_table[h].entries[0].Deleted)) {

                return  _table[h].entries[0].Value;
            }

        }
        if (!(_table[h].entries[1].Active)) {

        }
        else if (_table[h].entries[1].Key == key) {

            if ((_table[h].entries[1].Active) && !(_table[h].entries[1].Deleted)) {

                return  _table[h].entries[1].Value;
            }
        }

        h += i * i;
        i += 1;

        if (h >= _capacity) {

            while (h >= _capacity) {
                h -= _capacity;
            }
        }

    }



}


template <class K, class T>
void HashTable<K, T>::Resize(int newCapacity) {


    int k = _size;
    K* keys = new K[_size];
    T* values = new T[_size];


    for (int i = 0, j = 0; i < _capacity; ++i) {

        if (_table[i].entries[0].Active && !(_table[i].entries[0].Deleted)) {

            keys[j] = _table[i].entries[0].Key;
            values[j] = _table[i].entries[0].Value;
            ++j;

        }
        if (_table[i].entries[1].Active && !(_table[i].entries[1].Deleted)) {

            keys[j] = _table[i].entries[1].Key;
            values[j] = _table[i].entries[1].Value;
            ++j;

        }
    }
    delete[]_table;

    _size = 0;
    _capacity = newCapacity;
    _table = new Bucket[_capacity];

    for (int i = 0; i < k; ++i) {
        Insert(keys[i], values[i]);
    }

    delete[]keys;
    delete[]values;


}


template <class K, class T>
int HashTable<K, T>::Capacity() const {
    return _capacity;
}

template <class K, class T>
int HashTable<K, T>::Size() const {
    return _size;
}


template <class K, class T>
void HashTable<K, T>::getKeys(K* keys) {
    int index = 0;

    for (int i = 0; i < _capacity; i++) {
        Bucket& bucket = _table[i];
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (bucket.entries[j].Active && !bucket.entries[j].Deleted) {
                keys[index++] = bucket.entries[j].Key;
            }
        }
    }
}

#endif