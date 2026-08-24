 1: int main() {  studentInfo taylor;
 2:   int* intPtr = malloc( sizeof(int) );
 3:     // Allocates a 32-bit integer (4 bytes)
 4: 
 5:   studentInfo* siPtr1 = malloc(sizeof(studentInfo));
 6:     // Allocates one studentInfo variable (44 bytes)
 7:   studentInfo* siPtr2 = malloc( sizeof(taylor) );
 8:     // Allocates one studentInfo variable (44 bytes)
 9: 
10:   char* strPtr = malloc( 20*sizeof(char) );
11:     // Allocates 20 bytes for a string which can
12:     //   hold 19 characters and the null character
13: 
14:   // Should check if each pointer is valid
15:   //   (i.e., not null or 0)
