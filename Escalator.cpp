#include <iostream>
using namespace std;

class BaseStack
{
public:
    virtual void push(int value) = 0;
    virtual void pop() = 0;
    virtual int top() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
    virtual void display() = 0;
    virtual ~BaseStack() {}
};

class Stack : public BaseStack
{
private:
    int arr[50];
    int topIndex;
    int capacity;

public:
    Stack(int size = 10)
    {
        capacity = size;
        topIndex = -1;
    }

    void push(int value) override
    {
        if (isFull())
        {
            cout << "Stack Overflow! Cannot push " << value << ".\n";
            return;
        }
        arr[++topIndex] = value;
        cout << value << " pushed successfully.\n";
    }

    void pop() override
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! No element to pop.\n";
            return;
        }
        cout << arr[topIndex] << " popped successfully.\n";
        topIndex--;
    }

    int top() override
    {
        if (isEmpty())
        {
            cout << "Stack is empty. No top element.\n";
            return -1;
        }
        return arr[topIndex];
    }

    bool isEmpty() override
    {
        return (topIndex == -1);
    }

    bool isFull() override
    {
        return (topIndex == capacity - 1);
    }

    void display() override
    {
        if (isEmpty())
        {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i <= topIndex; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Stack s(5);
    int choice, value;

    do
    {
        cout << "\n----- STACK MENU -----\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top Element\n";
        cout << "4. Check Empty\n";
        cout << "5. Check Full\n";
        cout << "6. Display\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            s.pop();
            break;

        case 3:
            value = s.top();
            if (value != -1)
                cout << "Top element: " << value << endl;
            break;

        case 4:
            cout << (s.isEmpty() ? "Stack is empty.\n" : "Stack is not empty.\n");
            break;

        case 5:
            cout << (s.isFull() ? "Stack is full.\n" : "Stack is not full.\n");
            break;

        case 6:
            s.display();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
