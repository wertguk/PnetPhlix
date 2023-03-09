#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            // Replace this line with correct code.
        }

        ValueType& get_value() const
        {
            throw 1;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            return false;  // Replace this line with correct code.
        }

        void advance()
        {
            // Replace this line with correct code.
        }

      private:
    };

    TreeMultimap()
    {
        root = nullptr;
    }

    ~TreeMultimap()
    {
        deleteTree(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        insertInOrder(root, key, value);
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }

  private:
    struct Node
    {
        Node* left;
        Node* right;
        std::list<ValueType> values;
        KeyType key;
    };
    
    Node* root;
    
    void deleteTree(Node* p){
        if (p == nullptr)
            return
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }

    void insertInOrder(Node* p, KeyType key, ValueType value){
        if (p == nullptr){
            Node* np = new Node;
            root = np;
            root->key = key;
            root->values.push_back(value);
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
        if (key < p->key){
            if (p->left == nullptr){
                Node* np = new Node;
                p->left = np;
                np->key = key;
                np->values.push_back(value);
                np->left = nullptr;
                np->right = nullptr;
                return;
            }
            insertInOrder(p->left, key, value);
        }
        if (key > p->key){
            if (p->right == nullptr){
                Node* np = new Node;
                p->right = np;
                np->key = key;
                np->values.push_back(value);
                np->left = nullptr;
                np->right = nullptr;
                return;
            }
            insertInOrder(p->right, key, value);
        }
        p->values.push_back(value);
    }
};




#endif // TREEMULTIMAP_INCLUDED
