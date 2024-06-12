#include <iostream>
#include <list>

#define PRINTNEWLINE()  cout<<'\n'<<'\n'

//include the necessary libraries
using std::cout;
using std::endl;
using std::string;


template <typename T>
class Node
{
        //***********************class atrributes (private)***********************
        Node<T>* address_; //pointer to the address of the node

    public:
        //***********************class atrributes (public)***********************
        T        data_; //data or object
        Node<T>* next_; //pointer to the next node
        Node<T>* prev_; //pointer to the previous node

        //***********************constructor (parametric)***********************
        Node (T const& data): data_{data}, next_{nullptr}, prev_{nullptr}, address_{this} {}

        //method to get the address of the node
        Node<T>* getAddress () const { return address_; }
};


template <typename T>
class LinkedList
{
        //private class attributes
        Node<T>* head_; //pointer to the first node
        Node<T>* tail_; //pointer to the last node
        
    public:

        //type definition
        using value_type             = T;
        using reference              = T&;
        using const_reference        = const T&;
        using iterator               = T*;
        using const_iterator         = const T*;
        using size_type              = std::size_t;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator       = std::reverse_iterator<iterator>;

        //default constructor
        LinkedList (): head_{nullptr}, tail_{nullptr} {}

        //destructor
        ~LinkedList () { clear(); }

        //class methods
        
        //method to insert a node at the start of the linkedlist
        LinkedList& pushFront (const_reference data)
        {
            Node<T>* newNode = new Node<T>(data);
            if (isEmpty())
            {
                head_ = newNode;
                tail_ = newNode;
            }
            else
            {
                newNode->next_ = head_;
                head_->prev_   = newNode;
                head_          = newNode;
            }
            return *this;
        }//end pushFront


        //method to insert a node at the end of the linkedlist
        LinkedList& pushBack (const_reference  data)
        {
            Node<T>* newNode = new Node<T>(data);
            if (isEmpty())
            {
                head_ = newNode;
                tail_ = newNode;
            }
            else
            {
                newNode->prev_ = tail_;
                tail_->next_   = newNode;
                tail_          = newNode;
            }
            return *this;
        }//end pushBack


        //method to add a node at a give position of the linkdedlist
        LinkedList& insertAt (const_reference data, size_type const& position) noexcept
        {
            //check if the list is empty or if it's the first or last position
            if (position <=0 || isEmpty() || position >= length()-1)
            {
                (position >= length()-1)? pushBack (data) : pushFront (data);
            }
            else
            {
                Node<T>* newNode      = new Node<T> (data);
                Node<T>* current      = get(position-1).getAddress();
                //position-1 because we want to access the node previous to the position where we want to insert the value

                newNode->next_        = current->next_;
                newNode->prev_        = current;
                current->next_->prev_ = newNode;
                current->next_        = newNode;                   
            }

            return *this;
        }//end insertAt


        //method to add an element to the linkedlist
        LinkedList& add (const_reference data) { pushBack(data); return *this; }
        
        //mehtod to remove a node from a given position of the linkedlist
        LinkedList& remove (const size_type& position)
        {
            if (isEmpty() || position < 0) // check if the given value is lower to 0
            {
                throw std::out_of_range("The list is empty.");
            }
            else if (position==0 || position == length()-1) // check if it's at the start or at the end of the linkedlist
            {
                (position==length()-1)? popBack() : popFront();
            }
            else
            {
                Node<T>* current      = get(position).getAddress();
                Node<T>* previous     = current->prev_;
                
                previous->next_       = current->next_;
                current->next_->prev_ = previous;
                delete current;       
                
                //exception will be thrown from get() function if position > lenght()                
            }
            
            return *this;
        }//end remove


