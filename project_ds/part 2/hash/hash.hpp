#ifndef HASH
#define HASH

#include <string>
#include <vector>

// basic Hash Chain node used for Hash Table

struct HashNode {
	std :: string date;
	float temp;
};

extern bool hashflag;

extern const int buckets;

extern std :: vector <HashNode * > hashTable[];

bool insert (std :: string, float);

bool createHash (void);

int calcHash (std :: string);

void printBuckets (void);

HashNode * search (std :: string);

bool modify (std :: string, float);

bool erase (std :: string);

void hashOptions (void);

void hashOption1 (void);

void hashOption2 (void);

void hashOption3 (void);

void hashOption4 (void);

void hashOption5 (void);

void hashOption6 (void);

void menuHash (void);

#endif // HASH