#include <iostream>
#include <string>

#include "CrtBmp.h"
#include "ParsingData.h"
#include "ReadWriteData.h"

uint16_t fieldW;
uint16_t fieldH;
uint64_t* field;

uint16_t max_x = 0;
uint16_t max_y = 0;
uint16_t min_x = 0;
uint16_t min_y = 0;

uint64_t* Expansion(uint16_t* fieldH, uint16_t* fieldW, uint64_t* field, char symbol) {
    uint16_t add_shift = 0;

    if (symbol == 'U' || symbol == 'D') {
        *fieldH = *fieldH + 1;
        if (symbol == 'U') add_shift = *fieldW;
    }

    if (symbol == 'L' || symbol == 'R') {
        *fieldW = *fieldW + 1;
        if (symbol == 'R') add_shift = *fieldW - 1;
    }

    uint64_t* newField = new uint64_t[*fieldH * *fieldW]();

    if (symbol == 'U' || symbol == 'D') {
        memcpy(newField + add_shift, field, (*fieldH - 1) * *fieldW * 8);
    }
    else {
        uint16_t count = 0;
        for (uint16_t i = 0; i < *fieldH * *fieldW; i++) {
            if (i % *fieldW != add_shift){
                newField[i] = field[count++];
            }
            
        }
    }

    return newField;
}

void SandHeapImpl(char* file_path, int max_iter, int freq) {
    bool moreThan4 = true;
    int iterations = 0;

    while (moreThan4) {
        moreThan4 = false;
        bool needToExtendUp = false;
        bool needToExtendDown = false;
        bool needToExtendLeft = false;
        bool needToExtendRight = false;

        bool* correct_decay = new bool[fieldH * fieldW]();

        if (iterations == max_iter + 1) {
            if (freq == 0) {
                CreateBmp(iterations - 1, file_path, fieldW, fieldH, field);
            }
            return;
        }

        for (uint16_t i = 0; i < fieldH * fieldW; i++) {
            uint16_t x = i % fieldW;
            uint16_t y = i / fieldW;
            if (field[i] > 3 && x != 0 && y != 0 && x != fieldW - 1 && y != fieldH - 1 && correct_decay[i] == 0) {

                if (field[toLin(y - 1, x, fieldW)] == 3) {
                    correct_decay[toLin(y - 1, x, fieldW)] = 1;
                }
                if (field[toLin(y, x - 1, fieldW)] == 3) {
                    correct_decay[toLin(y, x - 1, fieldW)] = 1;
                }
                if (field[toLin(y + 1, x, fieldW)] == 3) {
                    correct_decay[toLin(y + 1, x, fieldW)] = 1;
                }
                if (field[toLin(y, x + 1, fieldW)] == 3) {
                    correct_decay[toLin(y, x + 1, fieldW)] = 1;
                }

                field[toLin(y - 1, x, fieldW)] += 1;
                field[toLin(y, x - 1, fieldW)] += 1;
                field[toLin(y + 1, x, fieldW)] += 1;
                field[toLin(y, x + 1, fieldW)] += 1;
                field[i] -= 4;
                moreThan4 = true;
            }
        }
        for (uint16_t i = 0; i < fieldW; i++) {
            if (field[i] > 3) {
                needToExtendUp = true;
            }
            if (field[(fieldH - 1) * fieldW + i] > 3) {
                needToExtendDown = true;
            }
            if (field[i * fieldW] > 3) {
                needToExtendLeft = true;
            }
            if (field[fieldW - 1 + i * fieldW] > 3) {
                needToExtendRight = true;
            }
        }
        if (freq != 0 && iterations % freq == 0) {
            CreateBmp(iterations, file_path, fieldW, fieldH, field);
        }
        
        iterations++;

        if (needToExtendUp) {
            field = Expansion(&fieldH, &fieldW, field, 'U');
        }
        if (needToExtendDown) {
            field = Expansion(&fieldH, &fieldW, field, 'D');
        }
        if (needToExtendLeft) {
            field = Expansion(&fieldH, &fieldW, field, 'L');
        }
        if (needToExtendRight) {
            field = Expansion(&fieldH, &fieldW, field, 'R');
        }
    }
    CreateBmp(iterations - 1, file_path, fieldW, fieldH, field);
}

int main(int argc, char** argv) {
    
    char* data;
    char* file_path;
    int max_iter = 0;
    int freq = 0;

    Parsing(argc, argv, data, file_path, &max_iter, &freq);

    LinkedList list = GetData(data, min_x, max_x, min_y, max_y);

    fieldH = max_y - min_y + 2;
    fieldW = max_x - min_x + 2;
    field = new uint64_t[fieldH * fieldW]();

    list.printList(field, min_x, max_y, fieldW);

    SandHeapImpl(file_path, max_iter, freq);
     
    delete[] field;
}