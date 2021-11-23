#include <string.h>
#include "List.h"

static error_t ERR = (error_t)0;

const int NULLELEM = 0;

error_t ListCtor(list_t* list, int capacity, bool GRAPH)
{
	ptr_ver(list);

	list->capacity = capacity;

	list->elem = (elem_t*)calloc(list->capacity + 1, sizeof(elem_t)); // allocation memory for every elem in list
	ptr_ver(list->elem);

	int space = 1;

	while (space < capacity - 1)  // create the stack of free space right in list using the 'pointer' *free_space*
	{												// and field *next* of struct elem_t
		list->elem[space].next = space + 1;
		list->elem[space++].prev = -1;
	}
	list->elem[space].next = 0;
	list->elem[space].prev = -1;

	list->elem[0].data = 0; // set null list elem data, next and prev = 0
	list->elem[0].next = 0;
	list->elem[0].prev = 0;

	list->hash = ListCountHash(list);

	return NO_ERROR;
}

error_t ListPushAfter(list_t* list, int space, list_data_t num, bool GRAPH)
{
	ptr_ver(list);

	if (list->head == 0 && list->tail == 0)
	{
		int free_space = list->free_space; 

		list->free_space = list->elem[free_space].next;

		list->head = free_space;
		list->tail = free_space;

		list->elem[free_space].data = num;
		list->elem[free_space].prev = 0;
		list->elem[free_space].next = 0;

		if (list->def_level == TWO)
			list->hash = ListCountHash(list);

		if (GRAPH == GRAPH_ON)
			DrowGraph(list, space, PUSHAFTER);

		return NO_ERROR;
	}

	if (CheckElem(list, space))
	{
		if (ListVerificator(list, space))
			return ListVerificator(list, space);

		if (list->free_space == 0)
			ListReCtor(list);

		int free_space = list->free_space;

		list->free_space = list->elem[free_space].next;

		int next_space = NULLELEM;
		
		if (list->tail == space)
			list->tail = free_space;

		else
			next_space = (list->elem[space]).next;

		list->elem[free_space].next = next_space;
		list->elem[free_space].prev = space;

		list->elem[space].next = free_space;
		if (list->tail != free_space)
			list->elem[next_space].prev = free_space;

		list->elem[free_space].data = num;

		if (list->def_level == TWO)
			list->hash = ListCountHash(list);

		if (GRAPH == GRAPH_ON)
			DrowGraph(list, space, PUSHAFTER);

		return ListVerificator(list, space);
	}	
	else
	{
		SpaceError(space, return SPACE_ERROR);
	}
}

error_t ListPushBefore(list_t* list, int space, list_data_t num, bool GRAPH)
{
	ptr_ver(list);

	if (list->head == 0 && list->tail == 0)
	{
		int free_space = list->free_space; 

		list->free_space = list->elem[free_space].next;

		list->head = free_space;
		list->tail = free_space;

		list->elem[free_space].data = num;
		list->elem[free_space].prev = 0;
		list->elem[free_space].next = 0;

		if (list->def_level == TWO)
			list->hash = ListCountHash(list);

		if (GRAPH == GRAPH_ON)
			DrowGraph(list, space, PUSHBEFORE);

		return NO_ERROR;
	}
	
	if (CheckElem(list, space))
	{
		if (ListVerificator(list, space))
			return ListVerificator(list, space);;

		if (list->free_space == 0)
			ListReCtor(list);

		int free_space = list->free_space;

		list->free_space = list->elem[free_space].next;

		int prev_space = 0;

		if (list->head == space)
		{
			list->head = free_space;
			prev_space = free_space;
		}

		else
			prev_space = list->elem[space].prev;

		list->elem[free_space].next = space;
		list->elem[free_space].prev = prev_space;

		list->elem[space].prev = free_space;
		
		if (list->head != free_space)
			list->elem[prev_space].next = free_space;

		list->elem[free_space].data = num;

		if (list->def_level == TWO)
			list->hash = ListCountHash(list);

		if (GRAPH == GRAPH_ON)
			DrowGraph(list, space, PUSHBEFORE);

		return ListVerificator(list, space);
	}
	else
	{
		SpaceError(space, return SPACE_ERROR);
	}
}

