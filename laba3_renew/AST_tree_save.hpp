//
// Created by firewolf304 on 09.05.24.
//
#include <csignal>
#include "tree.hpp"
#ifndef LABA3_AST_TREE_HPP
#define LABA3_AST_TREE_HPP

template <class tk, class td>
class AST_tree : public tree<tk, td> {

private:
    int length = 0;
public:
    AST_tree(const AST_tree &  copy ) : tree<tk, td>(copy) {}
    AST_tree() : tree<tk, td>() {  }
    ~AST_tree() { this->clear(); }
    std::shared_ptr<typename tree<tk, td>::Node> & add(const tk & key, const td & obj, const bool & h = false, const bool & inserted = false, int & hops = def) {
        return _add(key, obj, this->data(), hops, h, inserted);
    }
    const std::shared_ptr<typename tree<tk, td>::Node> & remove(const tk & key, const bool & h = false, const bool & deleted = false, int & hops = def) {
        return _remove(key, this->data(), hops, h, deleted);
    }
    std::shared_ptr<typename tree<tk, td>::Node> R(std::shared_ptr<typename tree<tk, td>::Node> t) {
        /*auto x = t->left;
        t->left = x->right;
        x->right = t;
        if(x->bal == 0) {
            t->bal = 1;
            x->bal = -1;
        } else {
            t->bal = 0;
            x->bal = 0;
        }*/
        std::shared_ptr<typename tree<tk, td>::Node> x (t->left);
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
    std::shared_ptr<typename tree<tk, td>::Node> L(std::shared_ptr<typename tree<tk, td>::Node> t) {
        /*auto x = t->right;
        t->right = x->left;
        x->left = t;
        if(x->bal == 0) {
            t->bal = -1;
            x->bal = 1;
        } else {
            x->bal = 0;
            t->bal = 0;
        }*/
        std::shared_ptr<typename tree<tk, td>::Node> x (t->right);
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
    std::shared_ptr<typename tree<tk, td>::Node> LR(std::shared_ptr<typename tree<tk, td>::Node> t) {
        /*auto y = t->right;
        auto x = y->left;
        y->left = x->right;
        x->right = y;
        t->right = x->left;
        x->left = t;
        if(x->bal == -1) {
            t->bal = 0;
            y->bal = 1;
        }
        if(x->bal == 0) {
            t->bal = y->bal = 0;
        }
        if(x->bal == 1) {
            t->bal = -1;
            y->bal = 0;
        }
        x->bal = 0;*/
        /*auto x = t->left;
        auto y = x->right;
        if(x == nullptr || y == nullptr) { std::cout << "ErrorLR" << std::endl;return t;}
        x->right = y->left;
        y->left = x;
        t->left = y->right;
        y->right = t;
        if(y->bal == 1) {
            t->bal = 1;
            x->bal = 0;
        }
        if(y->bal == 0) {
            t->bal = x->bal = 0;
        }
        if(y->bal == -1) {
            t->bal = 0;
            x->bal = -1;
        }
        y->bal = 0;
        return y;*/
        /*auto y = x->left;
        if(y == nullptr) return x;
        auto z = y->right;
        if(z == nullptr) return x;
        y->right = z->left;
        z->left = y;
        x->left = z->right;
        z->right = x;
        if(z->bal == -1) {
            x->bal = 1;
            y->bal = 0;
        }
        if(z->bal == 0) {
            x->bal = y->bal = 0;
        }
        if(z->bal == 1) {
            x->bal = 0;
            y->bal = -1;
        }
        z->bal = 0;
        return z;*/

        std::shared_ptr<typename tree<tk, td>::Node> x(t->left);
        std::shared_ptr<typename tree<tk, td>::Node> y (x->right);
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
    std::shared_ptr<typename tree<tk, td>::Node> RL(std::shared_ptr<typename tree<tk, td>::Node> t) {// какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
        /*auto x = t->right;
        auto y = x->left;
        y->left = x->right;
        x->right = y;
        t->right = x->left;
        x->left = t;
        if(x->bal == -1) {
            t->bal = 0;
            y->bal = 1;
        }
        if(x->bal == 0) {
            t->bal = y->bal = 0;
        }
        if(x->bal == 1) {
            t->bal = -1;
            y->bal = 0;
        }
        x->bal = 0;*/
        /*auto x = t->right;
        auto y = x->left;
        if(x == nullptr || y == nullptr) { std::cout << "ErrorRL" << std::endl; return t;}
        x->left = y->right;
        x->right = y;
        t->right = x->left;
        x->left = t;
        if(x->bal == 1) {
            t->bal = -1;
            y->bal = 0;
        }
        if(x->bal == 0) {
            t->bal = y->bal = 0;
        }
        if(x->bal == -1) {
            t->bal = 0;
            y->bal = 1;
        }
        x->bal = 0;*/
        std::shared_ptr<typename tree<tk, td>::Node> x (t->right);
        std::shared_ptr<typename tree<tk, td>::Node> y (x->left);
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
        if ( _size( this->data()) == 0 ) {
            return true;
        } else {
            return false;
        }
    }
private:
    int _size(std::shared_ptr<typename tree<tk, td>::Node> & subtree, const int & lenght = 0)
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
    std::shared_ptr<typename tree<tk, td>::Node> _Del(const tk & k, std::shared_ptr<typename tree<tk, td>::Node> & t, std::shared_ptr<typename tree<tk, td>::Node> & t0, int & hops = def, const bool & h = false) {
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
                    if(t->right->bal == 0)
                        t = L(t);
                    else
                    {
                        const_cast<bool &>(h) = true;
                        if (t->right->bal == 1)
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
    /*std::shared_ptr<typename tree<tk, td>::Node> _Del(const tk & key, std::shared_ptr<typename tree<tk, td>::Node> & subtree, int & hops = def, const bool & h = false) {
        hops++;
        const_cast<bool &>(h) = false;
        if(subtree->left != nullptr) {
            bool hh = false;
            subtree->left = this->_Del(key, subtree->left, hops, hh);
            if(hh) {
                if(subtree->bal == -1) {
                    subtree->bal = 0;
                    const_cast<bool &>(h) = true;
                } else {
                    if (subtree->bal == 0) {
                        subtree->bal = 1;
                    } else {
                        if (subtree->right->bal == 0) {
                            subtree = L(subtree);
                        } else {
                            const_cast<bool &>(h) = true;
                            if (subtree->right->bal == 1) {
                                subtree = L(subtree);
                            } else {
                                subtree = RL(subtree);
                            }
                        }
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
    }*/

    //
    std::shared_ptr<typename tree<tk, td>::Node> _remove(const tk & k, std::shared_ptr<typename tree<tk, td>::Node> & t, int & hops = def, const bool & h = false, const bool & deleted = false ) noexcept {
        hops++;
        bool hh, del;
        if(t == nullptr) {
            const_cast<bool &>(deleted) = false;
            return nullptr;
        }
        if(k < t->item) {
            t->left = this->_remove(k, t->left, hops, hh, del);
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
                if(t->right->bal == 0)
                    t = L(t);
                else
                {
                    const_cast<bool &>(h) = true;
                    if (t->right->bal == 1)
                        t = L(t);
                    else
                        t = RL(t);
                }
            }
            const_cast<bool &>(deleted) = del;
            return t;
        }
        if(k > t->item) {
            t->right = this->_remove(k, t->right, hops, hh, del);
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
                if(t->left->bal == 0)
                    t = R(t);
                else
                {
                    const_cast<bool &>(h) = true;
                    if (t->left->bal == -1)
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
        t->right = _Del(k, t->right, t, hops, hh);
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
    /*std::shared_ptr<typename tree<tk, td>::Node> _remove(const tk & key, std::shared_ptr<typename tree<tk, td>::Node> & subtree, int & hops = def, const bool & h = false, const bool & deleted = false ) noexcept {
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
                } else {
                    if (subtree->bal == 0) {
                        subtree->bal = 1;
                    } else {
                        if (subtree->right->bal == 0) {
                            subtree = L(subtree);
                        } else {
                            const_cast<bool &>(h) = true;
                            if (subtree->right->bal == 1) {
                                // какой-то L
                                subtree = L(subtree);
                            } else {
                                // какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
                                subtree = RL(subtree);
                            }
                        }
                    }
                }
            }
            return subtree;
        }
        if(key > subtree->item) {
            bool hh = false;
            subtree->right = this->_remove(key, subtree->right, hops, hh, deleted);
            if(hh) {
                if(subtree->bal == 1) {
                    subtree->bal = 0;
                    const_cast<bool &>(h) = true;
                } else {
                    if (subtree->bal == 0) {
                        subtree->bal = -1;
                    } else {
                        if (subtree->left->bal == 0) {
                            subtree = R(subtree);
                        } else {
                            const_cast<bool &>(h) = true;
                            if (subtree->left->bal == -1) {
                                // какой-то L
                                subtree = R(subtree);
                            } else {
                                // какой-то RL (неизвестно точно алгоритм, взят как противоположность LR)
                                subtree = LR(subtree);
                            }
                        }
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
            auto x = std::move( subtree->right );
            subtree->left = nullptr;
            subtree->right = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
        if(subtree->right == nullptr) {
            auto x = std::move( subtree->left );
            subtree->left = nullptr;
            subtree->right = nullptr;
            subtree.reset();
            const_cast<bool &>(h) = true;
            return x;
        }
        bool hh = false;
        subtree->right = this->_Del(key, subtree->right, hops, hh);
        if(hh) {
            if(subtree->bal == 1) {
                subtree->bal = 0;
                const_cast<bool &>(h) = true;
            } else {
                if (subtree->bal == 0) {
                    subtree->bal = -1;
                } else {
                    auto x = subtree->left;
                    if (x->bal == 0) {
                        subtree = R(subtree);
                    } else {
                        const_cast<bool &>(h) = true;
                        if (x->bal == -1) {
                            subtree = R(subtree);
                        } else {
                            subtree = LR(subtree);
                        }
                    }
                }
            }
        }
        return subtree;
    }*/
    /*std::shared_ptr<typename tree<tk, td>::Node> & _add(const tk & key, const td & obj, std::shared_ptr<typename tree<tk, td>::Node> & subtree, int & hops, const bool & h = false, const bool & inserted = false) noexcept
    {
        hops++;
        if(!subtree) {
            subtree = std::make_shared<typename tree<tk, td>::Node>(key, obj);
            const_cast<bool &>(h) = true;
            const_cast<bool &>(inserted) = true;
            length++;
            return subtree;
        } else {
            const_cast<bool &>(h) = false;
            if(subtree.get()->item == key) {
                const_cast<bool &>(inserted) = false;
                return subtree;
            }
        }
        if(key < subtree.get()->item) {
            bool hh = false;
            subtree->left = this->_add(key, obj, subtree->left, hops, hh, inserted);
            if(hh) {
                if(subtree->bal == 1) subtree->bal = 0;
                else {
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
            const std::shared_ptr<typename tree<tk, td>::Node> & send = std::move(subtree);
            subtree->right = this->_add(key, obj, send->right, hops, hh, inserted);
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
    }*/

    //
    std::shared_ptr<typename tree<tk, td>::Node> & _add(const tk & k, const td & val, std::shared_ptr<typename tree<tk, td>::Node> & t, int & hops, const bool & h = false, const bool & ins = false) noexcept {
        hops++;
        bool hh, insert;
        if(!t) {
            t = std::make_shared<typename tree<tk, td>::Node>(k, val);
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
};

#endif //LABA3_AST_TREE_HPP
