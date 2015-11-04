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

#ifndef SHAREMIND_MINER_DATASTOREFACTORY_H
#define SHAREMIND_MINER_DATASTOREFACTORY_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include "datastoreapi.h"

#include <string>
#include <sharemind/ScopedObjectMap.h>

#include "DataStore.h"


namespace sharemind {

//class DataStore;
class DataStoreManager;

class DataStoreFactory {

public: /* Types: */

    using Wrapper = ::SharemindDataStoreFactory;

private: /* Types: */

    using DataStoreMap = ScopedObjectMap<std::string, DataStore>;

public: /* Methods: */

    DataStoreFactory();
    DataStoreFactory(DataStoreFactory &&) = delete;
    DataStoreFactory & operator=(DataStoreFactory &&) = delete;

    DataStore::Wrapper & dataStoreWrapper(const std::string & name);

    inline Wrapper & wrapper() noexcept { return m_wrapper; }
    inline const Wrapper & wrapper() const noexcept { return m_wrapper; }

private: /* Fields: */

    Wrapper m_wrapper;

    DataStoreMap m_dataStores;

}; /* class DataStoreFactory { */
} /* namespace sharemind { */

#endif /* SHAREMIND_MINER_DATASTOREFACTORY_H */
