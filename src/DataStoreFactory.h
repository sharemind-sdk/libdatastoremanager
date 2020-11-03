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

#ifndef SHAREMIND_LIBDATASTOREMANAGER_DATASTOREFACTORY_H
#define SHAREMIND_LIBDATASTOREMANAGER_DATASTOREFACTORY_H

#ifndef SHAREMIND_INTERNAL_
#error SHAREMIND_INTERNAL_ not defined
#endif

#include <sharemind/datastoreapi.h>

#include <memory>
#include <sharemind/SimpleUnorderedStringMap.h>
#include <string>
#include "DataStore.h"


namespace sharemind {

class DataStoreFactory: private ::SharemindDataStoreFactory {

public: /* Types: */

    using Wrapper = ::SharemindDataStoreFactory;

public: /* Methods: */

    DataStoreFactory();
    DataStoreFactory(DataStoreFactory &&) = delete;
    DataStoreFactory & operator=(DataStoreFactory &&) = delete;

    DataStore::Wrapper & dataStoreWrapper(const std::string & name);

    static DataStoreFactory & fromWrapper(Wrapper & wrapper) noexcept
    { return static_cast<DataStoreFactory &>(wrapper); }

    inline Wrapper & wrapper() noexcept { return *this; }
    inline const Wrapper & wrapper() const noexcept { return *this; }

private: /* Fields: */

    SimpleUnorderedStringMap<std::unique_ptr<DataStore> > m_dataStores;

}; /* class DataStoreFactory { */
} /* namespace sharemind { */

#endif /* SHAREMIND_LIBDATASTOREMANAGER_DATASTOREFACTORY_H */
