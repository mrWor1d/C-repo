#include <iostream>
#include <utility>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <limits>

#define PRINTLINE() std::cout <<'\n'<< "****************************************************************************************"<<'\n'<< std::endl;

using std::string;
using std::cout;
using std::endl;


template <typename T>
class Vector
{
        T* v_,
         * space_,
         * last_;
     
        void rangeCheck(std::size_t i) const
        {
            if (i >= size) {
                throw std::out_of_range("Index out of range");
            }
        }

    public:

        //typedefs
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = std::size_t;

        //constructors
        
        //default constructor
        Vector()
            : v_{new T[0]}, space_{v_}, last_{v_}
        {}

        //constructor with paramaters size and values
        Vector(size_type size, const_reference val)
            : v_{new T[size]}, space_{v_ + size}, last_{space_}
        {
            try {
                for (size_type i = 0; i < size; ++i) {
                    v_[i] = val;
                }
            } catch (...) {
                delete[] v_;
                throw;
            }
        }
       
       //copy constructor
         Vector(Vector<T> const& otherV)
              : v_{new T[otherV.size()]}, space_{v_ + otherV.size()}, last_{space_}
         {
              try {
                for (size_type i = 0; i < otherV.size(); ++i) {
                     v_[i] = otherV.v_[i];
                }
              } catch (...) {
                delete[] v_;
                throw;
              }
         }

        //destructor
        ~Vector () { delete[] v_; }

        //operator overloads to copy and move
        Vector<T>& operator=(Vector<T> const& otherV)
        {            
            Vector<T> temp{otherV};
            std::swap(v_, temp.v_);
            std::swap(space_, temp.space_);
            std::swap(last_, temp.last_);
            return *this;          
        }

        //modifiers

        //add elements to the end of the vector
        Vector& push_back(const_reference val)
        {
            if (space_ == last_) {
                size_type sz = size(),
                          new_size = (sz==0)? 5 : 2*sz;

                T* new_block = new T[new_size];

                try {
                    for (size_type i = 0; i < sz; ++i) {
                        new_block[i] = v_[i];
                    }
                } catch (...) {
                    delete[] new_block;
                    throw;
                }
                delete[] v_;
                v_ = new_block;
                space_ = new_block + sz;
                last_ = new_block + new_size;
            }
            
            *space_ = val;
            ++space_;            
            return *this;
        }

        //remove the last element of the vector
        Vector& pop_back()
        {
            if (space_ == v_) {
                throw std::out_of_range("Vector is empty");
            } else {
                --space_;
                *space_ = T{};
            }
            return *this;
        }

        //capacity
        size_type size() const noexcept { return space_ - v_; }
        size_type capacity() const noexcept { return last_ - v_; }
        bool empty() const noexcept { return v_ == space_; }

        //element access
        reference operator[](size_type i) { return v_[i]; }
        const_reference operator[](size_type i) const { return v_[i]; }
        reference at(size_type i) { rangeCheck(i); return v_[i]; }
        const_reference at(size_type i) const { rangeCheck(i); return v_[i]; }

        //iterators
        iterator begin() { return v_; }
        const_iterator begin() const { return v_; }
        iterator end() { return space_; }
        const_iterator end() const { return space_; }
        const_iterator cbegin() const { return v_; }
        const_iterator cend() const { return space_; }
};


int main ()
{
    Vector<int> v;
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;
    PRINTLINE();

    cout << "Size: " << v.push_back(1).push_back(2).push_back(3).push_back(4).push_back(5).size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;
    PRINTLINE();

    cout << "Elements: ";
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    PRINTLINE();
    
    cout << "Size: " << v.pop_back().size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;
    PRINTLINE();

    cout << "Elements: ";
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    PRINTLINE();

    v.pop_back();
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;
    PRINTLINE();

    cout << "Elements: ";
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    PRINTLINE();

    v.pop_back();
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;
    PRINTLINE();

    cout << "Elements: ";
    for (auto i = v.begin(); i != v.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;
    PRINTLINE();

    cout << "Size: " << v.pop_back().size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty: " << v.empty() << endl;

    return 0;
}