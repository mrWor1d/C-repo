#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

#define PRINTNEWLINE() std::cout << '\n' << "-*********************************************************************************************-" << '\n'<< std::endl;
#define PRINTLINE(line) std::cout << line << '\n'<< std::endl;
#define PRINT(x) std::cout << x;


//include the necessary libraries
using std::cout;
using std::endl;
using std::string;


template <typename T>
//class to create a node {(data || object) && next node pointe} that will be used in the linked list
class Node
{
       public:
        T data;
        Node<T>* next; 
        Node (T const& data): data{data}, next{nullptr} {}
};


template <typename T>
//class to create a linked list
class LinkedList
{
        //***********************class atrributes (private)***********************
        Node<T>* head;

    public:
        //***********************constructor (default)***********************
        LinkedList(): head{nullptr} {}

        //***********************destructor***********************
        ~LinkedList()
        {
            Node<T>* current = head;
            Node<T>* next = nullptr;

            while (current != nullptr){
                next = current->next;
                delete current;
                current = next;
            }
        }//end destructor

        //typedefs
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = std::size_t;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        //***********************class methods***********************

        //method to add a node at the head of the linked list
        LinkedList& insertAtHead(const_reference data)
        {
            Node<T>* newNode = new Node<T>(data); // Add missing template argument <T> when creating a new instance of 'Node'
            newNode->next = head;
            head = newNode;

            return *this;
        }//end method


        //method to add a node at a given position of the linked list
        LinkedList& insertAt(const_reference data, size_type position)
        {
            Node<T>* newNode = new Node<T>(data);
            
            //check if the position is at the head of the linked list
            if (position<=0 || head == nullptr){

                //add the new node at the head of the linked list
                newNode->next = head;
                head = newNode;
            } else {
                Node<T>* current = head;
                size_type currentPosition=0;
                
                //find the node at the position before the position to insert the new node
                while (currentPosition < position-1 && current->next != nullptr){//if the position is greater than the size of the linked list, the new node will be added at the tail

                    //move to the next node
                    current = current->next;
                    currentPosition++;
                }
                
                //insert the new node
                newNode->next = current->next; //point the new node to the next node
                current->next = newNode; //point the current node to the new node
            }//end if

            return *this;
        }//end method


        //method to add a node at the tail of the linked list
        LinkedList& insertAtTail(const_reference data)
        {
            Node<T>* newNode = new Node<T>(data);
                       
            //check if the linked list is empty
            if (head == nullptr){
                head = newNode;
            } else {
                Node<T>* current = head;

                //find the tail of the linked list
                while (current->next != nullptr){
                    current = current->next;
                }
                //add the new node at the tail of the linked list
                current->next = newNode;
            }//end if

            return *this;
        }//end method


        //method to remove a node at a given position of the linked list
        LinkedList& remove(size_type& position)
        {
            //check if the linked list is empty
            if (head == nullptr || position < 0){
                throw std::out_of_range("The list is empty");
            } 
            else if (position==0)
            {
                Node<T>* temp = head; //store the head node in a temporary variable
                head = head->next; //point the head to the next node
                delete temp; //delete the node
            } else {
                Node<T>* current = head;
                Node<T>* previous = nullptr;
                size_type currentPosition=0;
                
                //find the node at the position before the position to remove the node
                while (currentPosition < position && current != nullptr){//if the position is greater than the size of the linked list, the node at the tail will be removed

                    //move to the next node
                    previous = current;
                    current = current->next;
                    currentPosition++;
                }                
                //check if the position is greater than the size of the linked list
                if (current == nullptr){
                    throw std::out_of_range("The position is greater than the size of the list");
                } else { 
                    //remove the node
                    previous->next = current->next;
                    delete current;
                }//end nested if           
            }//end if-else

            return *this;
        }//end method


