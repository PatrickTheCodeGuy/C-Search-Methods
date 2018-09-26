/*
HashTable.h

 
 Class for the hash table. 
 This class creates a hash table by dynamically allocating an array of Records. The size of the array
 was determined by counting the amount of lines in the input file, multiplying by 2, & finding the next prime number.
 Functions: hash, insert, delete, statistics & print.
 */

#ifndef HashTable_h
#define HashTable_h
#include "Record.h"
#include "HashEntry.h"
#include <string>
class HashTable
{ 
private:
    
    int size; //size of hash table
    HashEntry **table;
    
public:
    
    /*
     Constructor
     Parameters: size of the array
     Creates an array of hash table entries
     sets each entry to null
     */
    HashTable(int arraySize)
    {
        size = arraySize;
        table = new HashEntry*[size]; //create array of Hash Entries
       
        for (int i = 0; i < size; i++)
            table[i] = NULL;
        
    }

    /*
     Hash function
     Parameters: a string, the primary key (record number) of the input
     Determines the index that the record will be entered into the array by squaring the value of the 
        index, and using modulo division
     */
    int hash(string recNum)
    {
        int sum = 0;
        
        for (int i = 0; i < recNum.length(); i++)
        {
            int tempA = stoi(recNum);
            sum += (tempA * tempA);
        }
        
        sum = sum % 53;
        
        return sum;
    }
    
    /*
     Insert Function
     Parameters: Record and a counter
     Finds the index of where each record will be entered in table by using the hash function
     Loops through the array up to the next available index, inserts the record, and sets the flag
     to 1 to signify the index is occupied.
     */
    void insert(Record *rec, int &count)
    {
        int index = hash(rec->getRecNum());
        
        while (table[index] != NULL && table[index]->getRecord() != rec)
        {
            index++;
            index %= size;
            count++;
        }
        table[index] = new HashEntry(rec);
        table[index]->setFlag(1);
        
    }
    
    /*
     Bad Hash function
     Parameter: a string, the primary key
     Converts the string to an integer and applies modulo division
     */
    int badHash(string recNum)
    {
        
        int sum = 0;
        
        for (int i = 0; i < recNum.length(); i++)
            sum += (recNum[i] * recNum[i]);
        
        sum = sum % 53;

        return sum;
    }
    
    /*
     Insert Function
     Parameters: Record and a counter
     Finds the index of where each record will be entered in table by using the hash function
     Loops through the array up to the next available index, inserts the record, and sets the flag
         to 1 to signify the index is occupied.
     */
    void badInsert(Record *rec, int &count)
    {
        int index = badHash(rec->getRecNum());

        while (table[index] != NULL && table[index]->getRecord() != rec && table[index]->getFlag() != -1)
        {
            index++;
            count++;
        }
        table[index] = new HashEntry(rec);
        table[index]->setFlag(1);
    }
    
    /*
     Statistics function
     Parameters: two ints, one holding the number of collisions, the other holding the number of entries in the array
     Displays the number of collisions that occurred when inserting entries into array.
     Calculates and displays the load factor by dividing the number of entries in the array
        by the size of the array.
     */
    void statistics(int collisions, int count)
    {
        cout << "There were " << collisions << " collisions." << endl;
        
        double loadFactor = (count * 100) / size;
        cout << "The load factor was " << loadFactor << "%" << endl;
    }
    
    /*
     Search function
     Parameter: the primary key of the record
     Gets the index by calling the hash function using the key.
     Using the index, the function loops through the array comparing the record number
        to the key and prints out the record if found
     */
    bool search(string key, Record *&record)
    {
        int index = hash(key);
        
        while (table[index] != 0)
        {
            Record *rec = table[index]->getRecord();
            string num = rec->getRecNum();
            
            if (num == key)
            {
                record = table[index]->getRecord();
                return true;
            }
            index++;
        }
        return false;
    }
    
  /*
   Delete function
   Parameters: a string, the primary key of the record to be deleted
   Finds the index of the key by using the hash function.
   Searches for the index of the key, and deletes the hash entry if found
   */
    bool deleteHash(string key)
    {
        int index = hash(key);
        
        while (table[index] != NULL)
        {
            Record *rec = table[index]->getRecord();
            string num = rec->getRecNum();
            
            if (num == key)
            {
                delete rec;
                table[index] = NULL;
                //table[index]->setFlag(-1);
                return true;
            }
            index++;
        }
        return false;
    }
    
    /*
     Print function
     Only prints the indexes of the hash table that aren't empty
     */
    void printTable()
    {
        for (int i = 0; i < size; i++)
        {
            if (table[i] != NULL)
            {
                Record *rec = table[i]->getRecord();
                cout << *rec;
            }
        }
    }
};

#endif /* HashTable_h */
