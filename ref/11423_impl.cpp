#include "11423.h"
// #include "function.h"

namespace oj
{
    Node::Node() : next(nullptr), prev(nullptr) {}

    Iter::Iter(data_t *begin) : p_(begin){};

    Random_iter::Random_iter(data_t *begin) : Iter(begin) {}

    void Random_iter::next_(Iter &des) const
    {
        des.assign(Random_iter(this->get() + 1));
    };

    void Random_iter::prev_(Iter &des) const
    {
        des.assign(Random_iter(this->get() - 1));
    };

    std::ptrdiff_t Random_iter::distance_(const Iter &begin, const Iter &end) const
    {
        return (end.get() - begin.get());
    }

    // Bidirect iter
    Bidirect_iter::Bidirect_iter(data_t *begin) : Iter(begin) {}

    void Bidirect_iter::next_(Iter &des) const
    {
        des.assign(Bidirect_iter(this->get()->next));
    }

    void Bidirect_iter::prev_(Iter &des) const
    {
        des.assign(Bidirect_iter(this->get()->prev));
    }

    std::ptrdiff_t Bidirect_iter::distance_(const Iter &begin, const Iter &end) const
    {
        std::ptrdiff_t dis = 0;
        Bidirect_iter cur(begin.get());
        while (cur.get() != end.get())
        {
            dis++;
            cur.next(cur);
        }
        return dis;
    }

} // namespace oj