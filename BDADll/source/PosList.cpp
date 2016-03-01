// PosList.cpp: implementation of the PosList class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "PosList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PosList::PosList()
{
	head = NULL;
    tail = NULL;
}

PosList::~PosList()
{
	ListDestroyAll();
}

/*PosList* PosList::ListNew(void)
{
    PosList*	pPoslist;

    if ((pPoslist = (PosList*)malloc(sizeof(PosList))) == NULL)
        return NULL;

    pPoslist->head = NULL;
    pPoslist->tail = NULL;

    return pPoslist;
}

void PosList::ListFree(PosList* pPoslist)
{
    free(pPoslist);
}*/

int PosList::ListAppend(int x, int y)
{
    ListNode*	node;

    if ((node = (ListNode*)malloc(sizeof(ListNode))) == NULL)
        return NULL;

    node->x = x;
    node->y = y;

    node->next = NULL;
    if (tail == NULL)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
	return 1;
}

ListNode* PosList::ListRemoveHead()
{
    ListNode*	p;

	p = head;
    if (head == tail)
        head = tail = NULL;
    else
        head = head->next;

	return p;
}

int PosList::ListEmpty()
{
    return (head == NULL);
}

void PosList::ListDestroyAll()
{
    ListNode*	p;

    while (!ListEmpty())
    {
        p = head;
        ListRemoveHead();
        free(p);
    }
}
