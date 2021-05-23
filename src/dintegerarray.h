
typedef struct {
    int* int_array;
    int size;
    int capacity;
} IntegerArray;


IntegerArray init_intarray(int);

void add_element_intarray(IntegerArray*, int);

void remove_element_intarray(IntegerArray*);

void clean_intarray(IntegerArray*);
