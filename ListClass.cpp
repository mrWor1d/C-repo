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
//class to create a node {(data || object) && next node pointer} that will be used in the linked list
class Node
{
        //***********************class atrributes (private)***********************
        Node<T>* address_; //pointer to the address of the node
                
    public:
        //***********************class atrributes (public)***********************
        T data_; //data or object
        Node<T>* next_; //pointer to the next node

        //***********************constructor (parametric)***********************
        Node (T const& data): data_{data}, next_{nullptr}, address_{this} {}

        //***********************destructor***********************
        ~Node()
        {
            next_ = nullptr;
        }//end destructor


        //***********************class methods***********************

        //method to get the address of the node
        Node<T>* getAddress () const { return address_; }
};


template <typename T>
//class to create a linked list
class List
{
        //***********************class atrributes (private)***********************
        Node<T>* head_; //pointer to the first node of the linked list

    public:
        //***********************constructor (default)***********************
        List(): head_{nullptr} {}

        //***********************destructor***********************
        ~List()
        {
            Node<T>* current = head_;
            Node<T>* nextNode = nullptr;

            while (current != nullptr){
                nextNode = current->next_;
                delete current;
                current = nextNode;
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

        //method to add a node at the beginning of the linked list
        List& insertAtHead(const_reference data)
        {
            Node<T>* newNode = new Node<T>(data);
            newNode->next_ = head_;
            head_ = newNode;

            return *this;
        }//end method


        //method to add a node at a given position of the linked list
        List& insertAt(const_reference data, size_type position)
        {
            Node<T>* newNode = new Node<T>(data);
            
            //check if the position is at the head of the linked list
            if (position<=0 || head_ == nullptr){

                //add the new node at the head_ of the linked list
                newNode->next_ = head_;
                head_ = newNode;
            } else {
                Node<T>* current = head_;
                size_type currentPosition=1;
                
                //find the node at the position before the position to insert the new node
                while (currentPosition < position && current->next_ != nullptr){//if the position is greater than the size of the linked list, the new node will be added at the tail

                    //move to the next node
                    current = current->next_;
                    currentPosition++;
                }
                
                //insert the new node
                newNode->next_ = current->next_; //point the new node to the next node
                current->next_ = newNode; //point the current node to the new node
            }//end if

            return *this;
        }//end method


        //method to add a node at the end of the linked list
        List& insertAtTail(const_reference data)
        {
            Node<T>* newNode = new Node<T>(data);
                       
            //check if the linked list is empty
            if (head_ == nullptr){
                head_ = newNode;
            } else {
                Node<T>* current = head_;

                //find the tail of the linked list
                while (current->next_ != nullptr){
                    current = current->next_;
                }
                //add the new node at the tail of the linked list
                current->next_ = newNode;
            }//end if

            return *this;
        }//end method


        //method to remove a node at a given position of the linked list
        List& remove(size_type& position)
        {
            //check if the linked list is empty
            if (head_ == nullptr || position < 0){
                throw std::out_of_range("The list is empty");
            } 
            else if (position==0)
            {
                Node<T>* temp = head_; //store the head node in a temporary variable
                head_ = head_->next_; //point the head to the next node
                delete temp; //delete the node
            } else {
                Node<T>* current = head_;
                Node<T>* previous = nullptr;
                size_type currentPosition=0;
                
                //find the node at the position before the position to remove the node
                while (currentPosition < position && current != nullptr){//if the position is greater than the size of the linked list, the node at the tail will be removed

                    //move to the next node
                    previous = current;
                    current = current->next_;
                    currentPosition++;
                }                
                //check if the position is greater than the size of the linked list
                if (current == nullptr){
                    throw std::out_of_range("The position is greater than the size of the list");
                } else { 
                    //remove the node
                    previous->next_ = current->next_;
                    delete current;
                }//end nested if           
            }//end if-else

            return *this;
        }//end method


        //function to print the linked list
        List& display()
        {
            Node<T>* current = head_;

            while (current != nullptr){
                cout << current->data_ << " ";
                current = current->next_;
            }
            cout << endl;

            return *this;
        }//end function

        //setters and getters

        //function to set the data of the node at a given position of the linked list
        List& setData(const_reference data, size_type position)
        {
            Node<T>* current = head_;
            size_type count = 0;

            while (current != nullptr && count < position){
                current = current->next_;
                count++;
            }

            if (current != nullptr){
                current->data_ = data;
            } else {
                throw std::out_of_range("The position is greater than the size of the list");
            }

            return *this;
        }//end function
        
        //function to get the node at a given position of the linked list
        Node<T> get (size_type position)
        {
            Node<T>* current = head_;
            size_type count = 0;

            while (current != nullptr && count < position){
                current = current->next_;
                count++;
            }

            if (current != nullptr){
                return* current;
            } else {
                throw std::out_of_range("The position is greater than the size of the list");
            }
        }//end function

        //function to get the size of the linked list
        size_type length()
        {
            Node<T>* current = head_;
            size_type count = 0;           

            while (current != nullptr){
                count++;
                current = current->next_;
            }

            return count;
        }//end function

        //function to check if the linked list contains a given value
        bool contains (const_reference data)
        {
            Node<T>* current = head_;
            bool found = false;

            while (current != nullptr && !found){
                if (current->data_ == data){
                    found = true;
                }
                current = current->next_;
            }

            return found;
        }//end function

        //function to get the position of a given value in the linked list
        size_type position (const_reference data)
        {
            Node<T>* current = head_;
            size_type count = 0;
            bool found = false;

            while (current != nullptr && !found){
                if (current->data_ == data){
                    found = true;
                } else {
                    current = current->next_;
                    count++;
                }
            }

            return (found)? count:-1;
        }//end function


        //function to check if the linked list is empty
        bool isEmpty() const noexcept { return head_ == nullptr; }


        //***********************iterators***********************

        //return the pointer to the first element of the linked list as a constant
        const_iterator begin() const { return head_; } //const_iterator is a pointer to const T

        //return the pointer to the first element of the linked list
        iterator begin() { return head_; } //iterator is a pointer to T

        //return the pointer to the last element of the linked list as a constant
        const_iterator end() const //const_iterator is a pointer to const T
        { 
            Node<T>* current = head_;
            while (current->next_ != nullptr){
                current = current->next_;
            }
            return current; 
        }

        //return the pointer to the last element of the linked list
        iterator end() //iterator is a pointer to T
        { 
            Node<T>* current = head_;
            while (current->next_ != nullptr){
                current = current->next_;
            }
            return current; 
        }

        //***********************element access***********************
        
        //return the first element of the linked list
        reference front() { return head_->data_; }

        //return the first element of the linked list as a constant
        const_reference front() const { return head_->data_; }

        //return the last element of the linked list
        reference back() 
        { 
            Node<T>* current = head_;
            while (current->next_ != nullptr){
                current = current->next_;
            }
            return current->data_; 
        }

        //return the last element of the linked list as a constant
        const_reference back() const 
        { 
            Node<T>* current = head_;
            while (current->next_ != nullptr){
                current = current->next_;
            }
            return current->data_; 
        }

        //return the element at a given position of the linked list
        reference at(size_type position) 
        { 
            Node<T>* current = head_;
            size_type count = 0;
            while (current != nullptr && count < position){
                current = current->next_;
                count++;
            }
            return current->data_; 
        }

        //return the element at a given position of the linked list as a constant
        const_reference at(size_type position) const 
        { 
            Node<T>* current = head_;
            size_type count = 0;
            while (current != nullptr && count < position){
                current = current->next_;
                count++;
            }
            return current->data_; 
        }

        //***********************operators***********************

        //overload the subscript operator to access the element at a given position of the linked list
        reference operator[] (size_type i) { return at(i); }

        //overload the subscript operator to access the element at a given position of the linked list as a constant
        const_reference operator[] (size_type i) const { return at(i); }

        //overload the  operator to return pointer to the element at a given position of the linked list


};



int main ()
{
    List<int> list;

    list.insertAtHead(5).display();

    list.insertAtHead(4).display();

    list.insertAtHead(3).display();

    PRINTNEWLINE();

    list.insertAtTail(6).display();

    list.insertAtTail(7).display();

    list.insertAtTail(8).display();

    PRINTNEWLINE();

    list.insertAt(11, 5).display();

    list.insertAt(12, 0).display();

    list.insertAt(13, 7).display();

    PRINTNEWLINE();

    PRINTLINE(list.at(0));

    PRINTLINE(list.at(2));

    PRINTLINE(list.at(6));

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

    PRINTLINE("The address of the node at position 5 is: ");

    PRINT(&list.at(5));

    PRINT(list.get(5).getAddress());

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


    PRINT(list[4]);
  
    
    return 0;
}

