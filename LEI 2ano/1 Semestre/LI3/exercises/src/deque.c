#include "deque.h"
#include <stdlib.h>
#include <stdio.h>


Deque* create() {
    Deque* deque = malloc(sizeof(Deque));
    deque->size = 0;
    deque->first = NULL;
    deque->last = NULL;
    deque->reversed = false;
    return deque;
}


static void _push(Deque* deque, void* data) {
    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->prev = deque->last;
    new->next = NULL;
    deque->last = new;
    /* if it was empty before, also set the first pointer */
    if (deque->size == 0) {
        deque->first = new;
    } 
    /* otherwise update the previous last */
    else {
        new->prev->next = new;
    }
    deque->size++;
}


static void _pushFront(Deque* deque, void* data) {
    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->next = deque->first;
    new->prev = NULL;
    deque->first = new;
    /* if it was empty before, also set the last pointer */
    if (deque->size == 0) {
        deque->last = new;
    } 
    /* otherwise update the previous last */
    else {
        new->next->prev = new;
    }
    deque->size++;
}


static void* _pop(Deque* deque) {
    if (deque->size == 0) {
        return NULL;
    }

    Node* last = deque->last;
    void* lastData = last->data;
    deque->last = last->prev;
    /* if there is only one element, set the first pointer to NULL */
    if (deque->size == 1) {
        deque->first = NULL;
    }
    /* otherwise, update the new last element  */
    else {
        deque->last->next = NULL;
    }
    deque->size--;
    free(last);
    return lastData;
}


static void* _popFront(Deque* deque) {
    if (deque->size == 0) {
        return NULL;
    }

    Node* first = deque->first;
    void* firstData = first->data;
    deque->first = first->next;
    /* if there is only one element, set the last pointer to NULL */
    if (deque->size == 1) {
        deque->last = NULL;
    }
    /* otherwise, update the new first element  */
    else {
        deque->first->prev = NULL;
    }
    deque->size--;
    free(first);
    return firstData;
}


void push(Deque* deque, void* data) {
    if (!deque->reversed) {
        _push(deque, data);
    }
    else {
        _pushFront(deque, data);
    }
}


void pushFront(Deque* deque, void* data) {
    if (!deque->reversed) {
        _pushFront(deque, data);
    }
    else {
        _push(deque, data);
    }
}


void* pop(Deque* deque) {
    if (!deque->reversed) {
        return _pop(deque);
    }
    else {
        return _popFront(deque);
    }
}


void* popFront(Deque* deque) {
    if (!deque->reversed) {
        return _popFront(deque);
    }
    else {
        return _pop(deque);
    }
}


int size(Deque* deque) {
    return deque->size;
}


bool isEmpty(Deque* deque) {
    return !deque->size;
}


/* Reverse the deque in constant time.
Here, we invert the reverse flag. When iterating, (e.g., printDeque): 
    if reversed, we do first -> prev -> prev -> ... -> last;
    else, we do last -> next -> next -> ... -> first.
Additionally, we invert the inserts/removes orders:
    if reversed, we do popFront when pop is called, and vice versa;
    if reversed, we do pushFront when push is called, and vice versa.
*/
void reverse(Deque* deque) {
    deque->reversed = !deque->reversed;
}


void printDeque(Deque* deque, void(*printFunc)(void*)) {
    Node* n = !deque->reversed ? deque->first : deque->last;
    
    printf("[");
    while (n) {
        printFunc(n->data);
        n = !deque->reversed ? n->next : n->prev;
        if (n) {
            printf(" -> ");
        }
    }
    printf("]\n");
}


void destroy(Deque* deque) {
    Node* cur = deque->first;

    while (cur) {
        Node* n = cur;
        cur = n->next;    
        free(n);
    }

    free(deque);
}
