#include "HashTable.h"

HashTable::HashTable(int length, double loadFactorCoef, double collisionsFactorCoef) : _opacity(length), _addCount(0),
                     _loadFactorCoef(loadFactorCoef), _collisionsFactorCoef(collisionsFactorCoef), _collisions(0) {

    if (_opacity < 0) {
        _opacity = 0;
    }

    if (_loadFactorCoef < 0) {
        _loadFactorCoef = 0.5;
    }

    if (_collisionsFactorCoef < 0) {
        _collisionsFactorCoef = 0.5;
    }

    _table = new std::list<int>[_opacity];
}

int HashTable::hashFunction(int x) {
    return x % _opacity;
}

void HashTable::resize() {
    std::vector<int> keys;

    for (auto&& item : *_table) {
        keys.push_back(item);
    }

    _table->clear();

    _opacity *= 2;
    _addCount = 0;
    _collisions = 0;
    _table->resize(_opacity);

    for (auto&& item : keys) {
        insert(item);
    }
}

void HashTable::insert(int key)
{
    int index = hashFunction(key);

    if ( !_table[index].empty() ) {
        ++_collisions;

        if (collisionsFactor() > _collisionsFactorCoef) {
            //resize();
        }
    }

    _table[index].push_back(key);
    ++_addCount;

    if (loadFactor() > _loadFactorCoef) {
        //resize();
    }
}

void HashTable::remove(int key) {
    int index = hashFunction(key);

    std::list<int> :: iterator i;

    for (i = _table[index].begin(); i != _table[index].end(); i++) {
        if (*i == key){
            break;
        }
    }

    if ( i != _table[index].end() ) {
        _table[index].erase(i);

        --_addCount;

        if ( !_table[index].empty() ) {
            --_collisions;
        }
    }
}

double HashTable::loadFactor() const {
    return (double) _addCount / _opacity;
}

double HashTable::collisionsFactor() const {
    return (double) _collisions / _addCount;
}

void HashTable::showTable() {
    for (int i = 0; i < _opacity; i++) {
        std::cout << i;

        for (auto item : _table[i]) {
            std::cout << " - " << item;
        }

        std::cout << '\n';
    }

    std::cout << "addCount = " << _addCount << '\n';
    std::cout << "loadFactor = " << loadFactor() << '\n';
    std::cout << "collisions = " << _collisions << '\n';
    std::cout << "collisionsFactor = " << collisionsFactor() << '\n';
}

