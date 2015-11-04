/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "DataStore.h"

#include "DataStoreFactory.h"


extern "C" {

void SharemindDataStore_clear(SharemindDataStore * datastore) {
    assert(datastore);
    assert(datastore->internal);
    static_cast<sharemind::DataStore *>(datastore->internal)->clear();
}

bool SharemindDataStore_set(SharemindDataStore * datastore,
                            const char * key,
                            void * value,
                            sharemind_datastore_destroy_fn_ptr destroyFn)
{
    assert(datastore);
    assert(datastore->internal);
    assert(key);
    try {
        return static_cast<sharemind::DataStore *>(datastore->internal)->set(
                    key,
                    value,
                    destroyFn);
    } catch (...) { return false; }
}

void * SharemindDataStore_get(SharemindDataStore * datastore, const char * key)
{
    assert(datastore);
    assert(datastore->internal);
    assert(key);
    return static_cast<sharemind::DataStore *>(datastore->internal)->get(key);
}

bool SharemindDataStore_remove(SharemindDataStore * datastore, const char * key)
{
    assert(datastore);
    assert(datastore->internal);
    assert(key);
    try {
        return static_cast<sharemind::DataStore *>(datastore->internal)->remove(
                    key);
    } catch (...) { return false; }
}

} // extern "C" {

namespace sharemind {

DataStore::DataStore(DataStoreFactory & factory)
    : m_wrapper{this,
                &factory.wrapper(),
                &SharemindDataStore_clear,
                &SharemindDataStore_get,
                &SharemindDataStore_remove,
                &SharemindDataStore_set}
{}

} // namespace sharemind {
