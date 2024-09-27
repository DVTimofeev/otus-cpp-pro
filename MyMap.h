#pragma once

#include <functional>
#include <exception>
#include <memory>
#include <stdexcept>

template<
    class Key,
    class T,
    class Allocator = std::allocator<std::pair<const Key, T>>
> 
class MyMap
{
public:
    MyMap(){}

    void emplace(Key key_, T value_)
    {
        if(!root)
        {
            root = constructNode(key_, value_);
            ++size_;
            return;
        }

        auto parent = root;
        bool finished = false;
        while (!finished)
        { 
            if (key_ == parent->key)
            {
                parent->val = value_;
                return;
            }
            else if (key_ < parent->key)
            {
                if (parent->left)
                    parent = parent->left;
                else
                {
                    parent->left = constructNode(key_, value_);
                    finished = true;
                }
            }                
            else 
            {
                if (parent->right)
                    parent = parent->right;
                else
                {
                    parent->right = constructNode(key_, value_);
                    finished = true;
                }
            }
        }
        ++size_;
        
    }

    T at(const Key& key_) const
    {
        
        auto temp_root = root;
        while (true)
        {
            if (!temp_root)
                throw std::out_of_range("no such key in map");

            if (key_ == temp_root->key)
                return temp_root->val;
            else if (key_ < temp_root->key)
                temp_root = temp_root->left;
            else
                temp_root = temp_root->right;
        }
    }

    size_t size() const { return size_; }
    

private:
    struct Node
    {
        Node(Key key_, T val_): key{key_}, val{val_} {}

        Key key;
        T val;
        Node* left = nullptr;
        Node* right = nullptr;

        bool operator < ( const Node &r ) const
        {
            return key < r.key;
        }
    };

    Node* constructNode(Key key, T value)
    {
        typename Allocator::template rebind<Node>::other nodeAlloc;
        Node* newNode = nodeAlloc.allocate(1);
        nodeAlloc.construct(newNode, key, value);
        return newNode;
    }

    Node* root = nullptr;
    Allocator alloc;
    size_t size_ = 0;
};
