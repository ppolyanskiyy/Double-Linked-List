#include"List.h"

int main() {

	char** head_node = NULL;

	StringListInit(&head_node, "First");
	StringListPrint(head_node);

	StringListInit(&head_node, "Second");
	
	StringListAdd(head_node, "hello1");
	StringListAdd(head_node, "hello2");
	StringListAdd(head_node, "hello3");
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

	/*printf("---> Replace <ll> to <ffff> :   ");
	StringListReplaceInStrings(&head_node, "ll", "ffff");
	StringListPrint(head_node);	*/

	StringListDestroy(&head_node);
	StringListPrint(head_node);

	return 0;
}
