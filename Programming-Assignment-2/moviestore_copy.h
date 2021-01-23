#ifndef _moviestore_h__
#define _moviestore_h__

#include <string>
#include <iostream>

#include "bst.h"
#include "movie.h"
#include "director_comparator.h"
#include "title_comparator.h"


class MovieBalanceCondition
{
  public:
    bool operator() (int current_height, int ideal_height) const
    {
      if (current_height >= 2 * ideal_height + 1)
      {
        return false;
      }

      return true;
    }
};


class MovieStore 
{
  public:
    MovieStore();
    void insert(const Movie &); //Insert the parameter Movie object into all three BST indices
    void remove(const std::string &); //Remove the movie corresponding to the parameter id value from all indices
    void remove(const std::string &, const std::string &); //Remove the movie corresponding to the parameter title and director values in order from all indices
    void removeAllMoviesWithTitle(const std::string &); // Remove all movies with the paramter title from all indices
    void makeAvailable(const std::string &); // Makes the given key available in the moviestore.
    void makeUnavailable(const std::string &, const std::string &); // Makes the given key unavailable in the moviestore
    void updateCompany(const std::string &, const std::string &); // Changes company of all the director's movies to given company

  public:
    void printPrimarySorted( ) const; // It is primary indice which is sorted by movie's id's  lexicographic order
    void printSecondarySorted( ) const; // It is secondary indice which is sorted by movie's director's lexicographic order
    void printTernarySorted( ) const; // It is secondary indice which is sorted by movie's title's lexicographic order

  public:
    void printMoviesWithID(const std::string &,
                           const std::string &,
                           unsigned short =0) const;
    void printMoviesOfDirector(const std::string &,
                               const std::string & ="a",
                               const std::string & ="{") const;
  public:
    void printTrees( ) const
    {
      primaryIndex.print(std::cout);
      secondaryIndex.print(std::cout);
      ternaryIndex.print(std::cout);
    }

  private:
    typedef Movie::SecondaryKey SKey;
    typedef BinarySearchTree<std::string, Movie, MovieBalanceCondition> MSTP;
    typedef BinarySearchTree<SKey, const Movie *, 
                             MovieBalanceCondition, DirectorComparator> MSTS;
    typedef BinarySearchTree<SKey, Movie *,
                             MovieBalanceCondition, TitleComparator> MSTT;

  private:
    void printPrimarySorted(MSTP::Node *) const;
    void printSecondarySorted(MSTS::Node *) const;
    void printTernarySorted(MSTT::Node *) const;

  private:
    MSTP primaryIndex;
    MSTS secondaryIndex;
    MSTT ternaryIndex;
};


#endif