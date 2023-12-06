#pragma pack(1)
#include <string>
#include <fstream>
#include "CrtBmp.h"



void CreateBmp(int iterations, char* file_path, uint16_t fieldW, uint16_t fieldH, uint64_t* field) {
    uint16_t bitsPerPixel = 4;
    uint16_t colorCount = 1 << bitsPerPixel;

    RgbQuad palette[16];

    palette[0].red = static_cast<uint8_t>(255);
    palette[0].green = static_cast<uint8_t>(255);
    palette[0].blue = static_cast<uint8_t>(255);
    palette[0].reserved = 0;

    palette[1].red = static_cast<uint8_t>(0);
    palette[1].green = static_cast<uint8_t>(127);
    palette[1].blue = static_cast<uint8_t>(0);
    palette[1].reserved = 0;

    palette[2].red = static_cast<uint8_t>(255);
    palette[2].green = static_cast<uint8_t>(255);
    palette[2].blue = static_cast<uint8_t>(0);
    palette[2].reserved = 0;

    palette[3].red = static_cast<uint8_t>(127);
    palette[3].green = static_cast<uint8_t>(0);
    palette[3].blue = static_cast<uint8_t>(127);
    palette[3].reserved = 0;

    palette[4].red = static_cast<uint8_t>(0);
    palette[4].green = static_cast<uint8_t>(0);
    palette[4].blue = static_cast<uint8_t>(0);
    palette[4].reserved = 0;

    for (int i = 5; i < colorCount; i++) {
        palette[i].red = static_cast<uint8_t>(0);
        palette[i].green = static_cast<uint8_t>(0);
        palette[i].blue = static_cast<uint8_t>(0);
        palette[i].reserved = 0;
    }

    uint16_t width = fieldW;
    uint16_t height = fieldH;
    uint8_t* imageData = new uint8_t[fieldH * fieldW];

    for (uint16_t i = 0; i < fieldH * fieldW; i++) {
        imageData[i] = (field[i] >= 4 ? 4 : field[i]);
    }

    std::ofstream file((file_path + std::to_string(iterations) + "out.bmp"), std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open output.bmp for writing." << std::endl;
        return;
    }

    bmpFileHeader fileHeader;
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(bmpFileHeader) + sizeof(bmpBitmapInfo) + colorCount * sizeof(RgbQuad) + width * height / 2;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(bmpFileHeader) + sizeof(bmpBitmapInfo) + colorCount * sizeof(RgbQuad);

    bmpBitmapInfo infoHeader;
    infoHeader.biSize = sizeof(bmpBitmapInfo);
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = bitsPerPixel;
    infoHeader.biCompression = 0;

    infoHeader.biXPelsPerMeter = 0;
    infoHeader.biYPelsPerMeter = 0;
    infoHeader.biClrUsed = colorCount * 4;
    infoHeader.biClrImportant = colorCount;

    uint32_t w_idbmp = infoHeader.biWidth / 2 + infoHeader.biWidth % 2;
    w_idbmp += (4 - w_idbmp % 4) % 4;
    infoHeader.biSizeImage = w_idbmp * infoHeader.biHeight;
    uint8_t* imageDataBmp = new uint8_t[infoHeader.biSizeImage];

    for (int i = 0; i < infoHeader.biHeight; i++) {
        for (int j = 0; j < infoHeader.biWidth / 2; j++) {
            imageDataBmp[(infoHeader.biHeight - 1 - i) * w_idbmp + j] = imageData[i * infoHeader.biWidth + 2 * j + 1] + (imageData[i * infoHeader.biWidth + 2 * j] << 4);
        }
        if (infoHeader.biWidth % 2 == 1) {
            imageDataBmp[(infoHeader.biHeight - i - 1) * w_idbmp + infoHeader.biWidth / 2] = (imageData[i * infoHeader.biWidth + infoHeader.biWidth - 1] << 4);
        }
        for (int j = infoHeader.biWidth / 2 + infoHeader.biWidth % 2; j < w_idbmp; j++) {
            imageDataBmp[(infoHeader.biHeight - 1 - i) * w_idbmp + j] = 0;
        }
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(palette), colorCount * sizeof(RgbQuad));
    file.write(reinterpret_cast<const char*>(imageDataBmp), infoHeader.biSizeImage);
    file.close();

}