#include "HashTable.h"
#include "HashUtils.h"
#include "HashUtils.cpp"
#include "Word.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main()
{
    clock_t sstart, eend;
    sstart = clock();
    HashTable<string,long> Table;
    string word, start, end , *keys, stopwords[571];
    string documents[22] = { "reut2-000.sgm" ,"reut2-001.sgm" ,"reut2-002.sgm" ,"reut2-003.sgm" ,"reut2-004.sgm" ,
                            "reut2-005.sgm" ,"reut2-006.sgm" ,"reut2-007.sgm" ,"reut2-008.sgm" ,"reut2-009.sgm" ,
                            "reut2-010.sgm" ,"reut2-011.sgm" ,"reut2-012.sgm" ,"reut2-013.sgm" ,"reut2-014.sgm" ,
                            "reut2-015.sgm" ,"reut2-016.sgm" ,"reut2-017.sgm" ,"reut2-018.sgm" ,"reut2-019.sgm" ,
                            "reut2-020.sgm", "reut2-021.sgm" };
    Word most[10];

    
    bool flag = true;  // Flag is for reading only body part. It becomes true when it sees <Body>, false when it sees </Body>
    ifstream file;
    start = "<BODY>";
    end = "</BODY>";

    file.open("stopwords.txt");
    for (int i = 0; file >> word; ++i) {
        stopwords[i] = word;
    }
    file.close();


    for (int i = 0; i < 22; ++i) {

        file.open(documents[i]);

        while (file >> word)
        {
            

            if (word.find(start) != string::npos) {
                flag = false;
                word = First(word, word.find(start));
            }
            else if (word.find(end) != string::npos) {
                flag = true;
            }
            // If we are not in body part, it skips without inserting that word to table
            if (flag) {
                continue;
            }

            //Since "U.S." is converted to "us" in toLower function, and "us" is in the stopwords list, we had to insert it manually
            if (word == "U.S.") {
                Table.Insert("US", Table.Get("US") + 1);
            }           
            word = toLower(word);

            //Since toLower function eliminates all punctuation marks and numbers, it may return empty string
            if (word == "") 
                continue;
            //Inserts the word to the Hashtable
            Table.Insert(word, Table.Get(word) + 1);
        }
        file.close();
    }

    

    //Deletes stopwords from the Hashtable
    for (int i = 0; i < 571; ++i) {
        Table.Delete(stopwords[i]);
    }
    keys = new string[Table.Size()];
    Table.getKeys(keys);
    
    //Traverses the Hashtable then inserts most 10 frequents words to MOST list

    for (int i = 0; i < Table.Size(); ++i) {
        if (i < 10) {
            most[i].setKey(keys[i]);
            most[i].setValue( Table.Get(keys[i]) );
        }
        else {
            insertionSort(most);
            if (Table.Get(keys[i]) > most[0].getValue() ){
                most[0].setKey(keys[i]);
                most[0].setValue(Table.Get(keys[i]));
            }
        }
        
    }
    insertionSort(most);

    //Prints the most frequent words list
    for (int i = 9; i >=0; --i){
        cout << "Word: " << most[i].getKey() << "    Count: " << most[i].getValue() << endl;
    }
    delete[]keys;

    //Printing time spent (milliseconds)
    eend = clock();

    cout << "Time spent: "<< eend - sstart<< " milliseconds"<<endl;
    return 0;

}


