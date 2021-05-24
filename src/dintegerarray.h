
typedef struct {
    int* int_array;
    int size;
    int capacity;
} IntegerArray;


void init_intarray(IntegerArray*, int);

void add_element_intarray(IntegerArray*, int);

void remove_element_intarray(IntegerArray*);

void clean_intarray(IntegerArray*);
