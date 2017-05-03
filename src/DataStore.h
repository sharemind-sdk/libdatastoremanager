/*
 * Copyright (C) 2015-2017 Cybernetica
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
#include <memory>
#include <string>
#include <utility>
#include "datastoreapi.h"


namespace sharemind {

class DataStoreFactory;

class DataStore {

public: /* Types: */

    using Wrapper = ::SharemindDataStore;

private: /* Types: */

    class Deleter {

    public: /* Methods: */

        Deleter(sharemind_datastore_destroy_fn_ptr destroyer) noexcept
            : m_destroyer(std::move(destroyer))
        {}

        void operator()(void * value) const noexcept
        { return (*m_destroyer)(value); }

    private: /* Fields: */

        sharemind_datastore_destroy_fn_ptr m_destroyer;

    };

    using Value = std::unique_ptr<void, Deleter>;

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
        return m_values.emplace(std::forward<K>(key),
                                Value(value, Deleter(destroyFn))).second;
    }

    inline void * get(const std::string & key) const noexcept {
        auto const it(m_values.find(key));
        return it != m_values.end() ? it->second.get() : nullptr;
    }

    inline bool remove(const std::string & key)
    { return m_values.erase(key) != 0u; }

    inline Wrapper & wrapper() noexcept { return m_wrapper; }
    inline Wrapper const & wrapper() const noexcept { return m_wrapper; }

private: /* Fields: */

    Wrapper m_wrapper;
    std::map<std::string, Value> m_values;

}; /* class DataStore { */
} /* namespace sharemind { */

#endif /* SHAREMIND_MINER_DATASTORE_H */
