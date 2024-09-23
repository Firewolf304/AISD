#include <iostream>
#include <map>
#include "tree.hpp"
#include <math.h>
typedef int DataType;
typedef int KeyType;
DataType lrand()
{
    return rand() << 16 | rand();
}
void test_rand(int n) {
    tree <DataType, KeyType> tree;
    srand((unsigned)time(nullptr));	//Инициализация генератора ПСЧ
    KeyType* m = new KeyType[n];
    DataType data = 1;
    int nn = 0;
    for (int i = 0; i < n; i++)
    {
        m[i] = lrand();
        tree.add(m[i], data, nn);
    }
    nn = 0;
    double I = 0;
    double D = 0;
    double S = 0;
    bool res = false;
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)
        {
            nn = 0;
            auto resul = lrand();
            res = tree.remove(resul, nn);
            //std::cout << resul << " " << res << std::endl;
            D += nn;
            nn = 0;
            res = tree.add(m[rand() % n], data, nn);
            I += nn;
            nn = 0;
            try
            {
                tree.find(lrand(), nn);
            }
            catch (std::runtime_error&) {}
            S += nn;
        }
        else
        {
            int ind = rand() % n;
            nn = 0;
            res = tree.remove(m[ind], nn);
            //std::cout << m[ind] << " " << res << std::endl;

            D += nn;
            DataType data = lrand();
            nn = 0;
            res = tree.add(data, data, nn);
            I += nn;
            m[ind] = data;
            nn = 0;
            try
            {
                tree.find(m[rand() % n], nn);
            }
            catch (std::runtime_error&) {}
            S += nn;
        }
    std::cout << "Размер дерева после удаления: " << tree.size() << std::endl;
    std::cout << "1.39*log2(n) = " << 1.39*(log((double)n) / log(2.0)) << std::endl;
    std::cout << "Вставка: " << I / (n / 2) << std::endl;
    std::cout << "Удаление: " << D / (n / 2) << std::endl;
    std::cout << "Поиск: " << S / (n / 2) << std::endl;
    delete[] m;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    tree<KeyType , DataType> my_tree;

    auto it1 = tree<KeyType,DataType>::Iterator(nullptr, &my_tree);
    auto it2 = tree<KeyType,DataType>::Iterator(nullptr, &my_tree);
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
            std::cout << "RETURN: " << (my_tree.remove(std::atoi(value.c_str())) ? "true" : "false") << std::endl;
        }},
        {"get_order - получение порядкового номера по ключу", [&my_tree]()->void {
            std::string value;
            std::cout << "Insert int key: ";
            std::getline(std::cin >> std::ws, value);
            std::cout << "RETURN: " << my_tree.getOrder(std::atoi(value.c_str())) << std::endl;
        }},
        {"empty - проверка пустоты дерева", [&my_tree]()->void {
            std::cout << "RETURN: " << (my_tree.empty() ? "true" : "false") << std::endl;
        }},
        {"test", [&my_tree]()->void {
            for(auto it2 = my_tree.begin(); !it2.is_off(); ++it2) {
                std::cout << my_tree.getOrder((*it2)->item) << " " << (*it2)->item << std::endl;
            }
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
            std::cout << "RETURN: KEY=" << val->item << " VALUE=" << val->data << std::endl;
        }},
        {"add - добавление поддерева", [&my_tree]()->void {
            std::string key, value;
            std::cout << "Insert int key: ";
            std::getline(std::cin >> std::ws, key);
            std::cout << "Insert int value: ";
            std::getline(std::cin >> std::ws, value);
            std::cout << "RETURN: " << (my_tree.add(std::atoi(key.c_str()), std::atoi(value.c_str())) ? "true" : "false") << std::endl;
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
                        std::cout << "RETURN: KEY=" << (*it1)->item << " VALUE=" << (*it1)->data << std::endl;
                    } break;
                    case 1: {
                        std::cout << "RETURN: KEY=" << (*it2)->item << " VALUE=" << (*it2)->data << std::endl;
                    } break;
                    case 2: {
                        std::cout << "RETURN: KEY=" << (*rit1)->item << " VALUE=" << (*rit1)->data << std::endl;
                    } break;
                    case 3: {
                        std::cout << "RETURN: KEY=" << (*rit2)->item << " VALUE=" << (*rit2)->data << std::endl;
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
                        (*it1)->data = std::atoi(line.c_str());
                    } break;
                    case 25: {
                        std::string line;
                        std::cout << "Insert int value: ";
                        std::getline(std::cin >> std::ws, line);
                        (*it1)->data = std::atoi(line.c_str());
                    } break;
                    case 26: {
                        std::string line;
                        std::cout << "Insert int value: ";
                        std::getline(std::cin >> std::ws, line);
                        (*it1)->data = std::atoi(line.c_str());
                    } break;
                    case 27: {
                        std::string line;
                        std::cout << "Insert int value: ";
                        std::getline(std::cin >> std::ws, line);
                        (*it1)->data = std::atoi(line.c_str());
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
    /*std::cout << "EMPTY: " << my_tree.empty() << std::endl;;
    my_tree.add(95, 123);
    my_tree.add(90, 321);
    my_tree.add(89, 321);
    my_tree.add(88, 321);
    my_tree.add(91, 321);
    my_tree.add(87, 51336);
    my_tree.add(86, 51336);
    my_tree.add(98, 51336);
    std::cout << "RETURN WRITE: " << my_tree.write(90, 849) << std::endl;
    std::cout << "RETURN WRITE: " << my_tree.write(190, 84646545) << std::endl;
    auto var = my_tree.find(90);
    std::cout << "FIND: " << var->data << std::endl;
    //std::cout << "RESET: "<< my_tree.reset(89, my_tree.root) << std::endl;
    std::cout << "SIZE: " << my_tree.size() << std::endl;
    my_tree.print_key();
    my_tree.print();

    auto it = my_tree.begin();
    auto rit = my_tree.rbegin()++;
    std::cout << "ITERATOR BEGIN: (" << (*it)->item  << ") " << (*it)->data << " IS_OFF=" <<it.is_off() << std::endl;
    std::cout << "ITERATOR RBEGIN: (" << (*rit)->item  << ") " << (*rit)->data << " IS_OFF=" <<rit.is_off() << std::endl;
    std::cout << "SIZE: " << my_tree.size() << std::endl;

    std::cout << "getORDER(89): " << my_tree.getOrder(89) << std::endl;
    for(auto it2 = my_tree.end(); !it2.is_off(); --it2) {
        std::cout << my_tree.getOrder((*it2)->item) << " " << (*it2)->item << std::endl;
    }*/
    return 0;
}
