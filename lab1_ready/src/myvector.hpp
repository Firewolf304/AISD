//
// Created by firewolf on 09.03.24.
//

#ifndef LAB1_MYVECTOR_HPP
#define LAB1_MYVECTOR_HPP
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

//std::vector a()
template<class T>
class myvector {
    typedef std::allocator<T> Allocator;
    int n = 1;
    int n0 = 1;
    int size = sizeof(T);
    Allocator memory;
    T* massive;
    // 0 0 0 0 13123 123123123 123123123
public:
    int capacity = 0;
    myvector(ssize_t size = 1) {
        if(size <= 0) {
            this->n = 1;
            this->n0 = 1;
        } else {
            this->n = size;
            this->n0 = size;
        }
        this->massive = std::allocator_traits<Allocator>::allocate(this->memory, size);
        for(int i = 0; i < this->n; i++) {
            std::allocator_traits<Allocator>::construct(this->memory, &this->massive[i]);
        }
    }
    ~myvector() {
        std::allocator_traits<Allocator>::deallocate(this->memory, this->massive, this->n);
    }
    T& operator[](int index) {
        if(index >= n && index < 0) {
            throw std::out_of_range("Index is over of " + std::to_string(n));
        }
        return this->massive[index];
    }
    constexpr myvector& operator=(std::initializer_list<T> massive) {
        this->resize(0);
        for (int value : massive) {
            capacity++;
            this->push_back(value); // Добавляем элементы из списка
        }
        this->n0 = massive.size();
        return *this;
    }
    constexpr myvector& operator=(myvector<T> massive) {
        this->resize(0);
        for (int value : massive) {
            capacity++;
            this->push_back(value); // Добавляем элементы из списка
        }
        return *this;
    }
    T read(int index) {
        if(index >= this->capacity || index < 0) {
            throw std::out_of_range("Index is over of " + std::to_string(n));
        }
        return this->operator[](index);
    }
    bool write(int index, T value) {
        if(index < this->n || index >= 0) {
            this->operator[](index) = value;
            return true;
        }
        return false;
    }
    ssize_t length() { return this->n; }
    void push_back(T value) {
        capacity++;
        int save = this->n;
        if(this->n == capacity) {
            this->resize(this->n + n0);
        }
        this->massive[capacity-1] = value;
    }
    void resize(ssize_t new_size) {
        T* newArr = std::allocator_traits<Allocator>::allocate(this->memory, new_size);
        if(new_size >= this->n) {
            std::copy(this->massive, this->massive + this->n, newArr);
            for (size_t i = this->n; i < new_size; ++i) {
                std::allocator_traits<Allocator>::construct(this->memory, &newArr[i]);
            }
        } else {
            std::copy(this->massive, this->massive + new_size, newArr);
        }
        std::allocator_traits<Allocator>::deallocate(this->memory, this->massive, this->n);

        this->n = new_size;
        this->massive = newArr;
    }
    // 612837 612837 612837 612837
    void clear() {
        for (size_t i = 0; i < this->n; ++i) {
            std::allocator_traits<Allocator>::destroy(this->memory, &this->massive[i]);
        }
        std::allocator_traits<Allocator>::deallocate(this->memory, this->massive, this->n);
        //free(this->massive);
        this->n = this->n0;
        this->massive = std::allocator_traits<Allocator>::allocate(this->memory, this->n);
        for(int i = 0; i < this->n; i++) {
            std::allocator_traits<Allocator>::construct(this->memory, &this->massive[i]);
        }
        this->capacity = 0;
        //std::fill_n(this->massive, this->n, 0);
    }
    bool empty() { return this->capacity == 0; }
    bool insert(int index, T value) {
        if(index < 0) {
            return false;
        } else if (index >= this->n && this->n == this->capacity) {
            this->resize(index+n0);capacity++;
            this->n+=n0;
        } else {
            //if(this->n-1 == this->capacity) {
                capacity++;
                T *newArr = std::allocator_traits<Allocator>::allocate(this->memory, this->n + 1);
                std::copy(this->massive, this->massive + index, newArr);
                std::copy(this->massive + index, this->massive + this->n, newArr + index + 1);
                std::allocator_traits<Allocator>::deallocate(this->memory, this->massive, this->n);
                this->massive = newArr;
                if(this->capacity == this->n) {
                    this->n+=n0;
                }
            //}
        }
        this->operator[](index) = value;
        return true;
    }
    class Iterator {
    public:
        int index = -1;
        myvector<T>* massive;
        Iterator() = default;
        Iterator( int index, myvector<T>* massive ) : index(index), massive(std::move(massive)) {}
        T& operator*() {
            if(index >= massive->capacity || index < 0) {
                throw std::runtime_error("Index over of " + std::to_string(index));
            }
            return massive->massive[index];
        }
        Iterator& operator++() {                                                  // итератор постинкремент
            this->index++;
            return *this;
        }
        Iterator& operator++(int) {                                                  // итератор постинкремент
            this->index++;
            return *this;
        }
        Iterator& operator--() {                                                  // итератор постинкремент
            this->index--;
            return *this;
        }
        Iterator& operator--(int) {                                                  // итератор постинкремент
            this->index--;
            return *this;
        }
        Iterator&  operator+(ssize_t value) {                                                  // итератор постинкремент
            this->index+=value;
            return *this;
        }
        friend T operator+(int value, Iterator& it) {                                                  // итератор постинкремент
            it.index+=value;
            return it;
        }
        Iterator&  operator-(int value) {                                                  // итератор постинкремент
            this->index-=value;
            return *this;
        }
        friend T operator-(int value, Iterator& it) {                                                  // итератор постинкремент
            it.index-=value;
            return it;
        }
        friend bool operator==(Iterator& it1, const Iterator& it2) {                            // итератор равенства

            //return it1.massive->massive[it1.index] == it2.massive->massive[it2.index] ;
            return it1.index == it2.index;
        }
        friend bool operator!=(const Iterator& it1, const Iterator& it2) {                            // итератор неравенства
            return it1.index != it2.index;
        }
    };
    class ReverseIterator {
    public:
        myvector<T>* massive;
        int index = massive->n;
        ReverseIterator() = default;
        ReverseIterator( int index, myvector<T>* massive ) : index(index), massive(std::move(massive)) {}
        T& operator*() {
            if(index >= massive->capacity || index < 0) {
                throw std::runtime_error("Index over of " + std::to_string(index));
            }
            return massive->massive[this->massive->n - index - 1];
        }
        ReverseIterator& operator++() {                                                  // итератор постинкремент
            this->index++;
            return *this;
        }
        ReverseIterator& operator++(int) {                                                  // итератор постинкремент
            this->index++;
            return *this;
        }
        ReverseIterator& operator--() {                                                  // итератор постинкремент
            this->index--;
            return *this;
        }
        ReverseIterator& operator--(int) {                                                  // итератор постинкремент
            this->index--;
            return *this;
        }
        ReverseIterator&  operator+(ssize_t value) {                                                  // итератор постинкремент
            this->index+=value;
            return *this;
        }
        friend T operator+(int value, ReverseIterator& it) {                                                  // итератор постинкремент
            it.index+=value;
            return it;
        }
        ReverseIterator&  operator-(int value) {                                                  // итератор постинкремент
            this->index-=value;
            return *this;
        }
        friend T operator-(int value, ReverseIterator& it) {                                                  // итератор постинкремент
            it.index-=value;
            return it;
        }
        friend bool operator==(ReverseIterator& it1, const ReverseIterator& it2) {                            // итератор равенства
            //return it1.massive->massive[it1.index] == it2.massive->massive[it2.index] ;
            return it1.index == it2.index;
        }
        friend bool operator!=(const ReverseIterator& it1, const ReverseIterator& it2) {                            // итератор неравенства
            return it1.index != it2.index;
        }
    };
    Iterator begin() {
        return Iterator(0, this);
    }
    Iterator end() {
        return Iterator(this->capacity, this);
    }
    ReverseIterator rbegin() {
        return ReverseIterator(0, this);
    }
    ReverseIterator rend() {
        return ReverseIterator(this->capacity, this);
    }
    ssize_t find(T value) {
        for(auto d = this->begin(); d != this->end(); d++) {
            if(d.massive->massive[d.index] == value) {
                return d.index;
            }
        }
        return -1;
    }
    Iterator find_iterator(T value) {
        for(auto d = this->begin(); d != this->end(); d++) {
            if(d.massive->massive[d.index] == value) {
                return d;
            }
        }
        return this->end();
    }
    bool have(T value) {
        return this->find_iterator(value) != this->end();
    }
    bool errase (int index) {
        if(index >= 0 && index < this->n) {
            this->capacity--;
            T* newArr;
            if(this->capacity <= this->n / 2) {
                newArr = std::allocator_traits<Allocator>::allocate(this->memory, this->capacity + this->n0);
                this->n = this->capacity + this->n0;
            } else {
                newArr = std::allocator_traits<Allocator>::allocate(this->memory, this->n);
            }
            std::copy(this->massive, this->massive + index, newArr);
            std::copy(this->massive + index+1, this->massive + this->n, newArr+index);
            std::allocator_traits<Allocator>::deallocate(this->memory, this->massive, this->n);
            this->massive = newArr;
            return true;

        }
        return false;
    }
    constexpr bool errase_value(T value) {
        int saven = this->n;
        for(auto d = this->begin(); d != this->end(); d++) {
            if(*d == value) {
                this->errase(d.index);
                d--;
            }
        }
        return saven != this->n;
    }

};


