1: int printf( const char* format, ... );
2:   // format = a string, which can contain
3:   //          formatting tags, to write to
4:   //          the screen (stdout)
5:   // return value = number of characters
6:   //                successfully written to
7:   //                stdout
8:   //                (note, this value is usually
9:   //                ignored)

// example of printf 10.3 
1: int main() {
2:   int i = 42;
3:   char c = 'a';
4:   char s[10] = "string\0";
5: 
6:   printf("Hello World!\n");
7:   printf("The int is %d, the char is %c,", i, c );
8:   printf(" and the string is %s\n", s );
9:   printf("To print the percentage sign, use %%");
