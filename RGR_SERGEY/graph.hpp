//
// Created by firewolf304 on 27.05.24.
//

#ifndef RGR_ME_GRAPH_HPP
#define RGR_ME_GRAPH_HPP
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <iomanip>
#include <queue>
#include "Edge.hpp"

int sz=0;

template <class EdgeT> class GraphForm {
public:
//Вставка и удаление вершин и рёбер
    virtual bool InsertV(int index) = 0;
    virtual bool DeleteV(int index) = 0;
    virtual bool InsertE(int v1, int v2, std::shared_ptr<EdgeT> t) = 0;
    virtual bool DeleteE(int v1, int v2) = 0;
//Удалить входящие и исходящие из вершины рёбра
    virtual int DeleteEsFromVertex(int index, bool directed) = 0;
//Проверка и получение
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual std::shared_ptr<EdgeT> getEdge(int v1, int v2) = 0;
};
template <class EdgeT> class GraphMatrixForm : public GraphForm<EdgeT> {
    bool directed;
public:
    std::vector<std::vector<std::shared_ptr<EdgeT>>> matrix;
    GraphMatrixForm(bool directed) : directed(directed) {}
    bool InsertV(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(index < 0 || index > size) return false;
        //Создаём новую пустую строку
        std::vector<std::shared_ptr<EdgeT> > newLine;
        newLine.assign(size, nullptr);
        //Вставляем новую строку:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //Вставляем новый столбец:
        for(int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, std::shared_ptr<EdgeT>(nullptr));
        return true;
    }
    bool DeleteV(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(index < 0 || index >= size) return false;
        //Удаляем строку:
        matrix.erase(matrix.begin() + index);
        --size;
        //Удаляем столбец:
        for(int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;
    }
    bool InsertE(int v1, int v2, std::shared_ptr<EdgeT> t) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Петля или ребро уже есть
        if(v1 == v2 || matrix[v1][v2] != nullptr) return false;
        //Вставляем ребро
        matrix[v1][v2] = t;
        return true;
    }
    bool DeleteE(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Ребра нет
        if(v1 == v2 || matrix[v1][v2] == nullptr) return false;
        matrix[v1][v2] = nullptr;
        return true;
    }
    int DeleteEsFromVertex(int index, bool directed) {
        int size = matrix.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if(index < 0 || index >= size) return 0;
        //Удаляем связанные с вершиной рёбра
        for(int i = 0; i < size; i++) {
            if(matrix[i][index] != nullptr) {
                //delete matrix[i][index];
                matrix[i][index].reset();
                ++deleted;
                //Стираем симметричное ребро
                if(directed == false)
                    matrix[index][i].reset();
            }
            if(matrix[index][i] != nullptr) {
                matrix[index][i].reset();
                //matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;

    }
    bool hasEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        if(v1 == v2) //Петля
            return false;
        if(matrix[v1][v2] != nullptr)
            return true;
        return false;
    }
    std::shared_ptr<EdgeT> getEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw std::runtime_error("Incorrect value");
        if(v1 == v2 || matrix[v1][v2] == nullptr)//Петля
            throw std::runtime_error("Loop value");
        return matrix[v1][v2];
    }
    class EdgeIterator  {
        bool end;
        GraphMatrixForm * f;
    public:
        int i, j;
        EdgeIterator(GraphMatrixForm * graph, int i, int j, bool end = false) : f(graph), i(i), j(j) {}
        bool onEnd() { return end; }
        void operator++ () {
            if(end)
                return;
            ++j;
            while(i < f->matrix.size()) {
                while(j < f->matrix.size()) {
                    if(f->matrix[i][j])
                        return;
                    ++j;
                }
                ++i;
                j = (f->directed ? 0 : i + 1);
            }
            end = true;
        }
        std::shared_ptr<EdgeT> operator* () {
            if(end) throw std::runtime_error("Iterator in end");
            if(!(f->matrix[i][j])) {
                return f->matrix[i][j];
            }
        }
    };

    EdgeIterator begin() {
        for(int i = 0; i < matrix.size(); ++i)
            for(int j = 0; j < matrix.size(); ++j)
                if(this->matrix[i][j]) {
                    return EdgeIterator(this, i, j, false);
                }
        return EdgeIterator(this,-1, -1, true);
    }
    EdgeIterator end() {
        for(int i = matrix.size()-1; i >= 0 ; --i)
            for(int j = matrix.size()-1; j >= 0 ; --j)
                if(this->matrix[i][j]) {
                    return EdgeIterator(this, i, j, true);
                }
        return EdgeIterator(this,-1, -1, true);
    }

    class OutputEdgeIterator {
        int curI, curJ;
        bool end;
        std::shared_ptr<GraphMatrixForm>  f;
    public:
        OutputEdgeIterator(std::shared_ptr<GraphMatrixForm> f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }
        bool begin() {
            for(curJ = 0; curJ < f->matrix.size(); ++curJ)
                if(f->matrix[curI][curJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }
        bool toend(){
            for(curJ=f->matrix.size()-1; curJ>=0; --curJ)
                if (f->matrix[curI][curJ]){
                    end=false;
                    return true;
                }
            end=true;
            return false;
        }
        bool onEnd() {
            return end;
        }
        bool next() {
            if(end)
                return false;
            ++curJ;
            while(curJ < f->matrix.size()) {
                if(f->matrix[curI][curJ])
                    return true;
                ++curJ;
            }
            end = true;
            return false;
        }
        std:: shared_ptr<EdgeT> getEdge() {
            if(end)
                throw std::runtime_error("Out of range");
            return f->matrix[curI][curJ];
        }
    };

};

template <class EdgeT> class GraphListForm : public GraphForm<EdgeT> {

    class Node {
    public:
        std::shared_ptr<EdgeT> edge;
        int v2;
    };
     std::vector<std::list<Node>> edgeList;
    bool directed;

public:
    GraphListForm(bool directed) : directed(directed) {}
    bool InsertV(int index) {
        int size = edgeList.size();
        if(index < 0 || index > size) {
            return false; // если вставка не соответсвует
        }
        std::list<Node> newList{};
        edgeList.insert(edgeList.begin() + index, newList);
        for(int i = 0; i < size; ++i)
            for(auto j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);    //то увеличиваем этот номер
        return true;
    }
    bool DeleteV(int index) {
        int size = edgeList.size(); //Число вершин
        if(index < 0 || index >= size)  //Неверный номер вершины
            return false;
        for(int i = 0; i < size; ++i) {
            for (auto j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    edgeList[i].erase(j);
                    break;
                }
        }
        edgeList.erase(edgeList.begin() + index);
        --size;
        for(int i = 0; i < size; ++i)
            for(auto j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,
                    --((*j).v2);//то уменьшить этот номер
        return true;
    }
    bool InsertE(int v1, int v2, std::shared_ptr<EdgeT> t) {
        int size = edgeList.size();                             //Число вершин
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)        //Неверный номер вершины
            return false;
        if(v1 == v2 || hasEdge(v1, v2))                         //Петля или ребро уже есть
            return false;
        Node newNode;
        newNode.edge = t;
        newNode.v2 = v2;
        edgeList[v1].push_front(newNode);
        return true;
    }
    bool DeleteE(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if(v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //Удаляем ребро
        for(auto j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }
    int DeleteEsFromVertex(int index, bool directed) { //Удалить входящие и исходящие из вершины рёбра
        int size = edgeList.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if(index < 0 || index >= size)
            return 0;
        //Удаляем связанные с вершиной рёбра
        for(int i = 0; i < size; ++i)
            for(auto j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if((*j).v2 == index) {
                    (*j).edge.reset();
                    edgeList[i].erase(j);
                    ++deleted;
                    //Стираем симметричное ребро
                    if(directed == false)
                        for(auto k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if((*k).v2 == i) {
                                edgeList[index].erase(k);
                                break;
                            }
                    break;
                }
        if (directed==true){
            for(auto z = edgeList[index].begin(); z != edgeList[index].end(); ++z){
                (*z).edge.reset();
                deleted++;
            }
        }
        return deleted;
    }
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин

        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;//Неверный номер вершины

        //Lets go петля
        if(v1 == v2)
            return false;
        for(auto j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if((*j).v2 == v2)
                return true;
        return false;
    }
    std::shared_ptr<EdgeT> getEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if(v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw std::runtime_error("Incorrect index");
        //Петля
        if(v1 == v2)
            throw std::runtime_error("Trying insert loop");
        for(auto j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if((*j).v2 == v2)
                return (*j).edge;
                //return (*j).edge;
        //return nullptr;
        throw std::runtime_error("Trying insert loop");
    }
    class EdgeIterator {
        int curI;
        std::list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        GraphListForm *f;
    public:
        EdgeIterator(GraphListForm * f, int curI, std::list<typename GraphListForm<EdgeT>::Node>::iterator curJ, bool end = false) : f(f), curI(curI), curJ(curJ), end(end) {}
        bool onEnd() {
            return end;
        }
        void operator++() {
            if(end)
                return;
            ++curJ;
            while(curI < f->edgeList.size()) {
                while(curJ != f->edgeList[curI].end()) {
                    if((*curJ).edge && (f->directed || !f->directed && (*curJ).v2 > curI))
                        return;
                    ++curJ;
                }
                ++curI;
                if(curI < f->edgeList.size())
                    curJ = f->edgeList[curI].begin();
            }
            end = true;
        }
        std::shared_ptr<EdgeT> operator* () {
            if(end) throw std::runtime_error("Iterator in end");
            return (*curJ).edge;
        }
    };
    EdgeIterator begin() {
        for(int curI = 0; curI < this->edgeList.size(); ++curI)
            for(auto curJ = this->edgeList[curI].begin(); curJ != this->edgeList[curI].end(); ++curJ)
                if(curJ->edge) {
                    return EdgeIterator(this, curI, curJ, false);
                }
        return EdgeIterator(this, -1, (this->edgeList.end()--)->end(), true);
    }
    EdgeIterator end() {
        for(int curI = this->edgeList.size()-1; curI >= 0; curI--)
            for(auto curJ = this->edgeList[curI].begin(); curJ != this->edgeList[curI].end(); ++curJ)
                if(curJ->edge) {
                    return EdgeIterator(this, curI, curJ, false);
                }
        return EdgeIterator(this, -1, (this->edgeList.end()--)->end(), true);

    }
    class OutputEdgeIterator {
        int curI;
        typename std::list<typename GraphListForm<EdgeT>::Node>::iterator curJ;
        bool end;
        std::shared_ptr<GraphListForm> f;
    public:
        OutputEdgeIterator(std::shared_ptr<GraphListForm> f, int vIndex) {
            this->f = f;
            curI = vIndex;
            begin();
        }
        bool begin() {
            for(curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if((*curJ).edge) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }
        bool onEnd() {
            return end;
        }
        bool toend(){
            typename std::list<typename GraphListForm<EdgeT>::Node>::iterator prev_curJ;
            for(curJ = f->edgeList[curI].begin(); curJ != f->edgeList[curI].end(); ++curJ)
                if ((*curJ).edge)
                    prev_curJ=curJ;
            if (!(*prev_curJ).edge){
                end=true;
                return false;
            }
            else{
                end=false;
                curJ=prev_curJ;
                return true;
            };
        }
        bool next() {
            if(end)
                return false;
            ++curJ;
            while(curJ != f->edgeList[curI].end()) {
                if((*curJ).edge)
                    return true;
                ++curJ;
            }
            end = true;
            return true;
        }
        std::shared_ptr<EdgeT> getEdge() {
            if(end)
                throw std::runtime_error("");
            return (*curJ).edge;
        }

    };

};

template <class VertexT, class EdgeT>
class graph {
    std::vector<std::shared_ptr<VertexT>> vertexList;
    std::shared_ptr<GraphForm<EdgeT>> data;
    bool directed = false;              //Направленный граф
    bool dense = false;                 //М-граф
    int edgeCounter = 0;                //Число рёбер
public:
    graph() {
        this->data = std::make_shared<GraphListForm<EdgeT>>(false);
    }
    graph(int vertexCount, bool directed, bool dense) {
        if(dense) {
            this->data = std::make_shared<GraphMatrixForm<EdgeT>>(directed);
        } else {
            this->data = std::make_shared<GraphListForm<EdgeT>>(directed);
        }
        for(int i = 0; i < vertexCount; ++i)
            data->InsertV(i);
        for(int i = 0; i < vertexCount; ++i) {
            std::shared_ptr<VertexT> v = std::make_shared<VertexT>();
            v->setName(std::to_string(i));
            sz++;
            vertexList.push_back(v);
            data->InsertV(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;
    }
    graph(int vertexCount, int edgeCount, bool directed, bool dense) {
        if(dense) {
            this->data = std::make_shared<GraphMatrixForm<EdgeT>>(directed);
        } else {
            this->data = std::make_shared<GraphListForm<EdgeT>>(directed);
        }
        for(int i = 0; i < vertexCount; ++i)
            data->InsertV(i);
        for(int i = 0; i < vertexCount; ++i) {
            std::shared_ptr<VertexT> v = std::make_shared<VertexT>();
            v->setName(std::to_string(i));
            sz++;
            vertexList.push_back(v);
            data->InsertV(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;
        if(edgeCount <= 0) return;
        //Корректируем число рёбер, чтобы не превышало максимумы
        if(directed) {
            if(edgeCount > vertexCount * (vertexCount - 1))
                edgeCount = vertexCount * (vertexCount - 1);
            srand(time(0));
        } else {
            if(edgeCount > (vertexCount * (vertexCount - 1)) / 2)
                edgeCount = (vertexCount * (vertexCount - 1)) / 2;
        }
        //Вставляем
        int v1, v2;

        while(edgeCounter < edgeCount) {
            v1 = rand() % vertexCount;
            v2 = rand() % vertexCount;
            if(v1 == v2)
                continue;
            if(data->hasEdge(v1, v2))
                continue;

            std::shared_ptr<EdgeT> t = std::make_shared< EdgeT>(vertexList[v1], vertexList[v2]);
            data->InsertE(v1, v2, t);
            t->setWeight((rand() % 9) +1);
            if(directed == false)
                data->InsertE(v2, v1, t);
            ++edgeCounter;
        }
    }
    graph(const graph<VertexT, EdgeT> &G) : directed(G.directed), dense(G.dense) {
        data.reset();
        if(G.Dense()) {
            this->data = std::make_shared<GraphMatrixForm<EdgeT>>(G.data);
        } else {
            this->data = std::make_shared<GraphListForm<EdgeT>>(G.data);
        }
    }
    ~graph() { //деструктор
        while (vertexList.size()!=0)
            DeleteV(vertexList.size()-1);
        data.reset();
    }
    int V() { //возвращает число вершин в графе
        return vertexList.size();
    }
    int E() { //возвращает число ребер в графе
        return edgeCounter;
    }
    bool Directed() { //возвращает тип графа
        return directed;
    }
    bool Dense() { //возвращает форму представления графа
        return dense;
    }

    double K() {
        int max = vertexList.size() * (vertexList.size() - 1);
        if(!directed) {
            max /= 2;
        }
        if (max==0) {
            return -1;
        }
        else {
            return (double)edgeCounter / (double)max;
        }
    }
    void ToListGraph() {
        std::shared_ptr<GraphForm<EdgeT>> newData = std::make_shared<GraphListForm<EdgeT>>(this->directed); //Создаём структуру хранения L-графа
        for(int i = 0; i < vertexList.size(); ++i) //Создаём вершины
            newData->InsertV(i);
        for(int i = 0; i < vertexList.size(); ++i) //Переносим рёбра
            for(int j = 0; j < vertexList.size(); ++j)
                if(data->hasEdge(i, j))
                    newData->InsertE(i, j, data->getEdge(i, j));
        data.reset();
        data = std::move(newData);
        dense = false;
    }
    void ToMatrixGraph() {
        //Создаём структуру хранения М-графа
        std::shared_ptr<GraphForm<EdgeT>> newData = std::make_shared<GraphMatrixForm<EdgeT>>(directed);
        //Создаём вершины
        for(int i = 0; i < vertexList.size(); ++i)
            newData->InsertV(i);

        //Переносим рёбра
        for(int i = 0; i < vertexList.size(); ++i)
            for(int j = 0; j < vertexList.size(); ++j)
                if(data->hasEdge(i, j))
                    newData->InsertE(i, j, data->getEdge(i, j));
        data.reset();
        data = std::move(newData);
        dense = true;
    }

    // vertex point
    std::shared_ptr<VertexT> InsertV() {
        std::shared_ptr<VertexT> v = std::make_shared<VertexT>();
        if(!data->InsertV(vertexList.size()))
            throw std::runtime_error("Failed insert VertexT");
        v->setName(std::to_string(sz));
        sz++;
        vertexList.push_back(v);
        return v;
    }
    bool DeleteV(std::shared_ptr<VertexT> v) {
        int index = getIndex(v);
        edgeCounter -= data->DeleteEsFromVertex(index, directed);
        if(data->DeleteV(index)) {
            vertexList.erase(vertexList.begin() + index);
            return true;
        }
        return false;
    }
    bool DeleteV(int index) {
        edgeCounter -= data->DeleteEsFromVertex(index, directed);
        if(data->DeleteV(index)) {
            vertexList.erase(vertexList.begin() + index);
            return true;
        }
        return false;
    }

    bool DeleteV(std::string n) {
        std::shared_ptr<VertexT> v = std::make_shared<VertexT>();
        bool rez;
        try{
            v=getVertexFromName(n);
        }
        catch(const std::exception & ex){
            return false;
        }
        rez=DeleteV(v);
        return rez;
    }
    std::shared_ptr<VertexT>  getVertexFromName(std::string n){
        int i;
        for(i=0; i<vertexList.size(); i++)
            if (vertexList[i]->getName()==n)
                return vertexList[i];
        if (i==vertexList.size())
            throw std::runtime_error("No value");
    }

    // edge point
    bool InsertE(std::string v1, std::string v2){
        std::shared_ptr<VertexT> _v1 = std::make_shared<VertexT>();
        std::shared_ptr<VertexT> _v2= std::make_shared<VertexT>();
        try{
            _v1=getVertexFromName(v1);
        }
        catch(const std::exception & ex){
            return false;
        }
        try{
            _v2=getVertexFromName(v2);
        }
        catch(const std::exception & ex){
            return false;
        }
        try{
            InsertE(_v1, _v2);
        }
        catch (const std::exception & ex){
            return false;
        }
        return true;
    }
    std::shared_ptr< EdgeT> InsertE(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2) {

        std::shared_ptr<EdgeT> e = std::make_shared<EdgeT>(v1, v2);
        if(!data->InsertE(getIndex(v1), getIndex(v2), e))
            throw std::runtime_error("Cannot insert edge");
        if(!directed)
            data->InsertE(getIndex(v2), getIndex(v1), e);
        ++edgeCounter;
        return e;
    }
    bool DeleteE(std::string v1, std::string v2){
        std::shared_ptr<VertexT> _v1 = std::make_shared<VertexT>();
        std::shared_ptr<VertexT> _v2 = std::make_shared<VertexT>();
        try{
            _v1=getVertexFromName(v1);
        }
        catch(char*e){
            //cerr<<endl<<e<<endl;
            return false;
        };
        try{
            _v2=getVertexFromName(v2);
        }
        catch(char*e){
            //cerr<<endl<<e<<endl;
            return false;
        }
        if(!DeleteE(_v1, _v2)) return false;
        else return true;
    };
    bool DeleteE(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2) {
        if(data->DeleteE(getIndex(v1), getIndex(v2))) {
            --edgeCounter;
            if(directed == false)
                data->DeleteE(getIndex(v2), getIndex(v1));
            return true;
        } else
            return false;
    }



    int getIndex(std::shared_ptr<VertexT> v) {
        int index = 0;
        for(int i = 0; i < vertexList.size(); ++i) {
            if(vertexList[index] == v)
                break;
            ++index;
        }
        if(index == vertexList.size())
            throw std::runtime_error("Our of range");
        return index;
    }
    bool hasEdge(int v1, int v2) {
        if(v1 < 0 || v1 >= vertexList.size())
            return false;
        if(v2 < 0 || v2 >= vertexList.size())
            return false;
        return data->hasEdge(v1, v2);
    }
    bool hasEdge(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2) {
        try {
            getIndex(v1);
        }
        catch(const std::exception & e) {
            return false;
        }
        try {
            getIndex(v2);
        }
        catch(const std::exception & e)
        {
            return false;
        }
        return data->hasEdge(getIndex(v1), getIndex(v2));
    }
    std::shared_ptr<VertexT>  getVertex(int index) {
        if(index < 0 || index >= vertexList.size())
            throw std::runtime_error("Index out of range");
        return vertexList[index];
    }
    std::shared_ptr<EdgeT> getEdge(std::shared_ptr<VertexT> v1, std::shared_ptr<VertexT> v2) {
        std::shared_ptr<EdgeT> e = data->getEdge(getIndex(v1), getIndex(v2));
        return e;
    }
    bool write_data_edge(std::string _v1, std::string _v2, int data){
        std::shared_ptr<VertexT> v1, v2;
        try{
            v1=getVertexFromName(_v1);
        }
        catch(const std::exception & ex){
            return false;
        }
        try{
            v2=getVertexFromName(_v2);
        }
        catch(const std::exception & ex){
            return false;
        }
        try {
            std::shared_ptr<EdgeT> e = getEdge(v1, v2);
            e->setData(data);
        }
        catch (const std::exception& ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return false;
        }
        return true;
    }
    bool write_weight_edge(std::string _v1, std::string _v2, int w){
        std::shared_ptr<VertexT> v1, v2;
        try{
            v1=getVertexFromName(_v1);
        }
        catch(const std::exception & ex){
            return false;
        }
        try{
            v2=getVertexFromName(_v2);
        }
        catch(const std::exception & ex){
            return false;
        }
        try {
            std::shared_ptr<EdgeT> e =getEdge(v1, v2);
            e->setWeight(w);
        }
        catch (const std::exception& ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return false;
        }
        return true;
    }
    int read_data_edge(std::string _v1, std::string _v2){
        std::shared_ptr<EdgeT> e;
        std::shared_ptr<VertexT> v1, v2;
        try{
            v1=getVertexFromName(_v1);
            v2=getVertexFromName(_v2);
        }
        catch(const std::exception & ex){
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
        try {
            e=getEdge(v1, v2);
        }
        catch (const std::exception & ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
        try {
            if (e->isDataSet())
                return e->getData();
            else
                throw std::runtime_error("Cannot get data");
        }
        catch (const std::exception & ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
    }
    int read_weight_edge(std::string _v1, std::string _v2){
        std::shared_ptr<EdgeT> e;
        std::shared_ptr<VertexT> v1, v2;
        try{
            v1=getVertexFromName(_v1);
            v2=getVertexFromName(_v2);
            e=getEdge(v1, v2);
        }
        catch(const std::exception & ex){
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
        try {
            if (e->isWeightSet())
                return e->getWeight();
            else
                throw std::runtime_error("Cannot get data");
        }
        catch (const std::exception & ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
    }
    int read_data_vertex(std::string v1){
        std::shared_ptr<VertexT> v;
        try
        {
            v=getVertexFromName(v1);
        }
        catch(std::exception &ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
        int d;
        d=v->getData();
        try {
            if (v->dataSet!=false)
                return d;
            else
                throw std::invalid_argument ("Data not setted");
        }
        catch (std::exception &ex) {
            std::cout << "Exception: " << ex.what() << std::endl;
            return -1;
        }
    }
    bool write_data_vertex(std::string v1, int d){ //Записать данные о вершине
        std::shared_ptr<VertexT> v;
        try
        {
            v=getVertexFromName(v1);
        }
        catch(std::exception &ex){
            return false;
        }
        v->setData(d);
        return true;
    }
    bool write_name_vertex(std::string v1, std::string str){ //Записать данные о вершине
        std::shared_ptr<VertexT> v;
        try
        {
            v=getVertexFromName(v1);
        }
        catch(std::exception &ex){
            return false;
        }
        v->setName(str);
        return true;
    }


    void print_graph(){
        int i, j;
        std::shared_ptr<VertexT>  v;
        std::shared_ptr<EdgeT>  e;
        if (Dense()){
            std::cout<<"  ";
            for (i=0; i<V(); i++){
                v=getVertex(i);
                std::cout<<std::setw(4)<<v->getName();
            }
            std::cout<<std::endl;
            for(i=0; i<5*V(); i++)
                std::cout<<"_";
            std::cout<<std::endl;
            for (i=0; i<V(); i++){
                v=getVertex(i);
                std::cout<<v->getName()<<"|";
                for (j=0; j<V(); j++)
                    if (hasEdge(i,j)){
                        e=getEdge(getVertex(i),getVertex(j));
                        std::cout<<std::setw(4)<<e->getWeight();
                    }
                    else
                        std::cout<<std::setw(4)<<"0";
                std::cout<<std::endl;
            }
        }
        else
        {
            for (i=0; i<V(); i++){
                v=getVertex(i);
                std::cout<<"*"<<v->getName()<<"->";
                for (j=0; j<V(); j++){
                    v=getVertex(j);
                    if (hasEdge(i,j))
                        std::cout<<v->getName()<<"->";
                }
                std::cout<<std::endl;
            }
        }
    }
    // итератор вершин
    class VertexIterator {
        graph<VertexT, EdgeT> *g;
        bool end = true;
        int current = -1;
    public:
        VertexIterator( graph<VertexT, EdgeT> * g = nullptr, int current = -1, bool end = true) : g(g), current(current), end(end) {}
        bool onEnd() {
            return end;
        }
        std::shared_ptr<VertexT> operator*() {
            if(current >= g->vertexList.size() || current==-1 || g == nullptr)
                throw std::runtime_error("Index out of range");
            return g->vertexList[current];
        }
        bool operator++ () {
            try {
                if(end){
                    current=-1;
                    throw std::runtime_error("Index out of range");
                }
            }
            catch (const std::exception & e) {
                return false;
            }
            current++;
            if(g->vertexList.size()-1 == current)
                end = true;
            return true;
        }
        std::string read_vertex() {
            std::shared_ptr<VertexT> v;
            v=operator*();
            std::string d;
            d=v->getName();
            if (v->nameSet)
                return d;
            else
                throw std::runtime_error("Name not set");
        }
        int read_data_vertex(){
            std::shared_ptr<VertexT> v;
            try
            {
                v=operator*();
            }
            catch(const std::exception & e){
                std::cout << "Exception: " << e.what() << std::endl;
                return -1;
            };
            try {
                if (v->dataSet!=false)
                    return v->getData();
                else throw std::runtime_error("Data not set");
            }
            catch (const std::exception & e) {
                std::cout << "Exception: " << e.what() << std::endl;
                return -1;
            }
        };
    };

    VertexIterator beginV() {
        if(vertexList.size() == 0) {
            return VertexIterator(this);
        }
        return VertexIterator(this, 0, false);
    }
    VertexIterator endV() {
        if(vertexList.size() == 0) {
            return VertexIterator(this);
        }
        return VertexIterator(this, vertexList.size()-1, false);
    }


    class EdgeIterator {
        graph<VertexT, EdgeT> *g;
        std::shared_ptr<typename GraphMatrixForm<EdgeT>::EdgeIterator> mIt;
        std::shared_ptr<typename GraphListForm<EdgeT>::EdgeIterator> lIt;
        bool useM;
        bool end;

    public:
        EdgeIterator(graph<VertexT, EdgeT> * g, bool end = false) {
            this->g = g;
            if(g->Dense()) {
                if(end) {
                    mIt = std::make_shared<typename GraphMatrixForm<EdgeT>::EdgeIterator>( std::dynamic_pointer_cast<GraphMatrixForm<EdgeT>>(g->data)->end());
                    useM = true;
                } else {
                    mIt = std::make_shared<typename GraphMatrixForm<EdgeT>::EdgeIterator>( std::dynamic_pointer_cast<GraphMatrixForm<EdgeT>>(g->data)->begin());
                    useM = true;
                }
            } else {
                if(end) {
                    lIt = std::make_shared<typename GraphListForm<EdgeT>::EdgeIterator>( std::dynamic_pointer_cast<GraphListForm<EdgeT>>(g->data)->end() );
                    useM = false;
                } else {
                    lIt = std::make_shared<typename GraphListForm<EdgeT>::EdgeIterator>( std::dynamic_pointer_cast<GraphListForm<EdgeT>>(g->data)->begin() );
                    useM = false;
                }
            }
        }
        bool onEnd() {
            if(useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }
        void operator++() {
            if(useM)
                return mIt->operator++();
            else
                return lIt->operator++();
        }
        std::shared_ptr<EdgeT> operator* () {
            if(useM)
                return mIt->operator*();
            else
                return lIt->operator*();
        }
        std::string read_edge(){
            std::string str1, str2, str3;
            std::shared_ptr<EdgeT> e;
            e = operator*();
            std::shared_ptr<VertexT> _v1 = e->getVertex1(), _v2 = e->getVertex2();
            if (_v1->nameSet==false)
                str1="#data not set#";
            else
                str1=_v1->getName();
            if (_v2->nameSet==false)
                str2="#data not set#";
            else
                str2=_v2->getName();
            if (e->isWeightSet()==false)
                str3="#data not set#";
            else
                str3=std::to_string(e->getWeight());
            return "Исходная вершина: '" + str1 + "'. Входящая вершина: '" + str2 + "'. Вес ребра: '" + str3 + "'";
        }
    };
    EdgeIterator beginE () {
        return EdgeIterator(this, false);
    }
    EdgeIterator endE () {
        return EdgeIterator(this, true);
    }
    class OutputEdgeIterator {
        graph<VertexT, EdgeT> *g;
        std::shared_ptr<typename GraphMatrixForm<EdgeT>::OutputEdgeIterator> mIt;
        std::shared_ptr<typename GraphListForm<EdgeT>::OutputEdgeIterator> lIt;
        bool useM;
        int curV1, curV2;
    public:
        OutputEdgeIterator(graph<VertexT, EdgeT> * g,  std::shared_ptr<VertexT> v) {
            this->g = g;
            this->curV1 = g->getIndex(v);
            if(g->Dense()) {
                mIt = std::make_shared<typename GraphMatrixForm<EdgeT>::OutputEdgeIterator>( std::dynamic_pointer_cast<GraphMatrixForm<EdgeT>>(g->data), this->curV1);
                useM = true;
            } else {
                lIt = std::make_shared<typename GraphListForm<EdgeT>::OutputEdgeIterator>( std::dynamic_pointer_cast<GraphListForm<EdgeT>>(g->data), this->curV1 );
                useM = false;
            }
        }
        bool begin() {
            if(useM)
                return mIt->begin();
            else
                return lIt->begin();
        }
        bool end() {
            if(useM)
                return mIt->toend();
            else
                return lIt->toend();
        }
        bool onEnd() {
            if(useM)
                return mIt->onEnd();
            else
                return lIt->onEnd();
        }
        std::shared_ptr<EdgeT> operator*() {
            if (onEnd())
                throw std::runtime_error("Out of range");
            if(useM)
                return mIt->getEdge();
            else
                return lIt->getEdge();
        }
        bool operator++() {
            if(useM)
                return mIt->next();
            else
                return lIt->next();
        }
        std::string read_edge(){
            std::string str1, str2, str3;
            std::shared_ptr<EdgeT> e;
            e = operator*();
            std::shared_ptr<VertexT> _v1 = e->getVertex1(), _v2 = e->getVertex2();
            if (_v1->nameSet==false)
                str1="#data not set#";
            else
                str1=_v1->getName();
            if (_v2->nameSet==false)
                str2="#data not set#";
            else
                str2=_v2->getName();
            if (e->isWeightSet()==false)
                str3="#data not set#";
            else
                str3=std::to_string(e->getWeight());
            return "Исходная вершина: '" + str1 + "'. Входящая вершина: '" + str2 + "'. Вес ребра: '" + str3 + "'";
        }
    };

    std::shared_ptr<OutputEdgeIterator> getOutputEdgeIterator(int value) {
        return std::make_shared< OutputEdgeIterator>(this, this->getVertex(value));
    };
};

template <class VertexT, class EdgeT>
class FindShortWay {
#define INF 9999999
    std::shared_ptr<graph<VertexT, EdgeT>> g;
    std::shared_ptr<GraphForm<EdgeT>> temp;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<std::pair<int, int>>> save;
    bool ready = false;
public:
    FindShortWay(std::shared_ptr<graph<VertexT, EdgeT>> g) : g(g) { }

    void print_result() {
        if(ready) {
            for(auto way : save) {
                std::cout << "  ---------" << std::endl;
                for (auto value: way) {
                    std::cout << g->getVertex(value.first)->getName() << " " << g->getVertex(value.second)->getName()
                              << std::endl;
                }
            }
        }
    }

    bool check() {
        ready = false;
        if(!g->Directed())
            return false;
        this->temp = ToMatrix();
        this->matrix = std::vector<std::vector<int>>(g->V(), std::vector<int>(g->V(), 0) );
        for (int i=0; i < g->V(); i++){
            for (int j=0; j < g->V(); j++)
                if(i == j) {
                    matrix[i][j] = 0;
                }
                else if (temp->hasEdge(i,j)){
                    //matrix[i][j] = 1;
                    auto e = g->getEdge(g->getVertex(i),g->getVertex(j));
                    matrix[i][j] = e->getWeight();
                } else {
                    matrix[i][j] = INF;
                }
        }
        std::string value2;
        std::cout << "Insert vertex B: ";
        std::getline(std::cin >> std::ws, value2);

        FindCriticalEdge(matrix, value2);
        ready = true;
        return true;
    }
private:
    std::shared_ptr<GraphForm<EdgeT>> ToMatrix() {
        std::shared_ptr<GraphForm<EdgeT>> newData = std::make_shared<GraphMatrixForm<EdgeT>>(g->Directed());
        for (int i = 0; i < g->V(); ++i)
            newData->InsertV(i);
        for (int i = 0; i < g->V(); ++i)
            for (int j = 0; j < g->V(); ++j)
                if (g->hasEdge(i,j))
                    newData->InsertE(i, j, g->getEdge(g->getVertex(i), g->getVertex(j)));
        /*data.reset();
        data = std::move(newData);
        dense = true;*/
        return newData;
    }
    std::vector<int> dijkstra(int n, const std::vector<std::vector<int>>& adjMatrix, int src, int dest) {
        std::vector<int> dist(n, INF);
        std::vector<int> prev(n, -1);
        dist[src] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d > dist[u]) continue;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != INF) {
                    int weight = adjMatrix[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.push({dist[v], v});
                        prev[v] = u;
                    }
                }
            }
        }
        // Восстанавливаем путь от src до dest
        std::cout << "SRC=" << src << " DEST="<< dest << " DIST="<<dist[dest] << std::endl;
        if (dist[dest] != INF) {
            int cur = dest;
            std::vector<std::pair<int, int>> path;
            while (prev[cur] != -1) {
                path.emplace_back(prev[cur], cur);
                cur = prev[cur];
            }
            std::reverse(path.begin(), path.end());
            save.back() = path;  // Сохраняем путь в save
        }
        return dist;
    }
    void FindCriticalEdge(std::vector<std::vector<int>>& g, std::string b) {
        save.clear();
        int v = this->g->getIndex(this->g->getVertexFromName(b));
        int n = g.size();
        for (int u = 0; u < n; ++u) {
            this->save.push_back(std::vector<std::pair<int, int>>());
            std::vector<int> dist = dijkstra(n, g, u, v);
            int originalShortestPath = dist[v];
            if (originalShortestPath == INF) {
                std::cout << "No way" << std::endl;
                this->save.pop_back();
            } else {
                std::cout << "Find way" << std::endl;
            }
        }
    }
};

template <class VertexT, class EdgeT>
class Color {
#define INF 9999999
    std::shared_ptr<graph<VertexT, EdgeT>> g;
    std::shared_ptr<GraphForm<EdgeT>> temp;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<std::pair<int, int>>> save;
    bool ready = false;
public:
    Color(std::shared_ptr<graph<VertexT, EdgeT>> g) : g(g) { }

    bool check() {
        ready = false;
        if(g->Directed())
            return false;
        this->temp = ToMatrix();
        this->matrix = std::vector<std::vector<int>>(g->V(), std::vector<int>(g->V(), 0) );
        for (int i=0; i < g->V(); i++){
            for (int j=0; j < g->V(); j++)
                if(i == j) {
                    matrix[i][j] = 0;
                }
                else if (temp->hasEdge(i,j)){
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = 0;
                }
        }
        std::vector<int> color(matrix.size(), 0);
        for (int i = 0; i<matrix.size(); i++){
            if (color[i] == 0){
                color[i] = 1;}
            for (int j = 0; j < matrix.size();j++){
                if (i == j) continue;
                if (matrix[i][j] == 1 && color[j] == 0){
                    color[j] = color[i]*-1;}
                if (matrix[i][j] == 1 && color[j] == color[i]){
                    matrix[i][j] = 0;}
            }
        }
        std::cout << "--------MATRIX--------\n";
        for(auto y : matrix) {
            for(int val : y) {
                std::cout << val << " ";
            }
            std::cout <<  std::endl;
        }
        std::cout << "--------COLORS--------\n";
        for(int val : color) {
            std::cout << val << " ";
        }
        std::cout <<  std::endl;

        ready = true;
        return true;
    }
private:
    std::shared_ptr<GraphForm<EdgeT>> ToMatrix() {
        std::shared_ptr<GraphForm<EdgeT>> newData = std::make_shared<GraphMatrixForm<EdgeT>>(g->Directed());
        for (int i = 0; i < g->V(); ++i)
            newData->InsertV(i);
        for (int i = 0; i < g->V(); ++i)
            for (int j = 0; j < g->V(); ++j)
                if (g->hasEdge(i,j))
                    newData->InsertE(i, j, g->getEdge(g->getVertex(i), g->getVertex(j)));
        /*data.reset();
        data = std::move(newData);
        dense = true;*/
        return newData;
    }
};
#endif //RGR_ME_GRAPH_HPP
