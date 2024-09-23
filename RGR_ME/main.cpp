#include <iostream>
#include <map>
#include <functional>
#include "graph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::shared_ptr<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>> grapher = std::make_shared<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>();
    std::shared_ptr<Hamiltonian<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>> hamil;
    std::shared_ptr<FindShortWay<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>> reber;
    std::shared_ptr<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>::OutputEdgeIterator> oit1;
    auto vit1 = grapher->beginV();
    auto eit1 = grapher->beginE();

    std::map<std::string, std::function<void()>> start = {
        {"Создать пустой граф", [&]() {
            grapher = std::make_shared<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>();
        }},
        {"Создать граф с n вершимами, типа D, формат представления F", [&]() {
            std::string value;
            std::cout << "Insert vertex count: ";
            std::getline(std::cin >> std::ws, value);
            std::string directed;
            std::cout << "Oriented list (0/1): ";
            std::getline(std::cin >> std::ws, directed);
            std::string dense;
            std::cout << "Form graph (0=L/1=M): ";
            std::getline(std::cin >> std::ws, dense);
            grapher = std::make_shared<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>(std::atoi(value.c_str()), std::atoi(directed.c_str()), std::atoi(dense.c_str()));
        }},
        {"Создать граф с V вершинами, с E случайными ребрами, типа D , формы F", [&]() {
            std::string value;
            std::cout << "Insert vertex count: ";
            std::getline(std::cin >> std::ws, value);
            std::string edge;
            std::cout << "Insert edge count: ";
            std::getline(std::cin >> std::ws, edge);
            std::string directed;
            std::cout << "Oriented list (0/1): ";
            std::getline(std::cin >> std::ws, directed);
            std::string dense;
            std::cout << "Form graph (0=L/1=M): ";
            std::getline(std::cin >> std::ws, dense);
            grapher = std::make_shared<graph<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>(std::atoi(value.c_str()), std::atoi(edge.c_str()), std::atoi(directed.c_str()), std::atoi(dense.c_str()));
        }},
    };

    std::map<std::string, std::function<void()>> mapper = {
        {"Вывод графа", [&]() {
            grapher->print_graph();
        }},
        {"Кол-во вершин", [&]() {
            std::cout<< "Vertex count is " << grapher->V() << std::endl;
        }},
        {"Кол-во ребер", [&]() {
            std::cout<< "Edge count is " << grapher->E() << std::endl;
        }},
        {"Вывод формы представления", [&]() {
            std::cout<< "Edge count is " << (grapher->Dense() ? "M" : "L" ) << std::endl;
        }},
        {"Вывод типа графа", [&]() {
            std::cout<< "Edge count is (Oriented=1 / Not oriented=0)" << (grapher->Dense() ? "true" : "false" ) << std::endl;
        }},
        {"Вывод коэффициента насыщенности", [&]() {
            std::cout<< "K is " << grapher->K() << std::endl;
        }},
        {"Преобразование графа к форме M", [&]() {
            grapher->ToMatrixGraph();
        }},
        {"Преобразование графа к форме L", [&]() {
            grapher->ToListGraph();
        }},
        {"Добавление вершины к графу", [&]() {
            std::cout<< "Vertex " << (grapher->InsertV() ? "" : "not " ) << "added" << std::endl;
        }},
        {"Удаление вершины из графа", [&]() {
            std::string value;
            std::cout << "Insert vertex name: ";
            std::getline(std::cin >> std::ws, value);
            std::cout<< "Vertex " << (grapher->DeleteV(value) ? "" : "not " ) << "deleted" << std::endl;
        }},
        {"Добавление ребра к графу", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::cout<< "Edge " << (grapher->InsertE(value1, value2) ? "" : "not " ) << "added" << std::endl;
        }},
        {"Удаление ребра из графа", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::cout<< "Edge " << (grapher->DeleteE(value1, value2) ? "" : "not " ) << "deleted" << std::endl;
        }},
        {"Чтение данных о вершине", [&]() {
            std::string value;
            std::cout << "Insert vertex name: ";
            std::getline(std::cin >> std::ws, value);
            std::cout<< "Vertex data: " << grapher->read_data_vertex(value) << std::endl;
        }},
        {"Запись данных в вершину", [&]() {
            std::string name;
            std::cout << "Insert vertex name 1: ";
            std::getline(std::cin >> std::ws, name);
            std::string value;
            std::cout << "Insert data (int): ";
            std::getline(std::cin >> std::ws, value);

            std::cout<< "Vertex data: " << grapher->write_data_vertex(name, std::atoi(value.c_str())) << std::endl;
        }},
        {"Запись нового имени вершины", [&]() {
            std::string name;
            std::cout << "Insert old vertex name: ";
            std::getline(std::cin >> std::ws, name);
            std::string value;
            std::cout << "Insert new vertex name: ";
            std::getline(std::cin >> std::ws, value);
            std::cout<< "Vertex data: " << grapher->write_name_vertex(name, value) << std::endl;
        }},
        {"Чтение веса ребра", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::cout<< "Edge weight: " << grapher->read_weight_edge(value1, value2) << std::endl;
        }},
        {"Чтение данных о ребре", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::cout<< "Edge data: " << grapher->read_data_edge(value1, value2) << std::endl;
        }},
        {"Запись веса ребра", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::string value;
            std::cout << "Insert weight (int): ";
            std::getline(std::cin >> std::ws, value);
            std::cout<< "Result: " << grapher->write_weight_edge(value1, value2, std::atoi(value.c_str())) << std::endl;
        }},
        {"Запись данных ребра", [&]() {
            std::string value1;
            std::cout << "Insert vertex name from: ";
            std::getline(std::cin >> std::ws, value1);
            std::string value2;
            std::cout << "Insert vertex name to: ";
            std::getline(std::cin >> std::ws, value2);

            std::string value;
            std::cout << "Insert data (int): ";
            std::getline(std::cin >> std::ws, value);
            std::cout<< "Result: " << grapher->write_data_edge(value1, value2, std::atoi(value.c_str())) << std::endl;
        }},
        {"Итераторы вершин", [&]() {
            std::cout << "1. Установить итератор вершин на начальную вершину" << std::endl;
            std::cout << "2. Установить итератор вершин на конечную вершину" << std::endl;
            std::cout << "3. Переход к следующей позиции" << std::endl;
            std::cout << "4. Прочитать вершину по текущей позиции итератора" << std::endl;
            std::cout << "5. Прочитать данные вершины по текущей позиции итератора" << std::endl;
            std::cout << "6. Записать данные вершины по текущей позиции итератора" << std::endl;
            std::cout << "7. Записать имя вершины по текущей позиции итератора" << std::endl;
            int command;
            std::cin >> command;
            switch(command) {
                case 1: {
                    vit1 = grapher->beginV();
                } break;
                case 2: {
                    vit1 = grapher->endV();
                } break;
                case 3: {
                    vit1.operator++();
                } break;
                case 4: {
                    std::cout << "Vertex name: " << vit1.read_vertex() << std::endl;
                } break;
                case 5: {
                    std::cout << "Vertex data (int): " << vit1.read_data_vertex() << std::endl;
                } break;
                case 6: {
                    std::string value;
                    std::cout << "Insert new vertex data (int): ";
                    std::getline(std::cin >> std::ws, value);
                    (*vit1)->setData(std::atoi(value.c_str()));
                } break;
                case 7: {
                    std::string value;
                    std::cout << "Insert new vertex name: ";
                    std::getline(std::cin >> std::ws, value);
                    (*vit1)->setName(value);
                } break;
            }
        }},
        {"Итераторы рёбер", [&]() {
            std::cout << "1. Установить итератор рёбер на начальную вершину" << std::endl;
            std::cout << "2. Установить итератор рёбер на конечную вершину" << std::endl;
            std::cout << "3. Переход к следующей позиции" << std::endl;
            std::cout << "4. Прочитать вершины ребра и вес по текущей позиции итератора" << std::endl;
            std::cout << "5. Прочитать данные ребра по текущей позиции итератора" << std::endl;
            std::cout << "6. Записать данные ребра по текущей позиции итератора" << std::endl;
            std::cout << "7. Записать вес ребра по текущей позиции итератора" << std::endl;
            int command;
            std::cin >> command;
            switch(command) {
                case 1: {
                    eit1 = grapher->beginE();
                } break;
                case 2: {
                    eit1 = grapher->endE();
                } break;
                case 3: {
                    eit1.operator++();
                } break;
                case 4: {
                    std::cout << eit1.read_edge() << std::endl;
                } break;
                case 5: {
                    std::cout << "Edge data: " << (*eit1)->getData() << std::endl;
                } break;
                case 6: {
                    std::string value;
                    std::cout << "Insert new edge data (int): ";
                    std::getline(std::cin >> std::ws, value);
                    (*eit1)->setData(std::atoi(value.c_str()));
                } break;
                case 7: {
                    std::string value;
                    std::cout << "Insert new edge weight: ";
                    std::getline(std::cin >> std::ws, value);
                    (*eit1)->setWeight(std::atoi( value.c_str() ));
                } break;
            }
        }},
        {"Итераторы исходящих рёбер", [&]() {
            std::string value;
            std::cout << "Insert vertex: ";
            std::getline(std::cin >> std::ws, value);

            oit1 = grapher->getOutputEdgeIterator(std::atoi(value.c_str()));



            bool notexit = true;
            while (notexit) {
                std::cout << "1. Установить итератор на начальное ребро" << std::endl;
                std::cout << "2. Установить итератор на конечное ребро" << std::endl;
                std::cout << "3. Переход к следующей позиции" << std::endl;
                std::cout << "4. Прочитать вершины ребра и вес по текущей позиции итератора" << std::endl;
                std::cout << "5. Прочитать данные ребра по текущей позиции итератора" << std::endl;
                std::cout << "6. Записать данные ребра по текущей позиции итератора" << std::endl;
                std::cout << "7. Записать вес ребра по текущей позиции итератора" << std::endl;
                std::cout << "8. Вернуться" << std::endl;
                int command;
                std::cin >> command;
                switch (command) {
                    case 1: {
                        oit1->begin();
                    }
                        break;
                    case 2: {
                        oit1->end();
                    }
                        break;
                    case 3: {
                        oit1->operator++();
                    }
                        break;
                    case 4: {
                        std::cout << oit1->read_edge() << std::endl;
                    }
                        break;
                    case 5: {
                        std::cout << "Edge data: " << (*(*oit1))->getData() << std::endl;
                    }
                        break;
                    case 6: {
                        std::string value;
                        std::cout << "Insert new edge data (int): ";
                        std::getline(std::cin >> std::ws, value);
                        (*(*oit1))->setData(std::atoi(value.c_str()));
                    }
                        break;
                    case 7: {
                        std::string value;
                        std::cout << "Insert new edge weight: ";
                        std::getline(std::cin >> std::ws, value);
                        (*(*oit1))->setWeight(std::atoi(value.c_str()));
                    }
                        break;
                    case 8: {
                        notexit = !notexit;
                        break;
                    }
                }
            }
        }},
        {"Гамильтонов цикл", [&]() {
            std::cout << "1. Нахождение критического ребра" << std::endl;
            std::cout << "2. Вывод путей" << std::endl;
            int command;
            std::cin >> command;
            switch(command) {
                case 1: {
                    std::cout << "Гамильтонов цикл " << (hamil->check() ? "" : "не ") << "найден" << std::endl;
                } break;
                case 2: {
                    hamil->print_result();
                } break;

            }
        }},
        {"Определение критических ребер", [&]() {
            std::cout << "1. Нахождение критического ребра" << std::endl;
            std::cout << "2. Вывод путей" << std::endl;
            int command;
            std::cin >> command;
            switch(command) {
                case 1: {
                    reber->check();
                } break;
                case 2: {
                    reber->print_result();
                } break;

            }
        }},
    };
    std::vector<std::string> starter;
    for (const auto& pair : start) {
        starter.push_back(pair.first);
    }

    std::vector<std::string> keys;
    for (const auto& pair : mapper) {
        keys.push_back(pair.first);
    }
    std::cout << "Commands:" << std::endl;
    for(int i = 0; i < starter.size(); i++) {
        std::cout << "\t" << i << ". " << starter[i] << std::endl;
    }
    int command;
    std::cout << "Insert command: ";
    std::cin >> command;
    std::cout << "===========================" << std::endl;
    if(start.contains(starter[command])) {
        try {
            start[starter[command]]();
        } catch (std::exception const & e) {
            std::cout << "Exception" << std::endl;
            std::cout << "catch(): " << e.what() << std::endl;
        }

    }
    std::cout << "===========================" << std::endl;

    hamil = std::make_shared<Hamiltonian<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>(grapher);
    reber = std::make_shared<FindShortWay<Vertex<std::string, int>, Edge<Vertex<std::string, int>,int, int>>>(grapher);
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
                std::cout << "Exception" << std::endl;
                std::cout << "catch(): " << e.what() << std::endl;
            }

        }
        std::cout << "===========================" << std::endl;
    }

    return 0;
}
