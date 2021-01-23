#include "moviestore.h"


MovieStore::MovieStore( ) 
{
}



void
MovieStore::insert(const Movie & movie)
{
    MSTP::Node *current;
    Movie* newMovie;
    SKey key23(movie);
    std::string key1= movie.getID();
    
    primaryIndex.insert(key1, movie);
    current=primaryIndex.find( movie.getID() );
    
    newMovie= &(current->data);
    secondaryIndex.insert(key23, newMovie);
    ternaryIndex.insert(key23, newMovie);
}


void
MovieStore::makeAvailable(const std::string & id)
{
    MSTP::Node *current;
    current=primaryIndex.find(id);
    
    (current->data).setAvailable();
    
}


void
MovieStore::makeUnavailable(const std::string & title,
                           const std::string & director)
{
    
    MSTP::Node *current, *pre;
    
    current=primaryIndex.getRoot();
    
    while (current) {
 
        if (current->left == NULL) {
            if(current->data.getTitle()== title && current->data.getDirector()==director){
                current->data.setUnavailable();
            }
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right  && pre->right != current){
               pre = pre->right; 
            }
                
  
            if ( ! pre->right) {
                pre->right = current;
                current = current->left;
            }

            else {
                pre->right = NULL;
                if(current->data.getTitle()== title && current->data.getDirector()==director){
                    current->data.setUnavailable();
                }
                current = current->right;
            } 
        } 
    }
}


void
MovieStore::updateCompany(const std::string & director, 
                           const std::string & Company)
{
    MSTP::Node *current, *pre;
    current=primaryIndex.getRoot();
    
    while (current) {
 
        if (current->left == NULL) {
            if(current->data.getDirector()==director){
                current->data.setCompany(Company);
            }
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right  && pre->right != current){
                pre = pre->right;
            }
                
  
            if ( ! pre->right) {
                pre->right = current;
                current = current->left;
            }

            else {
                pre->right = NULL;
                if(current->data.getDirector()==director){
                    current->data.setCompany(Company);
                }
                current = current->right;
            } 
        } 
    }
}

void
MovieStore::printMoviesWithID(const std::string & id1,
                              const std::string & id2,
                              unsigned short since) const
{
MSTP::Node *current, *pre;
    current=primaryIndex.getRoot();
    while (current != NULL) {
    
        if (current->left == NULL) {
            if(current->data.getID()<=id1 && current->data.getID()>=id2 && current->data.getYear()>=since){
                cout<<current->data.getID()<< std::endl;
            }
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL
                   && pre->right != current)
                pre = pre->right;
 
            if (pre->right == NULL) {
                
                pre->right = current;
                current = current->left;
            }
 
            else {
                pre->right = NULL;
                if(current->data.getID()<=id1 && current->data.getID()>=id2 && current->data.getYear()>=since){
                cout<<current->data.getID()<< std::endl;
            }
                current = current->right;
            }
        }
    }
}


void
MovieStore::printMoviesOfDirector(const std::string & director,
                                  const std::string & first,
                                  const std::string & last) const
{
    
    MSTS::Node *current, *pre;
    current=secondaryIndex.getRoot();
    
    std::string direc=director;
    for(int i=0; i< direc.length(); ++i){
          if(direc[i]<='Z' && direc[i]>='A' ){
              direc[i]+=('a'-'A');
          }
    }
    
    while (current) {
        
        if (current->left == NULL) {
            std::string dir=current->data->getDirector();
            for(int i=0; i< dir.length(); ++i){
              if(dir[i]<='Z' && dir[i]>='A' ){
                  dir[i]+=('a'-'A');
              }
            }
            if(dir==direc && current->data->getTitle()>=first && current->data->getTitle()<=last){
                cout<< *(current->data) <<endl;
                
            }
            current = current->right;
        }
        else {
 
            pre = current->left;
            while (pre->right  && pre->right != current)
                pre = pre->right;
  
            if ( ! pre->right) {
                pre->right = current;
                current = current->left;
            }

            else {
                
                pre->right = NULL;
                std::string dir=current->data->getDirector();
                for(int i=0; i< dir.length(); ++i){
                  if(dir[i]<='Z' && dir[i]>='A' ){
                      dir[i]+=('a'-'A');
                  }
                }
                if(dir==direc && current->data->getTitle()>=first && current->data->getTitle()<=last){
                    cout<< *(current->data) <<endl;
                
                }
                current = current->right;
            } 
        } 
    }
    
}



void 
MovieStore::printPrimarySorted( ) const
{
  printPrimarySorted(primaryIndex.getRoot());
}


void  
MovieStore::printPrimarySorted(MSTP::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printPrimarySorted(t->left);
  std::cout << t->data << std::endl;
  printPrimarySorted(t->right);
}


void  
MovieStore::printSecondarySorted( ) const
{
  printSecondarySorted(secondaryIndex.getRoot());
}


void  
MovieStore::printSecondarySorted(MSTS::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printSecondarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printSecondarySorted(t->right);
}


void  
MovieStore::printTernarySorted( ) const
{
  printTernarySorted(ternaryIndex.getRoot());
}


void  
MovieStore::printTernarySorted(MSTT::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printTernarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printTernarySorted(t->right);
}

