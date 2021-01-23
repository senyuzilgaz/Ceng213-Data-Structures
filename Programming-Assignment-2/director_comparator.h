#ifndef _director_h__
#define _director_h__

#include "movie.h"
#include <cstring>

// Perform a case-insensitive, lexicographic comparison between the directors of two key arguments.
class DirectorComparator
{
  public:
    
    bool operator( ) (const Movie::SecondaryKey & key1, 
                      const Movie::SecondaryKey & key2) const
    {
      string first= key1.getDirector() , f=  key1.getTitle();
      string second= key2.getDirector() ,  s=  key2.getTitle()  ;
      
      for(int i=0; i< first.length(); ++i){
          if(first[i]<='Z' && first[i]>='A' ){
              first[i]+=('a'-'A');
          }
      }
      for(int i=0; i< second.length(); ++i){
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

        
        for(int i=0;  i<f.length(); ++i){
          if(f[i]<='Z' && f[i]>='A' ){
              f[i]+=('a'-'A');
          }
        }
        for(int i=0; i<s.length(); ++i){
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
