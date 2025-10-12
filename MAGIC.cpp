#include <iostream>
using namespace std;

int main()
{
    int n, arr[100];
    int even[100], odd[100];
    int eCount = 0, oCount = 0;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (arr[i] % 2 == 0)
            even[eCount++] = arr[i];
        else
            odd[oCount++] = arr[i];
    }

    // ---------- Sort Even in Ascending Order ----------
    for (int i = 0; i < eCount - 1; i++)
    {
        for (int j = 0; j < eCount - i - 1; j++)
        {
            if (even[j] > even[j + 1])
            {
                int temp = even[j];
                even[j] = even[j + 1];
                even[j + 1] = temp;
            }
        }
    }

    // ---------- Sort Odd in Descending Order ----------
    for (int i = 0; i < oCount - 1; i++)
    {
        for (int j = 0; j < oCount - i - 1; j++)
        {
            if (odd[j] < odd[j + 1])
            {
                int temp = odd[j];
                odd[j] = odd[j + 1];
                odd[j + 1] = temp;
            }
        }
    }

    // ---------- Merge and Display ----------
    cout << "\nEven Numbers (Ascending): ";
    for (int i = 0; i < eCount; i++)
    {
        cout << even[i] << " ";
    }

    cout << "\nOdd Numbers (Descending): ";
    for (int i = 0; i < oCount; i++)
    {
        cout << odd[i] << " ";
    }

    cout << "\n\nMerged Array (Even + Odd): ";
    for (int i = 0; i < eCount; i++)
        cout << even[i] << " ";
    for (int i = 0; i < oCount; i++)
        cout << odd[i] << " ";

    return 0;
}
