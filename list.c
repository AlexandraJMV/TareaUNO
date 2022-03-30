#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * lista = (List *) malloc(sizeof(List));
	if (lista == NULL)
		exit(1);
	else
	{
		lista->head = NULL;
		lista->tail = NULL;
		lista->current = NULL;
	}
	return lista;
}

void * firstList(List * list) {
	if (list->head != NULL)
	{
		list->current = list->head;
		return list->current->data;
	}
	else
		return NULL;
}

void * nextList(List * list) {
	if (list->current == NULL)
	{
		return NULL;
	}
	else if (list->current->next == NULL)
	{
			list->current = NULL;
			return NULL;
	}
		else
		{
			list->current = list->current->next;
			return list->current->data;
		}
}

void * lastList(List * list) {
	if (list->tail == NULL)
		return NULL;
	else
	{
		list->current = list->tail;
		return list->current->data;
	}
}

void * prevList(List * list) {
	if (list->current == NULL)
	{
		return NULL;
	}
	else if (list->current->prev == NULL)
	{
		return NULL;
	}
		else
		{
			list->current = list->current->prev;
			return list->current->data;
		}
}

void pushFront(List * list, void * data) {
	Node * new_node = createNode(data);

	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
		list->current = new_node;
	}
	else
	{
		new_node->next = list->head;
		list->head->prev = new_node;
		list->head = new_node;
	}

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
	Node * new_node = createNode(data);

	if (list->current == NULL)
   {
        pushFront(list, data);
    }
	else if (list->current->next ==  NULL)
	{
	    list->tail = new_node;
		list->current->next = list->tail;
		list->tail->prev= list->current;

	}
	else
	{
		new_node->next = list->current->next;
		list->current->next->prev = new_node;
		new_node->prev = list->current;
		list->current->next = new_node;
	}
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
	Node * aux_node = list->current;

	if (list->head == list->tail)
	{
		list->head = NULL;
		list->tail = NULL;
		free(list->current);
		list->current = NULL;
	}
	else if (list->current == list->head)
		{
			list->head = list->current->next;
			list->current->next->prev = NULL;
			list->current = list->current->next;

		}
		else if (list->current == list->tail)
		{
			list->tail = list->current->prev;
			list->current->prev->next = NULL;
			list->current = list->head;
		}
			else
			{
				list->current->prev->next =  list->current->next;
				list->current->next->prev = list->current->prev;
				list->current = list->current->next;
			}

    return aux_node->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
