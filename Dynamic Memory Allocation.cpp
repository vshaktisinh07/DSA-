#include <iostream>
using namespace std;

class DynamicMemoryAllocation
{
private:
    class Node
    {
    public:
        int data;
        Node *next;

        Node(int value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node *head;

public:
    DynamicMemoryAllocation()
    {
        head = nullptr;
    }

    void insert_at_beginning(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        cout << data << " inserted at beginning.\n";
    }

    void append(int data)
    {
        Node *newNode = new Node(data);

        if (head == nullptr)
        {
            head = newNode;
            cout << data << " appended as first node.\n";
            return;
        }

        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        cout << data << " appended at end.\n";
    }

    bool search(int key)
    {
        Node *temp = head;

        while (temp != nullptr)
        {
            if (temp->data == key)
            {
                cout << "Element " << key << " found in the list.\n";
                return true;
            }
            temp = temp->next;
        }

        cout << "Element " << key << " not found.\n";
        return false;
    }

    void delete_node(int key)
    {
        if (head == nullptr)
        {
            cout << "List is empty. Cannot delete.\n";
            return;
        }

        if (head->data == key)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted node with value " << key << ".\n";
            return;
        }

        Node *prev = nullptr;
        Node *curr = head;

        while (curr != nullptr && curr->data != key)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr)
        {
            cout << "Value " << key << " not found. Cannot delete.\n";
            return;
        }

        prev->next = curr->next;
        delete curr;
        cout << "Deleted node with value " << key << ".\n";
    }

    void reverse()
    {
        Node *prev = nullptr;
        Node *curr = head;
        Node *next = nullptr;

        while (curr != nullptr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
        cout << "Linked list reversed successfully.\n";
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }

        cout << "Linked List: ";
        Node *temp = head;

        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }

        cout << "NULL\n";
    }
};

int main()
{
    DynamicMemoryAllocation list;

    list.append(10);
    list.append(20);
    list.append(30);

    list.insert_at_beginning(5);

    list.display();

    list.search(20);
    list.search(100);

    list.delete_node(20);
    list.display();

    list.reverse();
    list.display();

    return 0;
}
