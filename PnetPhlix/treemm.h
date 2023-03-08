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
    Node* root;
    void deleteTree(Node* p);
    void insertInOrder(Node* p, KeyType key, ValueType value);
};

template <typename KeyType, typename ValueType>
struct Node
{
    Node* left;
    Node* right;
    std::list<ValueType> values;
    KeyType key;
};

void TreeMultimap::deleteTree(Node* p){
    if (p == nullptr)
        return
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
}


#endif // TREEMULTIMAP_INCLUDED
