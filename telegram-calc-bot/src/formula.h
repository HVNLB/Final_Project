#ifndef FORMULA_H
#define FORMULA_H

#define MAX_VARIABLES 3

struct Variable {
   const char *name;
   const char *unit_aliases[5]; 
};

struct Formula {
   const char *name;
   struct Variable variables[MAX_VARIABLES];
   double (*solver)(double known1, double known2, int missing_index);
};

extern struct Formula formula_list[];
extern int formula_count;

#endif
