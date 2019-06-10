#include"LinkedList.h"


void insb(enemey *&head, enemey*&head2)
{
	enemey *temp=head;
	head=head->next;
	temp->next=head2;
	head2=temp;
}
void inse(enemey *&head, enemey *&head2)
{
	enemey *temp=head2;
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	temp->next=head;
	head=head->next;
}

void insf(enemey *&head,enemey *&head2)
{

	if(head->type==2)
	{
		insb(head,head2);
		return;
	}
	enemey *pre=head2;
	enemey *curr=head2->next;
	if(pre->arriv_time>head->arriv_time)
	{
enemey *temp=head;
head=head->next;
temp->next=pre;
head2=temp;
return;
	}
	if(pre->arriv_time<head->arriv_time && curr->arriv_time>head->arriv_time)
	{
		pre->next=head;
		enemey *temp=head;
		head=head->next;
		temp->next=curr;
		return;
	}
	while(curr!=NULL)
	{
		if(curr->arriv_time<head->arriv_time)
		{
			curr=curr->next;
			pre=pre->next;
		}
		else
		{
			pre->next=head;
			enemey *temp=head;
			head=head->next;
			temp->next=curr;
			return;
		}
	}
	}
bool insertatend(enemey*&active,enemey *p)
{

	if (active==NULL)
	{

		active=p;
		active->next=NULL;
		
		return true;
	}
	else 
	{
	enemey*ptr=active;
	while (ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	ptr->next=p;
	ptr->next->next=NULL;
	return true;
	}
}

void insert_sorted(enemey*&e ,enemey*&head) //e is alive list head is dead list
{
	if (e->arriv_time >= head->arriv_time)
	{
		insb(head,e);
		return;
	}
	insf(head,e);
}

int count(enemey *head)//counting the no of enemies of a list
{
	int c=0;
	if (head==NULL) return 0;
	enemey *current=head;
	while (current!=NULL)
	{
		c++;
		current=current->next;
	}
	return c;
}


void Sort(enemey *& pList)//sorting function 
{
	if (pList==NULL) return;
enemey * pNew = NULL;                     /* sorted list */
enemey **ppNode;                          /* ptr to ptr to node */
enemey **ppLargest;                       /* ptr to ptr to largest node */
enemey * pLargest;                        /* ptr to largest node */
    while(pList != NULL){               /* while list not empty */
        ppLargest = &pList;             /*  find largest node */
        ppNode = &((*ppLargest)->next);
        while(NULL != *ppNode){
			if((*ppNode)->priority <= (*ppLargest)->priority)
				{ppLargest = ppNode;}
            ppNode = &((*ppNode)->next);
        }
        pLargest = *ppLargest;          /* move node to new */
        *ppLargest = pLargest->next;
        pLargest->next = pNew;
        pNew = pLargest;
    }    
	pList=pNew;
}


void Sortfd(enemey *& pList)//sorting function 
{
	if (pList==NULL) return;
enemey * pNew = NULL;                     /* sorted list */
enemey **ppNode;                          /* ptr to ptr to node */
enemey **ppLargest;                       /* ptr to ptr to largest node */
enemey * pLargest;                        /* ptr to largest node */
    while(pList != NULL){               /* while list not empty */
        ppLargest = &pList;             /*  find largest node */
        ppNode = &((*ppLargest)->next);
        while(NULL != *ppNode){
			if((*ppNode)->fd <= (*ppLargest)->fd)
				{ppLargest = ppNode;}
            ppNode = &((*ppNode)->next);
        }
        pLargest = *ppLargest;          /* move node to new */
        *ppLargest = pLargest->next;
        pLargest->next = pNew;
        pNew = pLargest;
    }    
	pList=pNew;
}

void array_of_enemies(castle g ,enemey **&elist)// including the active lists in a array of enemy
{

	enemey *ptra=g.tower[0].active;
	enemey*ptrb=g.tower[1].active;
		enemey*ptrc=g.tower[2].active;
		enemey*ptrd=g.tower[3].active;
		int i=0;
	
		while(ptra!=NULL)
		{
			elist[i]=ptra;
			ptra=ptra->next;
			i++;
		}
		while(ptrb!=NULL)
		{
			elist[i]=ptrb;
			ptrb=ptrb->next;
			i++;
		}
		while(ptrc!=NULL)
		{
			elist[i]=ptrc;
			ptrc=ptrc->next;
			i++;
		}
		while(ptrd!=NULL)
		{
			elist[i]=ptrd;
			ptrd=ptrd->next;
			i++;
		}
		cout<<i-1;
}
void delete_add(enemey *&head1,enemey *&head2)//function takes a node from a list and move it to another list underspecial cases
{
	enemey *temp1=head1;
	enemey *temp2=head2;
	if (temp1==NULL) return;
	if(head1->next==NULL && head2==NULL && head1->health==0)
	{
		head2=head1;
		head1=NULL;
		return;
	}


	if(head2!=NULL)
	{
	while(temp2->next!=NULL)
	{
		temp2=temp2->next;
	
	}
	}
	enemey *pre1=head1;
	temp1=head1->next;
while(temp1!=NULL)
{
	if(temp1->health==0)
		{
			pre1->next=temp1->next;
			if(temp2==NULL)
			{
			head2=temp1;
			head2->next=NULL;
			temp1=pre1->next;
			temp2=head2;
			}
			else
			{
				temp2->next=temp1;
				temp2=temp2->next;
				temp2->next=NULL;
				temp1=pre1->next;
			}
		}
		else
		{
		temp1=temp1->next;
		pre1=pre1->next;
		}
	}


if (head1->health==0)
{
	if(head2!=NULL)
	{
	temp1=head1;
	head1=head1->next;
	temp2->next=temp1;
	temp2=temp2->next;
	temp2->next=NULL;
	}
	else
	{
		temp2=head1;
		head1=head1->next;
		temp2->next=NULL;
		head2=temp2;
	}
}
}
void DestoryList(enemey*&head) //function remove delete all nodes in the list
{  enemey*del;
while(head!=NULL)
	{
		del=head;head=head->next;
		delete del;
	}
	
}
void Destroycastle(castle&g)//delete all the castle lists 
{
	for(int i=0;i<4;i++)
	{
		DestoryList(g.tower[i].active);
	}

}
void Destroyenemies(enemey**&enemies)//destroy the array of enemies 
{
	delete[] enemies;
}

