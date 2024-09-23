#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

#include "classHashTableOpen.h"
#include "classHashTableList.h"

using namespace std;

//Тестирование с помощью меню
void menuHashTableOpenMode();
void menuHashTableListMode();
void testHashTableOpenMode();
void testHashTableListMode();
void chiSquare();

int main(int argc, char *argv[]) {
    int mode = 1;
    while(mode != 0)
    {
        //Выбор режим запуска программы
        cout << "Меню:\n"
                "0. Выход" << endl <<
             "1. Таблица с открытой индексацией\n"
             "2. Таблица со списком коллизий\n"
             "3. Тестирование таблицы с открытой индексацией\n"
             "4. Тестирование таблицы со списком коллизий\n"
             "5. Исследование равномерности функции хэширования\n";
        cin >> mode;
        if(mode == 1)
            menuHashTableOpenMode();
        if(mode == 2)
            menuHashTableListMode();
        if(mode == 3)
            testHashTableOpenMode();
        if(mode == 4)
            testHashTableListMode();
        if(mode == 5)
            chiSquare();
        //system("CLS");
    }
    return 0;
}

//32 битный rand()
int rand32() {
    return (rand() << 16) | rand();
}

//Специфичный генератор ключей для задачи
//В диапазоне 100000.00
//         до 150000.00
double drand() {
    int rnd = rand32();
    if(rnd < 0)
        rnd = -rnd;
    return (double)(rnd % 5000000 + 10000000) / 100.0;
}

