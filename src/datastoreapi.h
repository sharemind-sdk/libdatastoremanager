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

#ifndef SHAREMIND_MINER_DATASTOREAPI_H
#define SHAREMIND_MINER_DATASTOREAPI_H

#include <sharemind/libmodapi/api_0x1.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

// TODO documentation

/** Forward declarations: */
typedef void (*sharemind_datastore_destroy_fn_ptr)(void *);

struct SharemindDataStoreManager_;
typedef SharemindDataStoreManager_ SharemindDataStoreManager;
struct SharemindDataStoreFactory_;
typedef SharemindDataStoreFactory_ SharemindDataStoreFactory;
struct SharemindDataStore_;
typedef SharemindDataStore_ SharemindDataStore;


/*******************************************************************************
    SharemindDataStoreManager
*******************************************************************************/

/** Wrapper object */
struct SharemindDataStoreManager_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    SharemindDataStoreFactory * (* get_datastore_factory)(SharemindDataStoreManager * manager,
                                                          const SharemindModuleApi0x1SyscallContext * ctx);
    SharemindDataStore * (* get_datastore)(SharemindDataStoreManager * manager,
                                           const SharemindModuleApi0x1SyscallContext * ctx,
                                           const char * name);
};


/*******************************************************************************
    SharemindDataStoreFactory
*******************************************************************************/

/** Wrapper object */
struct SharemindDataStoreFactory_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    SharemindDataStore * (* get_datastore)(SharemindDataStoreFactory * factory, const char * name);
};


/*******************************************************************************
    SharemindDataStore
*******************************************************************************/

/** Wrapper object */
struct SharemindDataStore_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    SHAREMIND_ICONST SharemindDataStoreFactory * SHAREMIND_ICONST factoryHandle;

    void (* clear)(SharemindDataStore * datastore);
    void * (* get)(SharemindDataStore * datastore, const char * key);
    bool (* remove)(SharemindDataStore * datastore, const char * key);
    bool (* set)(SharemindDataStore * datastore, const char * key, void * value, sharemind_datastore_destroy_fn_ptr destroy);
};


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_MINER_DATASTOREAPI_H */
