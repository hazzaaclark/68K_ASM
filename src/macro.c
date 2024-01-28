/* COPYRIGHT (C) HARRY CLARK 2024 */

/* MOTOROLA 68000 ASSEMBLER */

/* THIS FILE PERTAINS MORESO TOWARDS MODULARISATION OF COMPONENTS */
/* OF BEING ABLE TO REFER TO AND MAKE SPECIFIC FUNCTIONS ABOUT */
/* THE MACRO HANDLING SCHEME */

/* THESE FUNCTIONS WILL DICTATE THE PARSING AND LEXER NOTATION */
/* USED THROUGHOUT THE PROGRAM */

/* NESTED INCLUDES */

#include "assemble.h"
#include "common.h"
#include "disasm.h"

/* SYSTEM INCLUDES */

#include <stdio.h>
#include <stdlib.h>

/* TERMINATE THE MACRO BASED ON THEIR RESPECTIVE EXPRESSION */
/* THIS IS ASSUMING THAT THERE IS WHITESPACE BETWEEN THE MACRO BEING ENDED */

/* HOWEVER, IF THERE IS A REPEAT DIRECTIVE, WE CONTINUE THE COROUTINE */
/* BEFORE RECURSING OUT OF THE MACRO TO FREE UP DESIGNATED MEMORY */

STATIC
void MACRO_TERMINATE(FILE_SEMANTIC* SEMANTIC)
{
    char SYMBOL;
    struct EXPRESSION* EXP;

    /* IF THERE IS NO SYMBOL ENTRY */
    /* CREATE INITIALISE ONE UNDER THE ASSUMPTION OF */
    /* A NODE-BASED SYSTEM */

    /* THIS GOVERNS WHERE THE SYMBOL IS AS WELL AS */
    /* IT'S LENGTH AND ANY OTHER PREREQUISITIES THAT SHARE THAT SYMBOL */

    if(SEMANTIC->MNEMONIC != NULL)
    {
        if(SYMBOL != NULL)
        {
            /* CREATE A VOID STATIC CAST FOR EACH ITERATION OF THE SYMBOL MNEMOMIC */
            /* THIS IS SO THAT WE ARE ABLE TO READ AND POINTER TOWARDS EACH RESPECTIVE */
            /* INSTANCE IN THIS NODE-BASED SYSTEM */

            NODE_ENTRY* SYMBOL_NODE = (void*)(SEMANTIC, SEMANTIC->MNEMONIC, strlen(SEMANTIC->MNEMONIC));
        }

        /* CREATE THE EXPRESSION RELATIVE TO IT'S SEMANTIC VALUE */

        if(EXP != NULL)
        {
            EXP->SUB_EXP.EXP_NAME = SEMANTIC->MNEMONIC;
            EXP->NODE.HEAD = SEMANTIC->SOURCE_LINE;
            EXP->EXP_TYPE = SYMBOL_MACRO;
        }
    }
}

/* TERMINATE THE WHILE MACRO BY STORING LOCAL VARIABLES INTO THE NODE */
/* FURTHERMORE, WE EXIT THE WHILE DIRECTIVE BEFORE RECURSING INTO IT'S */
/* OTHER DEFINES - TREATING IT AS A DESIGNATED LOOP */

STATIC
void MACRO_TERMINATE_WHILE(FILE_SEMANTIC* SEMANTIC)
{
    struct EXPRESSION* EXP;
    struct NODE_ENTRY NODE;

    /* THIS NOTATION SERVES TO SHOWCASE THAT FOR EVERY SUBSEQUENT */
    /* INCLUSION OF THIS DIRECTIVE, WE WILL LOOK TO SEE IF THE EXPRESSION */
    /* CAN BE RECURSIVE */

    for(;;)
    {
        SEMANTIC->SOURCE_LINE = NODE.SOURCE_LINE;

        if(EXP->NODE.IS_EXPRESSION == false)
        {
            PRINT_SEMANTIC(SEMANTIC, "Expression must be evaluable on the first instance\n", '%x');
            break;
        }

        /* THIS ASSUMES THAT FOR EVERY CONSECUTIVE ELEMENT */
        /* IF THE VALUE OF THE NODE TREE EQUATES TO NOTHING */
        /* CEASE OPERATIONS - RECURSE BACK AROUND TO DETERMINE */
        /* THE START OF THE NODE TREE */ 

        if(NODE.VALUE == 0)
            break;

        /* NOW THAT WE HAVE RECURSED BACK AROUND TO THE START OF THE TREE */
        /* DETERMINE THE SOURCE OF THE MACRO AND EVALUATE IT'S CONDITION */

        /* IF THERE IS A EVALUABLE LINE, IT WILL CONTINUE TO PASS DOWN THE TREE */
        /* TO DETERMINE IT'S NEXT NODE TO PARSE */

        for (NODE.SOURCE_LINE = EXP->NODE.HEAD; NODE.SOURCE_LINE != NULL; NODE.SOURCE_LINE = NODE.NEXT)
        {
            ASSEMBLE_LINE(&SEMANTIC, sizeof(NODE.SOURCE_LINE));
        }
    }

    /* FREE ANY AND ALL UNECESSARY MEMORY FROM THE STACK */
    /* AFTER EXECUTION */

    free(NODE.SOURCE_LINE);
}