//Тестирование с помощью меню
void menuHashTableOpenMode() {
    //Переменные
    int tmp, tmp2;
    double dtmp;
    //Строки
    const char programName[] = "\nХэш-таблица с открытой индексацией и\nквадратичным зондированием\n";
    const char pressAnyKey[] = "\n";

    //Объекты для тестирования
    HashTableOpen<double, int> *obj;
    HashTableOpen<double, int>::Iterator *iterator;

    //Чистим экран
    //system("cls");

    //Запрос размера
    cout << "Количество данных для вставки: ";
    cin >> tmp;
    //system("cls");

    //Создаём таблицу
    obj = new HashTableOpen<double, int>(tmp);

    //Основной цикл меню
    bool iteratorExist(0);
    while(1) {
        //system("cls");
        cout << programName;

        //Отобразить коллекцию
        cout << "Коллекция\nСостояние\tКлюч\tЗначение" << endl;
        obj->print();

        //Отобразиь итератор
        if(iteratorExist) {
            cout << "Итератор" << endl;
            if(!iterator->isOff())
                cout << "Позиция: " << iterator->getPos() << "\tКлюч: " << iterator->getKey() << "\tЗначение: " << **iterator << endl;
            else
                cout << "Позиция: -\tКлюч: -\tЗначение: -" << endl;
        }

        //Текст меню
        if(iteratorExist) {
            cout << "Итератор:" << endl <<
                 "1. В начало" << endl <<
                 "2. Следующий элемент" << endl <<
                 "3. Получить значение" << endl <<
                 "4. Изменить значение" << endl <<
                 "5. Состояние итератора" << endl <<
                 "6. Переход к меню\n";
        } else {
            cout << "Меню:" << endl <<
                 "1. Вставить значение" << endl <<
                 "2. Удалить значение" << endl <<
                 "3. Получить значение" << endl <<
                 "4. Изменить значение" << endl <<
                 "5. Число элементов" << endl <<
                 "6. Очистка" << endl <<
                 "7. Проверка на пустоту" << endl <<
                 "8. Заполненность таблицы" << endl <<
                 "9. Создать итератор" << endl <<
                 "10. Число пройденных элементов" << endl;
        }
        cout << "0. Выход" << endl;

        //Выбор пункта и проверка на корректность
        cin >> tmp;
        if(tmp < 0 || (!iteratorExist && tmp > 11) || (iteratorExist && tmp > 8))
            continue;

        //Код пунктов меню
        switch(tmp) {
            case 1: //Вставка/Итератор вначало
                if(iteratorExist)
                    try
                    {
                        iterator->beg();
                    } catch(int &) {
                        cout << "Ошибка: пустая коллекция" << endl << pressAnyKey;
                    }
                else
                    try
                    {
                        cout << "Введите ключ и значение для вставки: ";
                        cin >> dtmp >> tmp2;
                        obj->insertData(dtmp, tmp2);
                    } catch(int &err) {
                        if (err == 1)
                            cout << "Ошибка: коллекция уже содержит идентичный ключ\n" << pressAnyKey;
                        else
                            cout << "Ошибка: коллекция заполнена\n" << pressAnyKey;
                    }
                break;
            case 2: //Удаление по ключу/Итератор вправо
                if(iteratorExist) {
                    if(!iterator->next()) {
                        cout << "Ошибка: итератор за пределами коллекции, установите итератор" << endl << pressAnyKey;
                    }
                } else {
                    cout << "Введите ключ удаляемого элемента: ";
                    cin >> dtmp;
                    if(obj->deleteData(dtmp) == 0) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции" << endl << pressAnyKey;
                    }
                }
                break;
            case 3: //Получить значение * 2
                if(iteratorExist) {
                    try {
                        cout << "Значение = " << **iterator << endl;
                    } catch(int &a) {
                        cout << "Ошибка: итератор вне коллекции\n";
                    }
                } else {
                    cout << "Введите ключ элемента: ";
                    cin >> dtmp;
                    try {
                        cout << obj->getData(dtmp) << '\n' << pressAnyKey;
                    }
                    catch(int &) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции\n" << pressAnyKey;
                    }
                }
                break;
            case 4: //Изменить значение * 2
                if(iteratorExist) {
                    try {
                        cout << "Текущее значение = " << **iterator << '\n';
                        cout << "Изменить на ";
                        cin >> tmp2;
                        **iterator = tmp2;
                    } catch(int &a) {
                        cout << "Ошибка: итератор вне коллекции\n";
                    }
                } else {
                    cout << "Введите ключ элемента и новое значение: ";
                    cin >> dtmp >> tmp2;
                    try {
                        obj->getData(dtmp) = tmp2;
                    }
                    catch(int &) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции\n" << pressAnyKey;
                    }
                }
                break;
            case 5: //Число элементов/Состояние итератора
                if(iteratorExist) {
                    if(iterator->isOff())
                        cout << "Итератор вне коллекции\n";
                    else
                        cout << "Итератор внутри коллекции\n";
                    cout << pressAnyKey;
                } else {
                    cout << "Число элементов в таблице: " << obj->getSize() << '\n' << pressAnyKey;
                }
                break;
            case 6: //Очистка/Удалить итератор
                if(iteratorExist) {
                    if(iterator)
                        delete iterator;
                    iteratorExist = 0;
                } else {
                    obj->clear();
                }
                break;
            case 7: //Проверка на пустоту
                if(!(obj->isEmpty()))
                    cout << "Коллекция пуста\n";
                else
                    cout << "Коллекция не пуста\n";
                cout << pressAnyKey;

                break;
            case 8: //Заполненность
                cout << "Заполненность таблицы: " << obj->getFilling() << '\n';
                cout << pressAnyKey;
                break;
            case 9: //Создать итератор
                try
                {
                    iterator = new HashTableOpen<double, int>::Iterator(*obj);
                    iteratorExist = 1;
                } catch(int &) {
                    cout << "Ошибка: пустая коллекция" << endl << pressAnyKey;
                }
                break;
            case 10: //Число пройденных элементов
                cout << "Число пройденных элементов: " << obj->getCounter() << '\n';
                cout << pressAnyKey;
                break;
            case 0: //Выход
                return;
                break;
        }
    }
}

