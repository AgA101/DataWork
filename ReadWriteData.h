#include <iostream>

class Node {
public:
    uint16_t x;
    uint16_t y;
    uint64_t gainCount;
    Node* next;

    Node(uint16_t x, uint16_t y, uint64_t gainCount) {
        this->x = x;
        this->y = y;
        this->gainCount = gainCount;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }
    void insertNode(uint16_t x, uint16_t y, uint64_t gainCount);
    bool isEmpty();
    void printList(uint64_t* field, uint16_t min_x, uint16_t max_y, uint16_t fieldW);
};

LinkedList GetData(char* data, uint16_t& min_x, uint16_t& max_x, uint16_t& min_y, uint16_t& max_y);

uint16_t toLin(uint16_t y, uint16_t x, uint16_t fieldW);