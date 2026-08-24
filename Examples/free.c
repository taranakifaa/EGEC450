 void free( void* ptr );
// ptr = the pointer to the memory to free
// free example 9.9

 1: int main() {
 2:   int strLen = 100;
 3: 
 4:   int* intPtr = malloc( sizeof(int) );
 5:   studentInfo* siPtr = malloc(sizeof(studentInfo));
 6:   char* strPtr = calloc( strLen, sizeof(char) );
 7: 
 8:   // Should check if each pointer is valid
 9:   //   (i.e., not null or 0)
10:   // Use the pointers as needed
11:   free( intPtr );
12:   free( infoPtr );
13:   free( strPtr );
14:   return 0;
15: }
