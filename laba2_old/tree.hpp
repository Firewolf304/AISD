//
// Created by firewolf304 on 19.04.24.
//

#ifndef LABA2_TREE_HPP
#define LABA2_TREE_HPP

#include <memory>
#include <functional>

/*


            20(1)
    10(0)
            30(1)


 */
static int def = 0;
template<class tk, class td>
class tree {
protected:
    class Node {
    public:
        tk item;
        td data;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        Node() = default;
        Node(const Node& node) {}
        Node(tk item, td data) : item(item), data(data) {}
        ~Node() {
            if(left != nullptr)
                left.reset();
            if(right != nullptr)
                right.reset();
        }
    };
    int length = 0;
    std::shared_ptr<Node> root = nullptr;

public:

    tree(const tree &  copy ) {}
    tree() {}
    ~tree() { if(root != nullptr) { root.reset(); } }
    bool add(const tk & key, const td & obj, int & hops = def) {
        return _add(key, obj, this->root, hops);
    }
    const std::shared_ptr<Node> & find( tk key, int & hops = def) {
        return _find(key, this->root, hops);
    }
    bool write( tk key, td obj) {
        return _write(key, obj, this->root);
    }

    int size() {
        return _size(this->root, 0);
    }
    bool clear()
    {
        return _reset(this->root);
        /*root->left.reset();
        root->right.reset();
        root.reset();*/
    }
    bool empty()  {
        if (this->_size(this->root) == 0) {
            return true;
        } else {
            return false;
        }
    }
    int getOrder(tk key) {                                                                                  // получение порядкового номера
        return _getOrder(key, this->root);
    }
    bool reset( std::shared_ptr<Node> & subtree)                                                            // удаление поддерева
    {
        return _reset(subtree);
    }
    bool reset( const tk & key, int & hops = def )                                                          // удаление ключа у поддерева с поддеревьями
    {
        return _reset(key, this->root, hops);
    }
    bool remove( const tk & key, int & hops = def )                                                          // удаление узла у поддерева
    {
        return _remove(key, hops);
    }
    void print_key()                                                                                        // рекурсивный вывод всех ключей
    {
        _print_key(this->root);
    }
    void print(int level = 0, char pose = 'N')                                                              // вывод дерева
    {
        _print(this->root, level, pose);
    }
private:
    bool _reset( std::shared_ptr<Node> & subtree )                                                          // удаление поддерева
    {
        if(subtree == nullptr)
            return false;
        subtree.reset();
        return true;
    }
    std::shared_ptr<Node> _getParent(tk key, std::shared_ptr<Node> & subtree, int & hops = def) {
        hops++;
        if(subtree->left != nullptr) {
            if(subtree->left->item == key)
                return subtree;
            auto res =  _getParent(key, subtree->left);
            if(res != nullptr) {
                return res;
            }
        }
        if(subtree->right != nullptr) {
            if(subtree->right->item == key)
                return subtree;
            auto res =  _getParent(key, subtree->right);
            if(res != nullptr) {
                return res;
            }
        }
        return nullptr;
    }
    bool _reset( const tk & key, std::shared_ptr<Node> & subtree, int & hops = def )                        // удаление поддерева по ключу
    {
        hops++;
        if(subtree->item == key) {
            subtree.reset();
            return true;
        }
        if(key < subtree->item) {
            if(subtree->left != nullptr)
                return _reset(key, subtree->left, hops);
        } else {
            if(subtree->right != nullptr)
                return _reset(key, subtree->right, hops);
        }
        return false;
    }
    bool _remove(const tk & key, int & hops = def )
    {
        try {
            //auto Root = find(key, hops);
            std::shared_ptr<Node> Root = nullptr,next, t0;
            std::function<std::shared_ptr<Node>(std::shared_ptr<Node> & )> check = [&key,&Root, &hops, &check](std::shared_ptr<Node> & subtree)->std::shared_ptr<Node> {
                hops++;
                if(subtree->left != nullptr) {
                    if(subtree->left->item == key) {
                        Root = subtree->left;
                        return subtree;
                    }
                    auto res = check(subtree->left);
                    if(res != nullptr) {
                        return res;
                    }
                }
                if(subtree->right != nullptr) {
                    if(subtree->right->item == key) {
                        Root = subtree->right;
                        return subtree;
                    }
                    auto res = check(subtree->right);
                    if(res != nullptr) {
                        return res;
                    }
                }
                if(subtree != nullptr) {
                    if(subtree->item == key) {
                        Root = subtree->right;
                        return subtree;
                    }
                }
                return nullptr;
            };
            auto pred = check(this->root);


            if(Root == nullptr) {
                return false;
            }
            if(Root->left != nullptr && Root->right != nullptr) {
                t0 = Root;
                pred = Root;
                Root =  Root->right;
                std::function<void()> reqursive = [&Root, &pred, &hops, &reqursive]()->void {
                    if(Root->left == nullptr) return;
                    pred = Root;
                    Root = Root->left;
                    hops++;
                    reqursive();
                };
                reqursive();
                t0->item = Root->item;
                t0->data = Root->data;
                next = Root->right;
            }
            else if (Root->left == NULL && Root->right == NULL) //Нет потомков у удаляемого
                next = nullptr;
            else if (Root->left == nullptr) //Нет левого потомка у удаляемого
                next = Root->right;
            else if (Root->right == nullptr) //Нет правого потомка у удаляемого
                next = Root->left;

            if(pred == nullptr) //Нет родителя у удаляемого
                root = next;
            else if(Root->item < pred->item) //Удаляемый левым потомком pred
                pred->left = next;
            else //Удаляемый правым потомком pred
                pred->right = next;
            Root->left = nullptr;
            Root->right = nullptr;
            Root.reset();
            length--;
            return true;
        } catch(std::runtime_error&) {return false;}
    }
    int _getOrder(tk key, std::shared_ptr<Node> & subtree)                                                  // рекурсивное получение последовательности ключа по поддереву
    {
        if(subtree == nullptr) {
            return 0;
        }
        if(key == subtree->item) {
            return _size(subtree) - 1 - _size(subtree->right);
        }
        if(key < subtree->item) {
            return _getOrder(key, subtree->left);
        } else {
            return _getOrder(key, subtree->left) + 1 + _getOrder(key, subtree->right);
        }
    }
    const std::shared_ptr<Node> & _find( tk key, std::shared_ptr<Node> & subtree, int & hops)               // рекурсивный поиск ключа по поддереву
    {
        hops++;
        if(subtree->item == key) {
            return subtree;
        }
        if(key < subtree->item) {
            if(subtree->left != nullptr)
                return _find(key, subtree->left, hops);
        } else {
            if(subtree->right != nullptr)
                return _find(key, subtree->right, hops);
        }
        throw std::runtime_error("No value");
    }
    bool _write( tk key, td obj, std::shared_ptr<Node> & subtree)                                           // рекурсивная запись значения в ключ
    {
        if(subtree == nullptr) {
            return false;
        }
        if(subtree->item == key) {
            subtree->data = obj;
            return true;
        }
        if(key < subtree->item) {
            if(subtree->left != nullptr)
                return _write(key, obj, subtree->left);
        } else {
            if(subtree->right != nullptr)
                return _write(key, obj, subtree->right);
        }
    }
    bool _add(const tk & key, const td & obj, std::shared_ptr<Node> & subtree, int & hops)
    {
        hops++;
        if(subtree == nullptr) {
            subtree = std::make_shared<Node>(key, obj);
            length++;
            return true;
        } else {
            if(subtree->item == key) {
                return false;
            }
        }
        if(key < subtree->item) {
            return _add(key, obj, subtree->left, hops);
        } else {
            return _add(key, obj, subtree->right, hops);
        }

    }
    int _size(std::shared_ptr<Node> & subtree, const int & lenght = 0)
    {
        if(subtree != nullptr) {
            const_cast<int &>(lenght)++;
            if(subtree->left != nullptr)
                _size(subtree->left, lenght);
            if(subtree->right != nullptr)
                _size(subtree->right, lenght);
        }
        return lenght;
    }
    void _print_key(std::shared_ptr<Node> & subtree)
    {
        if(subtree == nullptr) {
            return;
        }
        std::cout << subtree->item << std::endl;
        if(subtree->left != nullptr)
            _print_key(subtree->left);
        if(subtree->right != nullptr)
            _print_key(subtree->right);
    }
    void _print(std::shared_ptr<Node> & subtree, int level = 0, char pose = 'N')                            // рекурсивный вывод поддерева
    {
        if(subtree == nullptr) {
            return;
        }
        std::cout << std::string(level, '\t') << "(" << subtree->item << ") " << subtree->data << " " << pose << std::endl;
        ++level;
        if(subtree->left != nullptr)
            _print(subtree->left, level, 'L');
        if(subtree->right != nullptr)
            _print(subtree->right, level, 'R');
    }
    std::shared_ptr<Node> _BST_next( std::shared_ptr<Node> & subtree, int & hops = def)                     // рекурсивный алгоритм поиска следующего по ключу узла
    {
        hops++;
        if (subtree == nullptr)
            return nullptr;
        if(subtree->right != nullptr) {
            /*std::shared_ptr<Node> t = subtree->right;
            while(t->left != nullptr) {
                t = t->left;
            }
            return t;*/
            std::function<std::shared_ptr<Node>(std::shared_ptr<Node>&)> leftmost = [&](std::shared_ptr<Node> &node) -> std::shared_ptr<Node> {
                hops++;
                if (node->left == nullptr)
                    return node;
                return leftmost(node->left);
            };
            return leftmost(subtree->right);
        }
        else {
            return _parent_left(root,subtree);
        }
    }
    std::shared_ptr<Node> _parent_left( std::shared_ptr<Node> & a, std::shared_ptr<Node> & b ) noexcept     // поиск ближайшего левого родителя для заданного узла дерева
    { // ошибка
        if(a == b) {
            return nullptr;
        }
        if(b->item < a->item) {
            auto Node = _parent_left(a->left, b);
            if(Node != nullptr) {
                return Node;
            } else {
                return a;
            }
        } else {
            return _parent_left(a->right, b);
        }
    }


