//
// Created by firewolf304 on 02.06.24.
//

#ifndef LABA4_CLASSHASHTABLELIST_H
#define LABA4_CLASSHASHTABLELIST_H
//Вариант5: хэш таблица со списком коллизий,
//ключи: double на интервале от 100000.0 до 150000.0
//метод хэширования: модульный
//метод разрешения коллизий: квадратичное хеширование

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

using namespace std;
template <class K, class D>
class HashTableList {
    friend class Iterator;
    class Element;

    //Поля
    //Массив для хранения элементов
    Element **array;
    //Размер массивов и число элементов
    int capacity;
    int size;
    //Счётчик для тестирования
    int counter;

    //Методы
    //Преобразование ключа в натуральное число
    int keyToInt(K key);

    //Класс элемента таблицы
    class Element {
    public:
        //Ключ, данные, указатель на следующий элемент
        K key;
        D data;
        Element *next;
    };

public:
    //Конструктор и деструктор
    HashTableList(int capacity = 251);
    HashTableList(const HashTableList &other);
    ~HashTableList();

    //Методы АТД
    //Вставка, удаление, поиск
    bool insertData(K key, D data);
    bool deleteData(K key);
    D& getData(K key);
    //Коэффициент заполнения
    double getFilling();
    //Размер, опрос на пустоту, очистка
    int getSize();
    int getCapacity();
    bool isEmpty();
    void clear();

    //Класс итератора
    class Iterator {
        HashTableList<K, D> *table;
        bool off;
        int index;
        Element *pointer;
    public:
        Iterator(HashTableList<K, D> &table);
        D& operator*();
        bool beg();
        bool isOff();
        bool next();
        int getPos();
        K getKey();
    };

    //Дополнительные методы для тестирования
    void print();
    int getCounter();
};


template <class K, class D>
int HashTableList<K, D>::keyToInt(K key) {
    //Преобразование ключа типа double
    std::string numStr = std::to_string(std::fabs(key*key));

    // Удаление точки из строки
    numStr.erase(std::remove(numStr.begin(), numStr.end(), '.'), numStr.end());

    // Нахождение середины строки
    size_t len = numStr.size();
    size_t mid = len / 2;

    // Извлечение цифр из середины строки
    std::string middleDigits;
    if(key*key < 10000) {
        if (len % 2 == 0) {
            middleDigits = numStr.substr(mid - 1, 2); // Если четное количество цифр, взять две средние
        } else {
            middleDigits = numStr.substr(mid, 1); // Если нечетное количество цифр, взять одну среднюю
        }
    } else {
        middleDigits = numStr.substr(mid - 1, 3); // Если четное количество цифр, взять три средние
    }
    //return (int)(key * 1000.0);
    return std::atoi(middleDigits.c_str());
}

template <class K, class D>
HashTableList<K, D>::HashTableList(int capacity) {
    //Выбираем размер из чисел Мерсене
    int sizes[] = {3, 7, 13, 31, 61, 127, 251, 509,
                   1021, 2039, 4093, 8191, 16381, 32749, -1};
    this->capacity = capacity / 2;
    if(this->capacity == 0)
        this->capacity = 1;
    int index = 0;
    while(sizes[index] != -1 && sizes[index + 1] != -1 && sizes[index + 1] < this->capacity)
        ++index;
    if(sizes[index] == -1)
        throw 1;
    if(sizes[index + 1] != -1 &&
       sizes[index + 1] - this->capacity < this->capacity - sizes[index])
        ++index;
    this->capacity = sizes[index];

    //Создаём массив элементов
    this->size = 0;
    array = new Element*[this->capacity];
    for(int i = 0; i < this->capacity; ++i)
        array[i] = 0;
}

template <class K, class D>
HashTableList<K, D>::HashTableList(const HashTableList &other) {
    capacity = other.capacity;
    size = other.size;
    array = new Element*[capacity];
    Element el;
    Element last;
    for(int i = 0; i < capacity; ++i) {
        if(other.array[i] != 0) {
            el = other.array[i];
            array[i] = new Element;
            last = array[i];
            last.data = el.data;
            last.key = el.key;
            last.next = 0;
            el = el.next;
            while(el != 0) {
                last.next = new Element;
                last = last.next;
                last.data = el.data;
                last.key = el.key;
                last.next = 0;
                el = el.next;
            }
        }
    }
}

template <class K, class D>
HashTableList<K, D>::~HashTableList() {
    for(int i = 0; i < capacity; ++i) {
        if(array[i] != 0) {
            Element *next = array[i]->next;
            delete array[i];
            while(next != 0) {
                Element *nextnext = next->next;
                delete next;
                next = nextnext;
            }
        }
    }
    delete []array;
}

