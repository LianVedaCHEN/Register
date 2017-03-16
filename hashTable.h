//
//  hashTable.h
//  project5
//
//  Created by Veda on 16/11/21.
//  Copyright © 2016年 Veda. All rights reserved.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdio.h>
#include <iostream>
#include <functional>
#include <list>
#include "SDList.h"
#include <vector>
using std::less;
using std::vector;
using std::cout;
using std::endl;
template <typename Key,class ValueObject,typename Compare=less<ValueObject> >
class HashTable{
public:
    class iterator;
    friend  class iterator;
    typedef int (*HashFunc) (const Key&, int);//define the type and mode of hash function
    HashTable();//default construtor
    ~HashTable();//destrutor
    HashTable(HashFunc f,int size); //conversion constructor 
    HashTable(const HashTable& table);//copy constructor
    HashTable<Key,ValueObject,Compare>& operator=(const HashTable&);// overload the operator =
    HashTable<Key,ValueObject,Compare>* operator=(const HashTable*) const;
    ValueObject* operator[](const Key& key ); //overload the oprator[] so the user can find object in hash table by key
    void insert(const Key& key,ValueObject Item);
    //differenct version of remove
    void remove(const Key& key,const ValueObject& item);
    void remove(const Key& key);
    //different version of query
    bool query(const Key& key, ValueObject&);
    bool query(const Key& key);
    void clear();
    bool isEmpty() const;
    int size() const;
    iterator begin();
    iterator end();
    iterator begin()const;
    iterator end()const;
private:
    // hash table store the struct Element and new added ValueObject will be added into a object of Element and then stored in hash table
    struct Element{
    public:
        Key index;
        ValueObject data;
        bool operator<(const Element& ele) const{
            return (data<ele.data);}
        bool operator==(const Element& ele) const{
            return (data==ele.data);
        }
        bool operator==(const Element& ele) {
            return (data==ele.data);
        }
        
    };
    //store the hash function so the hash function can be initialized when construct
    HashFunc hash;
    int bucketSize;
    int elementNo;
    SDList<Element> **bucket;
    Compare comtor;
    HashFunc hashDefault(const Key& key, int s ){
        return key%s;
    }
    
};

