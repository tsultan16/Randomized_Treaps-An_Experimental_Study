#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// Dynamic Array Interface
class DynamicArray {
    private:
        int capacity;
        int size;
        int** arr;

        void grow();
        void shrink();

    public:
        DynamicArray(); // constructor
        ~DynamicArray(); // destructor
 
        int getSize() const;
        int getCapacity() const;
        int* get(int idx) const;
        int* searchItem(int key_sch) const;

        void insertItem(int id, int key);
        void deleteItem(int key_del);
        //void performOperation(int );

};

#endif // DYNAMIC_ARRAY_H