//Тестирование с помощью меню
void menuHashTableListMode() {
    //Переменные
    int tmp, tmp2;
    double dtmp;
    //Строки
    const char programName[] = "Хэш-таблица с открытой индексацией и\nквадратичным зондированием\n";
    const char pressAnyKey[] = "Для продолжения нажмите любую клавишу\n";

    //Объекты для тестирования
    HashTableList<double, int> *obj;
    HashTableList<double, int>::Iterator *iterator;

    //Чистим экран
    //system("cls");

    //Запрос размера
    cout << "Количество данных для вставки: ";
    cin >> tmp;
    //system("cls");
    //Создаём таблицу
    obj = new HashTableList<double, int>(tmp);

    //Основной цикл меню
    bool iteratorExist(0);
    while(1) {
        //system("cls");
        cout << programName;

        //Отобразить коллекцию
        cout << "Коллекция\n"
                "Массив Ключ:Значение\n";
        obj->print();

        //Отобразить итератор
        if(iteratorExist) {
            cout << "Итератор\n";
            if(!iterator->isOff())
                cout << "Позиция: " << iterator->getPos() << "\tКлюч: " << iterator->getKey() << "\tЗначение: " << **iterator << '\n';
            else
                cout << "Позиция: -\tКлюч: -\tЗначение: -\n";
        }

        //Текст меню
        if(iteratorExist) {
            cout << "Итератор:\n"
                    "1. В начало\n"
                    "2. Следующий элемент\n"
                    "3. Получить значение\n"
                    "4. Изменить значение\n"
                    "5. Состояние итератора\n"
                    "6. Переход к меню\n";
        } else {
            cout << "Меню:\n"
                    "1. Вставить значение\n"
                    "2. Удалить значение\n"
                    "3. Получить значение\n"
                    "4. Изменить значение\n"
                    "5. Число элементов\n"
                    "6. Очистка\n"
                    "7. Проверка на пустоту\n"
                    "8. Заполненность таблицы\n"
                    "9. Создать итератор\n"
                    "10. Количество элементов\n";
        }
        cout << "0. Выход\n";

        //Выбор пункта и проверка на корректность
        cin >> tmp;
        if(tmp < 0 || (!iteratorExist && tmp > 11) || (iteratorExist && tmp > 8))
            continue;

        //Код пунктов меню
        switch(tmp) {
            case 1: //Вставка/Итератор вначало
                if(iteratorExist) {
                    try{
                        iterator->beg();
                    } catch(int &) {
                        cout << "Ошибка: пустая коллекция" << endl << pressAnyKey;
                    }
                } else {
                    cout << "Введите ключ и значение для вставки: ";
                    cin >> dtmp >> tmp2;
                    if(!(obj->insertData(dtmp, tmp2))) {
                        cout << "Ошибка: коллекция уже содержит идентичный ключ\n" << pressAnyKey;
                    }
                }
                break;
            case 2: //Удаление по ключу/Итератор вправо
                if(iteratorExist) {
                    if(!iterator->next()) {
                        cout << "Ошибка: итератор за пределами коллекции, установите итератор\n" << pressAnyKey;
                    }
                } else {
                    cout << "Введите ключ удаляемого элемента: ";
                    cin >> dtmp;
                    if(obj->deleteData(dtmp) == 0) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции\n" << pressAnyKey;
                    }
                }
                break;
            case 3: //Получить значение * 2
                if(iteratorExist) {
                    try {
                        cout << "Значение = " << **iterator << '\n';
                    } catch(int &a) {
                        cout << "Ошибка: итератор вне коллекции\n";
                    }
                } else {
                    cout << "Введите ключ элемента: ";
                    cin >> dtmp;
                    try {
                        cout << obj->getData(dtmp) << '\n' << pressAnyKey;
                    }
                    catch(int &) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции\n" << pressAnyKey;
                    }
                }
                break;
            case 4: //Изменить значение * 2
                if(iteratorExist) {
                    try {
                        cout << "Текущее значение = " << **iterator << '\n';
                        cout << "Изменить на ";
                        cin >> tmp2;
                        **iterator = tmp2;
                    } catch(int &a) {
                        cout << "Ошибка: итератор вне коллекции\n";
                        cout << pressAnyKey;
                    }
                } else {
                    cout << "Введите ключ элемента и новое значение: ";
                    cin >> dtmp >> tmp2;
                    try {
                        obj->getData(dtmp) = tmp2;
                    }
                    catch(int &) {
                        cout << "Ошибка: введённый ключ отсутствует в коллекции\n" << pressAnyKey;
                    }
                }
                break;
            case 5: //Число элементов/Состояние итератора
                if(iteratorExist) {
                    if(iterator->isOff())
                        cout << "Итератор вне коллекции\n";
                    else
                        cout << "Итератор внутри коллекции\n";
                    cout << pressAnyKey;

                } else {
                    cout << "Число элементов в таблице: " << obj->getSize() << '\n' << pressAnyKey;
                }
                break;
            case 6: //Очистка/Удалить итератор
                if(iteratorExist) {
                    if(iterator)
                        delete iterator;
                    iteratorExist = 0;
                } else {
                    obj->clear();
                }
                break;
            case 7: //Проверка на пустоту
                if(!(obj->isEmpty()))
                    cout << "Коллекция пуста\n";
                else
                    cout << "Коллекция не пуста\n";
                cout << pressAnyKey;

                break;
            case 8: //Заполненность
                cout << "Заполненность таблицы: " << obj->getFilling() << '\n';
                cout << pressAnyKey;
                break;
            case 9: //Создать итератор
                /*if(!(obj->isEmpty()))
                   { cout << "Коллекция пуста, итератор не создан\n";
				_getch();}
                else*/
                try{
                    iterator = new HashTableList<double, int>::Iterator(*obj);
                    iteratorExist = 1;
                } catch(int &) {
                    cout << "Ошибка: пустая коллекция" << endl << pressAnyKey;
                }

                break;
            case 10:
                cout<< obj->getSize() <<endl;
                break;
            case 0: //Выход
                return;
                break;
        }
    }
}