        //mehtod to remove a node matching a given value in the linkedlist
        LinkedList& remove (const_reference data, bool const& object)
        {
            if (isEmpty()) // check if the linkedlist is empty
            {
                throw std::out_of_range("The list is empty.");                        
            }
            else
            {
                Node<T>* current      = get(data, 1).getAddress();
                Node<T>* previous     = current->prev_;

                previous->next_       = current->next_;
                current->next_->prev_ = previous;
                delete current;
                //exception will be thrown from get() function if the list doesn't contain the value     
            }
            
            return *this;
        }//end remove


        //method to remove the first node of the linkedlist
        LinkedList& popFront()
        {
            Node<T>* temp       = head_;
            head_->next_->prev_ = head_->prev_;
            head_               = head_->next_;
            delete temp;
            
            return *this;
        }//end popFront


        //method to remove the last node of the linkedlist
        LinkedList& popBack()
        {
            Node<T>* temp       = tail_;
            tail_->prev_->next_ = tail_->next_;
            tail_               = tail_->prev_;
            delete temp;
            
            return *this;
        }//end of popBack


        //method to remove all the elements of the linkedlist
        LinkedList& clear ()
        {
            Node<T>* current    = head_;
            Node<T>* nextNode   = nullptr;

            while (current != nullptr)
            {
                nextNode = current->next_;
                //nextNode->prev_=nullptr;
                delete current;
                current = nextNode;
            }
            
            return *this;
        }//end clear
        
        //method to get the size of the linkedlist
        size_type length () const noexcept
        {
            size_type count = 0;            

            if (!isEmpty())
            {
                Node<T>* current = head_;                    
                while (current != nullptr)
                {
                    current = current -> next_;
                    ++count;
                }
            }

            return count;
        }//end length

        //method to print all the values contained in the nodes of the linkedlist
        LinkedList& display () noexcept
        {
            if (!isEmpty())
            {
                Node<T>* current = head_;

                for (int i = 0; i < length(); ++i)
                {
                    cout<< current->data_ <<endl;
                    current = current->next_;
                }
            }
            
            return *this;
        }//end display


        //method to print all the values contained in the nodes of the linkedlist starting from its end
        LinkedList& reverse_display () noexcept
        {
            if (!isEmpty())
            {
                Node<T>* current = tail_;

                for (int i = 0; i < length(); ++i)
                {
                    cout<< current->data_ <<endl;
                    current = current->prev_;
                } 
            }          

            return *this;
        }//end display

        //method to set the data of a given position of the linkedlist
        LinkedList& set (const_reference data, size_type const& position) { at(position) = data; return *this; }

        //method to get the node at a given position of the linkedlist
        Node<T> get (size_type const& position)
        {
            if (position <= length())
            {
                Node<T>*  current;
                size_type count = 0;

                if (position <= length()/2)
                {
                    current = head_;
                    while (current != nullptr && count < position){
                        current = current->next_;
                        count++;
                    }
                }
                else
                {
                    current = tail_;
                    count   = length()-1;
                    while (current != nullptr && count > position){
                        current = current->prev_;
                        count--;
                    }
                }

                return *current;
            }
            else
            {
                throw std::out_of_range ("The position is greater than the size of the list");
            }
        }//end get
        
        //method overload
        Node<T> get (const_reference data, bool const& object)
        {
            if (contains(data))
            {
                Node<T>* current = head_;
                bool     found   = false;

                while (!found && current != nullptr)
                {
                    if (current->data_ == data) { found = true; }
                    else { current = current->next_; }
                }

                return (found)? *current : 0;
            }
            else
            {
                throw std::out_of_range ("The list doesn't contain the given value.");
            }
        }//end get
        

        //method to obtain the position of a given value within the linkedlist (first position = 0)
        size_type positionOf (const_reference data) const
        {  
            Node<T>*  current = head_;
            size_type count   = 0;
            bool      found   = false;

            while (!found && current != nullptr)
            {
                (current->data_ == data )? found=true : ++count;
                current = current -> next_;
            }
            return (found)? count : -1;
        }//enbd positionOf


