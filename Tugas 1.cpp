#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int x;
	tnode *next;
	tnode *prev;//4
} *head, *tail, *curr;

void push_front(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		node->next = NULL;
		node->prev = NULL;//3
	}
	else
	{
		node->next = head;
		head->prev = node;//1
		head = node;
		head->prev = NULL; //2
	}
}

void push_back(int value)
{
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
		tail->prev = NULL;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		tail->next = NULL;
	}
}

void push_mid(int value, int searchKey)
{
	//create node
	struct tnode *node = (tnode*)malloc(sizeof(tnode));
	node->x = value;
	
	//checking first node
	if(head == NULL)
	{
		head = tail = node;
		tail->next = NULL;
		tail->prev = NULL;
	}
	else
	{
		struct tnode *curr = head;
		while(curr!=NULL)
		{
			if(curr->x==searchKey)
			{
				if(curr==tail)
				{
					push_back(value);
				}
				else
				{
					node->next = curr->next;
					node->prev = curr;
					curr->next = node;
					node->next->prev = node;
				}
				break;
			}
			//pindahin posisi curr jika tdk ketemu
			curr = curr->next;
		}
		if(curr==NULL)
		{
			printf("Data %d is not found\n",searchKey);
		}
	}
}

void printList()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		return;
	}
	
	//struct tnode *curr = head;
	curr=head;
	while(curr!=NULL)
	{
		printf("%d ",curr->x);
		curr = curr->next;
	}
}

void del_back()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		//return;
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head=tail=NULL;
		}
		else
		{
			struct tnode *del = head;
			while(del->next!=tail)
			{
				del = del->next;
			}
			del->next = NULL;
			free(tail);
			tail=del;
		}
	}
}

void del_front()
{
	if(head==NULL)
	{
		printf("There is no data\n");
		//return;
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head=tail=NULL;
		}
		else
		{
			struct tnode *del = head;
			head = head->next;
			head->prev=NULL;
			free(del);
		}
	}
}

void del_mid(int searchKey)
{
	if(head==NULL)
	{
		printf("There is no data\n");
		//return;
	}
	else
	{
		struct tnode *del = head;
		while(del!=NULL)
		{
			if(del->x==searchKey)
			{
				if(del==head)
				{
					del_front();
				}
				else if(del==tail)
				{
					del_back();
				}
				else
				{
					del->prev->next = del->next;
					del->next->prev = del->prev;
					free(del);
				}
				break;
			}
			del = del->next;
		}
		if(del==NULL)
		{
			printf("Data %d is not found\n",searchKey);
		}
	}
}

int main()
{
	printf("Linked List\n");
	
	push_front(2);
	push_back(3);
	push_mid(5,2);
	push_front(7);
	push_back(9);
	push_mid(11,5);

	del_back();
	del_front();
	del_mid(11);
	
	printList();getchar();
	
	return 0;
}
