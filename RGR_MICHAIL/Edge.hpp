//
// Created by firewolf304 on 27.05.24.
//

#ifndef RGR_ME_EDGE_HPP
#define RGR_ME_EDGE_HPP
#include <vector>
template <class VertexT, class WeightT, class DataT> class Edge {
    std::shared_ptr<VertexT> v1, v2; //Вершины, которые соединяет ребро
    WeightT weight; //Вес
    DataT data; //Данные ребра
    bool weightSet, dataSet;
public:
    Edge(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2) :
            v1(v1),
            v2(v2),
            weightSet(false),
            weight(0),
            dataSet(false) {}
    Edge(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2, WeightT weight) :
            v1(v1),
            v2(v2),
            weight(weight),
            weightSet(true),
            dataSet(false) {}
    Edge(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2, WeightT weight, DataT data) :
            v1(v1),
            v2(v2),
            weight(weight),
            data(data),
            weightSet(true),
            dataSet(true) {}
    void setWeight(WeightT weight) {
        this->weight = weight;
        weightSet = true;
    }
    void setData(DataT data) {
        this->data = data;
        dataSet = true;
    }
    WeightT getWeight() {
        return weight;
    }
    DataT getData() {
        return data;
    }
    std::shared_ptr<VertexT> getVertex1(){
        return v1;
    };
    std::shared_ptr<VertexT> getVertex2(){
        return v2;
    };
    bool isWeightSet() {
        return weightSet;
    }
    bool isDataSet() {
        return dataSet;
    }
};
#endif //RGR_ME_EDGE_HPP
