#include <assert.h>

#include <iostream>;

using namespace std;

#include "IntArray.h"



void IntArray::checkIndex(int index) {

    assert(index >= 1 && index <= size);

}



IntArray::IntArray(int n) {

    assert(n > 0);

    size = n;

    array = new int[size];

    reset();

}



IntArray::~IntArray() {

    delete [] array;

}



void IntArray::reset() {

    for (int i = 0; i < size; i++) array[i] = 0;

}



/* inline */ int& IntArray::operator[](int index) {

    checkIndex(index);

    return array[index-1];

}



/* inline */ int IntArray::number() {

    return size;

}



int IntArray::sum() {

    int s = 0;

    for (int i = 0; i < size; i++) {

        s += array[i];

    }

    return s;

}



void IntArray::dump() {

    for (int i = 0; i < size; i++) cout << array[i] << " ";

    cout << endl;

}

