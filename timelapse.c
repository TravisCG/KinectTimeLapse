#include <stdio.h>
#include <stdlib.h>
#include <libfreenect_sync.h>
#include <png.h>
#include <unistd.h>

#include "timelapse.h"

void writePNG(char *prefix, unsigned int num){
   char         filename[100];
   png_structp  pngstr;
   png_infop    pnginfo;
   png_bytep   *row_pointers;
   int          y;
   FILE        *out;

   sprintf(filename, "%s_%d.png", prefix, num);
   out          = fopen(filename, "wb");
   pngstr       = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   pnginfo      = png_create_info_struct(pngstr);
   row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * 480);
   png_init_io(pngstr, out);
   png_set_IHDR(pngstr, pnginfo, 640, 480, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
   for(y = 0; y < 480; y++){
      row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(pngstr, pnginfo));
   }

   png_write_info(pngstr, pnginfo);
   png_write_image(pngstr, row_pointers);
   png_write_end(pngstr, NULL);

   for(y = 0; y < 480; y++){
      free(row_pointers[y]);
   }
   free(row_pointers);
   png_destroy_write_struct(&pngstr, &pnginfo);
   fclose(out);
}

void getData(Params p, freenect_device *camera){
   char *image;
   short *depth;
   uint32_t time;
   unsigned int imgnum;

   for(imgnum = 0; imgnum < p.picnum; imgnum++){
      freenect_sync_get_depth((void **)&depth, &time, 0, FREENECT_DEPTH_11BIT);
      freenect_sync_get_video((void **)&image, &time, 0, FREENECT_VIDEO_RGB);
      writePNG("test", imgnum);
      usleep(p.delay * 1000000);
   }

   free(depth);
   free(image);
}

void timelapse(Params p){
   freenect_context *kinect;
   freenect_device  *camera;

   if(freenect_init(&kinect, NULL) < 0){
      printf("Woops, init\n");
      return;
   }

   freenect_set_log_level(kinect, FREENECT_LOG_SPEW);
   freenect_select_subdevices(kinect, FREENECT_DEVICE_CAMERA);

   if(freenect_open_device(kinect, &camera, 0) < 0){
      printf("Wooops, device\n");
      return;
   }

   getData(p, camera);
   printf("%f %d\n", p.delay, p.picnum);

   freenect_close_device(camera);
   freenect_shutdown(kinect);
}
