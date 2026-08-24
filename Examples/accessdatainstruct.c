1: int main() {
2:   studentInfo taylor; // Declaring a variable
3:   studentInfo* ptr; // Declaring a pointer
4: 
5:   taylor.idNumber = 1234;
6:   ptr = &taylor; // Use of the reference operator
7:   if( ptr->idNumber == 1234 ) { // This is true
8:      // More code would follow
