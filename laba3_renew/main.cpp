#include <iostream>
#include "AST_tree.hpp"
#include <math.h>
typedef int DataType;
typedef int KeyType;
DataType lrand()
{
    return rand() << 16 | rand();
}
void test_rand(int n) {
    tree<KeyType , DataType > tree2;
    AST_tree <KeyType, DataType> tree;
    srand((unsigned)time(nullptr));	//Инициализация генератора ПСЧ
    KeyType* m = new KeyType[n];
    DataType data = 1;
    int nn = 0;
    for (int i = 0; i < n; i++)
    {
        m[i] = lrand();
        //std::cout << "\n\t\tTry add " << m[i] << std::endl;
        tree2.add(m[i], data, nn);
        tree.add(m[i], data, false, false);
        //std::cout << "--------\n";
        //tree.print();
    }
    nn = 0;
    int nn2 = 0;
    double I = 0;
    double D = 0;
    double S = 0;
    double I2 = 0;
    double D2 = 0;
    double S2 = 0;
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)
        {
            nn = 0;
            nn2 = 0;
            auto resul = lrand();
            tree2.remove(resul, nn2);
            tree.remove(resul, false, false, nn);
            //std::cout << resul << " " << res << std::endl;
            D += nn;
            D2 += nn2;
            nn = 0;
            nn2 = 0;
            int val = rand() % n;
            tree2.add(m[val], data, nn2);
            tree.add(m[val], data, false, false, nn);
            I += nn;
            I2 += nn2;
            nn2 = 0;
            nn = 0;
            try {
                tree2.find(lrand(), nn2);
            }
            catch (std::runtime_error&) {}
            try
            {
                tree.find(lrand(), nn);
            }
            catch (std::runtime_error&) {}
            S += nn;
            S2 += nn2;
            //std::cout << "--------\n";
            //tree.print();
            //sleep(1);
        }
        else
        {
            int ind = rand() % n;
            nn = 0;
            nn2 = 0;
            try {
                tree2.remove(m[ind], nn2);
                tree.remove(m[ind], false, false, nn);
            }catch(std::runtime_error&){}
            //std::cout << m[ind] << " " << res << std::endl;

            D += nn;
            D2 += nn2;
            DataType data = lrand();
            nn = 0;
            nn2 = 0;
            tree2.add(data, data, nn2);
            tree.add(data, data, false, false,nn);
            I += nn;
            I2 += nn2;
            m[ind] = data;
            nn = 0;
            nn2 = 0;
            int res = rand() % n;
            try
            {
                tree2.find(m[res], nn2);
            }
            catch (std::runtime_error&) {}
            try
            {
                tree.find(m[res], nn);
            }
            catch (std::runtime_error&) {}
            S += nn;
            S2 += nn2;
            //std::cout << "--------\n";
            //tree.print();
            //sleep(1);
        }
    std::cout << "Размер дерева после удаления: " << tree.size() << std::endl;
    std::cout << "1.39*log2(n) = " << 1.39*(log((double)n) / log(2.0)) << std::endl;
    std::cout << "Вставка: " << "AVL=" << I / (n / 2.) << " BST=" << I2 / (n / 2.) << std::endl;
    std::cout << "Удаление: " << "AVL=" <<  D / (n / 2.) << " BST=" << D2 / (n / 2.) << std::endl;
    std::cout << "Поиск: " << "AVL=" <<  S / (n / 2.) << " BST=" << S2 / (n / 2.) << std::endl;
    delete[] m;
}
void test_sort(int n) {
    tree <KeyType, DataType> tree;
    AST_tree <KeyType, DataType> tree2;
    KeyType* m = new KeyType[n];
    DataType v = 1;
    int nn = 0;
    int nn2 = 0;
    for (int i = 0; i < n; i++)
    {
        m[i] = i * 1000;
        tree.add(m[i], v, nn);
        tree2.add(m[i], v, false, false, nn2);
    }
    nn = 0;
    double I = 0;
    double D = 0;
    double S = 0;
    double I2 = 0;
    double D2 = 0;
    double S2 = 0;
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)
        {
            nn = 0;
            nn2 = 0;
            int val = lrand();
            tree.remove(val, nn);
            tree2.remove(val, false, false, nn2);

            D += nn;
            D2 += nn2;
            nn = 0;
            nn2 = 0;
            val = m[rand() % n];
            tree.add(val, v, nn);
            tree2.add(val, v, false, false, nn2);
            I += nn;
            I2 += nn2;
            val = lrand();
            try
            {
                nn2 = 0;
                tree2.find(val, nn2);
            }
            catch (std::exception&) {}
            try
            {
                nn = 0;
                tree.find(val, nn);
            }
            catch (std::exception&) {}
            S += nn;
            S2 += nn2;
        }
        else
        {
            int ind = rand() % n;
            nn = 0;
            nn2 = 0;
            tree.remove(m[ind], nn);
            tree2.remove(m[ind], false, false, nn2);
            D += nn;
            D2 += nn2;
            KeyType key = lrand() % (1000 * n);
            key = key + key % 2;
            nn = 0;
            nn2 = 0;
            tree.add(key, v, nn);
            tree2.add(key, v, false, false, nn2);
            I += nn;
            I2 += nn2;
            m[ind] = key;
            int val = m[rand() % n];
            try
            {
                nn2 = 0;
                tree2.find(val, nn2);
            }
            catch (std::exception&) {}
            try
            {
                nn = 0;
                tree.find(val, nn);
            }
            catch (std::exception&) {}
            S += nn;
            S2 += nn2;
        }
    std::cout << "Размер дерева после удаления: " << tree2.size() << std::endl;
    std::cout << "n/2 = " << n / 2. << std::endl;
    std::cout << "Вставка: BST=" << I / (n / 2) << " AVL=" << I2 / (n / 2) << std::endl;
    std::cout << "Удаление: BST=" << D / (n / 2) << " AVL=" << D2 / (n / 2) << std::endl;
    std::cout << "Поиск: BST=" << S / (n / 2) << " AVL=" << S2 / (n / 2) << std::endl;
    delete[] m;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    AST_tree<KeyType , DataType> my_tree;

    //auto it1 = tree<KeyType,DataType>::Iterator(nullptr, &my_tree);
    //auto it2 = tree<KeyType,DataType>::Iterator(nullptr, &my_tree);
    auto it1 = my_tree.begin();
    auto it2 = my_tree.begin();
    auto rit1 = tree<KeyType,DataType>::ReverseIterator(nullptr, &my_tree);
    auto rit2 = tree<KeyType,DataType>::ReverseIterator(nullptr, &my_tree);
    std::unordered_map<std::string, std::function<void()>> map = {
            {"test_rand - запуск теста", [&]()->void {
                std::string value;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                test_rand(std::atoi(value.c_str()));
            }},

            {"print - структурный вывод дерева", [&my_tree]()->void {
                my_tree.print();
            }},
            {"print_key - вывод всех ключей", [&my_tree]()->void {
                my_tree.print_key();
            }},
            {"remove - удаление поддерева по ключу", [&my_tree]()->void {
                std::string value;
                std::cout << "Insert int key: ";
                std::getline(std::cin >> std::ws, value);
                bool h = false, deleted = false;
                my_tree.remove(std::atoi(value.c_str()), h, deleted);
                std::cout << "RETURN: h=" << (h ? "true" : "false") << " deleted=" << (deleted ? "true" : "false") << std::endl;
            }},
            {"empty - проверка пустоты дерева", [&my_tree]()->void {
                std::cout << "RETURN: " << (my_tree.empty() ? "true" : "false") << std::endl;
            }},
            {"clear - очистка дерева", [&my_tree]()->void {
                std::cout << "RETURN: " << (my_tree.clear() ? "true" : "false") << std::endl;
            }},
            {"size - кол-во элементов поддерева", [&my_tree]()->void {
                std::cout << "RETURN: " << my_tree.size() << std::endl;
            }},
            {"write - запись значение по ключу", [&my_tree]()->void {
                std::string key, value;
                std::cout << "Insert int key: ";
                std::getline(std::cin >> std::ws, key);
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "RETURN: " << (my_tree.write(std::atoi(key.c_str()), std::atoi(value.c_str())) ? "true" : "false") << std::endl;
            }},
            {"find - поиск узла по ключу", [&my_tree]()->void {
                std::string key, value;
                std::cout << "Insert int key: ";
                std::getline(std::cin >> std::ws, key);
                auto val = my_tree.find(std::atoi(key.c_str()));
                std::cout << "RETURN: KEY=" << val->item << " VALUE=" << val->data << " SIZE=" << val->under_size << std::endl;
            }},
            {"test_sort - запуск теста", [&]()->void {
                std::string value;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                test_sort(std::atoi(value.c_str()));
            }},
            {"add - добавление поддерева", [&my_tree]()->void {
                std::string key, value;
                std::cout << "Insert int key: ";
                std::getline(std::cin >> std::ws, key);
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                bool h = false, inserted = false;
                my_tree.add(std::atoi(key.c_str()),std::atoi(value.c_str()), h, inserted);
                std::cout << "RETURN: h=" << (h ? "true" : "false") << " inserted=" << (inserted ? "true" : "false") << std::endl;
            }},
            {"it - меню итераторов", [&my_tree, &it1, &it2, &rit1, &rit2](){ // push_back
                int command;
                std::cout << "Commands:" << std::endl;
                std::cout << "\t" << "0. iterator1" << std::endl;
                std::cout << "\t" << "1. iterator2" << std::endl;
                std::cout << "\t" << "2. riterator1" << std::endl;
                std::cout << "\t" << "3. riterator2" << std::endl;
                std::cout << "\t" << "4. iterator1++" << std::endl;
                std::cout << "\t" << "5. iterator2++" << std::endl;
                std::cout << "\t" << "6. riterator1++" << std::endl;
                std::cout << "\t" << "7. riterator2++" << std::endl;
                std::cout << "\t" << "8. iterator1--" << std::endl;
                std::cout << "\t" << "9. iterator2--" << std::endl;
                std::cout << "\t" << "10. riterator1--" << std::endl;
                std::cout << "\t" << "11. riterator2--" << std::endl;
                std::cout << "\t" << "12. iterator1 == iterator2" << std::endl;
                std::cout << "\t" << "13. riterator1 == riterator2" << std::endl;
                std::cout << "\t" << "14. iterator1 != iterator2" << std::endl;
                std::cout << "\t" << "15. riterator1 != riterator2" << std::endl;
                std::cout << "\t" << "16. iterator1 = begin()" << std::endl;
                std::cout << "\t" << "17. iterator2 = begin()" << std::endl;
                std::cout << "\t" << "18. iterator1 = end()" << std::endl;
                std::cout << "\t" << "19. iterator2 = end()" << std::endl;
                std::cout << "\t" << "20. riterator1 = rbegin()" << std::endl;
                std::cout << "\t" << "21. riterator2 = rbegin()" << std::endl;
                std::cout << "\t" << "22. riterator1 = rend()" << std::endl;
                std::cout << "\t" << "23. riterator2 = rend()" << std::endl;

                std::cout << "\t" << "24. writing by iterator1" << std::endl;
                std::cout << "\t" << "25. writing by iterator2" << std::endl;
                std::cout << "\t" << "26. writing by riterator1" << std::endl;
                std::cout << "\t" << "27. writing by riterator2" << std::endl;
                std::cout << "Insert command: ";
                std::cin >> command;
                std::cout << "===========================" << std::endl;
                try {
                    switch (command) {
                        case 0: {
                            auto value = (it1);
                            std::cout << "RETURN: VALUE=" << value._data()->data << std::endl;
                        } break;
                        case 1: {
                            std::cout << "RETURN: VALUE=" << (*it2) << std::endl;
                        } break;
                        case 2: {
                            std::cout << "RETURN: VALUE=" << (*rit1) << std::endl;
                        } break;
                        case 3: {
                            std::cout << "RETURN: VALUE=" << (*rit2) << std::endl;
                        } break;

                        case 4: {
                            it1++;
                        } break;
                        case 5: {
                            it2++;
                        } break;
                        case 6: {
                            rit1++;
                        } break;
                        case 7: {
                            rit2++;
                        } break;

                        case 8: {
                            it1--;
                        } break;
                        case 9: {
                            it2--;
                        } break;
                        case 10: {
                            rit1--;
                        } break;
                        case 11: {
                            rit2--;
                        } break;

                        case 12: {
                            std::cout << "VALUE IS " << (it1 == it2 ? "true" : "false") << std::endl;
                        } break;
                        case 13: {
                            std::cout << "VALUE IS " << (rit1 == rit2 ? "true" : "false") << std::endl;
                        } break;

                        case 14: {
                            std::cout << "VALUE IS " << (it1 != it2 ? "true" : "false") << std::endl;
                        } break;
                        case 15: {
                            std::cout << "VALUE IS " << (rit1 != rit2 ? "true" : "false") << std::endl;
                        } break;

                        case 16: {
                            it1 = my_tree.begin();
                        } break;
                        case 17: {
                            it2 = my_tree.begin();
                        } break;
                        case 18: {
                            it1 = my_tree.end();
                        } break;
                        case 19: {
                            it2 = my_tree.end();
                        } break;

                        case 20: {
                            rit1 = my_tree.rbegin();
                        } break;
                        case 21: {
                            rit2 = my_tree.rbegin();
                        } break;
                        case 22: {
                            rit1 = my_tree.rend();
                        } break;
                        case 23: {
                            rit2 = my_tree.rend();
                        } break;

                        case 24: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            (*it1) = std::atoi(line.c_str());
                        } break;
                        case 25: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            (*it1) = std::atoi(line.c_str());
                        } break;
                        case 26: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            (*it1) = std::atoi(line.c_str());
                        } break;
                        case 27: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            (*it1) = std::atoi(line.c_str());
                        } break;
                        default:{
                            std::cout << "NO COMMAND" << std::endl;
                        }
                    }
                } catch (std::exception const & e) {
                    std::cout << "Exception" << std::endl;
                    std::cout << "catch(): " << e.what() << std::endl;
                }
                std::cout << "===========================" << std::endl;
            }}
    };
    std::vector<std::string> keys;
    for (const auto& pair : map) {
        keys.push_back(pair.first);
    }
    while(true) {
        std::cout << "Commands:" << std::endl;
        for(int i = 0; i < keys.size(); i++) {
            std::cout << "\t" << i << ". " << keys[i] << std::endl;
        }
        int command;
        std::cout << "Insert command: ";
        std::cin >> command;
        std::cout << "===========================" << std::endl;
        if(map.contains(keys[command])) {
            try {
                map[keys[command]]();
            } catch (std::exception const & e) {
                std::cout << "Exception" << std::endl;
                std::cout << "catch(): " << e.what() << std::endl;
            }

        }
        std::cout << "===========================" << std::endl;
    }
    return 0;
}