error_t ListRemove(list_t* list, int space, bool GRAPH)
{
	ptr_ver(list);

	if (CheckElem(list, space))
	{
		if (ListVerificator(list, space))
			return ListVerificator(list, space);

		if (list->head == space)
		{
			int next = list->elem[space].next;

			list->elem[next].prev = NULLELEM;
			list->head = next;
		}
		else if (list->tail == space)
		{
			int prev = list->elem[space].prev;

			list->elem[prev].next = NULLELEM;
			list->tail = prev;
		}
		else
		{
			int prev = list->elem[space].prev; 
			int next = list->elem[space].next;

			list->elem[next].prev = prev;
			list->elem[prev].next = next;
		}

		list->elem[space].prev = -1;
		list->elem[space].data = 0;

		list->elem[space].next = list->free_space;
		list->free_space = space;

		if (list->def_level == TWO)
			list->hash = ListCountHash(list);

		if (GRAPH == GRAPH_ON)
			DrowGraph(list, space, REMOVE);

		return ListVerificator(list, space);
	}
	else
	{
		SpaceError(space, return SPACE_ERROR);
	}
}

error_t ListDtor(list_t* list)
{
	ptr_ver(list);

	free(list->elem);
	list->elem = nullptr;

	list = nullptr;

	return NO_ERROR;
}

error_t ListSave(const char* file_name, list_t* list)
{
	ptr_ver(list);

	FILE* f = fopen(file_name, "wb");

	error_t err = NO_ERROR;

	fprintf(f, "%d %d %d %d %ld\n\n\n", list->capacity, list->head, list->tail, list->free_space, list->hash);

	int space = 0;
	do 
	{
		err = (error_t)fprintf(f, "%lg\t\t%d\t%d\n\n", list->elem[space].data, list->elem[space].next, list->elem[space].prev);
		space++;
	}
	while (space < list->capacity);

	fclose(f);

	return err;
}

error_t ListDownload(const char* file_name, list_t* list) // head = ??? tail = ??? free_space = ???
{
	ptr_ver(list);

	FILE* f = fopen(file_name, "rb");

	error_t err = NO_ERROR;

	err = (error_t)fscanf(f, "%d %d %d %d %lg", &list->capacity, &list->head, &list->tail, &list->free_space, &list->hash);

	ListCtor(list, list->capacity);

	int space = 0;
	do 
	{
		err = (error_t)fscanf(f, "%lg %d %d", &list->elem[space].data, &list->elem[space].next, &list->elem[space].prev);
		space++;
	}
	while (space < list->capacity);
	
	if (list->def_level == TWO)
		list->hash = ListCountHash(list);

	fclose(f);

	return err;
}

long ListCountHash(list_t* list)
{
	ptr_ver(list);

    long temp_hash = 0;

    for(int space = list->head; space != 0;)
    {
    	temp_hash += list->elem[space].next;
    	temp_hash += list->elem[space].prev;
    	temp_hash += (int)list->elem[space].data;
    	temp_hash += temp_hash << 5;
    	temp_hash ^= temp_hash >> 3;
    	space = list->elem[space].next;
    }

	temp_hash += list->head;
	temp_hash += temp_hash << 5;
    temp_hash ^= temp_hash >> 3;

	temp_hash += list->tail;
	temp_hash += temp_hash << 5;
    temp_hash ^= temp_hash >> 3;

	temp_hash += list->capacity;
	temp_hash += temp_hash << 5;
    temp_hash ^= temp_hash >> 3;

	temp_hash += list->free_space;
	temp_hash += temp_hash << 5;
    temp_hash ^= temp_hash >> 3;

    return temp_hash;
}

error_t ListVerificator(list_t* list, int space)
{
	ptr_ver(list);

	int next = list->elem[space].next;
	int prev = list->elem[space].prev;

	if (list->head < 0 || list->head > list->capacity)
		return VERIF_ERROR;

	else if (list->tail < 0 || list->tail > list->capacity)
		return VERIF_ERROR;

	else if (list->l_canary != LEFT_CANARY || list->r_canary != RIGHT_CANARY)
		return CANARY_ERROR;

	else if ((space != list->elem[next].prev && next != 0) || (space != list->elem[prev].next && prev != 0))
		return SEQUENCE_ERROR;

	else if (list->def_level == TWO)
	{
		if (list->hash != ListCountHash(list))
			return HASH_ERROR;

		else
			return NO_ERROR;
	}

	else
		return NO_ERROR;
}

bool CheckElem(list_t* list, int space)
{
	ptr_ver(list);

	if (list->elem[space].prev == -1) // check this elem is not a free_space elem
		return false;

	else if (space == 0) // check this elem is not the null elem
		return false;

	else 
		return true;
}

error_t ListReCtor(list_t* list, bool GRAPH)
{
	ptr_ver(list);

	list->capacity += CAPACITY_COEF; // new capacity

	list->elem = (elem_t*)realloc(list->elem, sizeof(elem_t));

	assert(list->elem);

	int cap = list->capacity;

	list->free_space = cap - CAPACITY_COEF; 

	for (int space = cap - CAPACITY_COEF; space < cap - 1; space++) // reconstruct of free space stack
	{
		list->elem[space].next = space + 1;
		list->elem[space].prev = -1;
		list->elem[space].data = 0;
	}
	list->elem[cap - 1].next = 0; // make the last free space elem
	list->elem[cap - 1].prev = -1;
	list->elem[cap - 1].data = 0;

	list->hash = ListCountHash(list);

	return NO_ERROR;
}

