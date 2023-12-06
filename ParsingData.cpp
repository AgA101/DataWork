#include "ParsingData.h"

int Comparison(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return a[i] == b[i] ? 1 : 0;
}

void Error(char symbol) {
    if (symbol == 'i') {
        std::cerr << "Incorrect data";
        return;
    }
    else if (symbol == 'o') {
        std::cerr << "Incorrect file path";
        return;
    }
    else if (symbol == 'm') {
        std::cerr << "argument -m/--max-iter must be a number";
        return;
    }
    else if (symbol == 'f') {
        std::cerr << "argument -f/--freq must be a number";
        return;
    }
    else {
        std::cerr << "unexpected condition";
        return;
    }
}

void Parsing(int argc, char** argv, char*& data, char*& file_path, int* max_iter, int* freq) {
    char previous_element = ' ';

    for (int i = 1; i < argc; ++i) {
        char* string_arg = argv[i];

        if (Comparison(string_arg, "-i") || Comparison(string_arg, "--input")) {
            previous_element = 'i';
        }
        else if (Comparison(string_arg, "-o") || Comparison(string_arg, "--output")) {
            previous_element = 'o';
        }
        else if (Comparison(string_arg, "-m") || Comparison(string_arg, "--max-iter")) {
            previous_element = 'm';
        }
        else if (Comparison(string_arg, "-f") || Comparison(string_arg, "--freq")) {
            previous_element = 'f';
        }
        else if (previous_element == 'o') {
            file_path = string_arg;
            previous_element = ' ';
        }
        else if (previous_element == 'i') {
            data = string_arg;
            previous_element = ' ';
        }
        else if (previous_element == 'm') {

            if (isdigit(*string_arg)) {
                *max_iter = atoi(string_arg);
                previous_element = ' ';
            }

        }
        else if (previous_element == 'f') {

            if (isdigit(*string_arg)) {
                *freq = atoi(string_arg);
                previous_element = ' ';
            }

        }
        else {
            Error(previous_element);
        }

    }
}