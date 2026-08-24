1: void* calloc( size_t nitems, size_t size );
2:   // nitems = number of items to allocate
3:   // size = size (in bytes) of each item to allocate
4:   // return value = a pointer (void*) of the
5:   //                allocated memory, this
6:   //                is null if calloc fails

// calloc example 9.7
1: void* calloc( size_t nitems, size_t size );
2:   // nitems = number of items to allocate
3:   // size = size (in bytes) of each item to allocate
4:   // return value = a pointer (void*) of the
5:   //                allocated memory, this
6:   //                is null if calloc fails
9.7. calloc example
 1: int main() {
 2:   int strLen = 100;
 3: 
 4:   int* intArray = calloc( 10, sizeof(int) );
 5:     // Allocates ten 32-bit signed integers
 6:     //   for an array
 7: 
 8:   char* string = calloc( strLen, sizeof(char) );
 9:     // Allocates "strLen" number of bytes
10:     //   for a character array (string)
11: 
12:   // Should check if each pointer is valid
13:   //   (i.e., not null or 0)