template <class K, class D>
bool HashTableList<K, D>::insertData(K key, D data) {
    //Вставка
    Element *ptr;
    counter = 1;
    //int index = keyToInt(key) % capacity;
    int index = ((keyToInt(key) * A) - ((int)(keyToInt(key) * A))) * capacity;
    //Проверка на несуществование элемента с таким же ключом
    ptr = array[index];
    while(ptr != 0) {
        if(ptr->key == key)
            return false;
        ptr = ptr->next;
        ++counter;
    }

    //Вставляем новый элемент в начало списка
    ptr = new Element();
    ptr->key = key;
    ptr->data = data;
    ptr->next = array[index];
    array[index] = ptr;
    ++size;
    return true;
}

template <class K, class D>
bool HashTableList<K, D>::deleteData(K key) {
    //Удаление
    Element *ptr, *prePtr;
    counter = 1;
    //int index = keyToInt(key) % capacity;
    int index = ((keyToInt(key) * A) - ((int)(keyToInt(key) * A))) * capacity;
    //Поиск удаляемого элемента
    prePtr = 0;
    ptr = array[index];
    while(ptr != 0) {
        if(ptr->key == key)
            break;
        prePtr = ptr;
        ptr = ptr->next;
        ++counter;
    }
    if(ptr == 0)
        return 0;

    //Удаляемый элемент первый в списке
    if(array[index] == ptr) {
        array[index] = ptr->next;
        delete ptr;
        --size;
        return 1;
    }

    //Удаляемый не первый элемент
    prePtr->next = ptr->next;
    delete ptr;
    --size;
    return 1;
}

template <class K, class D>
D& HashTableList<K, D>::getData(K key) {
    //Получение доступа к данным
    Element *ptr;
    counter = 1;
    //int index = keyToInt(key) % capacity;
    int index = ((keyToInt(key) * A) - ((int)(keyToInt(key) * A))) * capacity;

    //Поиск элемента с указанным ключом
    ptr = array[index];
    while(ptr != 0) {
        if(ptr->key == key)
            return ptr->data;
        ptr = ptr->next;
        ++counter;
    }

    //Элемент не найден
    throw 1;
}

template <class K, class D>
double HashTableList<K, D>::getFilling() {
    return ((double)size) / capacity;
}

template <class K, class D>
int HashTableList<K, D>::getSize() {
    return size;
}

template <class K, class D>
int HashTableList<K, D>::getCapacity() {
    return capacity;
}

template <class K, class D>
bool HashTableList<K, D>::isEmpty() {
    return (bool)size;
}

template <class K, class D>
void HashTableList<K, D>::clear() {
    Element *ptr, *ptrNext;
    for(int i = 0; i < capacity; ++i) {
        ptr = array[i];
        while(ptr != 0) {
            ptrNext = ptr->next;
            delete ptr;
            ptr = ptrNext;
        }
        array[i] = 0;
    }
}

template <class K, class D>
void HashTableList<K, D>::print() {
    Element *ptr;
    for(int i = 0; i < capacity; ++i) {
        cout << i << ". ";
        ptr = array[i];
        while(ptr != 0) {
            cout << ptr->key << ':' << ptr->data << '\t';
            ptr = ptr->next;
        }
        cout << '\n';
    }
}

template <class K, class D>
int HashTableList<K, D>::getCounter() {
    return counter;
}

//Определение итератора

template <class K, class D>
HashTableList<K, D>::Iterator::Iterator(HashTableList<K, D> &table) {
    this->table = &table;
    beg();
}

template <class K, class D>
D& HashTableList<K, D>::Iterator::operator*() {
    if(off)
        throw 1;
    return pointer->data;
}

template <class K, class D>
bool HashTableList<K, D>::Iterator::beg() {
    //Если в таблице нет элементов - указатель не установлен
    if(table->size == 0) {
        off = 1;
        throw 1;
    }

    //Ищем первый элемент
    off = 0;
    index = 0;
    while(table->array[index] == 0)
        ++index;
    pointer = table->array[index];
    return 1;
}

template <class K, class D>
bool HashTableList<K, D>::Iterator::isOff() {
    return off;
}

template <class K, class D>
bool HashTableList<K, D>::Iterator::next() {
    //Проверка на нахождение в коллекции
    if(off)
        return 0;

    //Ищем следующий элемент в списке
    if(pointer->next != 0) {
        pointer = pointer->next;
        return 1;
    }

    //Ищем следующий список
    ++index;
    while(index != table->capacity && table->array[index] == 0)
        ++index;

    //Вышли за пределы
    if(index == table->capacity) {
        off = 1;
        return 1;
    }

    //Список найден
    pointer = table->array[index];
    return 1;
}

template <class K, class D>
int HashTableList<K, D>::Iterator::getPos() {
    return index;
}

template <class K, class D>
K HashTableList<K, D>::Iterator::getKey() {
    if(off)
        throw 1;
    return pointer->key;
}
#endif //LABA4_CLASSHASHTABLELIST_H
