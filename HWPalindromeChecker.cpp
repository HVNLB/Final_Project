#include <iostream>
using namespace std;

int main()
{
     int n, num, digit, reverse = 0;

     cout << "Enter a positive number: ";
     cin >> num;

     n = num;

     do
     {
         digit = num % 10;
         reverse = (reveverse * 10) + digit;
         num = num / 10;
     } while (num != 0);

   
     if (n == reverse and n > 0) 
         cout << "Palindrome.";
     else
         cout << "Not Palindrome.";

    return 0;
}
