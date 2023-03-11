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
            m_it = m_list.begin();
        }
        
        Iterator(typename std::list<ValueType>::iterator it, std::list<ValueType> nlist)
        {
            m_it = it;
            m_list = nlist;
        }

        ValueType& get_value() const
        {
            return *m_it;
        }

        bool is_valid() const
        {
            return !(m_it == m_list.end());
        }

        void advance()
        {
            m_it++;
        }

      private:
        typename std::list<ValueType>::iterator m_it;
        std::list<ValueType> m_list;
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
        return findKey(root, key);
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
            return;
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
    
    Iterator findKey(Node* p, KeyType key) const{
        if (p == nullptr){
            std::list<ValueType> emptyList;
            return Iterator(emptyList.begin(), emptyList);
        }
        if (p->key == key){
            Iterator it = Iterator(p->values.begin(), p->values);
            return it;
        }
        if (p->key < key)
            findKey(p->left, key);
        if (p->key > key)
            findKey(p->right, key);
        std::list<ValueType> emptyList;
        return Iterator(emptyList.begin(), emptyList);
    }
};

#endif // TREEMULTIMAP_INCLUDED
