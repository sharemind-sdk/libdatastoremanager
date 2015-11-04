/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_MINER_DATASTORE_H
#define SHAREMIND_MINER_DATASTORE_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <cassert>
#include <map>
#include <sharemind/compiler-support/GccPR44436.h>
#include <string>
#include <utility>
#include "datastoreapi.h"


namespace sharemind {

class DataStoreFactory;

class DataStore {

public: /* Types: */

    using Wrapper = ::SharemindDataStore;

private: /* Types: */

    struct Value {
        inline Value(void * const v) noexcept : value(v) {}
        inline ~Value() noexcept {
            if (destroyFn)
                (*destroyFn)(value);
        }
        void * value;
        sharemind_datastore_destroy_fn_ptr destroyFn = nullptr;
    };

    using ValueMap = std::map<std::string, Value>;

public: /* Methods: */

    DataStore() = delete;
    DataStore(DataStore &&) = delete;
    DataStore & operator=(DataStore &&) = delete;
    DataStore(DataStoreFactory & factory);

    inline void clear() noexcept { m_values.clear(); }

    template <typename K>
    bool set(K && key,
             void * const value,
             sharemind_datastore_destroy_fn_ptr const destroyFn)
    {
        auto const r = m_values.insert({std::forward<K>(key), Value{value}});
        if (r.second)
            r.first->second.destroyFn = destroyFn;
        return r.second;
    }

    inline void * get(const std::string & key) const noexcept {
        ValueMap::const_iterator const it = m_values.find(key);
        return it != m_values.end() ? it->second.value : nullptr;
    }

    inline bool remove(const std::string & key)
    { return m_values.erase(key) != 0u; }

    inline Wrapper & wrapper() noexcept { return m_wrapper; }
    inline Wrapper const & wrapper() const noexcept { return m_wrapper; }

private: /* Fields: */

    Wrapper m_wrapper;
    ValueMap m_values;

}; /* class DataStore { */
} /* namespace sharemind { */

#endif /* SHAREMIND_MINER_DATASTORE_H */
