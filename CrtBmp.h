#pragma pack(1)
#include <iostream>

struct bmpFileHeader {
    int16_t bfType;
    int32_t bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    int32_t bfOffBits;
};

struct bmpBitmapInfo {
    int32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    int16_t biPlanes;
    int16_t biBitCount;
    int32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    uint32_t biClrImportant;
};

struct RgbQuad {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

void CreateBmp(int iterations, char* file_path, uint16_t fieldW, uint16_t fieldH, uint64_t* field);