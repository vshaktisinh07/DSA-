// 2nd program2. Mission: Topper Finder

// Project Title: Find the Largest and Second Largest Element
// Objective: Create a program that takes an array and finds the largest and second largest number, even if duplicates are present.

#include <iostream>
using namespace std;

int main()
{
    int n;

    cout << "ENTER NUBMBER OF ELEMENT : ";
    cin >> n;

    int arr[100];

    cout << "ENTER " << n << "ELEMENTS :\n " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int largest = arr[0];
    int secondlargest = -1;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > largest)
        {
            secondlargest = largest;
            largest = arr[i];
        }
        else if (arr[i] < largest && arr[i] > secondlargest)
        {
            secondlargest = arr[i];
        }
    }

    cout << "\nThe largest element is: " << largest << endl;

    if (secondlargest != -1)
        cout << "The second largest element is: " << secondlargest << endl;
    else
        cout << "No second largest element found (all elements may be equal)." << endl;

    return 0;
}