    std::shared_ptr<Node> _BST_prev( std::shared_ptr<Node> & subtree, int & hops = def)                     // рекурсивный алгоритм поиска предыдущего по ключу узла
    {
        hops++;
        if (subtree == nullptr)
            return nullptr;
        if(subtree->left != nullptr) {
            std::function<std::shared_ptr<Node>(std::shared_ptr<Node>&)> rightmost = [&](std::shared_ptr<Node> &node) -> std::shared_ptr<Node> {
                hops++;
                if (node->right == nullptr)
                    return node;
                return rightmost(node->right);
            };
            return rightmost(subtree->left);
        }
        else {
            return _parent_right(root,subtree);
        }
    }
    std::shared_ptr<Node> _parent_right( std::shared_ptr<Node> & a, std::shared_ptr<Node> & b ) noexcept    // поиск ближайшего правого родителя для заданного узла дерева
    {
        if(a == b) {
            return nullptr;
        }
        if(b->item > a->item) {
            auto Node = _parent_right(a->right, b);
            if(Node != nullptr) {
                return Node;
            } else {
                return a;
            }
        } else {
            return _parent_right(a->left, b);
        }
    }


    std::shared_ptr<Node> & _min(std::shared_ptr<Node> & start)                                             // рекурсивный поиск самого минимального ключа
    {
        if (start->left != nullptr) {
            return _min(start->left);
        } else {
            return start;
        }
    }
    std::shared_ptr<Node> & _max(std::shared_ptr<Node> & start)                                             // рекурсивный поиск самого максимального ключа
    {
        if (start->right != nullptr) {
            return _min(start->right);
        } else {
            return start;
        }

    }
public:
    class Iterator {
        tree<tk,td> * massive;                                                                              // указатель пренадлежности к коллекции
        std::shared_ptr<Node> current;                                                                      // указатель на текущий узел
    public:
        Iterator() = default;                                                                               // конструктор итератора как default
        Iterator( std::shared_ptr<Node> node, tree<tk,td> * tree ) : current(node), massive(tree)  {}       // конструктор итератора
        const std::shared_ptr<Node>& operator*() const                                                      // оператор доступа к данным текущего узла
        {
            if(this->current == nullptr)
                throw std::runtime_error("Index out of bands");
            return this->current;
        }
        Iterator& operator++()                                                                              // оператор преинкремент
        {
            current = massive->_BST_next(current);
            return *this;
        }
        Iterator& operator++(int)                                                                           // оператор постинкремент
        {
            current = massive->_BST_next(current);
            return *this;
        }
        friend bool operator==(Iterator& it1, const Iterator& it2)                                          // оператор равенства итератора
        {
            return *it1 == *it2;
        }
        friend bool operator!=(Iterator& it1, const Iterator& it2)                                          // оператор неравенства итератора
        {
            return *it1 != *it2;
        }
        bool is_off() const                                                                                 //проверка состояния итератора
        {
            return this->current == nullptr;
        }
        Iterator& operator--()                                                                              // оператор предекремент
        {
            current = massive->_BST_prev(current);
            return *this;
        }
        Iterator& operator--(int)                                                                           // оператор постдекремент
        {
            current = massive->_BST_prev(current);
            return *this;
        }
    };
    Iterator begin() {
        if(root== nullptr) {
            return Iterator(nullptr, this);
        }
        return Iterator(_min(this->root), this);
    }
    Iterator end() {
        if(root== nullptr) {
            return Iterator(nullptr, this);
        }
        return Iterator(_max(this->root), this);
    }
    class ReverseIterator {
        tree<tk,td> * massive;                                                                              // указатель пренадлежности к коллекции
        std::shared_ptr<Node> current;                                                                      // указатель на текущий узел
    public:
        ReverseIterator() = default;                                                                        // конструктор итератора как default
        ReverseIterator( std::shared_ptr<Node> node, tree<tk,td> * tree ) : current(node), massive(tree)  {}// конструктор итератора
        const std::shared_ptr<Node>& operator*() const                                                      // оператор доступа к данным текущего узла
        {
            if(this->current == nullptr)
                throw std::runtime_error("Index out of bands");
            return this->current;
        }
        ReverseIterator& operator++()                                                                       // оператор преинкремент
        {
            current = massive->_BST_prev(current);
            return *this;
        }
        ReverseIterator& operator++(int)                                                                    // оператор постинкремент
        {
            current = massive->_BST_prev(current);
            return *this;
        }
        friend bool operator==(ReverseIterator& it1, const ReverseIterator& it2)                            // оператор равенства итератора
        {
            return *it1 == *it2;
        }
        friend bool operator!=(ReverseIterator& it1, const ReverseIterator& it2)                            // оператор неравенства итератора
        {
            return *it1 != *it2;
        }
        bool is_off() const                                                                                 //проверка состояния итератора
        {
            return this->current == nullptr;
        }
        ReverseIterator& operator--()                                                                       // оператор предекремент
        {
            current = massive->_BST_next(current);
            return *this;
        }
        ReverseIterator& operator--(int)                                                                    // оператор постдекремент
        {
            current = massive->_BST_next(current);
            return *this;
        }
    };
    ReverseIterator rbegin() {                                                                              // получение рекурсивного начала
        if(root== nullptr) {
            return ReverseIterator(nullptr, this);
        }
        return ReverseIterator(_max(this->root), this);
    }
    ReverseIterator rend() {                                                                                // получение рекурсивного конца
        if(root== nullptr) {
            return ReverseIterator(nullptr, this);
        }
        return ReverseIterator(_min(this->root), this);
    }
};
/*template<class tk, class td>
class tree {
private:
    class Node {
    public:
        tk item;
        td data;
        Node * left = nullptr;
        Node * right = nullptr;
        Node() {}
        Node(tk item, td data) : item(item), data(data) {}
        ~Node() {
            delete left;
            delete right;
        }
    };
    int length; // длина дерева
    Node *root;


public:
    tree() {

    }
    tree(const tree &  copy ) {}
    ~tree() {
        delete root;
    }
    int size() { }
    void clear() {}
    bool empty() {}
    td& read(tk key, const int & looked) {}
    bool addRoot(const tk & key, const td & obj) {
        if(root == nullptr) {
            root = new Node();
        }
        //return *root;
    }
    bool add(tk key, td obj) {
        if(root == nullptr) {

        }
    }
    bool remove(tk key, const int & looked) {}
    void print() {}
    void walk() {}

    class Iterator {
    private:
        tree<tk, td> * ptr;
        Node * current;
    public:
        Iterator(const tree<tk, td> & ptr, Node * current) : ptr(std::move(ptr)), current(std::move(current)) {

        }
        Iterator & operator++() {}
        Iterator & operator--() {}
    };

    // service
private:
    Node & Create_Node(tk key, td data) {
        Node * node = std::allocator_traits<decltype(node->memory)>::allocate(node->memory, sizeof(Node));
        std::allocator_traits<decltype(this->memory)>::construct(node->memory, node, key, data);
    }

};*/

#endif //LABA2_TREE_HPP
