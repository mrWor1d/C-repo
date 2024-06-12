#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

#ifndef MYLIST_CLASS
#define MYLIST_CLASS

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
        ~List () { clear(); }

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

        //function to erase all the nodes of the linked list
        List& clear ()
        {
            Node<T>* current = head_;
            Node<T>* nextNode = nullptr;

            while (current != nullptr){
                nextNode = current->next_;
                delete current;
                current = nextNode;
            }
            
            return *this;
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
            if (position <= length()){
                Node<T>* current = head_;
                size_type count = 0;
                while (current != nullptr && count < position){
                    current = current->next_;
                    count++;
                }
                return current->data_;
            } else {
                throw std::out_of_range ("The position is greater than the size of the list");
            }
        }

        //return the element at a given position of the linked list as a constant
        const_reference at(size_type position) const 
        {
            if (position <= length){
                Node<T>* current = head_;
                size_type count = 0;
                while (current != nullptr && count < position){
                    current = current->next_;
                    count++;
                }
                return current->data_;

            } else {
                throw std::out_of_range ("The position is greater than the size of the list");
            }

        }

        //***********************operators***********************

        //overload the subscript operator to access the element at a given position of the linked list
        reference operator[] (size_type position) { return at(position); }

        //overload the subscript operator to access the element at a given position of the linked list as a constant
        const_reference operator[] (size_type position) const { return at(position); }

        //overload the  operator to return pointer to the element at a given position of the linked list


};


class Human
{
    protected:
        //***********************class atrributes (private)***********************
        string name_;
        int age_;
        Human* m_address_;
    
    public:
        //***********************constructor (default)***********************
        Human () : name_{""}, age_{0}, m_address_ {this} {}

        //***********************constructor (parametric)***********************
        Human (string& name, int& age) : name_{name}, age_{age}, m_address_ {this} {}

        //***********************class methods***********************

        //method to set the name of the human
        Human& setName(string& name) { name_ = name; return *this; }

        //method to set the age of the human
        Human& setAge(int& age) { age_ = age; return *this; }

        //method to get the name of the human
        string getName() const { return name_; }

        //method to get the age of the human
        int getAge() const { return age_; }

        //method to get the memory address of the human
        Human* memoryAddress() const { return m_address_; }
};


class Object
{
    protected:
        //***********************class atrributes (private)***********************
        Object* m_address_;

    public:
        //***********************constructor (default)***********************
        Object () : m_address_ {this} {}

        //***********************class methods***********************

        //method to get the memory address of the object
        Object* memoryAddress() const { return m_address_; }

};



#endif