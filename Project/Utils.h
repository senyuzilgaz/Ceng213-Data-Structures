#ifndef __UTILS__
#define __UTILS__
#include "HashTable.h"
#include "Word.h"
#include <iostream>
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
        while (j >= 0 && arr[j].getValue() > key.getValue())
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
string toLower(string str)
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
    for (int j = i + 6; str[j]; ++j) {
        last += str[j];
    }
    return last;
}
#endif