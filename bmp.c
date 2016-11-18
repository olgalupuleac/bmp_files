#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bmp.h"

size_t padding(LONG w){
    return (4 - (w * 3) % 4) % 4;
}

bmp* load_bmp(const char* filename){
    FILE* f = fopen(filename, "rb");
    bmp* bmp_in = malloc(sizeof(bmp));
    fread(bmp_in, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 1, f);
    bmp_in->picture = malloc(sizeof(BYTE*) * bmp_in->info.biHeight);
    LONG tmp;
    for(int i = bmp_in->info.biHeight - 1; i >= 0; i--){
        bmp_in->picture[i] = malloc(sizeof(BYTE) * bmp_in->info.biWidth * 3);
        fread(bmp_in->picture[i], sizeof(BYTE), bmp_in->info.biWidth * 3, f);
        fread(&tmp, sizeof(BYTE), padding(bmp_in->info.biWidth), f);
    }
    fclose(f);
    printf("Hello %d %d %d\n", bmp_in->info.biWidth, bmp_in->info.biHeight, bmp_in->info.biSize);
    fflush(stdout);
    return bmp_in;
}

void crop(bmp* bmp_file, size_t x, size_t y, size_t w, size_t h){
    assert(x + w <= bmp_file->info.biWidth);
    assert(y + h <= bmp_file->info.biHeight);
    BYTE** res = malloc(sizeof(BYTE*) * h);
    for(size_t i=0; i < h; i++){
        res[i] = malloc(sizeof(BYTE) * w * 3);
        memcpy(res[i], bmp_file->picture[y + i] + x * 3, w * 3);
    }
    printf("Hello\n");
    fflush(stdout);
    bmp_file->info.biHeight = h;
    bmp_file->info.biWidth = w;
    bmp_file->info.biSizeImage = w * h * 3 + padding(w);
    //bmp_file->info.biSize = bmp_file->info.biSizeImage + 54;
    for(size_t i = 0; i < bmp_file->info.biHeight; i++){
        free(bmp_file->picture[i]);
    }
    free(bmp_file->picture);
    bmp_file->picture = res;
}

void rotate(bmp* bmp_file){
    LONG h = bmp_file->info.biWidth;
    LONG w = bmp_file->info.biHeight;
    BYTE** res = malloc(sizeof(BYTE*) * h);
    for(int i = 0; i < h; i++){
        res[i] = malloc(sizeof(BYTE) * (w * 3 + padding(w)));
        for(LONG j = 0; j < w; j++){
            memcpy(res[i] + 3 * j, bmp_file->picture[j] + 3 * i, 3);
        }
        for(LONG j = w * 3; j < w * 3 + padding(w); j++){
            res[i][j] = 0;
        }
    }
    bmp_file->info.biHeight = h;
    bmp_file->info.biWidth = w;
    bmp_file->info.biSizeImage = w * h * 3 + padding(w);
    //bmp_file->info.biSize = bmp_file->info.biSizeImage + 54;
    for (size_t i = 0; i < bmp_file->info.biHeight; i++){
        free(bmp_file->picture[i]);
    }
    free(bmp_file->picture);
    bmp_file->picture = res;
}

void save_bmp(const char* filename, struct bmp* bmp_out){
    printf("Hello\n");
    fflush(stdout);
    FILE* f = fopen(filename, "wb");
    printf("Hello\n");
    fflush(stdout);
    fwrite(bmp_out, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 1, f);
    for(LONG i = bmp_out->info.biHeight - 1; i >= 0; i--){
        fwrite(bmp_out->picture[i], sizeof(BYTE), bmp_out->info.biWidth * 3 + padding(bmp_out->info.biWidth), f);
        free(bmp_out->picture[i]);
    }
    free(bmp_out->picture);
    free(bmp_out);
    fclose(f);
}
