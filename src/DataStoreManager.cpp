/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "DataStoreManager.h"

#include <cassert>
#include "libprocessfacility.h"
#include "DataStore.h"
#include "DataStoreFactory.h"


namespace {
extern "C" {

SharemindDataStoreFactory * SharemindDataStoreManager_get_datastore_factory(
        SharemindDataStoreManager * manager,
        const SharemindModuleApi0x1SyscallContext * ctx)
{
    assert(manager);
    assert(manager->internal);
    assert(ctx);
    assert(ctx->process_internal);

    try {
        // Get the manager object
        const sharemind::DataStoreManager & dsMan =
                *static_cast<sharemind::DataStoreManager *>(manager->internal);

        // Get the factory object
        const SharemindProcessFacility & pf =
                *static_cast<SharemindProcessFacility *>(ctx->process_internal);
        return dsMan.factoryWrapper(pf.get_process_id(&pf));
    } catch (...) {
        return nullptr;
    }
}

SharemindDataStore * SharemindDataStoreManager_get_datastore(
        SharemindDataStoreManager * manager,
        const SharemindModuleApi0x1SyscallContext * ctx,
        const char * name)
{
    assert(manager);
    assert(manager->internal);
    assert(ctx);
    assert(ctx->process_internal);
    assert(name);

    try {
        sharemind::DataStoreManager & dsMan =
                *static_cast<sharemind::DataStoreManager *>(manager->internal);
        const SharemindProcessFacility & pf =
                *static_cast<SharemindProcessFacility *>(ctx->process_internal);
        return dsMan.dataStoreWrapper(pf.get_process_id(&pf), name);
    } catch (...) {
        return nullptr;
    }
}

} // extern "C" {
} // anonymous namespace


namespace sharemind {

DataStoreManager::DataStoreManager() {
    m_wrapper.internal = this;
    m_wrapper.get_datastore_factory = &SharemindDataStoreManager_get_datastore_factory;
    m_wrapper.get_datastore = &SharemindDataStoreManager_get_datastore;
}

void DataStoreManager::registerFactory(const SharemindProcessId processId,
                                       DataStoreFactory & factory)
{
    #ifndef NDEBUG
    const bool r =
    #endif
          m_factories.insert({processId, &factory})
        #ifndef NDEBUG
            .second
        #endif
            ;
    assert(r);
}

bool DataStoreManager::unregisterFactory(const SharemindProcessId processId)
{ return m_factories.erase(processId); }

DataStoreFactory * DataStoreManager::factory(const SharemindProcessId processId)
        const noexcept
{
    const FactoryMap::const_iterator it = m_factories.find(processId);
    return it != m_factories.end() ? it->second : nullptr;
}

} /* namespace sharemind { */
