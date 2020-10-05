#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum Node { NODE_DATA, NODE_PREV, NODE_NEXT, NODE_SIZE };
enum Data { DATA_VALUE, DATA_NULL_TERMINANT, DATA_SIZE };

// Initializes list
void StringListInit(char*** head_node, const char* str) {
	if (!*head_node) {
		*head_node = (char**)calloc(NODE_SIZE, sizeof(char*));

		size_t size_of_str = strlen(str);
		size_t size_of_str_memory = (size_of_str + DATA_NULL_TERMINANT) * sizeof(char);

		(*head_node)[NODE_DATA] = (char*)calloc(size_of_str_memory, sizeof(char));

		if (*(head_node)[NODE_DATA]) {
			memcpy((*head_node)[NODE_DATA], str, size_of_str_memory);
			(*head_node)[NODE_DATA][size_of_str] = '\0';

			(*head_node)[NODE_PREV] = NULL;
			(*head_node)[NODE_NEXT] = NULL;
		}
	}
	else {
		printf("List already initialized\n");
	}
}

// Destroy list and set pointer to NULL
void StringListDestroy(char*** head_node) {
	if (!*head_node) return;

	char** current_node = (char**)(*head_node)[NODE_NEXT];
	char** current_node_prev = (char**)current_node[NODE_PREV];

	while (current_node[NODE_NEXT]) {

		free(current_node_prev[DATA_VALUE]);
		current_node_prev[DATA_VALUE] = NULL;

		current_node_prev[NODE_NEXT] = NULL;

		free(*current_node_prev);
		current_node_prev = NULL;

		current_node = (char**)current_node[NODE_NEXT];
		current_node_prev = (char**)current_node[NODE_PREV];
	}
	free(current_node[DATA_VALUE]);
	current_node[DATA_VALUE] = NULL;

	free(*current_node);
	current_node = NULL;
}

// Insert values at the end of the list
void StringListAdd(char** head_node, const char* str) {
	if (!*head_node) {
		StringListInit(&head_node, str);
	}
	else {
		size_t list_iter = 0;
		char** current_node = head_node;
		while (current_node[NODE_NEXT]) {
			current_node = (char**)current_node[NODE_NEXT];
			++list_iter;
		}

		char** new_node = (char**)calloc(NODE_SIZE, sizeof(char*));
		char** current_node_to_realloc = (char**)realloc(current_node[NODE_NEXT], sizeof(char**));

		if (current_node_to_realloc && new_node) {
			(char**)current_node[NODE_NEXT] = current_node_to_realloc;
			current_node_to_realloc = NULL;

			(char**)current_node[NODE_NEXT] = new_node;

			for (size_t node_it = 0; node_it < NODE_SIZE; ++node_it) {
				new_node[node_it] = (char*)calloc(sizeof(char), sizeof(char));
			}

			size_t size_of_str = strlen(str);
			size_t size_of_str_memory = (size_of_str + DATA_NULL_TERMINANT) * sizeof(char);

			char* new_node_to_realloc = (char*)realloc(new_node[NODE_DATA], size_of_str_memory);

			if (new_node_to_realloc &&
				new_node[NODE_DATA] &&
				new_node[NODE_PREV] &&
				new_node[NODE_NEXT])
			{
				new_node[NODE_DATA] = new_node_to_realloc;
				new_node_to_realloc = NULL;
				memcpy(new_node[NODE_DATA], str, size_of_str_memory);
				new_node[NODE_DATA][size_of_str] = '\0';
			}

			(char**)new_node[NODE_PREV];
			current_node_to_realloc = (char**)realloc(current_node[NODE_NEXT], sizeof(char**));

			if (current_node_to_realloc) {
				(char**)new_node[NODE_PREV] = current_node_to_realloc;
				current_node_to_realloc = NULL;
				(char**)new_node[NODE_PREV] = current_node;
			}

			new_node[NODE_NEXT] = NULL;
			current_node = NULL;
		}
	}
}

// Removes occurrence of str in the list
void StringListRemove(char*** head_node, const char* str) {
	if (!*head_node) return;

	const size_t list_string_first = 0;
	const size_t list_string_last = (size_t)(StringListSize(*head_node) - 1);

	size_t list_iter = 0;
	char** current_node = *head_node;
	while (list_iter <= list_string_last && strcmp(current_node[NODE_DATA], str)) {
		current_node = (char**)current_node[NODE_NEXT];
		++list_iter;
	}

	if (list_iter > list_string_last) return;

	else if (list_string_first == list_iter) {
		char** current_node_next = (char**)current_node[NODE_NEXT];
		*head_node = current_node_next;
		current_node_next = NULL;
	}
	else if (list_string_last == list_iter) {
		char** current_node_prev = (char**)current_node[NODE_PREV];
		current_node_prev[NODE_NEXT] = NULL;
		current_node_prev = NULL;

	}
	else {
		char** current_node_prev = (char**)current_node[NODE_PREV];
		char** current_node_next = (char**)current_node[NODE_NEXT];

		(char**)current_node_prev[NODE_NEXT] = current_node_next;
		(char**)current_node_next[NODE_PREV] = current_node_prev;
	}

	free(current_node[NODE_DATA]);
	current_node[NODE_DATA] = NULL;
	current_node[NODE_PREV] = NULL;
	current_node[NODE_NEXT] = NULL;

	free(*current_node);
	current_node = NULL;
}

// Return the number of items in the list
int StringListSize(const char** head_node) {
	if (!*head_node) return 0;

	size_t list_size = 0;
	char** current_node = head_node;
	while (current_node) {
		current_node = (char**)current_node[NODE_NEXT];
		++list_size;
	}
	current_node = NULL;

	return list_size;
}

// Return the index position of the firs occurrence of str in the list
int StringListIndexOf(const char** head_node, const char* str) {
	if (!*head_node) return -1;

	size_t list_iter = 0;
	char** current_node = head_node;
	while (strcmp(current_node[NODE_DATA], str)) {
		current_node = (char**)current_node[NODE_NEXT];
		++list_iter;
	}
	current_node = NULL;

	return list_iter;
}

// Print list
void StringListPrint(const char** head_node) {
	if (!*head_node) {
		printf("\nEmpty list\n");
		return;
	}

	size_t size_of_list = StringListSize(head_node);
	char** current_node = head_node;
	for (size_t i = 0; i < size_of_list; ++i) {
		printf("%s ", current_node[NODE_DATA]);
		current_node = (char**)current_node[NODE_NEXT];
	}

	current_node = NULL;
	printf("\n");
}