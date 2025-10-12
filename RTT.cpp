
// first program 1. Mission: Remove the Twins

// REMOVE THE TWIN
// Write a program to remove duplicate elements from an array and display only the unique values.

#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "ENTER NUMBER OF THE ELEMENT : " << endl;
    cin >> n;

    int arr[100];

    cout << "ENTER " << n << "ELEMENTS :\n " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n;)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < n - 1; k++)
                {
                    arr[k] = arr[k + 1];
                }
                n--;
            }
            else
            {
                j++;
            }
        }
    }

    cout << "AFTER REMOVING THE TWIN ELEMENT : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