        //method to check if the linked list contains a given value
        bool contains (const_reference data) const
        {
            Node<T>* current = head_;
            bool     found   = false;

            while (!found && current != nullptr)
            {
                (current->data_==data)? found = true : 0;
                current = current-> next_;
            }

            return found;
        }//end contains

        //method to check if the linkedlist is empty
        bool isEmpty () const { return head_ == nullptr; }//end isEmpty

        //iterators and element access

        //return the first element of the linkedlist
        reference front () { return head_->data_; }

        //return the first element of the linkedlist as a constant
        const_reference front () const { return head_->data_; }

        //return the last element of the linkedlist
        reference back () { return tail_->data_; }

        //return the last element of the linkedlist as a constant
        const_reference back () const { return tail_->data_; }

        //return the first node of the linkedlist
        Node<T>*& begin () { return head_; }

        //return the first node of the linkedlist
        Node<T> const*& begin () const { return head_; }

        //return the first node of the linkedlist
        Node<T>*& end () { return tail_; }

        //return the first node of the linkedlist
        Node<T> const*& end () const { return tail_; }

        //return the element at a given position of the linked list
        reference at (const size_type& position)
        {
            if (position <= length())
            {
                Node<T>*  current;
                size_type count = 0;

                if (position <= length()/2)
                {
                    current = head_;
                    while (current != nullptr && count < position){
                        current = current->next_;
                        count++;
                    }
                }
                else
                {
                    current = tail_;
                    count   = length()-1;
                    while (current != nullptr && count > position){
                        current = current->prev_;
                        count--;
                    }
                }

                return current->data_;
            }
            else
            {
                throw std::out_of_range ("The position is greater than the size of the list");
            }
        }//end at
        

        //return the element at a given position of the linked list as a constant
        const_reference at (const size_type& position) const
        {
            if (position <= length())
            {
                Node<T>* current;
                size_type count  = 0;
                
                if (position <= length()/2)
                {
                    current = head_;
                    while (current != nullptr && count < position){
                        current = current->next_;
                        count++;
                    }
                }
                else
                {
                    current = tail_;
                    count   = length()-1;
                    while (current != nullptr && count > position){
                        current = current->prev_;
                        count--;
                    }
                }

                return current->data_;
            }
            else
            {
                throw std::out_of_range ("The position is greater than the size of the list");
            }
        }//end at

        //operators
        reference operator[] (const size_type& position) { return at(position); }
        const_reference operator[] (const size_type& position) const { return at(position); }

        reference operator() (const size_type& position) { return at(position); }
        const_reference operator() (const size_type& position) const { return at(position); }

};//end LinkedList




int main ()
{
    LinkedList<int> list {};

    list.pushFront(9).pushBack(19).insertAt(13,1);
    list.pushBack(33).pushFront(0).insertAt(2,2);

    cout<<"first element of the list "<<list[0]<<'\t'<<list.front()<<'\t'<<list.begin()->data_<<'\n';
    cout<<"last element of the list "<<list(list.length()-1)<<'\t'<<list.back()<<'\t'<<list.end()->data_<<'\n';

    PRINTNEWLINE();

    list.display().set(55,3).display();
    cout<<"list size " << list.length()<<'\n'
        <<"the list contains 33 "<< list.contains(33) << '\n';

    PRINTNEWLINE();

    cout << "the positon of 5 is "<< list.positionOf(5) << '\n'
         << "the positon of 13 is "<< list.positionOf(13)<< '\n';

    list.remove(3).popBack().popFront();
    list.reverse_display();

    PRINTNEWLINE();

    list.add(39).remove(13,1);
    cout<<"the new list is ";
    list.display();

    PRINTNEWLINE();

    cout<< "is the list empty ? " << list.isEmpty() <<'\n'
        << "Size "<< list.length();

    PRINTNEWLINE();

    cout<< "The contains "  << '\n';    
    list.clear().add(1).display();

    PRINTNEWLINE();

    cout << "new list's size " << list.length();

    return 0;
}