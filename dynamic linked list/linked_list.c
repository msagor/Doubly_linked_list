
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// C linked list using pointers (google)

	
	typedef struct node {
		struct node* next;
		int key;
		int val_len;
	} node_t;
	

	node_t * head;
	node_t * fp;
	node_t * fp2;
	int memsize;
	int blksize;
	int remaining_size;
	int current_block_count;
	
	
	
	void Init(int M, int C)
	{
		head = (node_t*) malloc(M);
		fp = head;
		memsize = M;
		blksize = C;
		remaining_size = M;
		current_block_count = 0;
		
	}

	void Destroy()
	{
		free(head); //frees memory used
	}


	int Insert (int x, char* value_ptr, int value_len)
	{
		// Error checking
		if( value_len > (blksize - sizeof(node_t))) //check for insertion data too big
			printf("Error: insertion size %d too large",value_len);
		else if (current_block_count >= (memsize/blksize)) // check for full linked list
			printf("Error: linked list full");
		
		else 
		{
			//Main insert code

			
			
			if(current_block_count == 0)
			{
				fp->next = NULL; //if first node, set next to null
			}
			else
			{
				fp->next = (node_t*)((char*)fp + blksize); // if >1st node, set previous node's next to current node
				fp = (node_t*)((char*)fp + blksize);//move fp to start of current node
			}
			fp->key = x;
			fp->val_len = value_len;

			node_t* top_of_block_ptr = fp; // pointer to front of block
			++fp; //move free pointer to data area
			
			memcpy(fp, value_ptr, value_len);

			fp = top_of_block_ptr; //reset free pointer, for next allocation
			++current_block_count;

			
			
		}
		
	}

	char * Lookup(int x)
	{	
		fp2 = head;
		int i = 0;
		while(i<current_block_count)// Iterate through linked list
		{
			if (fp2->key == x) // data found, return data
				return (char*)(fp2->key);
			fp2 = (node_t*)((char*)fp2 + blksize); // check next item in list
					
			++i;
		}
		printf("value %d not found",x); // value not found, return NULL
		return NULL;
	}

	void Delete(int x)
	{
		fp2 = head;
		int i = 0;
		while(i<current_block_count)// Iterate through linked list
		{
			if( fp2->key == x)
			{
				if(current_block_count == 1) // if deletion is for first node
					head = (node_t*)((char*)fp2 + blksize); // move head right after first block
				else // deleting non-first nodes
				{
					fp2 = (node_t*)((char*)fp2 - blksize); // move fp2 to node before deleted node
					fp2->next = (node_t*)((char*)fp2 + (2*blksize)); // link node before and after deleted node
				}
					
				break;
			}

			if( i < current_block_count - 1)
				fp2 = (node_t*)((char*)fp2 + blksize);// increment node pointer
			++i;
		}

	}


	void PrintList()
	{
		fp2 = head;
		int i = 0;
		printf("\n");
		while(i < current_block_count)
		{
			
			printf("\nkey: %d\t value_length: %d", fp2->key, fp2->val_len); //print key
			if(fp2->next != NULL)		
				fp2 = fp2->next;
			
			++i;
		}
		printf("\n\n");
	}

