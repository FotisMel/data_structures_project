#ifndef DATE
#define DATE

#include <string>

#include "../shared/shared.hpp"

extern bool dateflag;

bool searchTemp (AVLNode *, float);

bool insertTemp (AVLNode *, float);

void printTemps (AVLNode *);

bool insertNode (std :: string, float);

bool createDate (void);

int convert (std :: string);

int iotDate (AVLNode *, int);

void iotDate (void);

bool modifyTemp (int, float, float);

bool erase (int);

void dateOptions (void);

void dateOption1 (void);

void dateOption2 (void);

void dateOption3 (void);

void dateOption4 (void);

void dateOption5 (void);

void menuDate (void);

#endif // DATE