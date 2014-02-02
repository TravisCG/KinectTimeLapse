#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "timelapse.h"

int main(int argc, char **argv){
   Params params;

   params = parseParams(argc, argv);
   timelapse(params);

   return(EXIT_SUCCESS);
}
