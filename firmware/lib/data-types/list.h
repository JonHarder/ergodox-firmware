/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * An interface to a simple linked-list that can be used to implement lists,
 * queues, stacks, and things
 *
 * Prefix: `list__`
 *
 *
 * Usage notes:
 *
 * - All functions that accept an `index` set `index %= list->length` before
 *   using it.  This will make all passed indices valid.  It will also provide
 *   a convenient way to reference the last element of a list, by passing `-1`
 *   as the index (as in Python).
 *
 * - All pointers to `list__node_t` are stored, returned, etc. as as `void`
 *   pointers until use, so that using files won't have to do so much work
 *   casting things.  They are converted internally to `list__node_t` before
 *   use, and should be stored by using code in pointers of appropriate (non
 *   `void *`) type.
 *
 * - Full node types should be defined in the using '.c' or '.h' file, with
 *   something like
 *
 *       typedef struct {
 *           list__node_t _private;  // must be the first element
 *           uint8_t      data;
 *       } node_t;
 *
 * - If you want to iterate through a list, use something like
 *
 *       for (node_t * node = list->head; node; node = node->_private.next) {
 *           // do stuff
 *       }
 *
 * - If you want to insert a new node at the end of `list` (for example), use
 *   something like
 *
 *       node_t * node = list__insert(list, -1, malloc(sizeof(node_t)));
 *       if (!node) return 1;  // error
 *
 *   Keep in mind that the initialization of the data stored in the node is the
 *   calling function's responsibility.
 *
 *
 * Assumptions:
 *
 * - Lists will never contain more elements than can be indexed by an `int8_t`
 *
 *
 * TODO: go over this again, in a little while, to make sure i like it
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


#include <stdint.h>

// ----------------------------------------------------------------------------

typedef struct list__node_t {
    void * next;  // will be cast to `list__node_t` before use
} list__node_t;

typedef struct list__list_t {
    void *  head;  // will be cast to `list__node_t` before use
    void *  tail;  // will be cast to `list__node_t` before use
    uint8_t length;
} list__list_t;

// ----------------------------------------------------------------------------

list__list_t * list__new           (void);
void *         list__insert        ( list__list_t * list,
                                     int8_t         index,
                                     void *         node );
void *         list__peek          (list__list_t * list, int8_t index);
void *         list__pop_index     (list__list_t * list, int8_t index);
void *         list__pop_node      (list__list_t * list, void * node);
void *         list__pop_node_next (list__list_t * list, void * node);
void           list__free          (list__list_t * list);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__FIRMWARE__LIB__DATA_TYPES__LIST__H



// ============================================================================
// === documentation ==========================================================
// ============================================================================


// ----------------------------------------------------------------------------
// typedefs -------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === list__node_t ===
/**                                           typedefs/list__node_t/description
 * The type of a "node", for the purposes of this library
 */

// === list__list_t ===
/**                                           typedefs/list__list_t/description
 * Simple struct to define and keep track of our list
 */


// ----------------------------------------------------------------------------
// functions ------------------------------------------------------------------
// ----------------------------------------------------------------------------

// === list__new() ===
/**                                             functions/list__new/description
 * Allocate a new (empty) list
 *
 * Returns:
 * - success: A pointer to the new list
 * - failure: `NULL`
 */

// === list__insert() ===
/**                                     functions/list__insert/description
 * Insert `node` at position `index % list->length`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position the new node will occupy
 * - `node`: A pointer to the node to insert
 *
 * Returns:
 * - success: A `void *` pointer to the new node
 * - failure: `NULL`
 */

// === list__peek() ===
/**                                            functions/list__peek/description
 * Return a pointer to the node at position `index % list->length`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position of the node to peek at
 *
 * Returns:
 * - success: A `void *` pointer to the node at position `index % list->length`
 * - failure: `NULL`
 */

// === list__pop_index() ===
/**                                       functions/list__pop_index/description
 * Return a pointer to the node at position `index % list->length`, and remove
 * the node from the list
 *
 * Warnings:
 * - Does not free the node's memory - this is the calling function's
 *   responsibility.
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `index`: An `int8_t` indicating the position of the node to pop
 *
 * Returns:
 * - success: A `void *` pointer to the node at position `index % list->length`
 * - failure: `NULL`
 */

// === list__pop_node() ===
/**                                        functions/list__pop_node/description
 * Remove `node` from the list, and return a pointer to it
 *
 * Warnings:
 * - Does not free the node's memory - this is the calling function's
 *   responsibility.
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `node`: A pointer to the node to pop (and free)
 *
 * Returns:
 * - success: A `void *` pointer to `node`
 */

// === list__pop_node_next() ===
/**                                   functions/list__pop_node_next/description
 * Remove `node` from the list, free its memory, and return a pointer to the
 * next element, if the node exists
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 * - `node`: A pointer to the node to pop (and free)
 *
 * Returns:
 * - success: A `void *` pointer to the next node in the list
 * - failure: `NULL`
 */

// === list__free() ===
/**                                            functions/list__free/description
 * Free all node pointers in `list`, then free `list`
 *
 * Arguments:
 * - `list`: A pointer to the list to be operated on
 */

