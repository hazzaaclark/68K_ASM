/* COPYRIGHT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 ASSEMBLER */

/* THIS FILE FOCUSSES ON THE DICTONARY ENTIRES PERTAINING TOWARDS IDENTIFIERS */
/* AND DIRECTIVES IN RELATION TO 68K ASSEMBLY */

/* NESTED INCLUDES */

#include "dictionary.h"

#undef USE_DICTIONARY

/* INITIALISE THE DICTIONARY HASH TABLE ENTRY SET */
/* DETERMINE THE ALLOCATABLE SIZE OF RESPECTIVE HASH TABLE ENTRIES */

/* CREATED A TREE SYSTEM TO STORE THE CORRESPONDING IDENTIFIER */
/* IN RELATION TO WHICH SEMANTIC IS BEING PARSED */

bool DICTIONARY_INIT(struct DICTIONARY_ENTRY* ENTRY)
{
    ENTRY->ENTRY_SUCCESS = true;

    /* FIRST DETERMINE THE ALLOCATABLE SPACE FOR THE HASH TABLE */
    /* TO STORE ALL PRE-REQUISITIES */

    ENTRY->HASH_TABLE = (void*)malloc(DICT_HASH_TABLE_ENTRIES * sizeof(*ENTRY->HASH_TABLE));

    if(ENTRY->HASH_TABLE == NULL)
        ENTRY->ENTRY_SUCCESS = false;
        return false;

    /* ALLOCATE THAT CORRESPONDING SPACE INTO THE RESPECTIVE ENTRY */
    /* THIS IS BY CASTING A POINTER TO DETERMINE THE OFFSET OF THE SYMBOL */
    /* BASED ON HASH TABLE ENTRIES */

    memset(ENTRY->HASH_TABLE, 0, sizeof(*ENTRY->HASH_TABLE) * DICT_HASH_TABLE_ENTRIES);

    COMPARE_IDENTIFIERS = ENTRY->HASH_CASES ? 0 : memcmp;

    return ENTRY->ENTRY_SUCCESS;
}

void DICTIONARY_FREE(void)
{
    struct DICTIONARY_ENTRY* ENTRY;

    /* FOR EVERY ADDRESSABLE HASH TABLE INDENTATION IN RELATION TO THE MAX AMOUNT */
    /* DETERMINE IF THE TABLE IS STILL BEING USED, OTHERWISE, FREE THE STACK */

    for (ENTRY = &(ENTRY->HASH_TABLE[0]); ENTRY < &(ENTRY->HASH_TABLE[DICT_HASH_TABLE_ENTRIES]); ENTRY++)
    {
        while(ENTRY != NULL)
            free(ENTRY);
    }

    free(ENTRY->HASH_TABLE);
}

/* CREATE AN INTIIAL ENTRY FOR THE SYMBOL BY WHICH THE LOOKUP TABLE IS TRYING TO ACCESS */
/* IN DOING SO, CREATE ALLOCATABLE SPACE WITHIN THE HASH TABLE FOR THE NEW ENTRY */

void DICTIONARY_CREATE_DIRECTIVE(struct DICTIONARY_ENTRY* ENTRY, const char* IDENTIFIER, UNK IDENTIFIER_LENGTH)
{
    /* ASSUME THAT AN ARBITRARY SEARCH VALUE DICTATES THE STATUS OF THE DIRECTIVE */
    /* IF THE SEARCH RESULT FINDS A CORRESPONDING DIRECTIVE, THE OFFSET POINTER WILL READ THIS */

    UINT* SEARCH_RESULT;

    /* IF THE SEARCH RESULT FINDS THE DIRECTIVE */
    /* SET THE READER TO THE ADDRESS OF THE PARENT OF THE NODE TREE */

    if(*SEARCH_RESULT == DICT_SEARCH_FOUND)
    {
        if(ENTRY->OFFSET != NULL)
            ENTRY->OFFSET = &(ENTRY->PARENT); 
    }

    /* OTHERWISE, CREATE THE MISSING NODES REQUIRED FOR THE SYMBOL */

    else
    {
        DICTIONARY_ENTRY* NEW_ENTRY = (DICTIONARY_ENTRY*)malloc(sizeof(ENTRY) - 1 + IDENTIFIER_LENGTH); 

        if(NEW_ENTRY == NULL)
            ENTRY->ENTRY_SUCCESS = false;

        else
            NEW_ENTRY->PARENT = NULL;
            NEW_ENTRY->LEFT = NULL;
            NEW_ENTRY->RIGHT = NULL;

            NEW_ENTRY->NEXT = NULL;
            NEW_ENTRY->PREVIOUS = NULL;
            NEW_ENTRY->TYPE =  -1;

            NEW_ENTRY->IDENTIFIER_LENGTH = IDENTIFIER_LENGTH;

            if(ENTRY->OFFSET != NULL)
                ENTRY->OFFSET = &NEW_ENTRY->PARENT;
    }
}

/* NOW WE CAN ACTUALLY BEGIN TO ADD CORRESPONDING ENTRIES TO THE HASH TABLE */
/* THIS IS BY ASSUMING THE APPROPRIATE IDENTIFIER LENGTH AND ADDING THE EVALUATION TO THE DICTIONARY */

DICTIONARY_ENTRY* DICTIONARY_LOOKUP(struct FILE_SEMANTIC* FILE_STATE, const char* IDENTIFIER, UNK IDENTIFIER_LENGTH)
{
    /* FIRST DETERMINE IF THE CORESPONDING SYMBOL IS WHAT WE ARE LOOKING FOR IN ACCORDANCE WITH IT'S LENGTH */

    char* EXPECTED = DICTIONARY_IDENTIFIER(FILE_STATE, IDENTIFIER, IDENTIFIER_LENGTH);
    UNK EXPECTED_LENGTH;

    /* IF IT DOES EXIST, EVALUATE IT'S LENGTH AND ACCOMODATE FOR A NEW ENTRY */

    if(EXPECTED != NULL)
    {
        IDENTIFIER = EXPECTED;
        IDENTIFIER_LENGTH = EXPECTED_LENGTH;
    }

    DICTIONARY_ENTRY* ENTRY_LOOKUP = (void*)malloc(sizeof(DICTIONARY_ENTRY) + (*IDENTIFIER) * IDENTIFIER_LENGTH);

    free(EXPECTED);

    return ENTRY_LOOKUP;
}
