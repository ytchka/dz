#include <iostream>
#include <fstream>
#include <initializer_list>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* previous;
    Node(int value) : value(value), left(nullptr), right(nullptr), previous(nullptr) {}
};

class BSTree {
private:
    Node* root;

    void add_element(Node*& node, int value) {
        if (node == nullptr) {
            node = new Node(value);
        }
        else if (value < node->value) {
            add_element(node->left, value);
            node->left->previous = node;
        }
        else if (value > node->value) {
            add_element(node->right, value);
            node->right->previous = node;
        }
    }

    bool delete_element(Node*& node, int value) {
        if (node == nullptr) {
            return false;
        }
        else if (value < node->value) {
            return delete_element(node->left, value);
        }
        else if (value > node->value) {
            return delete_element(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else {
                Node* temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->value = temp->value;
                return delete_element(node->right, temp->value);
            }
            return true;
        }
    }

    bool find_element(Node* node, int value) const {
        if (node == nullptr) {
            return false;
        }
        if (value < node->value) {
            return find_element(node->left, value);
        }
        if (value > node->value) {
            return find_element(node->right, value);
        }
        return true;
    }

    void print(Node* node) const {
        if (node != nullptr) {
            print(node->left);
            cout << node->value << " ";
            print(node->right);
        }
    }

    bool save_to_file(Node* node, ofstream& file) const {
        if (node != nullptr) {
            save_to_file(node->left, file);
            file << node->value << " ";
            save_to_file(node->right, file);
            return true;
        }
        return false;
    }

    bool load_from_file(Node*& node, ifstream& file) {
        int value;
        if (file >> value) {
            node = new Node(value);
            load_from_file(node->left, file);
            load_from_file(node->right, file);
            return true;
        }
        return false;
    }

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    BSTree() : root(nullptr) {}
    BSTree(initializer_list<int> list) : root(nullptr) {
        for (int value : list) {
            add_element(root, value);
        }
    }

    bool add_element(int value) {
        add_element(root, value);
        return true;
    }

    bool delete_element(int value) {
        return delete_element(root, value);
    }

    bool find_element(int value) const {
        return find_element(root, value);
    }

    void print() const {
        print(root);
        cout << endl;
    }

    bool save_to_file(const string& path) const {
        ofstream file(path);
        if (file.is_open()) {
            save_to_file(root, file);
            file.close();
            return true;
        }
        return false;
    }

    bool load_from_file(const string& path) {
        ifstream file(path);
        if (file.is_open()) {
            destroy(root);
            root = nullptr;
            load_from_file(root, file);
            file.close();
            return true;
        }
        return false;
    }

    ~BSTree() {
        destroy(root);
    }
};

int main() {
    initializer_list<int> list = { 5, 2, 4, 1, 3 };
    BSTree tree(list);
    return 0;
}