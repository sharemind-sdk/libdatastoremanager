/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_MINER_DATASTOREMANAGER_H
#define SHAREMIND_MINER_DATASTOREMANAGER_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <cstdint>
#include <map>
#include "datastoreapi.h"
#include "DataStoreFactory.h"
#include "libprocessfacility.h"


namespace sharemind {

class DataStoreFactory;

class DataStoreManager {

public: /* Types: */

    using Wrapper = SharemindDataStoreManager;

private: /* Types: */

    using FactoryMap = std::map<SharemindProcessId, DataStoreFactory *>;

public: /* Methods: */

    DataStoreManager();
    DataStoreManager(DataStoreManager &&) = delete;
    DataStoreManager(const DataStoreManager &) = delete;
    DataStoreManager & operator=(DataStoreManager &&) = delete;
    DataStoreManager & operator=(const DataStoreManager &) = delete;

    void registerFactory(const SharemindProcessId processId,
                         DataStoreFactory & factory);
    bool unregisterFactory(const SharemindProcessId processId);

    DataStore::Wrapper * dataStoreWrapper(const SharemindProcessId pid,
                                          const std::string & name) const
    {
        DataStoreFactory * const f = factory(pid);
        return f ? (&f->dataStoreWrapper(name)) : nullptr;
    }

    DataStoreFactory::Wrapper * factoryWrapper(const SharemindProcessId pid)
            const noexcept
    {
        DataStoreFactory * const f = factory(pid);
        return f ? &f->wrapper() : nullptr;
    }

    inline Wrapper & wrapper() noexcept { return m_wrapper; }
    inline const Wrapper & wrapper() const noexcept { return m_wrapper; }

private: /* Methods: */

    DataStoreFactory * factory(const SharemindProcessId processId)
            const noexcept;

private: /* Fields: */

    Wrapper m_wrapper;

    FactoryMap m_factories;

}; /* class DataStoreManager { */
} /* namespace sharemind { */

#endif /* SHAREMIND_MINER_DATASTOREMANAGER_H */
