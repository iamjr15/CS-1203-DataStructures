#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>

/* ************************************************************************
Main Function for Testing
 ************************************************************************ */

int main(){
	int i,M;
	struct skipList *slst1, *slst2;
	
	
	 srand ( time(NULL) );
	
        /* allocate memory to the pointers of Skip List */
	slst1=(struct skipList *)malloc(sizeof(struct skipList));  
    slst2=(struct skipList *)malloc(sizeof(struct skipList));  
	assert(slst1); assert(slst2);

	
	/*  Initialize the two skip lists */
	initSkipList(slst1); 
    initSkipList(slst2);  

	/*  Add to the skip list  M = 20 random integers in [0,100] */
	M=20;
	for(i=0;i<M;i++) addSkipList(slst1, rand()%101);
    for(i=0;i<M;i++) addSkipList(slst2, rand()%101);
	
	/*  Print out the skip list 
            in the breadth-first order, starting from top. 
	    In printing, move to a new printing line every time
            the end of the current level is reached.
	    E.g., the print out of a skip list 
            with 5 elements should look like
	 
	    7
	    7 14 29
	    3 7 9 14 20
	 
	 */
    
	printf("\nPrinting of Skip List 1 started ... \n");
	printSkipList(slst1);
	printf("Printing of Skip List 1 finished. \n\n\n");

	printf("\nPrinting of Skip List 2 started ... \n");
	printSkipList(slst2);
	printf("Printing of Skip List 2 finished. \n\n\n");
	
    
	/* DIFFERENCE AND MERGING */
    
    printf("TESTING DIFFERENCE \n");
	printf("Adding the same numbers to both skip lists: 200-205 \n");
	
	for(i=200; i<=205; i++) {
           addSkipList(slst1, i); 
           addSkipList(slst2, i);
	}

	
    diffSkipList(slst1, slst2);

    printf("\nPrinting of Skip List 1 after difference started ... \n");
	printSkipList(slst1);
	printf("Printing of Skip List 1 after difference finished. \n\n\n");
	printf("\nPrinting of Skip List 2 started ... \n");
	printSkipList(slst2);
	printf("Printing of Skip List 2 finished. \n\n\n");


    printf("TESTING MERGING \n");
    mergeSkipList(slst1, slst2);

    printf("\nPrinting of Skip List 1 after merging started ... \n");
	printSkipList(slst1);
	printf("Printing of Skip List 1 after merging finished. \n\n");
	
	printf("Attempting to print slst2 would cause and assertion error because it has been freed from memory.\n\n\n");


	
    printf("TESTING CONTAINS \n");
	for(i=200; i<=205; i++)
	printf("\n%d %s in the list!.\n",i,containsSkipList(slst1, i)==1?"IS":"IS NOT");

        printf("TESTING REMOVE \n");
	printf("\nRemoving 200,202 and 205 from Skip List 1 started ... \n");
	removeSkipList(slst1, 200);
	removeSkipList(slst1, 202);
	removeSkipList(slst1, 205);

	printf("\nPrinting of Skip List 1 after removing started ...\n");
	printSkipList(slst1);
	printf("\nRemoving 200,202 and 205 from Skip list 1 finished ... \n\n\n");


	for(i=200; i<=205; i++)
	printf("\n%d %s in the list!.\n",i,containsSkipList(slst1, i)==1?"IS":"IS NOT");
	


	printf("Freeing first list. Removing all values then all sentinels.\n");
	struct skipLink *bottomList;
	bottomList = slst1->topSentinel;
	while(bottomList->down){
		bottomList = bottomList->down;
	}
	struct skipLink *current, *temp;
	current = bottomList->next;
	while(current){
		temp = current;
		current = current->next;
		removeSkipList(slst1, temp->value);
	}

	current = slst1->topSentinel;
	temp = current->down;
	while(temp){
		current->down = temp->down;
		free(temp);
		temp = current->down;
	}
	free(slst1->topSentinel);
	free(slst1);

   return 0;

}


/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function: */
int flipSkipLink(void)
{
	return rand() % 2; 	
}

/* Move to the right as long as the next element is smaller than the input value: */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	return current;
}


