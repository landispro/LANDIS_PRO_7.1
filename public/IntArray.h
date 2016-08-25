#ifndef INTARRAY_H

#define INTARRAY_H



class IntArray {

public :

    IntArray(int n);

    virtual ~IntArray();

    void reset();

    int& operator[](int index);

    int number();

    int sum();

    void dump();

	int getsize() { return size; }

    

private :

    void checkIndex(int index);

    IntArray(const IntArray&);

    IntArray& IntArray::operator=(const IntArray&);

    int size;

    int* array;

};



#endif



