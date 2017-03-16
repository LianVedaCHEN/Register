//
//  SDList.hpp
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#ifndef SDList_hpp
#define SDList_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <functional>
using std::less;
using std::list;



template <typename Item, typename Compare=less<Item> >
class SDList{
public:
    SDList();
    SDList(const Compare& comtor2);
    SDList(const SDList<Item,Compare>& q);
    ~SDList();
    SDList<Item,Compare>& operator=(SDList<Item,Compare>& list);
    bool isEmpty() const;
    int size() const;//return the number of element in the list
    Item* insert(Item value);// insert the item after sorting
    typedef bool(*Test)();
    void remove(Test f);//remove elements which satisfy the requirement
    void clear();
    typedef typename list<Item>::iterator iterator ;
    typedef typename list<Item>::const_iterator const_iterator ;
    void remove( const Item& ele);//
    void remove( Item* ele);// remove the element with the same value of item
    void erase(iterator& itr);//erase the item pointed by iteartor
    iterator begin() const;
    iterator end() const;
    typename list<Item>::iterator begin() ;
    typename list<Item>::iterator end() ;
   
private:
    list<Item> innerList;
    int elementSize;
    Compare comtor;
    
};

template <typename Item, typename Compare >
SDList<Item,Compare>::SDList():elementSize(0),comtor(Compare()){}

template <typename Item, typename Compare >
SDList<Item,Compare>::SDList(const Compare& comtor2):elementSize(0),comtor(comtor2){}

template <typename Item, typename Compare >
SDList<Item,Compare>::SDList(const SDList<Item,Compare>& q):elementSize(q.size()),comtor(q.comtor),innerList(q.innerList){}

template <typename Item, typename Compare >
SDList<Item,Compare>::~SDList(){
    innerList.clear();
    elementSize=0;
}

template <typename Item, typename Compare >
SDList<Item,Compare>& SDList<Item,Compare>::operator=(SDList<Item,Compare>& list){
    if(elementSize!=0){
        innerList.clear();
    }
    innerList=list.innerList;
    elementSize=list.size();
    comtor=list.comtor;
    return *this;
}

template <typename Item, typename Compare >
bool SDList<Item,Compare>::isEmpty() const{
    return (elementSize==0);
}

template <typename Item, typename Compare >
int SDList<Item,Compare>::size() const{
    return elementSize;
}

template <typename Item, typename Compare >
Item* SDList<Item,Compare>::insert(Item value){
    //the insert function will fisrt search for the whole doubly linked list 
    //and find the correct position for the new item and then insert
    typename std::list<Item>::iterator itr;
    Item* temp= &value;
    for(itr=innerList.begin();itr!=innerList.end();itr++){
        if(comtor(value,*itr)){
            break;
        }
    }
    innerList.insert(itr,value);
    elementSize++;
    return temp;
}

template <typename Item, typename Compare >
void SDList<Item,Compare>::remove(Test f){
    innerList.remove_if(f);
    elementSize--;
}

template <typename Item, typename Compare >
void SDList<Item,Compare>::remove(const Item& ele){
  int c=0;
  typename list<Item>::iterator itr=innerList.begin();
     for(;itr!=innerList.end();itr++){
	if(*itr==ele){
	  innerList.erase(itr++);
          elementSize--;
	  break;
	}
    }
}

template <typename Item, typename Compare >
void SDList<Item,Compare>::remove(Item* ele){
    elementSize--;
    typename list<Item>::iterator itr=innerList.begin();
     for(;itr!=innerList.end();itr++){
	if(*itr==*ele){
	  innerList.erase(itr++);
	  break;
	}
    }
}

template <typename Item, typename Compare >
void SDList<Item,Compare>::erase(iterator& itr){
    elementSize--;
   innerList.erase(itr++);
    
}

template <typename Item, typename Compare >
void SDList<Item,Compare>::clear(){
    innerList.clear();
    elementSize=0;
}

template <typename Item, typename Compare >
typename SDList<Item,Compare>::iterator SDList<Item,Compare>::begin() const{
    return innerList.begin();
}

template <typename Item, typename Compare >
typename SDList<Item,Compare>::iterator SDList<Item,Compare>::end() const{
    return innerList.end();
}

template <typename Item, typename Compare >
typename list<Item>::iterator SDList<Item,Compare>::begin() {
    return innerList.begin();
}

template <typename Item, typename Compare >
typename list<Item>::iterator SDList<Item,Compare>::end() {
    return innerList.end();
}


#endif /* SDList_hpp */
