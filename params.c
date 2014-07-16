#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"

void print_help(){
  /*TODO Write some details to help*/
   printf("-delay: Delay between two picture\n");
   printf("-picnum: Number of pictures taken\n");
   printf("-fps: Frame per seconds of output video\n");
   printf("-ovl: Output video length\n");
   printf("-rstart: Start of recording\n");
   printf("-rend: End of recording\n");
   printf("-rlen: Length of recording\n");
   printf("-od: Output directory\n");
   printf("-prefix: Outputfile prefix\n");
}

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
      if(!strcmp(argv[i], "-fps")){
         p.fps = atoi(argv[i+1]);
      }
      if(!strcmp(argv[i], "-ovl")){
         p.videolen = atoi(argv[i+1]);
      }
      if(!strcmp(argv[i], "-rstart")){
         p.rstart = atoi(argv[i+1]);
      }
      if(!strcmp(argv[i], "-rend")){
         p.rend = atoi(argv[i+1]);
      }
      if(!strcmp(argv[i], "-rlen")){
         p.rlen = atoi(argv[i+1]);
      }
      if(!strcmp(argv[i], "-od")){
         strncpy(p.output_dir, argv[i+1], PATHLEN);
      }
      if(!strcmp(argv[i], "-prefix")){
         strncpy(p.prefix, argv[i+1], FILELEN);
      }
      if(!strcmp(argv[i], "-h")){
         print_help();
         exit(EXIT_SUCCESS);
      }
   }

   return(p);
}