template <typename Key,class ValueObject,typename Compare >
class HashTable<Key,ValueObject,Compare>::iterator{
public:
    iterator();
    iterator(const HashTable& table,int temp=0,int no=0);
    iterator(const iterator& itr);
    ~iterator();
    iterator& operator=(const iterator& itr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& itr);
    bool operator!=(const iterator& itr);
    ValueObject operator*();
    ValueObject* operator&();
    
private:
    SDList<Element>* current;
    typename SDList<Element>::iterator innerIterator;
    int currentIndex;
    int sizeOfTable;
    const HashTable* table;
};

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::iterator::iterator():current(NULL),currentIndex(0),sizeOfTable(0),table(NULL){}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::iterator::iterator(const HashTable& table1,int temp,int no):current(&(*table1.bucket[temp])),innerIterator((no==0)?(*(table1.bucket[temp])).begin():(*(table1.bucket[temp])).end()),currentIndex(temp),sizeOfTable(table1.bucketSize){
    
    table =  &table1;
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::iterator::iterator(const iterator& itr):current(itr.current),innerIterator(itr.innerIterator),currentIndex(itr.currentIndex),sizeOfTable(itr.sizeOfTable),table(itr.table){}


template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::iterator::~iterator(){
    if(current){
        current=0;
    }
    if(table)
        table=0;
    
}


template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator& HashTable<Key,ValueObject,Compare>::iterator::operator=(const iterator& itr){
    current=itr.current;
    innerIterator=itr.innerIterator;
    table =itr.table;
    sizeOfTable=itr.sizeOfTable;
    currentIndex=itr.currentIndex;
    return *this;
}




template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator& HashTable<Key,ValueObject,Compare>::iterator::operator++(){
    //when the iterator is beyond the boundary, report error 
    if(currentIndex==table->bucketSize){
        cout<<"beynd the upper boundary"<<endl;
        return *this;
    }
    // when iterator is at the end of hash table, ++ can not make it move any more
    if((currentIndex==table->bucketSize-1)&&(innerIterator==current->end())){
        innerIterator=current->end();
        return *this;
    }
    if(!current||current->size()==0){
        //if the bucket the iterator points now is empty, move to next bucket until it move to the one with element
        for(int i=currentIndex+1;i<table->bucketSize;i++){
            if((table->bucket[i]->size())!=0){
                current=table->bucket[i];
                innerIterator=current->begin();
                currentIndex=i;
                
                break;            }
        }
    }
    else{
        //if the bucket is not empty, ++ only makes it move to another element in the list
        if(currentIndex!=(table->bucketSize-1)&&innerIterator==(--(current->end()))){
            int count=0;
            for(int i=currentIndex+1;i<=table->bucketSize;i++){
                if(i<table->bucketSize){
                    if((table->bucket[i]->size())!=0){
                        current=table->bucket[i];
                        innerIterator=current->begin();
                        currentIndex=i;
                        break;
                    }
                }
                else{
                    count=i;
                }
            }

            if(count==table->bucketSize){
                innerIterator=current->end();
            }
            
        }
        else if(innerIterator==(--(current->end()))&&currentIndex==(table->bucketSize-1)){
            innerIterator=current->end();
        }
        
        else {
            
            innerIterator++;
            
        }
    }
    return *this;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::iterator::operator++(int){
    HashTable<Key,ValueObject,Compare>::iterator temp=*this;
    this->operator++();
    return temp;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator& HashTable<Key,ValueObject,Compare>::iterator::operator--(){
    if((currentIndex==0)&&innerIterator==current->begin()){
        cout<<"beynd the lower boundary"<<endl;
        return *this;
    }
    if(!current||current->size()==0){
        for(int i=currentIndex;i>=0;i--){
            if((table->bucket[i]->size())!=0){
                current=table->bucket[i];
                innerIterator=current->end()--;
                currentIndex=i;
                break;            }
        }
    }
    else{
        if(innerIterator!=(current->begin())){
            --innerIterator;
        }
        else {
            for(int i=currentIndex;i>=0;i--){
                if((table->bucket[i]->size())!=0){
                    current=table->bucket[i];
                    innerIterator=current->end()--;
                    currentIndex=i;
                    break;            }
            }
            
        }
    }
    return *this;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::iterator::operator--(int){
    HashTable<Key,ValueObject,Compare>::iterator temp=*this;
    this->operator--();
    return temp;
}

template <typename Key,class ValueObject,typename Compare >
bool HashTable<Key,ValueObject,Compare>::iterator::operator==(const iterator& itr){
    bool test=true;
    if(current!=itr.current){
        test=false;
    }
    if(currentIndex!=itr.currentIndex){
        test=false;
    }
    if(innerIterator!=itr.innerIterator){
        test=false;
    }
    return test;
    
}
template <typename Key,class ValueObject,typename Compare >
bool HashTable<Key,ValueObject,Compare>::iterator::operator!=(const iterator& itr){
    return !(*this==itr);
}

template <typename Key,class ValueObject,typename Compare >
ValueObject HashTable<Key,ValueObject,Compare>::iterator::operator*(){
    if(current->size()==0){
        throw std::runtime_error("Iteration has been broken");
    }
    return (*innerIterator).data;
}

template <typename Key,class ValueObject,typename Compare >
ValueObject* HashTable<Key,ValueObject,Compare>::iterator::operator&(){
    if(current->size()==0){
        throw std::runtime_error("Iteration has been broken");
    }
    return &(*innerIterator.data);
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::HashTable():elementNo(0),bucketSize(14),bucket(new SDList<Element>*[14]),comtor(Compare()),hash(hashDefault){
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::HashTable(HashFunc f,int size):elementNo(0),bucketSize(size),bucket(new SDList<Element>*[size]),comtor(Compare()),hash(f){
    for(int i=0;i<bucketSize;i++){
        bucket[i]=new SDList<Element>();
    }
    
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::HashTable(const HashTable& table):elementNo(table.elementNo),bucketSize(table.bucketSize),bucket(new SDList<Element>*[table.bucketSize]),comtor(table.comtor),hash(table.hash){
    if(table.bucket){
        bucket=new SDList<Element>* [bucketSize];
        for(int i=0;i<bucketSize;i++){
            bucket[i]=new SDList<Element>(*(table.bucket[i]));
        }
    }
    
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>::~HashTable(){
    if(bucket){
        for(int i=0;i<bucketSize;i++){
            delete bucket[i];
        }
        delete [] bucket;
    }
    bucketSize=0;
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>& HashTable<Key,ValueObject,Compare>::operator=(const HashTable<Key,ValueObject,Compare>& table){
    if(bucket){
        for(int i=0;i<bucketSize;i++){
            delete bucket[i];
        }
        delete [] bucket;
    }
    bucketSize=table.bucketSize;
    comtor=table.comtor;
    hash=table.hash;
    bucket=NULL;
    if(table.bucket){
        bucket=new SDList<Element>* [bucketSize];
        for(int i=0;i<bucketSize;i++){
            bucket[i]=new SDList<Element>(*(table.bucket[i]));        }
    }
    return *this;
    
}

template <typename Key,class ValueObject,typename Compare >
HashTable<Key,ValueObject,Compare>* HashTable<Key,ValueObject,Compare>::operator=(const HashTable<Key,ValueObject,Compare>* table) const{
    this=table;
    return *this;
    
}

template <typename Key,class ValueObject,typename Compare >
ValueObject* HashTable<Key,ValueObject,Compare>::operator[](const Key& key){
    SDList<Element>* temp = bucket[hash(key,bucketSize)];
    if(temp){
        typename list<Element>::iterator itr;
        itr=(*temp).begin();
        if(temp->size()!=0){
            for(;itr!=(*temp).end();itr++){
                if((*itr).index==key){
		   ValueObject* tempPtr=&((*itr).data);
                    return &((*itr).data);
                 
                }
            }
            
        }
        
        
    }
    return NULL;
}

template <typename Key,class ValueObject,typename Compare >
void HashTable<Key,ValueObject,Compare>::insert(const Key& key,ValueObject Item){
    //first put the ValueObject in a object of Element and then add it to hash table
    Element temp;
    temp.index=key;
    temp.data=Item;
    bucket[hash(key,bucketSize)]->insert(temp);
    elementNo++;
}

template <typename Key,class ValueObject,typename Compare >
void HashTable<Key,ValueObject,Compare>::remove(const Key& key){
    SDList<Element>* temp = bucket[hash(key,bucketSize)];
    if(temp){
        typename  SDList<Element>::iterator itr;
        itr=(*temp).begin();
        if(temp->size()!=0){
            for(;itr!=(*temp).end();itr++){
                if((*itr).index==key){
		   bucket[hash(key,bucketSize)]->erase(itr);
		    elementNo--;
                    break;
                }
            }
            
	    
        }
        
    }
    
}

template <typename Key,class ValueObject,typename Compare >
void HashTable<Key,ValueObject,Compare>::remove(const Key& key,const ValueObject& item){
    SDList<Element>* temp = bucket[hash(key,bucketSize)];
    if(temp){
            if(temp->size()!=0){
                Element tempE;
                tempE.index=key;
                tempE.data=item;
                temp->remove(tempE);
		 elementNo--;
            }
            
    }
}

template <typename Key,class ValueObject,typename Compare >
void HashTable<Key,ValueObject,Compare>::clear(){
    for(int i=0;i<bucketSize;i++){
        SDList<Element>* temp = bucket[i];
        if(temp){
            (*temp).clear();
            elementNo=0;
        }
    }
}

template <typename Key,class ValueObject,typename Compare >
bool HashTable<Key,ValueObject,Compare>::query(const Key& key, ValueObject& getItem){
    SDList<Element>* temp=bucket[hash(key,bucketSize)];
    if(temp->size()==0){
        return false;
    }
    typename list<Element>::iterator itr= temp->begin();
    for(;itr!=temp->end();itr++){
        if(key==(*itr).index){
            getItem=(((*itr).data));
            return true;
        }
    }
    
        return false;
}

template <typename Key,class ValueObject,typename Compare >
bool HashTable<Key,ValueObject,Compare>::query(const Key& key){
    SDList<Element>* temp=bucket[hash(key,bucketSize)];
    if(temp->size()==0){
        return false;
    }
    typename list<Element>::iterator itr= temp->begin();
    for(;itr!=temp->end();itr++){
        if(key==(*itr).index){
            return true;
        }
    }
    return false;
}


template <typename Key,class ValueObject,typename Compare >
bool HashTable<Key,ValueObject,Compare>::isEmpty() const{
    return elementNo==0;
}

template <typename Key,class ValueObject,typename Compare >
int HashTable<Key,ValueObject,Compare>::size() const{
    return elementNo;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::begin(){
    int temp_current=0;
    for(int i=0;i<bucketSize;i++){
        if(bucket[i]->size()!=0){
            temp_current=i;
            break;
        }
    }
    HashTable<Key,ValueObject,Compare>::iterator temp(*this,temp_current,0);
    return temp;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::end(){
    int temp_current=0;
    for(int i=bucketSize-1;i>=0;i--){
        if(bucket[i]->size()!=0){
            temp_current=i;
            break;
        }
    }
    HashTable<Key,ValueObject,Compare>::iterator temp(*this,temp_current,1);
    return temp;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::begin() const{
    int temp_current=0;
    for(int i=0;i<bucketSize;i++){
        if(bucket[i]->size()!=0){
            temp_current=i;
            break;
        }
    }
    HashTable<Key,ValueObject,Compare>::iterator temp(*this,temp_current,0);
    return temp;
}

template <typename Key,class ValueObject,typename Compare >
typename HashTable<Key,ValueObject,Compare>::iterator HashTable<Key,ValueObject,Compare>::end() const{
    int temp_current=0;
    for(int i=bucketSize-1;i>=0;i--){
        if(bucket[i]->size()!=0){
            temp_current=i;
            break;
        }
    }
    HashTable<Key,ValueObject,Compare>::iterator temp(*this,temp_current,1);
    return temp;
}
#endif
