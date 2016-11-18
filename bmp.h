#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include <stdint.h>

typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef int32_t LONG;
typedef int8_t BYTE;

#pragma pack (push, 1)
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack (pop)

#pragma pack (push, 1)
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack (pop)

#pragma pack (push, 1)
typedef struct bmp {
   BITMAPFILEHEADER file;
   BITMAPINFOHEADER info;
   BYTE** picture;
} bmp;
#pragma pack (pop)

size_t padding(LONG w);
bmp* load_bmp(const char* filename);
void crop(bmp* bmp_file, size_t x, size_t y, size_t w, size_t h);
void rotate(bmp* bmp_file);
void save_bmp(const char* filename, struct bmp* bmp_out);

#endif // BMP_H_INCLUDED
