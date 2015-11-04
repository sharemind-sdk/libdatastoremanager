/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
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
