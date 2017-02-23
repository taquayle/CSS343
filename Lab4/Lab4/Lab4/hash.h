#ifndef HASH_H
#define HASH_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <fStream>

using namespace std;

template <class T>
class Hash
{
private:
   int tableSize;
   int numberOfEntries;
   T hashTable[tableSize];
   

public:
   int hashFunction(T key);
   void rehashFunction();
   void setTableSize(int s){ tableSize = s; }
   void setNumberOfEntries(int entries) { numberOfEntries = entries; }
   void updateNumberOfEntries(){ numberOfEntries = numberOfEntries + 1; }

   int getTableSize(){ return tableSize; }
   int getNumberOfEntries() { return numberOfEntries; }
   float getLoadFactor() const;
   float getMaxLoadFactor() const;

   int getPrime();
   bool isPrime(int);

   void linearProbing(T);
   void rehashIfCollision(T);
   void doubleHashing(T);

   void clearHashMap(){ hashMap.clear(); }
   void displayHashMap();
};

#endif HASH_H