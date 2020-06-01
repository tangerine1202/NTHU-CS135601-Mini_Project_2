#include <cstddef>
#include "12727.h"
// #include "function.h"

namespace oj
{
    Node *getNodeAddrFromNodeDataPtr(const value_type *nodeDataPtr)
    {
        Node *ret;
        size_t offset = offsetof(Node, data);
        ret = reinterpret_cast<Node *>(reinterpret_cast<size_type>(nodeDataPtr) - offset);
        return ret;
    }

    iterator_impl_base &list_iterator::operator++()
    {
        this->_node = this->_node->next;
        return *this;
    }; // increments the iterator; the iterator should then point to the next node
    bool list_iterator::operator!=(const iterator_impl_base &rhs) const
    {
        return this->_node != getNodeAddrFromNodeDataPtr(&(*rhs));
    }; // compares whether two iterators point to the same node

    list::list()
    {
        this->_head = this->_tail = new Node();
        this->_size = 0;
    };
    list::~list()
    {
        Node *tmp;
        while (this->_head != nullptr)
        {
            tmp = this->_head;
            this->_head = this->_head->next;
            delete tmp;
        }
        delete this->_head;
    };
    void list::clear()
    {
        this->~list();
        this->_head = this->_tail = new Node();
        this->_size = 0;
    }; // make this list empty as if it's new
    size_type list::size() const
    {
        return this->_size;
    }; // returns the number of elements in the list
    bool list::empty() const
    {
        return this->_head == this->_tail;
    }; // returns whether the list is empty
    iterator list::begin()
    {
        return iterator(list_iterator(this->_head).clone());
    }; // returns an iterator that points to the first node (if none, point to end)
    iterator list::end()
    {
        return iterator(list_iterator(this->_tail).clone());
    }; // returns an iterator that points to a special node that is the node after the last element
    void list::insert(iterator pos, size_type count, const value_type val)
    {
        Node *posNode = getNodeAddrFromNodeDataPtr(&(*pos));
        bool pos_is_head = (posNode == this->_head);
        if (posNode == this->_head)
        {
            for (int i = 0; i < count; i++)
            {
                Node *newNode = new Node(val);
                this->_head->prev = newNode;
                newNode->next = this->_head;
                this->_head = newNode;
            }
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                Node *newNode = new Node(val);
                newNode->prev = posNode->prev;
                newNode->next = posNode;
                if (pos_is_head)
                    this->_head = newNode;
                else
                    posNode->prev->next = newNode;
                posNode->prev = newNode;
            }
        }
        this->_size += count;
    }; // inserts #count val right before pos
    void list::erase(iterator l, iterator r)
    {
        for (; l != r; ++l)
        {
            Node *curNode = getNodeAddrFromNodeDataPtr(&(*l));
            if (curNode == this->_head)
                this->_head = this->_head->next;
            if (curNode->prev != nullptr)
                curNode->prev->next = curNode->next;
            if (curNode->next != nullptr)
                curNode->next->prev = curNode->prev;
            delete curNode;
            this->_size--;
        }
    }; // erase nodes with index in [l, r)

} // namespace oj