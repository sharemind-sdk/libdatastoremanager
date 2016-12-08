/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
 */

#ifndef SHAREMIND_MINER_DATASTORE_H
#define SHAREMIND_MINER_DATASTORE_H

#ifndef SHAREMIND_INTERNAL_
#error SHAREMIND_INTERNAL_ not defined
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

    /* Methods: */

        Value(Value const & copy) = delete;
        Value & operator=(Value const & rhs) = delete;

        inline Value(void * const v) noexcept : value(v) {}

        inline Value(Value && move) noexcept
            : value(move.value)
            , destroyFn(move.destroyFn)
        {
            move.value = nullptr;
            move.destroyFn = nullptr;
        }

        inline ~Value() noexcept {
            if (destroyFn)
                (*destroyFn)(value);
        }

        inline Value & operator=(Value && rhs) noexcept {
            if (destroyFn)
                (*destroyFn)(value);
            value = rhs.value;
            destroyFn = rhs.destroyFn;
            rhs.value = nullptr;
            rhs.destroyFn = nullptr;
            return *this;
        }

    /* Fields: */

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
        auto const r = m_values.emplace(std::forward<K>(key), Value{value});
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
