//
// Created by firewolf304 on 09.05.24.
//
#include <csignal>
#include "tree.hpp"
#ifndef LABA3_AST_TREE_HPP
#define LABA3_AST_TREE_HPP

template <class tk, class td>
class AST_tree : public tree<tk, td> {
protected:
    class Node : protected tree<tk, td>::Node {
    public:
        tk item;
        td data;
        int length = -1;
        int under_size = 0;
        int bal = 0;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        Node() : AST_tree<tk, td>::Node() {  }
        Node(const Node& node) : AST_tree<tk, td>::Node() {}
        Node(tk item, td data) : item(item), data(data) {}
        virtual ~Node() {
            if(left != nullptr)
                left.reset();
            if(right != nullptr)
                right.reset();
        }
    };
//std::shared_ptr<typename AST_tree<tk, td>::Node> root = nullptr;
private:
    int length = 0;
public:
    AST_tree(const AST_tree &  copy ) : tree<tk, td>(copy) {}
    AST_tree() : tree<tk, td>() {  }
    ~AST_tree() { this->clear(); }
    virtual std::shared_ptr<Node> & add(const tk & key, const td & obj, const bool & h = false, const bool & inserted = false, int & hops = def) {
        return _add(key, obj, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops, h, inserted);
    }
    const std::shared_ptr<typename AST_tree<tk, td>::Node> & remove(const tk & key, const bool & h = false, const bool & deleted = false, int & hops = def) {
        return _remove(key, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops, h, deleted);
    }
    void print(int level = 0, char pose = 'N')                                                              // вывод дерева
    {
        _print(reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), level, pose);
    }
    int size() {
        int size = 0;
        _size(reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), size);
        return size;
    }
    const std::shared_ptr<typename AST_tree<tk, td>::Node> & find( tk key, int & hops = def) {
        return _find(key, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops);
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> R(std::shared_ptr<typename AST_tree<tk, td>::Node> t) {
        std::shared_ptr<typename AST_tree<tk, td>::Node> x(t->left);
        t->left = x->right;
        x->right = t;
        if(x->bal == -1) {
            t->bal = 0;
            x->bal = 0;
        } else {
            t->bal = -1;
            x->bal = 1;
        }
        return x;
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> L(std::shared_ptr<typename AST_tree<tk, td>::Node> t) {
        std::shared_ptr<typename AST_tree<tk, td>::Node> x (t->right);
        t->right = x->left;
        x->left = t;
        if(x->bal == 1) {
            t->bal = 0;
            x->bal = 0;
        } else {
            t->bal = 1;
            x->bal = -1;
        }
        return x;
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> LR(std::shared_ptr<typename AST_tree<tk, td>::Node> t) {
        if (!t || !t->left) {
            return t; // Если t или его левый ребенок равен nullptr, возвращаем t
        }
        std::shared_ptr<typename AST_tree<tk, td>::Node> x(t->left);
        std::shared_ptr<typename AST_tree<tk, td>::Node> y (x->right);
        if (!y) {
            return t; // Если y равен nullptr, возвращаем t
        }
        x->right = y->left;
        y->left = x;
        t->left = y->right;
        y->right = t;
        if(y->bal == -1) {
            t->bal = 1;
            x->bal = 0;
        }
        if(y->bal == 0) {
            x->bal = 0;
            y->bal = 0;
        }
        if(y->bal == 1) {
            t->bal = 0;
            x->bal = -1;
        }
        y->bal = 0;
        return y;
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> RL(std::shared_ptr<typename AST_tree<tk, td>::Node> t) {// какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
        if (!t || !t->right) {
            return t; // Если t или его левый ребенок равен nullptr, возвращаем t
        }
        std::shared_ptr<typename AST_tree<tk, td>::Node> x(t->right);
        std::shared_ptr<typename AST_tree<tk, td>::Node> y (x->left);
        if (!y) {
            t->right = x->left;
            x->left = t;
            t->bal = 0;
            x->bal = 0;
            return x;
        }
        x->left = y->right;
        y->right = x;
        t->right = y->left;
        y->left = t;
        if(y->bal == -1) {
            t->bal = 0;
            x->bal = 1;
        }
        if(y->bal == 0) {
            t->bal = 0;
            x->bal = 0;
        }
        if(y->bal == 1) {
            t->bal = -1;
            x->bal = 0;
        }
        y->bal = 0;
        return y;
    }

    bool empty()  {
        if ( _size( reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data())) == 0 ) {
            return true;
        } else {
            return false;
        }
    }
private:
    int _size(std::shared_ptr<typename AST_tree<tk, td>::Node> & subtree, const int & lenght = 0)
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
    std::shared_ptr<typename AST_tree<tk, td>::Node> _Del(const tk & k, std::shared_ptr<typename AST_tree<tk, td>::Node> & t, std::shared_ptr<typename AST_tree<tk, td>::Node> & t0, int & hops = def, const bool & h = false) {
        hops++;
        bool hh;
        const_cast<bool &>(h) = false;
        if(t->left != nullptr) {
            t->left = _Del(k, t->left, t0, hops, hh);
            if(hh) {
                if(t->bal == -1)
                {
                    t->bal = 0;
                    const_cast<bool &>(h) = true;
                }
                else
                if(t->bal == 0)
                    t->bal = 1;
                else
                {
                    if(t->right != nullptr ? t->right->bal == 0 : false)
                        t = L(t);
                    else
                    {
                        const_cast<bool &>(h) = true;
                        if (t->right != nullptr ? t->right->bal == 1 : false)
                            t = L(t);
                        else
                            t = RL(t);
                    }
                }
            }
            return t;
        }
        else {
            /*auto data = this->find(key);
            data->item = subtree->item;
            data->data = subtree->data;
            auto x = subtree->right;
            subtree->left = nullptr;
            subtree->right = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;*/
            t0->item = t->item;
            t0->data = t->data;;
            auto x = t->right;
            this->length--;
            t.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> _remove(const tk & k, std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops = def, const bool & h = false, const bool & deleted = false ) noexcept {
        hops++;
        bool hh, del;
        if(t == nullptr) {
            const_cast<bool &>(deleted) = false;
            return nullptr;
        }
        if(k < t->item) {
            t->left = this->_remove(k, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(t->left), hops, hh, del);
            if(hh) {
                if(t->bal == -1)
                {
                    t->bal = 0;
                    const_cast<bool &>(h) = true;
                }
                else
                if(t->bal == 0)
                    t->bal = 1;
                else
                if(t->right != nullptr ? t->right->bal == 0 : false)
                    t = L(t);
                else
                {
                    //if(t->right == nullptr) {hops *= 4/6;}
                    const_cast<bool &>(h) = true;
                    if (t->right != nullptr ? t->right->bal == 1: false)
                        t = L(t);
                    else
                        t = RL(t);
                }
            }
            const_cast<bool &>(deleted) = del;
            return t;
        }
        if(k > t->item) {
            t->right = this->_remove(k, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(t->right), hops, hh, del);
            if(hh) {
                if(t->bal == 1)
                {
                    t->bal = 0;
                    const_cast<bool &>(h) = true;
                }
                else
                if(t->bal == 0)
                    t->bal = -1;
                else
                if(t->left != nullptr ? t->left->bal == 0 : false)
                    t = R(t);
                else
                {
                    //if(t->right == nullptr) {hops *= 4/6;}
                    const_cast<bool &>(h) = true;
                    if (t->left != nullptr ?  t->left->bal == -1 : false)
                        t = R(t);
                    else
                        t = LR(t);
                }
            }
            const_cast<bool &>(deleted) = del;
            return t;
        }
        const_cast<bool &>(deleted) = true;
        if((t->left == nullptr) && (t->right == nullptr)) {
            t.reset();
            this->length--;
            const_cast<bool &>(h) = true;
            return nullptr;
        }
        if(t->left == nullptr) {
            auto x = std::move(t->right);
            t.reset();
            this->length--;
            const_cast<bool &>(h) = true;
            return x;
        }
        if(t->right == nullptr) {
            auto x = std::move(t->left);
            t.reset();
            this->length--;
            const_cast<bool &>(h) = true;
            return x;
        }
        int save = hops;
        t->right = _Del(k, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(t->right), t, hops, hh);
        //hops = save;
        if(hh) {
            if(t->bal == 1)
            {
                t->bal = 0;
                const_cast<bool &>(h) = true;
            }
            else
            if(t->bal == 0)
                t->bal = -1;
            else
            {
                auto x = t->left;
                if (x->bal == 0)
                    t = R(t);
                else
                {
                    const_cast<bool &>(h) = true;
                    if (x->bal == -1)
                        t = R(t);
                    else
                        t = LR(t);
                }
            }
        }
        return t;
    }
    virtual std::shared_ptr<typename AST_tree<tk, td>::Node> & _add(const tk & k, const td & val, std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops, const bool & h = false, const bool & ins = false) noexcept {
        hops++;
        bool hh, insert;
        if(!t) {
            t = std::make_shared<typename AST_tree<tk, td>::Node>(k, val);
            const_cast<bool &>(h) = true;
            const_cast<bool &>(ins) = true;
            length++;
            return t;
        }
        const_cast<bool &>(h) = false;
        if(k == t->item) {
            const_cast<bool &>(ins) = false;
            return t;
        }
        if(k < t->item) {
            t->left = _add(k, val, t->left, hops, hh, ins);
            if(hh) {
                if (t->bal == 1)
                {
                    t->bal = 0;
                }
                else
                if(t->bal == 0)
                {
                    t->bal = -1;
                    const_cast<bool &>(h) = true;
                }
                else
                if(t->left->bal == -1)
                    t = R(t);
                else
                    t = LR(t);
            }
        }
        else {
            t->right = _add(k, val, t->right, hops, hh, ins);
            if(hh)
                //âûðîñëà ïðàâàÿ âåòâü
                if (t->bal == -1)
                    t->bal = 0;
                else
                if(t->bal == 0)
                {
                    t->bal = 1;
                    const_cast<bool &>(h) = true;
                }
                else
                if(t->right->bal == 1)
                    t = L(t);
                else
                    t = RL(t);
        }
        const_cast<bool &>(ins) = insert;
        return t;
    }
    void _print(std::shared_ptr<typename AST_tree<tk,td>::Node> & subtree, int level = 0, char pose = 'N')                            // рекурсивный вывод поддерева
    {
        /*if(subtree == nullptr) {
            return;
        }
        std::cout << std::string(level, '\t') << "(" << subtree->item << ") " << subtree->data << " " << pose << std::endl;
        ++level;
        if(subtree->left != nullptr)
            _print(subtree->left, level, 'L');
        if(subtree->right != nullptr)
            _print(subtree->right, level, 'R');
            */
        if(subtree == nullptr) {
            return;
        }
        ++level;
        if(subtree->right != nullptr)
            _print(subtree->right, level, 'R');
        std::cout << std::string(level, '\t') << subtree->item << "," << subtree->bal << std::endl;
        if(subtree->left != nullptr)
            _print(subtree->left, level, 'L');

    }
    const std::shared_ptr<typename AST_tree<tk,td>::Node> & _find( tk key, std::shared_ptr<Node> & subtree, int & hops)               // рекурсивный поиск ключа по поддереву
    {
        hops++;
        if(hops > 31000) {
            return nullptr;
        }
        if(subtree.get()->item == key) {
            return subtree;
        }
        if(key < subtree.get()->item) {
            if(subtree->left != nullptr)
                return _find(key, subtree->left, hops);
        } else {
            if(subtree.get()->right != nullptr)
                return _find(key, subtree->right, hops);
        }
        throw std::runtime_error("No value");
    }
};

#endif //LABA3_AST_TREE_HPP
