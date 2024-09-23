//
// Created by firewolf304 on 27.05.24.
//

#ifndef RGR_ME_VERTEX_HPP
#define RGR_ME_VERTEX_HPP
template <class NameT, class DataT> class Vertex {
    NameT name; //Имя вершины
    DataT data; //Данные вершины
public:
    bool nameSet, dataSet;
//Конструкторы
    Vertex() :
            nameSet(false),dataSet(false) {}
    Vertex(NameT name, DataT data) :
            name(name),
            data(data),
            nameSet(true),
            dataSet(true) {}
//Установка, получение имени и данных
    void setName(NameT name) {
        this->name = name;
        nameSet = true;
    }
    void setData(DataT data) {
        this->data = data;
        dataSet = true;
    }
    NameT getName() {
        return name;
    }
    DataT getData() {
        return data;
    }
    bool isNameSet() {
        return nameSet;
    }
    bool isDataSet() {
        return dataSet;
    }
};
#endif //RGR_ME_VERTEX_HPP
