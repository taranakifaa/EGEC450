#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int numbers[] = {0,1,2,3,4,5,6,7,8,9};
int counter = 0;

int main()
{
    while(1)
    {
        for(int i = 0; i < 10; i++)
        {
            if(numbers[i] >= 0)
            {
                counter++;
                cout << counter << endl;
                this_thread::sleep_for(chrono:: seconds(1));
            }
            else
            {
                this_thread::sleep_for(chrono::seconds(1));
                counter = 0;
            }
        }
    }
}
