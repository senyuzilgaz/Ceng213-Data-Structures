#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <functional>
#include <cstddef>
#include <ostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>
 using namespace std;

#include <iostream>  


class DefaultBalanceCondition 
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      return true;
    }
};


template <typename Key, typename Object,
          typename BalanceCondition=DefaultBalanceCondition,
	  typename Comparator=std::less<Key> >
class BinarySearchTree
{
  public:  
    struct Node   // core structure of BinarySearchTree
    {
       Key key;         // unique key
       Object data;     // data to be stored, characterized by key
       Node * left;     // pointer to left subtree
       Node * right;    // pointer to right subtree
       size_t height;   // height of the node
       size_t subsize;  // size of the subtree node roots including itself

       Node(const Key &, const Object &, 
            Node *, Node *, size_t =0, size_t =1);   // Node constructor
    };

  public:  
    BinarySearchTree();  // zero-parameter constructor
    BinarySearchTree(const std::list<std::pair<Key, Object> > &); // list is always sorted!
    ~BinarySearchTree();  // destructor

  public:  
    void insert(const Key &, const Object &);  // insert new Key-Object
    void remove(const Key &);  // remove Node characterized by Key
    void toCompleteBST();  // convert into a complete BST

  public:  
    Node * find(const Key &) const; // single item
    std::list<Node *> find(const Key &, const Key &) const; // range queries
    int height() const;  // return the height of the tree
    size_t size() const; // return the number of items in the tree
    bool empty() const;  //return whether the tree is empty or not
    Node * getRoot() const; // return a pointer to the root of the tree
    void print(std::ostream &) const;  // print tree structure into an output stream

  private:  
    Node * root;                     // designated root
    size_t numNodes;                 // size
    Comparator isLessThan;           // operator upon which BST nodes are arranged
    BalanceCondition isBalanced;     // signals whether the BST is balanced or not
  
  private:  
    Node * find(const Key &, Node *) const;
    int height(Node *) const;
    int subsize(Node *) const;
    void print(Node *, std::ostream &) const;

   

  private:
    void makeEmpty(Node * &);// utility for destructor  
    void makeArray(Node * , Node * [], int &);
    void completeHelp(Node*[], int, Node * &); // utility for toCompleteBST
    template <typename iter>
    void constructorHelp(Node*& , iter &, int, int) const; // utility for constructor
    void insertHelp(const Key & , const Object & , Node * & ); // utility for constructor
    void removeHelp(const Key & , Node * & , Node * & , char ); // utility for removal
    Node* succesor(Node*  , Node* , Node*&, Node*& ); // Fýnds successor of a node
    int findMid( int); // Finds middle node for complete tree with given length
    
    
    // Define your private utility functions below this line


    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

  private:  // static utility functions
    template <typename T> //static utility function
    static const T & max(const T &, const T &);


     

};

#endif


template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::Node::
Node(const K & _k, const O & _d, Node * _l, Node * _r, size_t _h, size_t _s)
  : key(_k), data(_d), left(_l), right(_r), height(_h), subsize(_s)
{
}


template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::BinarySearchTree()
  : root(NULL), numNodes(0)  //comparator(C() ??)
{
}


template <typename K, typename O, typename B, typename C>

BinarySearchTree<K,O,B,C>::BinarySearchTree(const std::list<std::pair<K,O> > & datalist)
   : root(NULL), numNodes(0)  // change it as you'd like
{
    
    typename std::list<std::pair<K,O> >::const_iterator iter= datalist.begin();
    numNodes= datalist.size();
    constructorHelp(root, iter, 0, numNodes);
}
template <typename K, typename O, typename B, typename C>
template <typename iter >
void
BinarySearchTree<K,O,B,C>::constructorHelp( Node*& current, iter & i, int ind, int  length) const