list_data_t ListShowElem(list_t* list, int space)
{
	ptr_ver(list);

	if (CheckElem(list, space))
		return list->elem[space].data;

	else
		return -111111;
}

list_data_t SlowListShowElem(list_t* list, int logic_space)
{
	ptr_ver(list);

	int space = list->head;
	int iter = 1;

	printf("%d\n\n", space);

	while(CheckElem(list, space))
	{
		if (iter == logic_space)
		{
			printf("success\n");
			return list->elem[space].data;
		}

		space = list->elem[space].next;
		iter++;
	}
	printf("baaaad\n");
	return -111111;
}

void DrowGraph(list_t* list, int space, int mode)
{
	assert(list);

	FILE* graph = fopen("temp.dot","wb");

	assert(graph);

	if (mode == PUSHAFTER)
	{
		int space3 = list->elem[space].next;

		//---------------------------------------------------
		//node_space
		int space1 			= space;
		list_data_t data1 	= list->elem[space].data; 
		int next1_before 	= list->elem[space3].next;
		int next1_after 	= list->elem[space].next;
		int prev1_before 	= list->elem[space].prev;
		int prev1_after 	= list->elem[space].prev;

		//---------------------------------------------------
		//node_next
		int space2 			= next1_before;
		list_data_t data2 	= list->elem[space2].data;
		int next2_before 	= list->elem[space2].next;
		int next2_after 	= list->elem[space2].next;
		int prev2_before	= space;
		int prev2_after 	= space3;

		//---------------------------------------------------
		//node_new_next
		list_data_t data3 	= list->elem[space3].data;
		int next3 			= list->elem[space3].next;
		int prev3			= list->elem[space3].prev;

		fprintf(graph,  "digraph push {\n"
						"	graph [rankdir=\"LR\"];\n"
						"	node [shape=record];\n"
						"	struct1 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=blue];\n"
	             		"	struct2 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=blue];\n"
	             		"	struct3 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d|<f3> prev = %d\"];\n\n"
	             		"	struct1:f0 -> struct3:f3;\n"
	             		"	struct1:f2 -> struct3:f2;\n"
	             		"	struct3:f0 -> struct1:f2;\n"
	             		"	struct3:f0 -> struct2:f3;\n"
	             		"	struct1:f0 -> struct2:f3 [style=dotted];\n"
	             		"	struct2:f0 -> struct1:f2 [style=dotted];}\n",
	             		space1, data1, next1_before, next1_after, prev1_before, prev1_after,
	             		space2, data2, next2_before, next2_after, prev2_before, prev2_after,
	             		space3, data3, next3, prev3);
	}
	else if (mode == PUSHBEFORE)
	{
		int space3 = list->elem[space].prev;

		//----------------------------------------------------
		//node_prev
		int space1 = list->elem[space3].prev;
		list_data_t data1= list->elem[space1].data;
		int next1_before = list->elem[space3].next;
		int next1_after = list->elem[space1].next;
		int prev1_before = list->elem[space].prev;
		int prev1_after = list->elem[space].prev;

		//----------------------------------------------------
		//node_space
		int space2 = space;
		list_data_t data2 = list->elem[space2].data;
		int next2_before = list->elem[space2].next;
		int next2_after = list->elem[space2].next;
		int prev2_before = list->elem[space3].prev;
		int prev2_after = list->elem[space2].prev;

		//----------------------------------------------------
		//node_new_prev

		list_data_t data3 = list->elem[space3].data;
		int next3 = list->elem[space3].next;
		int prev3 = list->elem[space3].prev;

		fprintf(graph,  "digraph push {\n"
						"	graph [rankdir=\"LR\"];\n"
						"	node [shape=record];\n"
						"	struct1 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=blue];\n"
	             		"	struct2 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=blue];\n"
	             		"	struct3 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d|<f3> prev = %d\"];\n\n"
	             		"	struct2:f3 -> struct3:f3;\n"
	             		"	struct2:f0 -> struct3:f2;\n"
	             		"	struct3:f0 -> struct1:f2;\n"
	             		"	struct3:f0 -> struct2:f3;\n"
	             		"	struct1:f0 -> struct2:f3 [style=dotted];\n"
	             		"	struct2:f0 -> struct1:f2 [style=dotted];}\n",
	             		space1, data1, next1_before, next1_after, prev1_before, prev1_after,
	             		space2, data2, next2_before, next2_after, prev2_before, prev2_after,
	             		space3, data3, next3, prev3);
	}
	else if (mode == REMOVE)
	{
		//----------------------------------------------------
		//node_rm
		int space3 = space;
		list_data_t data3 = list->elem[space3].data;
		int next3 = list->elem[space3].next;
		int prev3 = list->elem[space3].prev;

		//----------------------------------------------------
		//node_next
		int space2 = list->elem[space3].next;
		list_data_t data2 = list->elem[space2].data;
		int next2_before = list->elem[space2].next;
		int next2_after = list->elem[space2].next;
		int prev2_before = list->elem[space2].prev;
		int prev2_after = list->elem[space3].prev;

		//----------------------------------------------------
		//node_prev
		int space1 = list->elem[space3].prev;
		list_data_t data1 = list->elem[space1].data;
		int next1_before = list->elem[space1].next;
		int next1_after = list->elem[space3].next;
		int prev1_before = list->elem[space3].prev;
		int prev1_after = list->elem[space3].prev;

		fprintf(graph,  "digraph remove {\n"
						"	graph [rankdir=\"LR\"];\n"
						"	node [shape=record];\n"
						"	struct1 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=green];\n"
	             		"	struct2 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d : %d|<f3> prev = %d : %d\",\n"
	             		"		fillcolor=green];\n"
	             		"	struct3 [label=\"<f0> %d|<f1> data = %lg|<f2> next = %d|<f3> prev = %d\"];\n\n"
	             		"	struct3:f3 -> struct1:f0 [style=dotted];\n"
	             		"	struct3:f2 -> struct2:f0 [style=dotted];\n"
	             		"	struct1:f2 -> struct3:f0 [style=dotted];\n"
	             		"	struct2:f3 -> struct3:f0 [style=dotted];\n"
	             		"	struct1:f2 -> struct2:f0;\n"
	             		"	struct2:f3 -> struct1:f0;}\n",
	             		space1, data1, next1_before, next1_after, prev1_before, prev1_after,
	             		space2, data2, next2_before, next2_after, prev2_before, prev2_after,
	             		space3, data3, next3, prev3);
	}
	fclose(graph);

	system("dot -Tpng -O temp.dot");
}

