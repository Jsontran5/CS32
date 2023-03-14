#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED


#include <list>
#include <vector>
#include <utility>

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
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
        }
        else
        {
            Node* cur = m_root;
            for (;;)
            {
                if (key == cur->key)
                {
                    cur->values.push_back(value);
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
                    }

                }
            }
        }
        
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }

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

};

#endif // TREEMULTIMAP_INCLUDED
