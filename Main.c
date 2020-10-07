#include"list.h"

int main() {

	char** head_node = NULL;

	StringListInit(&head_node, "First");
	StringListPrint(head_node);

	StringListInit(&head_node, "Second");

	StringListAdd(head_node, "hello");	
	StringListAdd(head_node, "hello2");
	StringListAdd(head_node, "hello");
	StringListAdd(head_node, "world");
	StringListAdd(head_node, "Last");

	StringListPrint(head_node);

	printf("\n> Size of list: %d", StringListSize(head_node));
	printf("\n> Index of <hello2>: %d \n\n", StringListIndexOf(head_node, "hello2"));

	StringListPrint(head_node);

	printf("---> Remove <First> :   ");
	StringListRemove(&head_node, "First");
	StringListPrint(head_node);

	printf("---> Remove <hello2> :   ");
	StringListRemove(&head_node, "hello2");
	StringListPrint(head_node);

	printf("---> Remove <Error> :   ");
	StringListRemove(&head_node, "Error");
	StringListPrint(head_node);

	printf("---> Remove <Last> :   ");
	StringListRemove(&head_node, "Last");
	StringListPrint(head_node);

	printf("---> Replace <hello> to <bye> :   ");
	StringListReplaceInStrings(head_node, "hello", "bye");
	StringListPrint(head_node);	

	printf("---> Destroy List :   ");
	StringListDestroy(&head_node);
	StringListPrint(head_node);

	printf("\n");
	char** head_node2 = NULL;

	StringListInit(&head_node2, "b");
	StringListAdd(head_node2, "d");
	StringListAdd(head_node2, "a");
	StringListAdd(head_node2, "b");
	StringListAdd(head_node2, "c");
	StringListAdd(head_node2, "b");
	StringListAdd(head_node2, "e");
	StringListAdd(head_node2, "c");

	StringListPrint(head_node2);

	printf("---> Sorting :   ");
	StringListSort(&head_node2);
	StringListPrint(head_node2);

	printf("---> Remove Duplicates :   ");
	StringListRemoveDuplicates(head_node2);
	StringListPrint(head_node2);

	printf("---> Destroy List :   ");
	StringListDestroy(&head_node2);
	StringListPrint(head_node2);

	return 0;
}
