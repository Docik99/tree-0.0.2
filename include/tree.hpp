#include <iostream>
using namespace std;

template <typename T>
class tree_t
{
private:
    struct node_t {
        node_t * left;
        node_t * right;
        T value;

        node_t() {
            left = nullptr;
            right = nullptr;
            value = 0;
        }
        ~node_t() {
            delete left;
            delete right;
        }

        void add(T new_value) {
            if (value > new_value) {
                if (left == nullptr) {
                    left = new node_t();
                    left->value = new_value;
                }
                else left->add(new_value);
            }
            else if (value < new_value) {
                if (right == nullptr){
                    right = new node_t;
                    right->value = new_value;
                }
                else right->add(new_value);
            }
        }

        void print_t(ostream & stream, int range) const {
            if (right != nullptr) right->print_t(stream, range + 4);
            for (int i = 0; i < range + 4; i++) stream << '-';
            stream << value << '\n';
            if (left != nullptr) left->print_t(stream, range + 4);
        }

        bool find_t(T new_value) const {
            if (value == new_value) return true;
            else if (value < new_value) {
                if (right != nullptr) return right->find_t(new_value);
                else return false;
            }
            else if (value > new_value) {
                if (left != nullptr) return left->find_t(new_value);
                else return false;
            }
            else return false;
        }
    };
private:
    node_t * root_;
public:

    tree_t() {
        root_ = nullptr;
    }

    tree_t(initializer_list<T> k) {
        root_ = nullptr;
        for (T value : k) insert(value);
    }

    ~tree_t() {
        delete root_;
    }

    void insert(T value) {
        if (root_ == nullptr) {
            root_ = new node_t;
            root_->value = value;
        }
        else root_->add(value);
    }

    auto operator == (tree_t<T> const & other) {
        return comp(root_, other.root_);
    }


    bool comp(node_t *f_tree, node_t *s_tree) {
        if (f_tree == nullptr && s_tree == nullptr) return true;
        else if (f_tree != nullptr && s_tree != nullptr) {
            if (f_tree->value != s_tree->value) return false;
            else return ( comp(f_tree->left, s_tree->left) && comp(f_tree->right, s_tree->right) );
        }
        else return false;
    }

    bool remove(T new_value){
        if (root_ != nullptr && root_->find_t(new_value)){
            node_t * first = root_;
            node_t * second = nullptr;

            while (true) { // ищем элемент который нужно удалить
                if (first->value == new_value) break;
                else if (new_value > first->value && first->right != nullptr) {
                    second = first;
                    first = first->right;
                }
                else if (new_value < first->value && first->left != nullptr) {
                    second = first;
                    first = first->left;
                }
                else return false;
            }

            node_t * data = first;
            if (first->right != nullptr) { //если есть правое занчение
                second = first->right;
                if (second->left == nullptr) { // но нет левого у правого
                    data->value = second->value;
                    first->right = second->right;
                }
                else { // если есть левое у правого
                    first = first->right;
                    second = second->left;
                    while (second->left != nullptr) {
                        first = first->left;
                        second = second->left;
                    }
                    data->value = second->value;
                    if (second->right != nullptr) { // если у крайнего левого есть правые ответвления
                        first->left = second->right;
                        second->right = nullptr;
                        * second = nullptr;
                        delete second;
                    }
                    else {
                        first->left = nullptr;
                        delete second;
                    }
                }
            }
            else if (first->left != nullptr) { // если нет правого но есть левое.
                if (root_ != first) {
                    if (second->right == nullptr) second->left = first->left;
                    else second->right = first->left;
                }
                else root_ = root_->left;
            }
            else { // если нет ни того ни другого
                if (second->right == first) second->right = nullptr;
                else if (second->left == first) second->left = nullptr;
            }

            return true;
        }
        else return false;
    }

    bool find(T value) const {
        if (root_ != nullptr) return root_->find_t(value);
        else return false;
    }

    void print(ostream & stream) const {
        if (root_ != nullptr) {
            root_->print_t(stream, 0);
        }
        else stream << "Tree is empty\n";
    }
};