/*template<class T>
class myvector {
private:
    ssize_t size = 0;       // кол-во элементов
    ssize_t n = 0;          // размер массива
    ssize_t n0 = 0;
    std::allocator<T> alloc_massive;
    T* massive;
public:
    myvector() = default;
    myvector (myvector<T> const &value) {  }                     // принятие копии коллекции
    myvector ( ssize_t size = 1 )  {                 // конструктор по размеру
        n0 = size;
        this->size = size;
        this->massive = this->alloc_massive.allocate(size);
    }
    ~myvector() {}
    void push_back(T value) {  }                                // добавить в конец
    bool push_back(int pose, T value) {}                        // добавить по индексу
    bool pop(int pose) { return true; }                                       // убрать по индексу
    //bool pop(T value) { return false; }                                               // убрать с конца

    ssize_t length() { return this->size; }                        // длина массива
    void clear() {}                                             // очистка
    bool empty() {}                                             // ты пустой?
    bool have(T value) {}
    int index(T value) {}                                       // поиск индекса
    T read(int index) {  } // если ничего, то throw
    bool change(T value, int num) {  }
    class Iterator {                                  // это НЕ реверс
    public:
        int index;                                              // индекс
        myvector* massive;                                      // принадлежность к объекту
        Iterator() {}
        Iterator(myvector const & value) { this->massive = value; }
        T& operator*() {}
        Iterator operator++(T value) {}                         // итератор постинкремент
        Iterator operator--(T value) {}                         // итератор постинкремент
        friend bool operator==(Iterator it1, Iterator it2) {}                         // итератор равенства
        friend bool operator!=(Iterator it1, Iterator it2) {}                         // итератор неравенства
    };
    class ReverseIterator {                            // это реверс
    public:
        int index;                                              // индекс
        myvector* massive;                                      // принадлежность к объекту
        ReverseIterator() {}
        ReverseIterator(myvector const & value) { this->massive = value; }
        T& operator*() {}
        ReverseIterator operator++(T value) {}                         // итератор постинкремент
        ReverseIterator operator--(T value) {}                         // итератор постинкремент
        bool operator==(ReverseIterator it1) {}                         // итератор равенства
        bool operator!=(ReverseIterator it1) {}                         // итератор неравенства
    };

    Iterator begin() {}                                         // начало
    Iterator end() {}                                           // конец
    ReverseIterator rbegin() {}                                 // реверс начало
    ReverseIterator rend() {}                                   // реверс конца
    friend class ReverseIterator;
    friend class Iterator;

};*/

#endif //LAB1_MYVECTOR_HPP
