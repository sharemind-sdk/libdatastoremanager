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

#ifndef SHAREMIND_MINER_DATASTOREMANAGER_H
#define SHAREMIND_MINER_DATASTOREMANAGER_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <cstdint>
#include <map>
#include <sharemind/libprocessfacility.h>
#include "datastoreapi.h"
#include "DataStoreFactory.h"


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
