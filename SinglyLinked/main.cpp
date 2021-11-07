#include "SL_List.h"


int main()
{
	list_t list = {};

	char f[] = "TestSave.txt";

	ListDownload(f, &list);

	ListSave("SaveTestSave.txt", &list);

	ListPushAfter(&list, 3, 22.22, GRAPH_ON);

	/* ListCtor(&list);

	int space = 0;
	double num = 0;
	scanf("%d %lg", &space, &num);

		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);

	error_t err = ListPushAfter(&list, space, num);

		errprint(err);
		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);
		printf ("%lg %d %d\n\n", list.elem[1].data, list.elem[1].next, list.elem[1].prev);

	err = ListPushAfter(&list, 1, 17.71);

		errprint(err);
		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);
		printf ("%lg %d %d\n\n", list.elem[2].data, list.elem[2].next, list.elem[2].prev);

	err = ListPushAfter(&list, 1, 17.71);

		errprint(err);
		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);
		printf ("%lg %d %d\n\n", list.elem[3].data, list.elem[3].next, list.elem[3].prev);

	err = ListPushAfter(&list, 1, 17.71);

		errprint(err);
		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);
		printf ("%lg %d %d\n\n", list.elem[4].data, list.elem[4].next, list.elem[4].prev);

	err = ListPushAfter(&list, 1, 17.71);

		errprint(err);
		printf("%d  %d  %d\n\n", list.head, list.tail, list.free_space);
		printf ("%lg %d %d\n\n", list.elem[5].data, list.elem[5].next, list.elem[5].prev);

	ListSave("TestSave.txt", &list); */

	return NO_ERROR;
}