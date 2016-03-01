// PosList.h: interface for the PosList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POSLIST_H__5B31FEDD_47C8_402F_B1F0_940F123FE5FD__INCLUDED_)
#define AFX_POSLIST_H__5B31FEDD_47C8_402F_B1F0_940F123FE5FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct ListNode ListNode;
struct ListNode
{
	int			x;
	int			y;
	ListNode*	next;
};

class PosList  
{
public:
	ListNode*	head;
	ListNode*	tail;

	PosList();
	virtual ~PosList();

	int			ListAppend		(int, int);
	ListNode*	ListRemoveHead	();
	int			ListEmpty		();
	void		ListDestroyAll	();

//	PosList*	ListNew			(void);
//	void		ListFree		();
//	ListNode*	ListFirst		();
//	ListNode*	ListNext		(ListNode*);
};

#endif // !defined(AFX_POSLIST_H__5B31FEDD_47C8_402F_B1F0_940F123FE5FD__INCLUDED_)
