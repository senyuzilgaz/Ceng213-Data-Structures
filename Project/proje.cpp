#include "HashTable.h"
#include "HashUtils.h"
#include "HashUtils.cpp"
#include "Word.h"
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

// Sorts the most frequent words list in ascending order
void insertionSort(Word arr[])
{
    int i, j;
    Word key;
    for (i = 1; i < 10; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].getValue() > key.getValue() )
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
//Check if the word is in the stopwords list
bool isStopWord(string arr[], string word)
{
    for (int i = 0; i < 571; ++i)
    {
        if (arr[i] == word)
            return true;
    }
    return false;
}

//It converts string's all letters to lowercase while skipping punctuation marks and numbers.
string toLower( string str)
{
    string last;
    for (unsigned int i = 0; i < str.size(); ++i) {

        
        if (str[i] >= 'A' && str[i] <= 'Z') {
            last += (str[i] + ('a' - 'A'));
            continue;
        }
            

        else if (str[i] >= 'a' && str[i] <= 'z') {
            last += str[i];
            continue;
        }
            
        else if (str[i] == '\'') {
            last += str[i];
            continue;
        }
            
        
    }
    return last;
}
//Since the first word may be adjoined with "<Body>" it takes first word without "<Body>" part
string First(string str, int i)
{
    string last;
    for (int j = i+6; str[j]; ++j) {
        last += str[j];
    }
    return last;
}

int main()
{
    auto t_start = std::chrono::high_resolution_clock::now();
    HashTable<string,long> Table;
    string word, start, end , *keys, stopwords[571];
    string documents[22] = { "reut2-000.sgm" ,"reut2-001.sgm" ,"reut2-002.sgm" ,"reut2-003.sgm" ,"reut2-004.sgm" ,
                            "reut2-005.sgm" ,"reut2-006.sgm" ,"reut2-007.sgm" ,"reut2-008.sgm" ,"reut2-009.sgm" ,
                            "reut2-010.sgm" ,"reut2-011.sgm" ,"reut2-012.sgm" ,"reut2-013.sgm" ,"reut2-014.sgm" ,
                            "reut2-015.sgm" ,"reut2-016.sgm" ,"reut2-017.sgm" ,"reut2-018.sgm" ,"reut2-019.sgm" ,
                            "reut2-020.sgm", "reut2-021.sgm" };
    Word most[10];

    // Flag is for reading only body part. It becomes true when it sees <Body>, false when it sees </Body>
    bool flag = true;
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

            //Since "U.S." is converted to "us" in toLower function, and "us" is in the stopwords list, we had to insert it manually
            if (word == "U.S.") {
                Table.Insert("US", Table.Get("US")+1 );
            }
            else if (word.find(end) != string::npos) {
                flag = true;
            }
            // If we are not in body part, it skips without inserting that word to table
            if (flag) {
                continue;
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

    keys = new string[Table.Size()];

    //Deletes stopwords from the Hashtable
    for (int i = 0; i < 571; ++i) {
        Table.Delete(stopwords[i]);
    }

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
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    cout << "Time spent: "<<elapsed_time_ms<< " milliseconds"<<endl;
    return 0;

}


