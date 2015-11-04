/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
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
