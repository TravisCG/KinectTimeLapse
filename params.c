#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"

Params parseParams(int argc, char **argv){
   int i;
   Params p;

   for(i = 1; i < argc; i++){
      if(!strcmp(argv[i], "-delay")){
         p.delay = atof(argv[i+1]);
      }
      if(!strcmp(argv[i], "-picnum")){
         p.picnum = atoi(argv[i+1]);
      }
      //TODO add additional command lines here
   }

   return(p);
}
