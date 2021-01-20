#ifndef WORD_H
#define WORD_H


#include <string>
using namespace std;

class Word {
public:

    // Constructors
    Word(): key("zero"), value(0) {}

    Word(const string key, int value) : key(key), value(value) {}

    Word& operator=(const Word& rhs) {

        key = rhs.key;
        value = rhs.value;
        return *this;
    }


    const string getKey() const {
        return key;
    }

    void setKey( string ke)  {
        key = ke;
    }

    int getValue() const {
        return value;
    }

    void setValue( int val) {
        value = val;
    }


private:
    string key; 
    int value; 

};
#endif //WORD_H
