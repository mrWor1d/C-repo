#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

#define PRINTLINE() std::cout << '\n' << "-*********************************************************************************************-" << '\n'<< std::endl;

//include the necessary libraries
using std::cout;
using std::endl;
using std::string;


template <typename T>
//class to create a node {(data || object) && next node pointe} that will be used in the linked list
class Node
{
        T data;
        Node* next;
    public:
        Node (T const& data): data{data}, next{nullptr} {}
};


template <typename T>
//class to create a linked list
class LinkedList
{
        //class atrributes (private)
        Node* head;

    public:
        //constructor (default)
        LinkedList(): head{nullptr} {}

        //typedefs
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = std::size_t;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        //class methods

        //method to add a node at the head of the linked list
        LinkedList& insertAtHead(const_reference data)
        {
            Node* newNode = new Node(data);
            newNode->next = head;
            head = newNode;

            return *this;
        }//end method


        //method to add a node at a given position of the linked list
        LinkedList& insertAt(const_reference data, size_type& position)
        {
            Node* newNode = new Node(data);
            
            //check if the position is at the head of the linked list
            if (position<=0 || head == nullptr){

                //add the new node at the head of the linked list
                newNode->next = head;
                heade = newNode;
            } else {
                Node* current = head;
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
            Node* newNode = new Node(data);
                       
            //check if the linked list is empty
            if (head == nullptr){
                head = newNode;
            } else {
                Node* current = head;

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
                Node* temp = head; //store the head node in a temporary variable
                head = head->next; //point the head to the next node
                delete temp; //delete the node
            } else {
                Node* current = head;
                Node* previous = nullptr;
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
        

};



int main ()
{
    return 0;
}

