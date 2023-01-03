#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <vector>


class HashTable {
public:
    HashTable(int length, double loadFactorCoef = 0.5, double collisionsFactorCoef = 0.5);

    int hashFunction(int x);
    void resize();

    void insert(int x);
    void remove(int key);

    double loadFactor() const;
    double collisionsFactor() const;

    void showTable();

private:
    std::list<int> *_table;

    int _opacity;
    int _addCount;
    int _collisions;
    double _loadFactorCoef;
    double _collisionsFactorCoef;
};


#endif //HASHTABLE_H
