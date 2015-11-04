/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "DataStoreFactory.h"

#include <cassert>
#include "DataStoreManager.h"


namespace {
extern "C" {

SharemindDataStore * SharemindDataStoreFactory_get_datastore(
        SharemindDataStoreFactory * factory,
        const char * name)
{
    assert(factory);
    assert(factory->internal);
    assert(name);
    try {
        return &static_cast<sharemind::DataStoreFactory *>(factory->internal)
                    ->dataStoreWrapper(name);
    } catch (...) { return nullptr; }
}

} // extern "C" {
} // anonymous namespace


namespace sharemind {

DataStoreFactory::DataStoreFactory()
    : m_wrapper{this, &SharemindDataStoreFactory_get_datastore}
{}

DataStore::Wrapper & DataStoreFactory::dataStoreWrapper(
        const std::string & name)
{
    // Check for an existing data store
    DataStoreMap::const_iterator const it{m_dataStores.find(name)};
    if (it != m_dataStores.cend())
        return it->second->wrapper();

    // Create a new data store
    DataStore * const ds = new DataStore{*this};
    try {
        #ifndef NDEBUG
        bool const r =
        #endif
                m_dataStores.insert(name, ds)
        #ifndef NDEBUG
                    .second
        #endif
                ;
        assert(r);
    } catch (...) {
        delete ds;
        throw;
    }
    return ds->wrapper();
}

} /* namespace sharemind { */
