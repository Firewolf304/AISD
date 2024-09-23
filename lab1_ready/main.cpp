#include <iostream>
#include "src/myvector.hpp"
#include <unordered_map>
#include <functional>
int main() {
    std::cout << "Hello, World!" << std::endl;

    std::unordered_map<std::string, std::function<void()>> mapper;
    myvector<int> massive(2);
    auto it1 = massive.begin();
    auto it2 = massive.begin();
    auto rit1 = massive.rbegin();
    auto rit2 = massive.rbegin();
    mapper = {
            {"it - меню итераторов", [&massive, &it1, &it2, &rit1, &rit2](){ // push_back
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
                            std::cout << "INDEX IS " << it1.index << " VALUE: " << *it1 << std::endl;
                        } break;
                        case 1: {
                            std::cout << "INDEX IS " << it2.index << " VALUE: " << *it2 << std::endl;
                        } break;
                        case 2: {
                            std::cout << "INDEX IS " << rit2.index << " VALUE: " << *rit2 << std::endl;
                        } break;
                        case 3: {
                            std::cout << "INDEX IS " << rit2.index << " VALUE: " << *rit2 << std::endl;
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
                            it1 = massive.begin();
                        } break;
                        case 17: {
                            it2 = massive.begin();
                        } break;
                        case 18: {
                            it1 = massive.end();
                        } break;
                        case 19: {
                            it2 = massive.end();
                        } break;

                        case 20: {
                            rit1 = massive.rbegin();
                        } break;
                        case 21: {
                            rit2 = massive.rbegin();
                        } break;
                        case 22: {
                            rit1 = massive.rend();
                        } break;
                        case 23: {
                            rit2 = massive.rend();
                        } break;

                        case 24: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            *it1 = std::atoi(line.c_str());
                        } break;
                        case 25: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            *it2 = std::atoi(line.c_str());
                        } break;
                        case 26: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            *rit1 = std::atoi(line.c_str());
                        } break;
                        case 27: {
                            std::string line;
                            std::cout << "Insert int value: ";
                            std::getline(std::cin >> std::ws, line);
                            *rit2 = std::atoi(line.c_str());
                        } break;

                        default:{
                            std::cout << "NO COMMAND" << std::endl;
                        }
                    }
                } catch (std::exception const & e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                std::cout << "===========================" << std::endl;

            }},
            {"push_back - значение в конец", [&massive](){ // push_back
                std::string line;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, line);
                massive.push_back(std::atoi(line.c_str()));
            }},
            {"output - вывод", [&massive](){ // output
                std::cout << "OUPUT: " << std::endl;
                for(int d = 0; d < massive.capacity ; ++d) {
                    std::cout << d << ". " << "\t" << massive[d] << std::endl;
                }
            }},
            {"read - чтение по индексу", [&massive](){
                std::string line;
                std::cout << "Insert index: ";
                std::getline(std::cin >> std::ws, line);
                std::cout << "VALUE: " << massive.read(std::atoi(line.c_str())) << std::endl;
            }},
            {"write - запись по индексу", [&massive](){
                std::string index, value;
                std::cout << "Insert index: ";
                std::getline(std::cin >> std::ws, index);
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                massive.write(std::atoi(index.c_str()), std::atoi(value.c_str()));
            }},
            {"clear - очистка в первоначальное состояния", [&massive](){
                massive.clear();
            }},
            {"capacity - кол-во записанных элементов", [&massive](){
                std::cout << "CAPACITY: " << massive.length() << std::endl;
            }},
            {"empty - пустой?", [&massive](){
                std::cout << "EMPTY: " << (massive.empty() ? "true" : "false") << std::endl;
            }},
            {"insert - вставить куда угодно", [&massive](){
                std::string index, value;
                std::cout << "Insert index: ";
                std::getline(std::cin >> std::ws, index);
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "INSERT: " << (massive.insert(std::atoi(index.c_str()), std::atoi(value.c_str())) ? "true" : "false") << std::endl;
            }},
            {"find - поиск элемента", [&massive](){
                std::string value;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "INDEX: " << massive.find(std::atoi(value.c_str())) << std::endl;
            }},
            {"have - есть ли элемент", [&massive](){
                std::string value;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "HAVE: " << (massive.have(std::atoi(value.c_str())) ? "true" : "false") << std::endl;
            }},
            {"erase - удалить элемент по индексу", [&massive](){
                std::string value;
                std::cout << "Insert idnex: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "ERASE: " << (massive.errase(std::atoi(value.c_str())) ? "true" : "false") << std::endl;
            }},
            {"erase_value - удалить элемент по значению", [&massive](){
                std::string value;
                std::cout << "Insert int value: ";
                std::getline(std::cin >> std::ws, value);
                std::cout << "ERASE VALUE: " << (massive.errase_value(std::atoi(value.c_str())) ? "true" : "false") << std::endl;
            }},
            {"length - выделенная память", [&massive](){
                std::cout << "LENGTH: " << massive.capacity << std::endl;
            }},

    };

    std::vector<std::string> keys;
    for (const auto& pair : mapper) {
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
        if(mapper.contains(keys[command])) {
            try {
                mapper[keys[command]]();
            } catch (std::exception const & e) {
                std::cout << "Error: " << e.what() << std::endl;
            }

        }
        std::cout << "===========================" << std::endl;
    }


    /*massive = {123,123,123};

    std::vector<int> awdawd;
    std::cout << "READ: " << massive.read(0) << std::endl;
    massive.push_back(321);
    std::cout << "SIZE: " << massive.length() << std::endl;
    for (int i = 0; i < massive.length(); ++i) {
        std::cout << massive[i] << std::endl;
    }
    massive.clear();
    std::cout << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << *d << std::endl;
    }
    std::cout << "WRITE: " << massive.write(0, 123) << std::endl;
    std::cout << "WRITE: " << massive.write(999, 123) << std::endl;
    std::cout << "WRITE: " << massive.write(-1, 123) << std::endl;
    massive[2] = 123;
    massive.push_back(818887);
    massive.push_back(123);
    massive.push_back(8123);
    massive.push_back(81233);
    massive.push_back(8123);
    massive.push_back(123);
    massive.push_back(123);
    massive.push_back(123);
    std::cout << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }
    std::cout << "FOUND: " << massive.find(818887) << std::endl;
    std::cout << "FOUND ITER: " << massive.find_iterator(818887).index << std::endl;
    std::cout << "FOUND BOOL: " << massive.have(818887) << std::endl;
    std::cout << "ERRASE: " << massive.errase(1) << std::endl;
    std::cout << "ERRASE VAL: " << massive.errase_value(123) << std::endl;

    std::cout << "REVERSE SIZE: " << massive.length() << std::endl;
    for(auto d = massive.rbegin(); d != massive.rend(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }

    std::cout <<"SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }



    //std::cout << "INSERT: " << massive.insert(7, 2) << ", SIZE: " << massive.length() << std::endl;
    std::cout << "INSERT: " << massive.insert(3,2) << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }


    /*std::vector<int> vec;
    for (int i = 1 ; i < 6 ; ++i )
    {
        vec.push_back ( 2 * i );
    }
    std::vector <int>::iterator vIter;
    std::cout << "The vector vec is: " << std::endl;
    for ( vIter = vec.begin( ) ; vIter != vec.end( ); vIter++)
        std::cout << "\t" << std::distance(vec.begin(), vIter) << ". " << *vIter << std::endl;
    std::vector <int>::reverse_iterator rvIter;
    std::cout << "The vector vec reversed is: " << std::endl;
    for ( rvIter = vec.rbegin( ) ; rvIter != vec.rend( ); rvIter++)
        std::cout << "\t" << std::distance(vec.rbegin(), rvIter) << ". " << *rvIter << std::endl;*/

    return 0;
}
