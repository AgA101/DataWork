#include <fstream>
#include "ReadWriteData.h"

uint16_t toLin(uint16_t y, uint16_t x, uint16_t fieldW) {
    return y * fieldW + x;
};


bool LinkedList::isEmpty() {
    Node* cur = head;
    return (head == nullptr ? 1 : 0);
}

void LinkedList::printList(uint64_t* field, uint16_t min_x, uint16_t max_y, uint16_t fieldW) {
    Node* cur = head;

    while (cur != nullptr) {
        uint16_t x = cur->x - min_x;
        uint16_t y = max_y - cur->y + 1;
        field[toLin(y, x, fieldW)] = cur->gainCount;
        cur = cur->next;
    }

}

void LinkedList::insertNode(uint16_t x, uint16_t y, uint64_t gainCount) {
    Node* newNode = new Node(x, y, gainCount);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = newNode;
}

LinkedList GetData(char* data, uint16_t& min_x, uint16_t& max_x, uint16_t& min_y, uint16_t& max_y) {
    std::ifstream cin(data);
    uint16_t x;
    uint16_t y;
    uint64_t gainCount;
    LinkedList list;

    while (cin >> x >> y >> gainCount) {
        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);
        min_x = std::min(min_x, x);
        min_y = std::min(min_y, y);
        list.insertNode(x, y, gainCount);
    }
    return list;
}