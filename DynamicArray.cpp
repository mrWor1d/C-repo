#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <iostream>
using namespace std;


template <typename T>
class Dynarray {

    std::size_t size_;
    T* first_;

    void rangeCheck(std::size_t i) const
    {
        if (i >= size) {
            throw std::out_of_range("Index out of range");
        }
    }

    public:
        // typedefs
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = std::size_t;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        // constructors

        //default constructor
        Dynarray( size_type size = 0) 
            : size_{size}, first_{(size_)? new T[size_]:nullptr}
        {}

        //constructor with initializer list
        Dynarray (size_type size, const_reference val)
            : Dynarray{size}
        {
            try {
                for (size_type i = 0; i < size_; ++i) {
                    first_[i] = val;
                }
            } catch (...) {
                delete[] first_;
                throw;
            }
        }

        //copy constructor 
        Dynarray(Dynarray<T>const& d)
            : Dynarray{d.size_}
        {
            try {
                for (size_type i = 0; i < size_; ++i) {
                    first_[i] = d.first_[i];
                }
            } catch (...) {
                delete[] first_;
                throw;
            }
        }

        //move constructor 
        Dynarray<T>& operator=(Dynarray<T> const& d)
        {
            //copy and swap idiom (strong exception safety guarantee)
            Dynarray<T> tmp{d};
            std::swap(size_, tmp.size_);
            std::swap(first_, tmp.first_);
            
            return *this;
        }

        //destructor
        ~Dynarray() { delete[] first_; }

        //iterators
        const_iterator begin() const { return first_; } //const_iterator is a pointer to const T
        iterator begin() { return first_; } //iterator is a pointer to T
        const_iterator end() const { return first_ + size_; } //const_iterator is a pointer to const T
        iterator end() { return first_ + size_; } //iterator is a pointer to T
        const_iterator cbegin() const { return first_; } //const_iterator is a pointer to const T
        const_iterator cend() const { return first_ + size_; } //const_iterator is a pointer to const T
        const_reverse_iterator rbegin() const { return const_reverse_iterator{cend()}; } //const_reverse_iterator is a reverse const_iterator
        reverse_iterator rbegin() { return reverse_iterator{end()}; } //reverse_iterator is a reverse iterator
        const_reverse_iterator rend() const { return const_reverse_iterator{first_}; } //const_reverse_iterator is a reverse const_iterator
        reverse_iterator rend() { return reverse_iterator{first_}; } //reverse_iterator is a reverse iterator
        const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; } //const_reverse_iterator is a reverse const_iterator
        const_reverse_iterator crend() const { return const_reverse_iterator{first_}; } //const_reverse_iterator is a reverse const_iterator

        //capacity
        size_type size() const noexcept { return size_; }
        bool empty() const noexcept { return size_ == 0; }

        //element access
        const_reference operator[](size_type i) const { return first_[i]; }
        reference operator[](size_type i) { return first_[i]; }
        const_reference at(size_type i) const { rangeCheck(i); return first_[i]; }
        reference at(size_type i) { rangeCheck(i); return first_[i]; }
        
        //modifiers
        void swap(Dynarray& d) noexcept
        {
            std::swap(size_, d.size_);
            std::swap(first_, d.first_);
        }

};


int main()
{
    Dynarray<int> d{5};
    d[0] = 7;
    d[1] = 2;
    d[2] = 3;
    d[3] = 9;
    d[4] = 5;

    for (auto p = d.cbegin(); p != d.cend(); ++p) {
        cout << *p << ' '<<endl;
    }

    std::cout << '\n';

    for (auto p = d.begin(); p != d.end(); ++p) {
        *p*=2;
    }

    for (auto p = d.crbegin(); p != d.crend(); ++p) {
        std::cout << *p << ' ';
    }
}