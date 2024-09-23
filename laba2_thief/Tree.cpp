#include <vector>
#include <iostream>
using namespace std;
template <class Data, class Key> class Tree
{
private:
    class Node;
    int length; //длина дерева
    Node *root;	//указатель на корень

private:
    class Node
    {
    public:
        Key key;             //ключ объекта
        Data data;           //значение объекта в элементе
        Node *left;          // указатель на левого сына
        Node *right;         //указатель на правого сына
        Node(Data d, Key k) {//конструктор с параметрами
            key = k;
            data = d;
            left = right = NULL;
        }

    };

public:
    Tree();                                              //конструктор без параметров
    Tree(const Tree<Data, Key>& anotherTree);            //конструктор копирования
    ~Tree(void);                                         //деструктор
    int size();                                          //опрос размера дерева
    void clear();                                        //очистка дерева
    bool empty();                                        //проверка дерева на пустоту
    Data& read(Key key, int& looked);                    //доступ к данным с заданным ключом
    bool add(Key key, Data obj, int& looked);            //включение данных с заданным ключом
    bool remove(Key key, int& looked);                   //удаление данных с заданным ключом
    void print();                                        //вывод структуры дерева на экран
    void walk();                                         //обход узлов дерева по схеме
    int external_path_length();                          //определение длины внешнего пути дерева  (рекурсивно)

private:
    void _copy(Node *r);                              //вспомогательная функция для копирования дерева
    void _clear(Node *r);                             //вспомогательная функция для очистки дерева
    void _show(Node *r, int level);                   //вспомогательная функция для вывода структуры
    void _count_level(Node *r, int level, int &sum);  //вспомогательная функция для определения внешнего пути
    Node* _BST_predecessor(Node *x);                  //рекурсивный алгоритм поиска предыдущего по ключу узла
    Node* _BST_successor(Node *x);                    //рекурсивный алгоритм поиска следующего по ключу узла
    Node* _max(Node *t);                              //поиск максимального по ключу узла в поддереве
    Node* _min(Node *t);                              //поиск минимального по ключу узла в поддереве
    Node* _parent_right(Node *t, Node *x);            //поиск ближайшего правого родителя для заданного узла дерева
    Node* _parent_left(Node *t, Node *x);             //поиск ближайшего левого родителя для заданного узла дерева

public:
    class Iterator
    {
    private:
        Tree *ptr;	//указатель на объект коллекции
        Node *cur;	//указатель на текущий элемент коллекции
    public:
        //конструктор
        Iterator(Tree<Data, Key> &tree) {
            ptr = &tree;
            cur = NULL;
        }

        //установка на первый
        void begin() {
            cur = ptr->root;
            if (cur != NULL)
                while (cur->left != NULL)
                    cur = cur->left;
        }

        //установка на последний
        void end() {
            cur = ptr->root;
            if (cur != NULL)
                while (cur->right != NULL)
                    cur = cur->right;
        }

        //установка на следующий
        void next() {
            cur = ptr->_BST_successor(cur);
        }

        //установка на предыдущий
        void prev() {
            cur = ptr->_BST_predecessor(cur);
        }

        //проверка состояния итератора
        bool is_off() const {
            return (cur == NULL);
        }

        //доспуп к данным текущего элемента
        Data& operator*() {
            if (cur != NULL)
                return cur->data;
            else
                throw std::runtime_error("Итератор за пределами дерева");
        }
    };

    friend class Iterator;
};

//конструктор без параметров
template<class Data, class Key>
Tree<Data, Key>::Tree(void)
{
    length = 0;
    root = NULL; //в начале дерево пусто
}

//конструктор копирования
template<class Data, class Key>
Tree<Data, Key>::Tree(const Tree<Data, Key>& anotherTree)
{
    root = NULL;
    length = 0;
    _copy(anotherTree.root);
}

//копирование дерева
template<class Data, class Key>
void Tree<Data, Key>::_copy(Node *r)
{
    if (r == NULL)
        return;
    int tmp;
    add(r->key, r->data, tmp);
    _copy(r->left);
    _copy(r->right);
}

//деструктор
template<class Data, class Key>
Tree<Data, Key>::~Tree(void)
{
    clear();
}

//опрос размера дерева
template<class Data, class Key>
int Tree<Data, Key>::size()
{
    return length;
}

//очистка дерева
template<class Data, class Key>
void Tree<Data, Key>::clear()
{
    _clear(root);
    ///looked = length;
    root = NULL;
    length = 0;
}

//очистка по обходу LtR дерева
template<class Data, class Key>
void Tree<Data, Key>::_clear(Node *r)
{
    if (r == NULL)
        return;
    _clear(r->left);
    Node *rtree = r->right;
    delete r;
    _clear(rtree);
}

//проверка дерева на пустоту
template<class Data, class Key>
bool Tree<Data, Key>::empty()
{
    return (length == 0 && root == NULL);
}

//доступ к данным с заданным ключом
template<class Data, class Key>
Data& Tree<Data, Key>::read(Key key, int& looked)
{
    looked = 0;
    Node* t = root;
    while (t != NULL && key != (t->key))	//проход по дереву до задонного ключа
    {
        if (key < (t->key))//если ключ меньше
            t = t->left;//идем влево
        else
            t = t->right;//идем влево
        looked++;
    }
    if (t == NULL)//если ключа не существует
        throw std::runtime_error("Данного ключа не существует");
    return t->data;
}

