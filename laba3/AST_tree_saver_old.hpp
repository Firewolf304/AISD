//
// Created by firewolf304 on 09.05.24.
//
#include "tree_save.hpp"
#ifndef LABA3_AST_TREE_HPP
#define LABA3_AST_TREE_HPP

template <class tk, class td>
class AST_tree : private tree<tk, td> {
    class Node {
    public:
        tk item;
        td data;
        int bal = 0;
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

private:
    std::shared_ptr<Node> root = nullptr;
    int length = 0;
public:
    AST_tree(const AST_tree_saver &  copy ) : tree<tk, td>(copy) {}
    AST_tree() : tree<tk, td>() {  }
    ~AST_tree() { this->clear(); }
    std::shared_ptr<Node> & add(const tk & key, const td & obj, const bool & h = false, const bool & inserted = false, int & hops = def) {
        return _add(key, obj, this->root, hops, h, inserted);
    }
    const std::shared_ptr<Node> & remove(const tk & key, const bool & h = false, const bool & deleted = false, int & hops = def) {
        return _remove(key, this->root, hops, h, deleted);
    }
    const std::shared_ptr<Node> & find( tk key, int & hops = def) {
        return _find(key, this->root, hops);
    }
    bool write( tk key, td obj) {
        return _write(key, obj, this->root);
    }
    std::shared_ptr<Node> & data() {
        return this->root;
    }
    int size() {
        return _size(this->root, 0);
    }
    bool empty()  {
        if (this->_size(this->root) == 0) {
            return true;
        } else {
            return false;
        }
    }
    int getOrder(tk key) {                                                                                  // получение порядкового номера
        auto value = _getOrder(key, this->root);
        if(value > size()) {
            return -1;
        }
        return value;
    }
    bool reset( std::shared_ptr<Node> & subtree)                                                            // удаление поддерева
    {
        return _reset(subtree);
    }
    bool reset( const tk & key, int & hops = def )                                                          // удаление ключа у поддерева с поддеревьями
    {
        return _reset(key, this->root, hops);
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
    const std::shared_ptr<Node> & _Del(const tk & key, std::shared_ptr<Node> & subtree, int & hops = def, const bool & h = false) {
        hops++;
        const_cast<bool &>(h) = false;
        if(subtree->left != nullptr) {
            bool hh = false;
            subtree->left = this->_Del(key, subtree->left, hops, hh);
            if(hh) {
                if(subtree->bal == -1) {
                    subtree->bal = 0;
                    const_cast<bool &>(h) = true;
                } else if(subtree->bal == 0) {
                    subtree->bal = 1;
                } else if(subtree->right->bal == 0) {
                    subtree = L(subtree);
                } else {
                    const_cast<bool &>(h) = true;
                    if(subtree->right->bal == 1) {
                        subtree = L(subtree);
                    } else {
                        subtree = RL(subtree);
                    }
                }
            }
            return subtree;
        } else {
            auto data = this->find(key);
            data->item = subtree->item;
            data->data = subtree->data;
            auto x = subtree->right;
            subtree->left = nullptr;
            subtree->right = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
    }
    const std::shared_ptr<Node> & _remove(const tk & key, std::shared_ptr<Node> & subtree, int & hops = def, const bool & h = false, const bool & deleted = false ) {
        hops++;
        const_cast<bool &>(h) = false;
        if(subtree == nullptr) {
            const_cast<bool &>(deleted) = false;
            return nullptr;
        }
        if(key < subtree->item) {
            bool hh = false;
            subtree->left = this->_remove(key, subtree->left, hops, hh, deleted);
            if(hh) {
                if(subtree->bal == -1) {
                    subtree->bal = 0;
                    const_cast<bool &>(h) = true;
                } else if(subtree->bal == 0) {
                    subtree->bal = 1;
                } else if(subtree->right->bal == 0) {
                    subtree = L(subtree);
                } else {
                    const_cast<bool &>(h) = true;
                    if(subtree->right->bal == 1) {
                        // какой-то L
                        subtree = L(subtree);
                    } else {
                        // какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
                        subtree = RL(subtree);
                    }
                }
            }
            return subtree;
        }
        if(key > subtree->item) {
            bool hh = false;
            subtree->right = this->_remove(key, subtree->right, hops, hh, deleted);
            if(hh == true) {
                if(subtree->bal == -1) {
                    subtree->bal = 0;
                    const_cast<bool &>(h) = true;
                } else if(subtree->bal == 0) {
                    subtree->bal = 1;
                } else if(subtree->left->bal == 0) {
                    subtree = L(subtree);
                } else {
                    const_cast<bool &>(h) = true;
                    if(subtree->left->bal == 1) {
                        // какой-то L
                        subtree = L(subtree);
                    } else {
                        // какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
                        subtree = RL(subtree);
                    }
                }
            }
            return subtree;
        }
        const_cast<bool &>(deleted) = true;
        if(subtree->left == nullptr && subtree->right == nullptr ) {
            subtree.reset();
            const_cast<bool &>(h) = true;
            return nullptr;
        }
        if(subtree->left == nullptr) {
            auto x = subtree->left;
            subtree->left = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
        if(subtree->right == nullptr) {
            auto x = subtree->right;
            subtree->right = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
        bool hh = false;
        subtree->right = _Del(key, subtree->right, hops, hh);
        if(hh = true) {
            if(subtree->bal == 1) {
                subtree->bal = 0;
                const_cast<bool &>(h) = true;
            } else if(subtree->bal == 0) {
                subtree->bal = -1;
            } else {
                auto x = subtree->left;
                if(x->bal == 0) {
                    subtree = R(subtree);
                } else {
                    const_cast<bool &>(h) = true;
                    if(x->bal == -1) {
                        subtree = R(subtree);
                    } else {
                        subtree = LR(subtree);
                    }
                }
            }
        }
        return subtree;
    }
    std::shared_ptr<Node> & _add(const tk & key, const td & obj, std::shared_ptr<Node> & subtree, int & hops, const bool & h = false, const bool & inserted = false)
    {
        hops++;
        if(subtree == nullptr) {
            subtree = std::make_shared<Node>(key, obj);
            const_cast<bool &>(h) = true;
            const_cast<bool &>(inserted) = true;
            length++;
            return subtree;
        } else {
            const_cast<bool &>(h) = false;
            if(subtree->item == key) {
                const_cast<bool &>(inserted) = false;
                return subtree;
            }
        }

        if(key < subtree->item) {
            bool hh = false;
            subtree->left = this->_add(key, obj, subtree->left, hops, hh, inserted);
            if(hh) {
                if(subtree->bal == 1) {
                    subtree->bal = 0;
                } else {
                    if(subtree->bal == 0) {
                        subtree->bal = -1;
                        const_cast<bool &>(h) = true;
                    } else {
                        if (subtree->left->bal == -1) {
                            // какой-то L(t)
                            subtree = R(subtree);
                            // = x;
                        } else {
                            // какой-то LR(t)
                            subtree = LR(subtree);
                        }
                    }
                }
            }
        } else {
            bool hh = false;
            subtree->right = this->_add(key, obj, subtree->right, hops, hh, inserted);
            if(hh) {
                if(subtree->bal == -1) {
                    subtree->bal = 0;
                } else {
                    if(subtree->bal == 0) {
                        subtree->bal = 1;
                        const_cast<bool &>(h) = true;
                    } else {
                        if (subtree->right->bal == 1) {
                            // какой-то L(t)
                            subtree = L(subtree);
                            // = x;
                        } else {
                            // какой-то LR(t)
                            subtree = RL(subtree);
                        }
                    }
                }
            }
        }
        return subtree;
    }
    std::shared_ptr<Node> R(std::shared_ptr<Node> t) {
        auto x = t->left;
        t->left = x->right;
        x->right = t;
        if(x->bal == 1) {
            t->bal = 0;
            x->bal = 1;
        } else {
            t->bal = 1;
            x->bal = -1;
        }
        return x;
    }
    std::shared_ptr<Node> L(std::shared_ptr<Node> t) {
        auto x = t->right;
        t->right = x->left;
        x->left = t;
        if(x->bal == 1) {
            x->bal = 0;
            t->bal = 1;
        } else {
            x->bal = 1;
            t->bal = -1;
        }
        return x;
    }
    std::shared_ptr<Node> LR(std::shared_ptr<Node> t) {
        auto x = t->left;
        auto y = x->right;
        t->left = x->right;
        x->right = t;
        if(x->bal == 1) {
            t->bal = 0;
            x->bal = 1;
        } else {
            t->bal = 1;
            x->bal = -1;
        }
        return x;
    }
    std::shared_ptr<Node> RL(std::shared_ptr<Node> t) {// какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
        auto x = t->right;
        auto y = x->left;
        t->right = x->left;
        x->left = t;
        if(y->bal == 1) {
            x->bal = 0;
            t->bal = 1;
        } else {
            x->bal = 1;
            y->bal = -1;
        }
        return y;
    }
};

#endif //LABA3_AST_TREE_HPP
