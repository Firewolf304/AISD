//
// Created by firewolf304 on 09.05.24.
//
#include <csignal>
#include "tree.hpp"
#ifndef LABA3_AST_TREE_HPP
#define LABA3_AST_TREE_HPP

enum colors {RED = 1, BLACK = -1};

template <class tk, class td>
class AST_tree : public tree<tk, td> {
protected:
    class Node : protected tree<tk, td>::Node {
    public:
        tk item;
        td data;
        int length = -1;
        int under_size = 0;
        int key;
        std::shared_ptr<Node> parent = nullptr;
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        colors color;
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
    const std::shared_ptr<Node> & add(const tk & key, const td & obj, const bool & inserted = false, int & hops = def) {
        return _add(key, obj, nullptr,reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops, inserted);
    }
    const std::shared_ptr<typename AST_tree<tk, td>::Node> & remove(const tk & key, const bool & h = false, const bool & deleted = false, int & hops = def) {
        return _remove(key, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops, h, deleted);
    }
    void print(int level = 0)                                                              // вывод дерева
    {
        _print(reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), level);
    }
    int size() {
        int size = 0;
        _size(reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), size);
        return size;
    }
    const std::shared_ptr<typename AST_tree<tk, td>::Node> & find( tk key, int & hops = def) {
        return _find(key, reinterpret_cast<std::shared_ptr<AST_tree<int, int>::Node> &>(this->data()), hops);
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
    std::shared_ptr<typename AST_tree<tk, td>::Node> _grandparent(std::shared_ptr<typename AST_tree<tk, td>::Node> & n) {
        if((n != nullptr) && (n->parent != nullptr)) {
            return n->parent->parent;
        }
        return nullptr;
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> _uncle(std::shared_ptr<typename AST_tree<tk, td>::Node> & n) {
        auto g = _grandparent(n);
        if(g == nullptr)
            return nullptr;
        if(n->parent == g->left)
            return g->right;
        else
            return g->left;
    }
    std::shared_ptr<typename AST_tree<tk, td>::Node> _remove(const tk & k, std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops = def, const bool & h = false, const bool & deleted = false ) noexcept {

    }
    void _rotate_left(std::shared_ptr<typename AST_tree<tk, td>::Node> & t) {
        auto pivot = t->right;
        pivot->parent = t->parent;

        if(t->parent != nullptr) {
            if(t->parent->left==t) {
                t->parent->left = pivot;
            } else {
                t->parent->right = pivot;
            }
        }
        t->right = pivot->left;
        if(pivot->left != nullptr)
            pivot->left->parent = t;
        t->parent = pivot;
        pivot->left = t;
    }
    void _rotate_right(std::shared_ptr<typename AST_tree<tk, td>::Node> & t) {
        auto pivot = t->left;
        pivot->parent = t->parent;
        if(t->parent != nullptr) {
            if(t->parent->left == t) {
                t->parent->left = pivot;
            } else {
                t->parent->right = pivot;
            }
        }
        t->left = pivot->right;
        if(pivot->right != nullptr) {
            pivot->right->parent = t;
        }
        t->parent = pivot;
        pivot->right = t;
    }

    const std::shared_ptr<typename AST_tree<tk, td>::Node> & _add(const tk & k, const td & val, const std::shared_ptr<typename AST_tree<tk, td>::Node> & parent, std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops, const bool & inserted) noexcept {
        hops++;
        if(t == nullptr) {
            t = std::make_shared<Node>(k, val);
            t->item = k;
            t->data = val;
            t->parent = parent;
            t->color = BLACK;
            const_cast<bool &>(inserted) = true;
            _add_1(t, hops);
            return t;
        } else {
            if(t->item == k) {
                const_cast<bool &>(inserted) = false;
                return nullptr;
            }
            t->under_size++;
        }
        //const_cast<int &>(size)++;
        if(k < t->item) {
            return _add(k, val, t, t->left, hops, inserted);
        } else {
            return _add(k, val, t,t->right, hops, inserted);
        }
    }
    void _add_1(std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops) noexcept {
        hops++;
        if(t->parent == nullptr)
            t->color = BLACK;
        else
            _add_2(t, hops);
    }
    void _add_2(std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops) noexcept {
        hops++;
        if(t->parent->color == BLACK)
            return;
        else
            _add_3(t, hops);
    }
    void _add_3(std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops) noexcept {
        hops++;
        auto u = _uncle(t);
        std::shared_ptr<AST_tree<tk, td>::Node> g;
        if((u != nullptr) && (u->color == RED) ) {
            t->parent->color = BLACK;
            u->color = BLACK;
            g = _grandparent(t);
            g->color = RED;
            _add_1(g, hops);
        } else {
            _add_4(t, hops);
        }
    }
    void _add_4(std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops) noexcept {
        hops++;
        auto g = _grandparent(t);
        if((t == t->parent->right) && (t->parent == g->left)) {
            _rotate_left(t->parent);
            t = t->left;
        } else if((t == t->parent->left) && (t->parent == g->right)) {
            _rotate_right(t->parent);
            t = t->right;
        }
        _add_5(t, hops);
    }
    void _add_5(std::shared_ptr<typename AST_tree<tk, td>::Node> & t, int & hops) noexcept {
        auto g = _grandparent(t);
        t->parent->color = BLACK;
        g->color = RED;
        if((t == t->parent->left) && (t->parent == g->left) ) {
            _rotate_right(g);
        } else {
            _rotate_left(g);
        }
    }

    void _print(std::shared_ptr<typename AST_tree<tk,td>::Node> & subtree, int level = 0)                            // рекурсивный вывод поддерева
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
            _print(subtree->right, level);
        std::cout << std::string(level, '\t') << subtree->item << ",";
        if(subtree->color == BLACK)
            std::cout << "B" << std::endl;
        else if(subtree->color == RED)
            std::cout << "R" << std::endl;
        else
            std::cout << "N" << std::endl;
        if(subtree->left != nullptr)
            _print(subtree->left, level);

    }
    const std::shared_ptr<typename AST_tree<tk,td>::Node> & _find( tk key, std::shared_ptr<Node> & subtree, int & hops)               // рекурсивный поиск ключа по поддереву
    {
        hops++;
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