//включение данных с заданным ключом
template<class Data, class Key>
bool Tree<Data, Key>::add(Key key, Data obj, int& looked)
{
    looked = 0;
    if (root == NULL) {//добавление в начало
        root = new Node(obj, key);
        length++;
        return true;
    }

    Node *t = root, *pred = NULL;
    while (t != NULL) {
        pred = t;
        looked++;
        if (key == (t->key))//если ключи совпадают
            return false;
        if (key < (t->key))//если ключ меньше
            t = t->left;//добавляем влево
        else
            t = t->right;//иначе добавляем вправо
    }

    if (key < (pred->key))
        pred->left = new Node(obj, key);
    else
        pred->right = new Node(obj, key);
    length++;
    return true;
}

//удаление данных с заданным ключом
template<class Data, class Key>
bool Tree<Data, Key>::remove(Key key, int& looked)
{
    Node *t = root, *pred = NULL, *next = NULL, *t0 = NULL;
    looked = 1;

    while (t != NULL && t->key != key) {
        pred = t; //Запоминаем родителя удаляемого
        if (key < t->key) //если ключ меньше
            t = t->left;//идем влево
        else
            t = t->right;//идем вправо
        looked++;
    }

    if (t == NULL) //Удаляемый не найден
        return false;

    if (t->left != NULL && t->right != NULL) { //Оба потомка у удаляемого есть
        t0 = t;	//Запоминаем удаляемого
        pred = t;
        t = t->right;
        while (t->left != NULL) {
            pred = t;
            t = t->left;
            looked++;
        }
        t0->key = t->key;
        t0->data = t->data;
        next = t->right;
    }
    else //Менее двух потомков у удаляемого
    if (t->left == NULL && t->right == NULL) //Нет потомков у удаляемого
        next = NULL;
    else
    if (t->left == NULL) //Нет левого потомка у удаляемого
        next = t->right;
    else
    if (t->right == NULL) //Нет правого потомка у удаляемого
        next = t->left;

    if (pred == NULL) //Нет родителя у удаляемого
        root = next;
    else
    if (t->key < pred->key)	//Удаляемый левым потомком pred
        pred->left = next;
    else					//Удаляемый правым потомком pred
        pred->right = next;

    delete t;
    length--;
    return true;
}

//обход структуры по LtR
template <class Data, class Key>
void Tree<Data, Key>::walk()
{
    if (root == NULL)
        throw std::runtime_error("Нет данных");

    Node *it = root;
    std::vector<Node*> up(length);
    int top = 0;

    while (it != NULL) {
        while (it != NULL) {
            if (it->right != NULL)
                up[top++] = it->right;

            up[top++] = it;
            it = it->left;
        }

        it = up[--top];

        while (top != 0 && it->right == NULL) {
            cout << it->key << "->";
            it = up[--top];
        }

        cout << it->key << "->";

        if (top == 0)
            break;

        it = up[--top];
    }
    cout << endl;
}

//вспомогательная функция для вывода структуры
template <class Data, class Key>
void Tree<Data, Key>::_show(typename Tree<Data, Key>::Node *r, int level)
{
    if (r == NULL)
        return;
    _show(r->right, level + 1);
    for (int i = 0; i <= 2 * level; i++)
        cout << " ";
    cout << r->key << endl;
    _show(r->left, level + 1);
}

//вывод структуры дерева на экран
template<class Data, class Key>
void Tree<Data, Key>::print()
{
    if (root == NULL) {
        return;
    }
    _show(root, 0);
}


//определение длины внешнего пути дерева
template<class Data, class Key>
int Tree<Data, Key>::external_path_length()
{
    if (root == NULL)
        return -1;
    int sum = 0;
    _count_level(root, 1, sum);
    return sum;
}

//вспомогательная функция для определения внешнего пути
template <class Data, class Key>
void Tree<Data, Key>::_count_level(Node *r, int level, int &sum)
{
    if (r == NULL)
        return;
    _count_level(r->left, level + 1, sum);
    _count_level(r->right, level + 1, sum);
    if (r->right == NULL || r->left == NULL)
        sum += level;
}

template <class Data, class Key> typename Tree<Data, Key>::Node* Tree<Data, Key>::_BST_successor(typename Tree<Data, Key>::Node *x)
{
    if (x == NULL)
        return NULL;
    if (x->right != NULL)
    {
        Node* t = x->right;
        while (t->left != NULL)
            t = t->left;
        return t;
    }
    else
        return _parent_left(root, x);
}

template <class Data, class Key> typename Tree<Data, Key>::Node* Tree<Data, Key>::_parent_left(typename Tree<Data, Key>::Node *t, typename Tree<Data, Key>::Node *x) {
    if (t == x)
        return NULL;
    if (x->key < t->key) {
        Node *rp = _parent_left(t->left, x);
        if (rp != NULL)
            return rp;
        else
            return t;
    }
    else
        return _parent_left(t->right, x);
}

template <class Data, class Key> typename Tree<Data, Key>::Node* Tree<Data, Key>::_BST_predecessor(typename Tree<Data, Key>::Node *x) {
    if (x == NULL)
        return NULL;
    if (x->left != NULL)
    {
        Node* t = x->left;
        while (t->right != NULL)
            t = t->right;
        return t;
    }
    else
        return _parent_right(root, x);
}

template <class Data, class Key> typename Tree<Data, Key>::Node* Tree<Data, Key>::_parent_right(typename Tree<Data, Key>::Node *t, typename Tree<Data, Key>::Node *x) {
    if (t == x)
        return NULL;
    if (x->key > t->key) {
        Node *rp = _parent_right(t->right, x);
        if (rp != NULL)
            return rp;
        else
            return t;
    }
    else
        return _parent_right(t->left, x);
}
