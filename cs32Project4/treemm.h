#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED


#include <list>
#include <vector>
#include <utility>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
private: 

    struct Node
    {
        KeyType key;
        std::list<ValueType> values;
        Node* left;
        Node* right;
        Node(const KeyType& k, const ValueType& v)
        {
            key = k;
            values.push_back(v);
            left = nullptr;
            right = nullptr;
        }
    };

  

    Node* m_root;
    void FreeTree(Node* node)
    {
        if (node != nullptr)
        {
            FreeTree(node->left);
            FreeTree(node->right);
            delete node;
        }
        return;
    }
public:
    class Iterator
    {
    public:
        Iterator()
        {
            m_curNode = nullptr;
        }

        Iterator(Node* node)
        {
            m_curNode = node;
            m_value = m_curNode->values.begin();
        }

        ValueType& get_value() const
        {
            if (m_curNode == nullptr)
            {
                throw 1;
            }

            if (m_value != m_curNode->values.end())
            {
                return *m_value;
            }

       
            throw 1;
            
        }

        bool is_valid() const
        {
            
            if (m_curNode == nullptr)
            {
                return false;
            }
            return (m_value != m_curNode->values.end());
        }

        void advance()
        {
          
          if (m_value != m_curNode->values.end())
            {
                m_value++;
            }

        }

    private:
        Node* m_curNode; 
        typename std::list<ValueType>::iterator m_value;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        FreeTree(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            return;
        }
        else
        {
            Node* cur = m_root;
            for (;;)
            {
                if (key == cur->key)
                {
                    cur->values.push_back(value);
                    return;
                }
                else if (key < cur->key)
                {
                    if (cur->left != nullptr)
                    {
                        cur = cur->left;
                    }
                    else
                    {
                        cur->left = new Node(key, value);
                        return;
                    }
                }
                else if (key > cur->key)
                {
                    if (cur->right != nullptr)
                    {
                        cur = cur->right;
                    }
                    else
                    {
                        cur->right = new Node(key, value);
                        return;
                    }

                }
            }
        }
        
    }

    Iterator find(const KeyType& key) const
    {
        Node* temp = m_root;
        
       while (temp != nullptr)
        {
           if (key < temp->key)
           {
               temp = temp->left;
           }
           else if (key > temp->key)
           {
               temp = temp->right;
           }
           else if(key == temp->key)
           {
               return Iterator(temp);
           }
          
        }

        return Iterator();  // Replace this line with correct code.
    }



};

#endif // TREEMULTIMAP_INCLUDED
