#include <stdio.h>
#include <stdlib.h>
#include <libfreenect_sync.h>
#include <unistd.h>

#include "timelapse.h"

void getImages(Params p, freenect_device *camera){
   char *image;
   short *depth;
   uint32_t time;
   unsigned int imgnum;

   for(imgnum = 0; imgnum < p.picnum; imgnum++){
      freenect_sync_get_depth((void **)&depth, &time, 0, FREENECT_DEPTH_11BIT);
      freenect_sync_get_video((void **)&image, &time, 0, FREENECT_VIDEO_RGB);
      usleep(p.delay * 1000000);
   }

   free(depth);
   free(image);
}

void timelapse(Params p){
   freenect_context *kinect;
   freenect_device  *camera;

   if(freenect_init(&kinect, NULL) < 0){
      return;
   }

   freenect_set_log_level(kinect, FREENECT_LOG_ERROR);
   freenect_select_subdevices(kinect, FREENECT_DEVICE_CAMERA);

   if(freenect_open_device(kinect, &camera, 0) < 0){
      return;
   }

   getImages(p, camera);
   printf("%f %d\n", p.delay, p.picnum);

   freenect_close_device(camera);
   freenect_shutdown(kinect);
}
