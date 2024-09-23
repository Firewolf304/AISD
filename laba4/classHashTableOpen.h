//
// Created by firewolf304 on 02.06.24.
//

#ifndef LABA4_CLASSHASHTABLEOPEN_H
#define LABA4_CLASSHASHTABLEOPEN_H
#include <iostream>

using namespace std;
const double A = 0.618033;
template <class K, class D>
class HashTableOpen {
    //Тип состояния
    enum State {FREE, DELETED, BUSY};
    friend class Iterator;

    //Поля
    //Массивы для хранения ключей, состояний и значений
    K *keyArray;
    D *dataArray;
    State *stateArray;
    //Размер массивов и число элементов
    int capacity;
    int size;
    //Счётчик для тестирования
    int counter;

    //Методы
    //Преобразование ключа в натуральное число
    int keyToInt(K key);

public:
    //Конструктор и деструктор
    HashTableOpen(int capacity = 125);
    HashTableOpen(const HashTableOpen &other);
    ~HashTableOpen();

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
        HashTableOpen<K, D> *table;
        bool off;
        int index;
    public:
        Iterator(HashTableOpen<K, D> &table);
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

//Определение

template <class K, class D>
int HashTableOpen<K, D>::keyToInt(K key) {
    //Преобразование ключа типа double
    //return (int)key % capacity;
    //return  ((key * A) - ((int)(key * A))) * capacity;
    //return (key*key) / capacity;
    return (int)(key*key) % capacity;
}

template <class K, class D>
HashTableOpen<K, D>::HashTableOpen(int capacity) {
    //Выбираем размер из чисел Мерсене
    int sizes[] = {4, 8, 16, 32, 64, 128, 256, 512,
                   1024, 2048, 4096, 8192, -1};
    this->capacity = capacity * 2;	//////////////////////////////////////////////////////////////////////////////////////////////
    int index = 0;
    while(sizes[index] != -1 && sizes[index] < this->capacity)
        ++index;
    if(sizes[index] == -1)
        throw 1;
    if(index > 0 && this->capacity - sizes[index - 1] < sizes[index] - this->capacity)
        --index;
    this->capacity = sizes[index];

    //Создаём массивы
    this->size = 0;
    keyArray = new K[this->capacity];
    dataArray = new D[this->capacity];
    stateArray = new State[this->capacity];

    //Устанавливаем в состояние FREE
    for(int i = 0; i < this->capacity; ++i)
        stateArray[i] = FREE;
}

template <class K, class D>
HashTableOpen<K, D>::HashTableOpen(const HashTableOpen &other) {
    size = other.size;
    capacity = other.capacity;
    keyArray = new K[capacity];
    dataArray = new D[capacity];
    stateArray = new State[capacity];
    for(int i = 0; i < capacity; ++i) {
        keyArray[i] = other.keyArray[i];
        dataArray[i] = other.dataArray[i];
        stateArray[i] = other.stateArray[i];
    }
}

template <class K, class D>
HashTableOpen<K, D>::~HashTableOpen() {
    delete []keyArray;
    delete []dataArray;
    delete []stateArray;
}

template <class K, class D>
bool HashTableOpen<K, D>::insertData(K key, D data) {
    //Вставка, квадратичная обработка коллизий
    counter = 1;
    int index = keyToInt(key);
    int attempt = 0;
    int deletedIndex = -1;

    while(attempt != capacity && stateArray[index] != FREE) {
        //Запоминаем индекс первой удалённой ячейки
        if(stateArray[index] == DELETED && deletedIndex == -1)
            deletedIndex = index;
        //Если встретился такой же ключ - вставка невозможна
        if(stateArray[index] == BUSY && keyArray[index] == key)
            throw 1;
        //Находим следующий ключ
        ++attempt;
        //index = (((index + attempt) * A) - ((int)((index + attempt) * A))) * capacity;
        index = (index + attempt * attempt) % capacity;
        ++counter;
    }

    //Проверка на наличие свободного места в таблице
    if(attempt == capacity && deletedIndex == -1)
        throw 2;

    //Если нет ни одной удалённой ячейки - пишем в найденную
    //свободную
    if(deletedIndex == -1)
        deletedIndex = index;

    //Пишем в найденную ячейку
    keyArray[deletedIndex] = key;
    dataArray[deletedIndex] = data;
    stateArray[deletedIndex] = BUSY;
    ++size;
    return true;
}

template <class K, class D>
bool HashTableOpen<K, D>::deleteData(K key) {
    //Удаление, квадратичная обработка коллизий
    counter = 1;
    int index = ((keyToInt(key) * A) - ((int)(keyToInt(key) * A)) ) * capacity;
    int attempt = 0;

    while(attempt != capacity && stateArray[index] != FREE) {
        //Ищем элемент с совпадающим ключом
        if(stateArray[index] == BUSY && keyArray[index] == key) {
            stateArray[index] = DELETED;
            --size;
            return 1;
        }
        //Находим следующий ключ
        ++attempt;
        index = (index + attempt * attempt) % capacity;
        //index = (((index + attempt) * A) - ((int)((index + attempt) * A))) *  capacity;
        ++counter;
    }

    //Элемент не найден
    return 0;
}

template <class K, class D>
D& HashTableOpen<K, D>::getData(K key) {
    //Получение доступа к данным
    counter = 1;
    int index = ((keyToInt(key) * A) - ((int)(keyToInt(key) * A)) ) * capacity;
    int attempt = 0;

    while(attempt != capacity && stateArray[index] != FREE) {
        //Ищем элемент с совпадающим ключом
        if(stateArray[index] == BUSY && keyArray[index] == key)
            return dataArray[index];

        //Находим следующий ключ
        ++attempt;
        index = (index + attempt * attempt) % capacity;
        //index = (((index + attempt) * A) - ((int)((index + attempt) * A))) *  capacity;
        ++counter;
    }

    //Элемент не найден
    throw 1;
}

template <class K, class D>
double HashTableOpen<K, D>::getFilling() {
    return ((double)size) / capacity;
}

template <class K, class D>
int HashTableOpen<K, D>::getSize() {
    return size;
}

template <class K, class D>
int HashTableOpen<K, D>::getCapacity() {
    return capacity;
}

template <class K, class D>
bool HashTableOpen<K, D>::isEmpty() {
    return (bool)size;
}

template <class K, class D>
void HashTableOpen<K, D>::clear() {
    for(int i = 0; i < capacity; ++i)
        stateArray[i] = FREE;
}

template <class K, class D>
void HashTableOpen<K, D>::print() {
    for(int i = 0; i < capacity; ++i) {
        cout << i << ". ";
        if(stateArray[i] == FREE)
            cout << "свободно\t\t\n";
        if(stateArray[i] == DELETED)
            cout << "удалено\t\n";
        if(stateArray[i] == BUSY)
            cout << "занято\t\t" << (double)keyArray[i] << '\t' << dataArray[i] << '\n';
    }
}

template <class K, class D>
int HashTableOpen<K, D>::getCounter() {
    return counter;
}

//Определение итератора

template <class K, class D>
HashTableOpen<K, D>::Iterator::Iterator(HashTableOpen<K, D> &table) {
    this->table = &table;
    beg();
}

template <class K, class D>
D& HashTableOpen<K, D>::Iterator::operator*() {
    if(off)
        throw 1;
    return table->dataArray[index];
}

template <class K, class D>
bool HashTableOpen<K, D>::Iterator::beg() {
    //Если в таблице нет элементов - указатель не установлен
    if(table->size == 0) {
        off = 1;
        throw 1;
    }

    //Ищем первую занятую ячейку
    off = 0;
    index = 0;
    while(table->stateArray[index] != BUSY) {
        ++index;
        if(index == table->capacity) {
            off = 1;
            return 0;
        }
    }
    return 1;
}

template <class K, class D>
bool HashTableOpen<K, D>::Iterator::isOff() {
    return off;
}

template <class K, class D>
bool HashTableOpen<K, D>::Iterator::next() {
    //Проверка на нахождение в коллекции
    if(off)
        return 0;

    //Из последней ячейки сразу выходим из коллекции
    if(index == table->capacity - 1) {
        off = 1;
        return 1;
    }

    //Ищем следующую занятую ячейку
    index += 1;
    while(table->stateArray[index] != BUSY) {
        ++index;
        //Выход за пределы коллекции
        if(index == table->capacity) {
            off = 1;
            return 1;
        }
    }
    return 1;
}

template <class K, class D>
int HashTableOpen<K, D>::Iterator::getPos() {
    return index;
}

template <class K, class D>
K HashTableOpen<K, D>::Iterator::getKey() {
    if(off)
        throw 1;
    return table->keyArray[index];
}

#endif //LABA4_CLASSHASHTABLEOPEN_H
