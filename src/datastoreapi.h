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

#ifndef SHAREMIND_LIBDATASTOREMANAGER_DATASTOREAPI_H
#define SHAREMIND_LIBDATASTOREMANAGER_DATASTOREAPI_H

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

// TODO documentation

/** Forward declarations: */
typedef void (*sharemind_datastore_destroy_fn_ptr)(void *);

struct SharemindDataStoreFactory_;
typedef struct SharemindDataStoreFactory_ SharemindDataStoreFactory;
struct SharemindDataStore_;
typedef struct SharemindDataStore_ SharemindDataStore;


/*******************************************************************************
    SharemindDataStoreFactory
*******************************************************************************/

/** Wrapper object */
struct SharemindDataStoreFactory_ {
    SharemindDataStore * (* get_datastore)(SharemindDataStoreFactory * factory, const char * name);
};


/*******************************************************************************
    SharemindDataStore
*******************************************************************************/

/** Wrapper object */
struct SharemindDataStore_ {
    void (* clear)(SharemindDataStore * datastore);
    void * (* get)(SharemindDataStore * datastore, const char * key);
    bool (* remove)(SharemindDataStore * datastore, const char * key);
    bool (* set)(SharemindDataStore * datastore, const char * key, void * value, sharemind_datastore_destroy_fn_ptr destroy);
};


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_LIBDATASTOREMANAGER_DATASTOREAPI_H */
