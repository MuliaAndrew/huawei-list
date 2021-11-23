#ifndef ERRORS_H
#define ERRORS_H\

#define SpaceError(space, ret_code)						\
			printf("Unvalid space : %d.\nCheck existing elemets spaces", space); 	\
			ret_code

#define errprint(value) printf("%d\n", value)

#define ptr_ver(ptr) if((ptr) == nullptr) \
                        return PTR_ERROR

enum error_t
{
    FILE_ERROR   	= 1,
    NO_ERROR     	= 0,
    REMOVE_ERROR  	= 10,
    CTOR_ERROR    	= 11,
    DTOR_ERROR    	= 12,
    PUSH_ERROR   	= 13,
    RECTOR_ERROR    = 14,
    PTR_ERROR    	= 15,
    VERIF_ERROR   	= 16,
    HASH_ERROR    	= 17,
    SEQUENCE_ERROR	= 18,
    SPACE_ERROR 	= 19,
    CANARY_ERROR 	= 21,
    POP_ERROR_NUM 	= 123456
};

#endif 