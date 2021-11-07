#ifndef SL_List_h
#define SL_List_h

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "errors.h"

#ifndef DEFAULT_CAPACITY
    #define DEFAULT_CAPACITY 32
#endif

#ifndef SET_DEF_LEVEL
    #define SET_DEF_LEVEL 1
#endif

#ifndef LEFT_CANARY
    #define LEFT_CANARY 111111
#endif

#ifndef RIGHT_CANARY
    #define RIGHT_CANARY 999999
#endif

//#define DUMP(ERR)								\
//			printf("")

//-------------------------------------------------------------------

typedef double list_data_t;
typedef int canary_t;

const int CAPACITY_COEF = 30;

const bool GRAPH_ON = 1;
const bool GRAPH_OFF = 0;

enum mode
{
	PUSH,
	REMOVE
};

//-------------------------------------------------------------------

enum defence_level
{
    ONE   = 1,
    TWO   = 2
};

struct elem_t
{
	list_data_t data 	= 0;
	int next 			= 0;
	int prev 			= 0;
};

struct list_t
{
	canary_t l_canary 	= LEFT_CANARY;
	int capacity 		= DEFAULT_CAPACITY;
	int head 			= 0;
	int tail 			= 0;
	elem_t* elem 		= nullptr;
	int free_space 		= 1;
	long hash 			= 0;
	int def_level 		= (defence_level)SET_DEF_LEVEL;
	canary_t r_canary   = RIGHT_CANARY;
};

//-------------------------------------------------------------------

error_t ListCtor(list_t* list, int capacity = DEFAULT_CAPACITY, bool GRAPH = GRAPH_OFF);

error_t ListDtor(list_t* list);

error_t ListReCtor(list_t* list, bool GRAPH = GRAPH_OFF);

//-------------------------------------------------------------------

error_t ListPushAfter(list_t* list, int space, list_data_t num, bool GRAPH = GRAPH_OFF);

error_t ListPushBefore(list_t* list, int space, list_data_t num, bool GRAPH = GRAPH_OFF);

error_t ListRemove(list_t* list, int space, bool GRAPH = GRAPH_OFF);

list_data_t ListShowElem(list_t* list, int space);

list_data_t SlowListShowElem(list_t* list, int logic_space);

bool CheckElem(list_t* list, int space);

//-------------------------------------------------------------------

error_t ListSave(const char* file_name, list_t* list);

error_t ListDownload(const char* file_name, list_t* list);

//-------------------------------------------------------------------

long ListCountHash(list_t* list);

error_t ListVerificator(list_t* list, int space);

void DrowGraph(list_t* list, int space, int mode);

#endif