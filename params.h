#ifndef PARAMS_H
#define PARAMS_H

#define PATHLEN 100
#define FILELEN 20

typedef struct _Params {
   unsigned int picnum;
   double delay;
   char output_dir[PATHLEN];
   char prefix[FILELEN];
   unsigned int fps;
   unsigned int videolen;
} Params;

Params parseParams(int argc, char **argv);

#endif
