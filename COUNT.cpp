#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];
    int positiveCount = 0, negativeCount = 0;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Counting positive and negative numbers
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
            positiveCount++;
        else if (arr[i] < 0)
            negativeCount++;
    }

    cout << "\nCount of Positive Numbers: " << positiveCount << endl;
    cout << "Count of Negative Numbers: " << negativeCount << endl;

    return 0;
}
