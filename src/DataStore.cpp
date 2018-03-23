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

#include "DataStore.h"

#include "DataStoreFactory.h"


extern "C" {

void SharemindDataStore_clear(SharemindDataStore * datastore);
void SharemindDataStore_clear(SharemindDataStore * datastore) {
    assert(datastore);
    sharemind::DataStore::fromWrapper(*datastore).clear();
}

bool SharemindDataStore_set(SharemindDataStore * datastore,
                            const char * key,
                            void * value,
                            sharemind_datastore_destroy_fn_ptr destroyFn);
bool SharemindDataStore_set(SharemindDataStore * datastore,
                            const char * key,
                            void * value,
                            sharemind_datastore_destroy_fn_ptr destroyFn)
{
    assert(datastore);
    assert(key);
    try {
        return sharemind::DataStore::fromWrapper(*datastore).set(
                    key,
                    value,
                    destroyFn);
    } catch (...) { return false; }
}

void * SharemindDataStore_get(SharemindDataStore * datastore, const char * key);
void * SharemindDataStore_get(SharemindDataStore * datastore, const char * key)
{
    assert(datastore);
    assert(key);
    return sharemind::DataStore::fromWrapper(*datastore).get(key);
}

bool SharemindDataStore_remove(SharemindDataStore * datastore,
                               const char * key);
bool SharemindDataStore_remove(SharemindDataStore * datastore, const char * key)
{
    assert(datastore);
    assert(key);
    try {
        return sharemind::DataStore::fromWrapper(*datastore).remove(key);
    } catch (...) { return false; }
}

} // extern "C" {

namespace sharemind {

DataStore::DataStore()
    : ::SharemindDataStore{
            &SharemindDataStore_clear,
            &SharemindDataStore_get,
            &SharemindDataStore_remove,
            &SharemindDataStore_set}
{}

} // namespace sharemind {