void testHashTableOpenMode() {
    srand(time(NULL));
    cout << "Тестирование хэш-таблицы с открытой индексацией\n";

    //Опрос параметров тестирования
    int N, K;
    double emp_alpha;
    cout << "Количество вставляемых элементов: ";
    cin >> N;
    cout << "Заполненность: ";
    cin >> emp_alpha;

    //Создание коллекции
    HashTableOpen<double, int> *obj = new HashTableOpen<double, int>(N);
    K = obj->getCapacity() * emp_alpha;
    cout << "Создана коллекция с реальным размером: " << obj->getCapacity() << '\n';
    cout << "Для тестирования производится " << K / 2 << " операций\n";

    //Массив чисел для тестирования
    double *arr = new double[K];

    //Счётчики операций
    int insertCounter(0), deleteCounter(0), findCounter(0);

    //Первоначальное заполнение
    for(int i = 0; i < K; ++i) {
        arr[i] = drand();
        obj->insertData(arr[i], 1);
    }

    //Цикл тестирования
    for(int i = 0; i < K / 2; ++i) {
        //10 процентов промахов
        if(i % 10 == 0) {
            //В большинстве случаев произойдут промахи:
            //Удаление случайного ключа
            obj->deleteData(drand());
            deleteCounter += obj->getCounter();

            //Вставка уже существуюего элемента
            try {
                obj->insertData(arr[rand() % K], 1);
            }
            catch(int) { }
            insertCounter += obj->getCounter();

            //Получение случайного ключа
            try {
                obj->getData(drand());
            }
            catch(int) { }
            findCounter += obj->getCounter();
        } else {
            //Промахов не должно быть:
            //Удаляем существующий ключ
            int deletedIndex = rand() % K;
            obj->deleteData(arr[deletedIndex]);
            deleteCounter += obj->getCounter();

            //Вставляем новый ключ
            double newKey = drand();
            obj->insertData(newKey, 1);
            insertCounter += obj->getCounter();

            //Ставим этот ключ на место удалённого ранее
            arr[deletedIndex] = newKey;

            //Получаем существующий ключ
            try {
                obj->getData(arr[rand() % K]);
            }
            catch(int) { }
            findCounter += obj->getCounter();
        }
    }

    double alpha = ((double)obj->getSize()) / (obj->getCapacity());
    cout << "Число элементов после тестирования: " << obj->getSize() << endl;
    cout << "Заполненность: " << alpha << endl;
    //cout << "-ln(1 - a)/a = " << -log(1 - alpha)/alpha << endl;
    cout << (1+alpha) / 2 << endl;
    cout << "Трудоёмкость вставок: " << double(insertCounter) / double(K) * 2.0 << '\n';
    cout << "Трудоёмкость удалений: " << double(deleteCounter) / double(K) * 2.0 << '\n';
    cout << "Трудоёмкость поиска: " << double(findCounter) / double(K) * 2.0 << '\n';
    delete []arr;
    delete obj;

}

