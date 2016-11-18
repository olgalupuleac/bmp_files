#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "bmp.h"

int main(/*int argc, char**argv*/)
{
    bmp* bmp_file = load_bmp("out.bmp");
    crop(bmp_file, 4, 4, 11, 13);
    rotate(bmp_file);
    save_bmp("outout.bmp", bmp_file);
    return 0;
}
