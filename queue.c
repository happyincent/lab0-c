/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    /* check if malloc returns NULL */
    if (q == NULL) {
        return NULL;
    }

    /* clear allocated struct */
    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* check if the q is NULL */
    if (q == NULL) {
        return;
    }

    while (q->head) {
        list_ele_t *remove = q->head;
        q->head = q->head->next;

        /* freeing the strings */
        if (remove->value != NULL) {
            free(remove->value);
            remove->value = NULL;
        }

        /* freeing the list elements */
        free(remove);
        remove = NULL;
    }

    /* Free queue structure */
    free(q);
    q = NULL;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* check if the q is NULL */
    if (q == NULL) {
        return false;
    }

    /* allocate space for the new list element */
    list_ele_t *newh = malloc(sizeof(list_ele_t));

    /* check if malloc returns NULL */
    if (newh == NULL) {
        return false;
    }

    /* allocate space for the string */
    size_t len = strlen(s);
    newh->value = malloc((len + 1) * sizeof(char));

    /* check if malloc returns NULL */
    if (newh->value == NULL) {
        /* free the new list element */
        free(newh);
        newh = NULL;
        return false;
    }

    /* clear and set the string */
    memset(newh->value, 0, len + 1);
    memcpy(newh->value, s, len);

    /* insert head */
    newh->next = q->head;
    q->head = newh;

    /* check if tail exist */
    if (q->tail == NULL) {
        q->tail = newh;
    }

    /* increase size with 1 */
    ++(q->q_size);

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */

    /* check if the q is NULL */
    if (q == NULL) {
        return false;
    }

    /* allocate space for the new list element */
    list_ele_t *newh = malloc(sizeof(list_ele_t));

    /* check if malloc returns NULL */
    if (newh == NULL) {
        return false;
    }

    /* allocate space for the string */
    size_t len = strlen(s);
    newh->value = malloc((len + 1) * sizeof(char));

    /* check if malloc returns NULL */
    if (newh->value == NULL) {
        /* free the new list element */
        free(newh);
        newh = NULL;
        return false;
    }

    /* clear and set the string */
    memset(newh->value, 0, len + 1);
    memcpy(newh->value, s, len);

    /* insert tail */
    newh->next = NULL;
    if (q->tail != NULL) {
        q->tail->next = newh;
    }
    q->tail = newh;

    /* check if head exist */
    if (q->head == NULL) {
        q->head = newh;
    }

    /* increase queue size with 1 */
    ++(q->q_size);

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* check if the q is NULL */
    if (q == NULL) {
        return false;
    }

    list_ele_t *remove = q->head;

    /* check if the head element is NULL */
    if (remove == NULL) {
        return false;
    }

    /* copy the removed string to *sp */
    if (remove->value != NULL) {
        if (sp != NULL) {
            memset(sp, 0, bufsize);
            memcpy(sp, remove->value, bufsize - 1);
        }
        free(remove->value);
        remove->value = NULL;
    }

    /* remove and free the head element */
    q->head = remove->next;
    free(remove);
    remove = NULL;

    /* decrease queue size with 1 */
    --(q->q_size);

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    return (q == NULL) ? 0 : q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* check if q is NULL or empty */
    if (q == NULL || q->head == NULL) {
        return;
    }

    /* iterate the queue to reverse each next pointer */
    list_ele_t *left = q->head;
    list_ele_t *right = NULL;
    list_ele_t *tmp = NULL;

    q->tail = left;

    while (left != NULL) {
        tmp = left->next;
        left->next = right;
        right = left;
        left = tmp;
    }

    q->head = right;
}