/* Create a new skip link for a value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	return tmp;
}


/* Add a new skip link recursively */
struct skipLink* skipLinkAdd(struct skipLink * current, TYPE e) {
	struct skipLink *new, *down;
	new =0;
	assert(current);
	if(current->down==NULL){
		new = newSkipLink(e, current->next, NULL);
		current->next = new;
		
	}
	else{
		down = skipLinkAdd(slideRightSkipList(current->down, e), e);
		if(down&& flipSkipLink()){
			new = newSkipLink(e, current->next, down);
			current->next = new;
		}
	}
	return new;
}


/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list: */
void initSkipList (struct skipList *slst) 
{
	slst->size=0;
	slst->topSentinel=(struct skipLink * )malloc(sizeof(struct skipLink));
	assert(slst->topSentinel);
	slst->topSentinel->next=NULL;
	slst->topSentinel->down=NULL;
}

/* Checks if an element is in the skip list: */
int containsSkipList(struct skipList *slst, TYPE e)
{
	assert(slst);
	struct skipLink *current, *down;
	current = slideRightSkipList(slst->topSentinel, e);
	down = current->down;
	while(down){
		current = slideRightSkipList(current->down, e);
		if(current->next && EQ(current->next->value, e)){
			return 1;
		}
		down = current->down;
	}
	return 0;
}


/* Remove an element from the skip list: */
void removeSkipList(struct skipList *slst, TYPE e)
{
	assert(slst);
	struct skipLink *current, *temp;
	current = slst->topSentinel;
	while(current){
		current = slideRightSkipList(current, e);
		if(current->next != NULL && EQ(current->next->value, e)){
			temp = current->next;
			current->next = current->next->next;

			free(temp);
			if(current->down ==NULL){
				slst->size--;
			}
		}
		current = current->down;
	}
}




/* Add a new element to the skip list: */
void addSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *downLink, *newLink;
	downLink = skipLinkAdd(slideRightSkipList(slst->topSentinel, e),e);
	if(downLink && flipSkipLink()){
		newLink = newSkipLink(e, NULL, downLink);
		slst->topSentinel = newSkipLink(0, newLink, slst->topSentinel);
	}
	slst->size++;

}

/* Find the number of elements in the skip list: */
int sizeSkipList(struct skipList *slst){
	
	return slst->size;
	
}


/* Print the links in the skip list: */
void printSkipList(struct skipList *slst)
{	
	assert(slst);
	assert(slst->size);
	struct skipLink *currentList;
	struct skipLink *currentlink;
	TYPE val;
	currentList = slst->topSentinel;
	while(currentList){
		currentlink = currentList->next;
		while(currentlink){
			val = currentlink->value;
			printf("%.1f\t", val );
			currentlink = currentlink->next; 
		}
		currentList = currentList->down;
		
		printf("\n");
	}

}


/* Merge two skip lists, by adding elements of skip list 2 to skip list 1 
 that are not already contained in skip list 1. 
 The function should also remove the entire skip list 2 from the memory.*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)
{
	assert(slst1);
	assert(slst2);
	assert(slst1->size);
	assert(slst2->size);
	struct skipLink *bottomList;
	bottomList = slst2->topSentinel;
	while(bottomList->down){
		bottomList = bottomList->down;
	}
	struct skipLink *current, *temp;
	current = bottomList->next;
	while(current){
		if(!containsSkipList(slst1, current->value)){
			addSkipList(slst1, current->value);
		}
		temp = current;
		current = current->next;
		removeSkipList(slst2, temp->value);
	}
	current = slst2->topSentinel;
	temp = current->down;
	while(temp){
		current->down = temp->down;
		free(temp);
		temp = current->down;
	}
	free(slst2->topSentinel);
	free(slst2);

		
}
	


/* Find a difference of two skip lists 
   by removing elements of skip list 2 from skip list 1. */

	/*assumed slst2 should remain unchanged */
void diffSkipList(struct skipList *slst1, struct skipList *slst2)
{
	assert(slst1);
	assert(slst2);
	assert(slst1->size);
	assert(slst2->size);
	struct skipLink *bottomList;
	bottomList = slst2->topSentinel;
	while(bottomList->down){
		bottomList = bottomList->down;
	}
	struct skipLink *current;
	current = bottomList->next;
	while(current){
		removeSkipList(slst1, current->value);
		current = current->next;
	}

		
	
} /* end of the function */