{
  if(ind<length){
      current= new Node(i->first, i->second, NULL, NULL, 0,1);
      
      if(2*ind+1<length){
          constructorHelp(current->left, i, 2*ind+1, length);
      }
      current->key= i->first;
      current->data= i->second;
      ++i;
      if(2*ind+2<length){
          constructorHelp(current->right, i, 2*ind+2, length);
      }
      current->height= max( height(current->left), height(current->right))+1;
      current->subsize= subsize(current->left)+subsize(current->right)+1;
  }
 
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::toCompleteBST()
{   
    int i=0;
    Node* arr[100];
    makeArray(root, arr, i);
    completeHelp(arr, numNodes, root);

}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::makeArray( Node*  cur, Node *arr[], int &i)
{
    if(!cur){
        return;
    }
    makeArray(cur->left, arr, i);
    arr[i++]=cur;
    makeArray(cur->right, arr, i);
}
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::findMid( int length)
{
    int len, x, y, mid;
    len= length;
    
    if(len==0){
        mid=-1;
        return mid;
    }
    
    
    x= floor( log2( len+1)) ;
    y= pow( 2, x)-1;
    mid= floor(y/2);
    
    if(pow(2, x-1)>= len-y){
        mid+= len-y;
    }
    
    else{
        mid+= pow(2, x-1);
    }
    return mid;
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::completeHelp(Node* arr[], int len, Node * & current)
{
    int mid;
    if(!len){
        current=nullptr;
        return;
    }
    mid=findMid(len);
    
    if(mid==-1){
        current=nullptr;
        return;
    }
    
    
    current=*(arr+mid);
    
    
    completeHelp(arr, mid, current->left);
    
    completeHelp(arr+mid+1,len-mid-1, current->right);
    
    if(!current->left && !current->right){
        current->height=0;
        current->subsize=1;
    }
    else{
        current->height= max(height(current->left), height(current->right))+1;
        current->subsize= subsize(current->left)+subsize(current->right)+1;
    }
    
    
    
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insert(const K & k, const O & x)
{
    insertHelp(k, x, root);
    
}


template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::insertHelp(const K & key, const O & obj, Node * & current)
{
  if (current == NULL)
  {
    current= new Node(key, obj, NULL, NULL, 0, 1);
    
  }
  else if (isLessThan(key, current->key))
  {
    insertHelp(key, obj, current->left);
    
    current->height= max(height(current->left),height(current->right))+1;
    current->subsize= subsize(current->left)+subsize(current->right)+1;
    
    if(!isBalanced( height(current),  floor(log2(current->subsize) ) )  ){
        int i=0;
        Node* arr[100];
        makeArray(current, arr, i);
        completeHelp(arr, current->subsize, current);
    }
    
  }
  else if (isLessThan( current->key, key))
  {
    insertHelp(key, obj, current->right);
    
    current->height= max(height(current->left),height(current->right))+1;
    current->subsize= subsize(current->left)+subsize(current->right)+1;
    
    if(!isBalanced( height(current), floor(log2(current->subsize) )) ){
        int i=0;
        Node* arr[100];
        makeArray(current, arr, i);
        completeHelp(arr, current->subsize, current);
    }
    
    
  }
  else 
  {
    current->data= obj;
    
  }
}


template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::remove(const K & k)
{

    Node* del=find(k,root);
    
    if(del==NULL){
        return;
    }
    
    removeHelp(k, root, root,  'x');
    delete del;
    numNodes--;
    
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::removeHelp(const K & key, Node * &current, Node * &ancestor, char ch)
{
  if (current == NULL)
  {
    return;
  }
  else if (isLessThan(key, current->key))
  {
    removeHelp(key, current->left, current, 'l');
    current->height= max(height(current->left),height(current->right))+1;
    current->subsize= subsize(current->left)+subsize(current->right)+1;
    
    if(!isBalanced( height(current), floor(log2(current->subsize) )) ){
        int i=0;
        Node* arr[100];
        makeArray(current, arr, i);
        completeHelp(arr, current->subsize, current);
    }

  }
  else if (isLessThan(current->key, key))
  {
    removeHelp(key, current->right, current, 'r');
    current->height= max(height(current->left),height(current->right))+1;
    current->subsize= subsize(current->left)+subsize(current->right)+1;
    
    if(!isBalanced( height(current), floor(log2(current->subsize) )) ){
        int i=0;
        Node* arr[100];
        makeArray(current, arr, i);
        completeHelp(arr, current->subsize, current);
    }
    
  }
  else //found
  {
    Node* temp=current;
    if(!current->left && !current->right){
        
        if( ch=='x'){
            current=NULL;
            root=NULL;
        }
        
        if( ch=='l'){
            current=NULL;
            ancestor->left=NULL;
            
        }
        if( ch=='r'){
            current=NULL;
            ancestor->right=NULL;
        }
        if(ch=='z'){
            current=NULL;
        }
        
        
    }
    
    else if( (current->left && current->right)==0 && (current->left || current->right)==1 ){
        
        if(current->right){
            if(ch=='x'){
                current=current->right;
                root=current;

            }
            if(ch=='l'){
                current=current->right;
                ancestor->left=current;
               
            }
            if(ch=='r'){
                current=current->right;
                ancestor->right=current;

            }
            if(ch=='z'){
                current=current->right;
            }
        }
        
        if(current->left){
            if(ch=='x'){
                current=current->left;
                root=current;
  
            }
            if(ch=='l'){
                current=current->left;
                ancestor->left=current;
   
            }
            if(ch=='r'){
                current=current->left;
                ancestor->right=current;
  
            }
            if(ch=='z'){
                current=current->left;
  
            }
        }
    }
    else{
        Node* suc, *an;
        succesor(current->right, current, suc, an);
        removeHelp(suc->key,current->right, current->right,'z');
        suc->right=current->right;
        suc->left=current->left;
        current=suc;
        
    }
    if(current){
       current->height= max(height(current->left),height(current->right))+1;
        current->subsize= subsize(current->left)+subsize(current->right)+1;
        if(!isBalanced( height(current), floor(log2(current->subsize) )) ){
        int i=0;
            Node* arr[100];
            makeArray(current, arr, i);
            completeHelp(arr, current->subsize, current);
        } 
    }   
  }
  
}
template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::succesor(Node*  current , Node*  ancestor, Node *& suc, Node*&an)
{
    
  while(current->left){
      ancestor=current;
      current=current->left;
  }
  an=ancestor;
  suc=current;
}

template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key) const
{
  return find(key, root);
}


template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::find(const K & key, Node * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

template <typename K, typename O, typename B, typename C>
std::list<typename BinarySearchTree<K,O,B,C>::Node *>
BinarySearchTree<K,O,B,C>::find(const K & lower, const K & upper) const
{
    std::list<Node *> ranges;
    
    stack<Node *> s; 
    Node *current = root; 
  
    while (current  || !s.empty() ) 
    { 
        while (current  ) 
        { 
            s.push(current);
            
            if(current->key<lower){
                current=NULL;
            }
            else{
                current= current->left; 
            }
        }
        
        current =s.top(); 
        s.pop();
        if(current->key>=lower && current->key<= upper ){
                    ranges.push_back(current);
                }
        if(current->key>=upper){
            
            current=NULL;
        }
        else{
            current = current->right; 
        }
    } 
  return ranges;
}


template <typename K, typename O, typename B, typename C>
typename BinarySearchTree<K,O,B,C>::Node *
BinarySearchTree<K,O,B,C>::getRoot() const
{
  return root;
}


template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height() const
{
  return height(root);
}


template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::height(Node * t) const
{
  return (t == NULL) ? -1 : t->height;
}




// private utility
template <typename K, typename O, typename B, typename C>
int
BinarySearchTree<K,O,B,C>::subsize(Node * t) const
{
  return (t == NULL) ? 0 : t->subsize;
}


template <typename K, typename O, typename B, typename C>
size_t
BinarySearchTree<K,O,B,C>::size() const
{
  return numNodes;
}


template <typename K, typename O, typename B, typename C>
bool
BinarySearchTree<K,O,B,C>::empty() const
{
  return numNodes == 0;
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::makeEmpty(Node * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;

    --numNodes;
  }
  
  t = NULL;
}

template <typename K, typename O, typename B, typename C>
BinarySearchTree<K,O,B,C>::~BinarySearchTree()
{
  makeEmpty(root);
}


template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}

template <typename K, typename O, typename B, typename C>
void
BinarySearchTree<K,O,B,C>::print(Node * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << ",S" << t->subsize << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}


template <typename K, typename O, typename B, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,B,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}
