/*
 Hash Entry class

 
 The hash table will be made of an array of hash entries.
 Each instance of the HashEntry class has a Record and a flag.
 The flag is used to determine whether or not an index of the hash table is empty.
  Functions: constructors, getters & setters.
 */

#ifndef HashEntry_h
#define HashEntry_h
#include <iostream>
#include "Record.h"

class HashEntry
{
    
public:
    Record *rec;
    int flag;

    //constructors
    HashEntry()
    {
        flag = 0;
    }
    HashEntry(Record *aRecord)
    {
        rec = aRecord;
        flag = 0;
    }
    
    //getter and setter functions
    void setRecord(Record *theRecord) { rec = theRecord; }
    Record* getRecord() { return rec; }
    
    int getFlag() { return flag; }
    void setFlag(int aFlag) { flag = aFlag; }
    
};

#endif /* HashEntry_h */
