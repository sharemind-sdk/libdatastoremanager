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

#include "DataStoreFactory.h"

#include <cassert>
#include <sharemind/DebugOnly.h>


namespace {
extern "C" {

SharemindDataStore * SharemindDataStoreFactory_get_datastore(
        SharemindDataStoreFactory * factory,
        const char * name);
SharemindDataStore * SharemindDataStoreFactory_get_datastore(
        SharemindDataStoreFactory * factory,
        const char * name)
{
    assert(factory);
    assert(name);
    try {
        auto & cxxFactory = sharemind::DataStoreFactory::fromWrapper(*factory);
        return &cxxFactory.dataStoreWrapper(name);
    } catch (...) { return nullptr; }
}

} // extern "C" {
} // anonymous namespace


namespace sharemind {

DataStoreFactory::DataStoreFactory()
    : ::SharemindDataStoreFactory{&SharemindDataStoreFactory_get_datastore}
{}

DataStore::Wrapper & DataStoreFactory::dataStoreWrapper(
        const std::string & name)
{
    // Check for an existing data store
    auto const it(m_dataStores.find(name));
    if (it != m_dataStores.cend())
        return it->second->wrapper();

    // Create a new data store
    auto ds(std::make_unique<DataStore>());
    auto & r(ds->wrapper());
    SHAREMIND_DEBUG_ONLY(auto const rit =)
            m_dataStores.emplace(name, std::move(ds));
    assert(rit.second);
    return r;
}

} /* namespace sharemind { */