        //function to print the linked list
        LinkedList& display()
        {
            Node<T>* current = head;

            while (current != nullptr){
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;

            return *this;
        }//end function
        

        //function to get the size of the linked list
        size_type length()
        {
            Node<T>* current = head;
            size_type count = 0;           

            while (current != nullptr){
                count++;
                current = current->next;
            }

            return count;
        }//end function

        //function to check if the linked list contains a given value
        bool contains(const_reference data)
        {
            Node<T>* current = head;
            bool found = false;

            while (current != nullptr && !found){
                if (current->data == data){
                    found = true;
                }
                current = current->next;
            }

            return found;
        }//end function

        //function to get the position of a given value in the linked list
        size_type position(const_reference data)
        {
            Node<T>* current = head;
            size_type count = 0;
            bool found = false;

            while (current != nullptr && !found){
                if (current->data == data){
                    found = true;
                } else {
                    current = current->next;
                    count++;
                }
            }

            return (found)? count:-1;
        }//end function

        //function to get the pointer to a given position of the linked list
        Node<T>* getAddress(size_type i)
        {
            Node<T>* current = head;
            size_type count = 0;
            while (current != nullptr && count < i){
                current = current->next;
                count++;
            }
            return current;
        }//end function

        //function to check if the linked list is empty
        bool isEmpty() const noexcept { return head == nullptr; }


        //***********************iterators***********************

        //return the pointer to the first element of the linked list as a constant
        const_iterator begin() const { return head; } //const_iterator is a pointer to const T

        //return the pointer to the first element of the linked list
        iterator begin() { return head; } //iterator is a pointer to T

        //return the pointer to the last element of the linked list as a constant
        const_iterator end() const //const_iterator is a pointer to const T
        { 
            Node<T>* current = head;
            while (current->next != nullptr){
                current = current->next;
            }
            return current; 
        }

        //return the pointer to the last element of the linked list
        iterator end() //iterator is a pointer to T
        { 
            Node<T>* current = head;
            while (current->next != nullptr){
                current = current->next;
            }
            return current; 
        }

        //***********************element access***********************
        
        //return the first element of the linked list
        reference front() { return head->data; }

        //return the first element of the linked list as a constant
        const_reference front() const { return head->data; }

        //return the last element of the linked list
        reference back() 
        { 
            Node<T>* current = head;
            while (current->next != nullptr){
                current = current->next;
            }
            return current->data; 
        }

        //return the last element of the linked list as a constant
        const_reference back() const 
        { 
            Node<T>* current = head;
            while (current->next != nullptr){
                current = current->next;
            }
            return current->data; 
        }

        //return the element at a given position of the linked list
        reference at(size_type i) 
        { 
            Node<T>* current = head;
            size_type count = 0;
            while (current != nullptr && count < i){
                current = current->next;
                count++;
            }
            return current->data; 
        }

        //return the element at a given position of the linked list as a constant
        const_reference at(size_type i) const 
        { 
            Node<T>* current = head;
            size_type count = 0;
            while (current != nullptr && count < i){
                current = current->next;
                count++;
            }
            return current->data; 
        }

        //***********************operators***********************

        //overload the subscript operator to access the element at a given position of the linked list
        reference operator[](size_type i) { return at(i); }

        //overload the subscript operator to access the element at a given position of the linked list as a constant
        const_reference operator[](size_type i) const { return at(i); }

        //overload the  operator to return pointer to the element at a given position of the linked list


};



int main ()
{
    LinkedList<int> list;

    list.insertAtHead(5).display();

    list.insertAtHead(4).display();

    list.insertAtHead(3).display();

    list.insertAtHead(2).display();

    list.insertAtHead(1).display();

    PRINTNEWLINE();

    list.insertAtTail(6).display();

    list.insertAtTail(7).display();

    list.insertAtTail(8).display();

    list.insertAtTail(9).display();

    list.insertAtTail(10).display();

    PRINTNEWLINE();

    list.insertAt(11, 5).display();

    list.insertAt(12, 0).display();

    list.insertAt(13, 10).display();

    PRINTNEWLINE();

    PRINTLINE(list.at(0));

    PRINTLINE(list.at(5));

    PRINTLINE(list.at(9));

    PRINTNEWLINE();

    PRINTLINE(list.front());

    PRINTLINE(list.back());

    PRINTNEWLINE();

    PRINTLINE(list.position(1));

    PRINTLINE(list.position(6));

    PRINTLINE(list.position(10));

    PRINTNEWLINE();

    PRINTLINE(list.contains(1));

    PRINTLINE(list.contains(6));

    PRINTLINE(list.contains(10));

    PRINTNEWLINE();

    PRINTLINE("The list is empty: ");
    PRINTLINE(list.isEmpty());

    PRINTLINE("the list contains the following elements: ");
    
    PRINT('{'); list.display(); PRINT('}');

    PRINTLINE("And the size of the list is: ")
    PRINTLINE(list.length());

    PRINTNEWLINE();
    list[7]=100;
    PRINTLINE(list[7]);

    list.getAddress(8)->data=200;
    PRINT(list[8]);
  
    
    return 0;
}

