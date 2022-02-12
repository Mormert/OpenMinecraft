#ifndef OPENMINECRAFT_PAIRHASH_H
#define OPENMINECRAFT_PAIRHASH_H

#include <functional>
#include <string>
#include <utility>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

#endif //OPENMINECRAFT_PAIRHASH_H
