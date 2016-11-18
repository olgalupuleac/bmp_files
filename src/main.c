#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char** argv)
{
    if (!strcmp(argv[1], "crop-rotate")){
         bmp* bmp_file = load_bmp(argv[2]);
         int x = atoi(argv[4]);
         int y = atoi(argv[5]);
         int w = atoi(argv[6]);
         int h = atoi(argv[7]);
         if (x < 0 || y < 0 || w <= 0 || h <= 0) return 1;
         if (bmp_file->info.biWidth < x + w || bmp_file->info.biHeight < y + h) return 1;
         crop(bmp_file, x, y, w, h);
         rotate(bmp_file);
         save_bmp(argv[3], bmp_file);
    }
    return 0;
}
