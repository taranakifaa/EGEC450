struct studentInfo {
 2:   char firstName[20]; // 19 char limits
 3:   char lastName[20]; // + null character: 0 or '\0'
 4:   unsigned int idNumber;
 5: };
 6: 
 7: int main() {
 8:   struct studentInfo taylor; // Declaring a variable
 9:   struct studentInfo* ptr; // Declaring a pointer
10:   // More code would follow
