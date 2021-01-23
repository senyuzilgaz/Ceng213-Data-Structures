#ifndef _title_h__
#define _title_h__

#include "movie.h"
#include <cstring>
#include "director_comparator.h"
using namespace std;

// Perform a case-insensitive, lexicographic comparison between the titles of two key arguments.
class TitleComparator
{
  public:
    
    bool operator( ) (const Movie::SecondaryKey & key1, 
                      const Movie::SecondaryKey & key2) const
    { 
      string first= key1.getTitle() , f=key1.getDirector();
      string second= key2.getTitle() , s=key2.getDirector();
  
      for(int i=0; i< first.length(); ++i){
          if(first[i]<='Z' && first[i]>='A' ){
              first[i]+=('a'-'A');
          }
      }
      for(int i=0; i<second.length(); ++i){
          if(second[i]<='Z' && second[i]>='A' ){
              second[i]+=('a'-'A');
          }
      }
      
      if(first<second){
          return true;
      }
      
      if(second<first){
          return false;
      }
      
      else{

        for(int i=0; i<f.length() ; ++i){
          if(f[i]<='Z' && f[i]>='A' ){
              f[i]+=('a'-'A');
          }
        }
        for(int i=0; i<s.length() ; ++i){
          if(s[i]<='Z' && s[i]>='A' ){
              s[i]+=('a'-'A');
          }
        }
    
        if(f<s){
            return true;
        }
          
        if(s<f){
            return false;
        }
        
      }
      
     
      
    }

};

#endif
