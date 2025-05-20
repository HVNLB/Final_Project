#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "units.h"

int parse_input(char *input, double *values, const char **units)
{
   char *token = strtok(input, " ");
   int count = 0;

   while (token && count < 3) {
      double val = 0;
      char unit_buf[32] = {0};
      int i = 0;

      
      while (isdigit(token[i]) || token[i] == '.' || token[i] == '-') {
         i++;
      }

      if (i == 0) return -1; 

      val = atof(token);

      
      strncpy(unit_buf, token + i, 31);
      unit_buf[31] = 0;

      const char *base = NULL;
      double factor = normalize_unit(unit_buf, &base);

      if (factor < 0) {
         printf("Unrecognized unit: %s\n", unit_buf);
         return -1;
      }

      values[count] = val * factor;
      units[count] = base;

      count++;
      token = strtok(NULL, " ");
   }

   return count;
}
