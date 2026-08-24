 1: int main() {
 2:   studentInfo taylor;
 3:   studentInfo* infoPtr;
 4:   unsigned int* intPtr;
 5: 
 6:   infoPtr = &taylor;
 7:   // studentInfo struct pointer points to
 8:   //   struct "taylor".
 9: 
10:   intPtr = &taylor.idNumber;
11:   // unsigned int pointer points to idNumber
12:   //   variable within the struct "taylor".

// example 2

   1: int main() {
 2:   studentInfo taylor;
 3:   char* charPtr;
 4: 
 5:   charPtr = taylor.firstName;
 6:   // No need for reference operator!
 7:   // char pointer points to beginning of
 8:   //   firstName variable (character #0)
 9:   //   within the struct "taylor".
10: 
11:   charPtr = &taylor.firstName[10];
12:   // char pointer points to the 11th character
13:   //   (character #10) of the firstName variable
14:   //   within the struct "taylor".
