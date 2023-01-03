#include "HashTable.h"

int main() {
    int a[] = {15, 8, 13, 1, 2};
    int n = sizeof(a) / sizeof(*a);

    HashTable hashT(7);

    for (int i = 0; i < n; i++) {
        hashT.insert(a[i]);
    }

    hashT.remove(2);
    hashT.showTable();

    return 0;
}
