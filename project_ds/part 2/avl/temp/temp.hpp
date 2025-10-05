#ifndef TEMP
#define TEMP

#include <string>

#include "../shared/shared.hpp"

extern bool tempflag;

bool searchDate (AVLNode *, std :: string);

bool insertDate (AVLNode *, std :: string);

void printDates (AVLNode *);

bool insertNode (float, std :: string);

bool createTemp (void);

int iotTemp (AVLNode *, int);

void iotTemp (void);

AVLNode * findMin (void);

AVLNode * findMax (void);

void tempOptions (void);

void tempOption1 (void);

void tempOption2 (void);

void tempOption3 (void);

void tempOption4 (void);

void menuTemp (void);

#endif // TEMP