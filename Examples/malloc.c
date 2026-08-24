1: void* malloc( size_t size );
2:   // size = size (in bytes) of memory block
3:   // return value = a pointer (void*) of the
4:   //                allocated memory, this
5:   //                is null if malloc fails

// another example 9.3 malloc example 
 1: int main() {
 2:   int* intPtr = malloc( 4 );
 3:     // Allocates 4 bytes for a 32-bit integer
 4: 
 5:   char* charPtr = malloc( 1 );
 6:     // Allocates 1 byte for an 8-bit character
 7: 
 8:   char* strPtr = malloc( 20 );
 9:     // Allocates 20 bytes for a string which can
10:     //   hold 19 characters and the null character
11: 
12:   // Should check if each pointer is valid
13:   //   (i.e., not null or 0)
