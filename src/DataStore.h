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

#ifndef SHAREMIND_LIBDATASTOREMANAGER_DATASTORE_H
#define SHAREMIND_LIBDATASTOREMANAGER_DATASTORE_H

#ifndef SHAREMIND_INTERNAL_
#error SHAREMIND_INTERNAL_ not defined
#endif

#include <cassert>
#include <memory>
#include <sharemind/datastoreapi.h>
#include <sharemind/SimpleUnorderedStringMap.h>
#include <string>
#include <utility>


namespace sharemind {

class DataStoreFactory;

class DataStore: private ::SharemindDataStore {

public: /* Types: */

    using Wrapper = ::SharemindDataStore;

private: /* Types: */

    struct Deleter {

    /* Methods: */

        void operator()(void * value) const noexcept {
            if (m_destroyer)
                return (*m_destroyer)(value);
        }

    /* Fields: */

        sharemind_datastore_destroy_fn_ptr const m_destroyer;

    };

    using Value = std::unique_ptr<void, Deleter>;

public: /* Methods: */

    DataStore();
    DataStore(DataStore &&) = delete;
    DataStore & operator=(DataStore &&) = delete;

    inline void clear() noexcept { m_values.clear(); }

    template <typename K>
    bool set(K && key,
             void * const value,
             sharemind_datastore_destroy_fn_ptr const destroyFn)
    {
        Value storage(value, Deleter{destroyFn});
        return m_values.emplace(std::forward<K>(key),
                                std::move(storage)).second;
    }

    inline void * get(const std::string & key) const noexcept {
        auto const it(m_values.find(key));
        return it != m_values.end() ? it->second.get() : nullptr;
    }

    inline bool remove(const std::string & key)
    { return m_values.erase(key) != 0u; }

    static DataStore & fromWrapper(Wrapper & wrapper ) noexcept
    { return static_cast<DataStore &>(wrapper); }

    inline Wrapper & wrapper() noexcept { return *this; }
    inline Wrapper const & wrapper() const noexcept { return *this; }

private: /* Fields: */

    SimpleUnorderedStringMap<Value> m_values;

}; /* class DataStore { */
} /* namespace sharemind { */

#endif /* SHAREMIND_LIBDATASTOREMANAGER_DATASTORE_H */