void testHashTableListMode() {
    srand(time(NULL));
    cout << "Тестирование хэш-таблицы со списком коллизий\n";

    //Опрос параметров тестирования
    int N, K;
    double ALPHA;
    cout << "Количество вставляемых элементов: ";
    cin >> N;
    cout << "Заполненность: ";
    cin >> ALPHA;

    //Создание коллекции
    HashTableList<double, int> *obj = new HashTableList<double, int>(N);
    K = obj->getCapacity() * ALPHA;
    cout << "Создана коллекция с реальным размером: " << obj->getCapacity() << '\n';
    cout << "Для тестирования производится " << K / 2 << " операций\n";

    //Массив чисел для тестирования
    double *arr = new double[K];

    //Счётчики операций
    int insertCounter(0), deleteCounter(0), findCounter(0);

    //Первоначальное заполнение
    for(int i = 0; i < K; ++i) {
        arr[i] = drand();
        obj->insertData(arr[i], 1);
    }

    //Цикл тестирования
    for(int i = 0; i < K / 2; ++i) {
        //10 процентов промахов
        if(i % 10 == 0) {
            //В большинстве случаев произойдут промахи:
            //Удаление случайного ключа
            obj->deleteData(drand());
            deleteCounter += obj->getCounter();

            //Вставка уже существуюего элемента
            obj->insertData(arr[rand() % K], 1);
            insertCounter += obj->getCounter();

            //Получение случайного ключа
            try {
                obj->getData(drand());
            }
            catch(int &a) {
                //Ничего не делаем
            }
            findCounter += obj->getCounter();
        } else {
            //Промахов не должно быть:
            //Удаляем существующий ключ
            int deletedIndex = rand() % K;
            obj->deleteData(arr[deletedIndex]);
            deleteCounter += obj->getCounter();

            //Вставляем новый ключ
            double newKey = drand();
            obj->insertData(newKey, 1);
            insertCounter += obj->getCounter();

            //Ставим этот ключ на место удалённого ранее
            arr[deletedIndex] = newKey;

            //Получаем существующий ключ
            try {
                obj->getData(arr[rand() % K]);
            }
            catch(int &) {
                //Ничего не делаем
            }
            findCounter += obj->getCounter();
        }
    }

    double alpha = (double)(obj->getSize()) / (obj->getCapacity());
    cout << "Число элементов после тестирования: " << obj->getSize() << endl;
    cout << "Заполненность: " << alpha << endl;
    //cout << "-ln(1-L)/L = " << -log(1 - alpha)/alpha << endl;
    cout << "Трудоёмкость вставок: " << ((double)insertCounter) / (K) * 2.0 << '\n';
    cout << "Трудоёмкость удалений: " << ((double)deleteCounter) / (K) * 2.0 << '\n';
    cout << "Трудоёмкость поиска: " << ((double)findCounter) / (K) * 2.0 << '\n';
    delete []arr;
    delete obj;
}

void chiSquare() {
    cout << "Качество хэш-функции по критерию хи-квадрат\n";
    srand(time(0));

    //Опрос параметров тестирования
    int N, M, delta;
    cout << "Количество вставляемых элементов: ";
    cin >> N;

    //Выбираем размер из чисел Мерсене
    int sizes[] = {3, 7, 13, 31, 61, 127, 251, 509,
                   1021, 2039, 4093, 8191, 16381, 32749, -1};
    delta = N - sizes[0];
    int index = 0;
    while(sizes[index + 1] != -1 && abs(sizes[index + 1] - N) < delta) {
        ++index;
        delta = abs(sizes[index] - N);
    }
    M = sizes[index];
    cout << "Размер массива: " << M << endl;

    //Создаём массив счётчиков
    int *counter = new int[M];
    for(int i = 0; i < M; ++i)
        counter[i] = 0;

    //Тестирование
    double val;
    int key;
    for(int i = 0; i < 20 * M; ++i) {
        val = drand();
        key = (int)(val * 100.0);
        index = key % M;
        ++(counter[index]);
    }

    //Рассчёт результата
    double m1 = M - sqrt((double) M);
    double m2 = M + sqrt((double) M);
    double hi = 0;
    for(int i = 0; i < M; ++i)
        hi += (counter[i] - 20.0) * (counter[i] - 20.0);
    hi /= 20.0;

    cout << "Результаты [m - sqrt(m)] [XI] [m + sqrt(m)]:\n";
    cout << '[' << m1 << "] [" << hi << "] [" << m2 << "]\n";
    delete []counter;

}