error_t ListDump(list_t* list, const char* file_name, error_t err)
{
	ptr_ver(list);

	FILE* dump = fopen(file_name, "wb");

	fprintf(dump,	"digraph remove {\n"
					"	graph [rankdir=\"UD\"];\n"
					"	node [shape=record];\n"
					"	struct_params [label=\"{<head> head = %d |<tail> tail = %d |<free_space> free_space = %d}\"];\n",
					list->head, list->tail, list->free_space);

	for (int space = 1; space < list->capacity; space++)
		fprintf(dump, 	"	struct_elem%d [label=\"{<space> %d |<data> data = %lg |<next> next = %d |<prev> prev = %d}\"];\n", 
						space, space, list->elem[space].data, list->elem[space].next, list->elem[space].prev);

	for (int space = list->head; space != list->tail;)
	{
		int next = list->elem[space].next;

		fprintf(dump,	"	struct_elem%d:next -> struct_elem%d:space;\n"
						"	struct_elem%d:prev -> struct_elem%d:space;\n",
						space, next, next, space);

		space = next;
	}

	for (int space = list->free_space, next = list->elem[space].next; next != 0; next = list->elem[space].next)
	{
		fprintf(dump, 	"	struct_elem%d:next -> struct_elem%d:space;\n", space, next);

		space = next;
	}

	fprintf(dump, 	"	struct_params:head -> struct_elem%d:space;\n"
					"	struct_params:tail -> struct_elem%d:space;\n"
					"	struct_params:free_space -> struct_elem%d:space;}\n",
					list->head, list->tail, list->free_space);

	fclose(dump);

	int len1 = strlen("dot -Tpng -O ");
	int len2 = strlen(file_name);

	char* cmd_msg = (char*)calloc(len1 + len2 + 2, sizeof(char));

	strcpy(cmd_msg, "dot -Tpng -O ");
	strcat(cmd_msg, file_name);
	strcat(cmd_msg, "\n");

	system(cmd_msg);

	return NO_ERROR;
}

list_data_t ListShowElem(list_t* list, space)
{
	ptr_ver(list);

	return list->elem[space].data;
}

list_data_t SlowListShowElem(list_t* list, logic_space)
{
	ptr_ver(list);

	int n = list->head;
	int iter = 0;

	while (n != logic_space && iter < list->capacity)
	{
		n = lest->elem[space].next;
		iter++;
	}

	return list->elem[n].data;
}