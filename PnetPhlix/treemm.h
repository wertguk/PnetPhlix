#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_it = m_list.begin();  //create invalid iterator
        }
        
        Iterator(std::list<ValueType> nlist)
        {
            m_list = nlist;
            m_it = m_list.begin();  //pass in list and iterator to first element in list
        }

        ValueType& get_value() const
        {
            return *m_it;   //return value of iterator
        }

        bool is_valid() const
        {
            return !(m_it == m_list.end()); //check if iterator points to end of list
        }

        void advance()
        {
            m_it++; //advances iterator
        }

      private:
        typename std::list<ValueType>::iterator m_it;   //stores list and iterator to list
        std::list<ValueType> m_list;
    };

    TreeMultimap()
    {
        root = nullptr; //set root to null pointer
    }

    ~TreeMultimap()
    {
        deleteTree(root);   //call deleteRoot private member function
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        insertInOrder(root, key, value);    //call insertInOrder private member function
    }

    Iterator find(const KeyType& key) const
    {
        return findKey(root, key);  //call findKey private member function
    }

  private:
    struct Node
    {
        Node* left; //node stores left right pointers
        Node* right;
        std::list<ValueType> values;    //stores list of values
        KeyType key;
    };
    
    Node* root;
    
    void deleteTree(Node* p){
        //delete tree with post-order traversal
        if (p == nullptr)
            return;
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }

    void insertInOrder(Node* p, KeyType key, ValueType value){
        if (p == nullptr){
            //insert at root
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
                //insert if left pointer is null
                Node* np = new Node;
                p->left = np;
                np->key = key;
                np->values.push_back(value);
                np->left = nullptr;
                np->right = nullptr;
                return;
            }
            //call insert on left subtree
            insertInOrder(p->left, key, value);
        }
        if (key > p->key){
            if (p->right == nullptr){
                //insert if right pointer is null
                Node* np = new Node;
                p->right = np;
                np->key = key;
                np->values.push_back(value);
                np->left = nullptr;
                np->right = nullptr;
                return;
            }
            //call insert on right subtree
            insertInOrder(p->right, key, value);
        }
        //add to values list if key in tree
        if (key == p->key)
            p->values.push_back(value);
    }
    
    Iterator findKey(Node* p, KeyType key) const{
        if (p == nullptr)
            return Iterator();  //if not found create invalid iterator
        if (p->key == key){
            Iterator it = Iterator(p->values);  //if found create iterator to list
            return it;
        }
        if (p->key > key)
            return findKey(p->left, key);   //find in left subtree
        if (p->key < key)
            return findKey(p->right, key);  //find in right subtree
        return Iterator();
    }
};

#endif // TREEMULTIMAP_INCLUDED
