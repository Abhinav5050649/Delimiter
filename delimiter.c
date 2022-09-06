#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Fix seg fault being caused due to stack pointers to pairs in initialise stack

// Creating a pair
typedef struct pair
{
    char ch;
    int line_number;
} pair;

// Creating a stack of pairs
typedef struct stack
{
    pair **stackOfPairs;
    int top;
} stack;

/*
First, need to create a method to initialise stack -- Done

stack operations
1) isEmpty
2) Top
3) Push
4) Pop

*/

//"D:\Programs\CPPProject\pat.c"
void initialise_stack(stack *st); // Prototype of function to initialise stack

bool isEmpty(stack *st); // Prototype of function to check if stack is empty or not

char top(stack *st); // Prototype of function to check the topmost element in stack

void push(stack *st, pair *p); // Prototype of function to push pair of {char, int} into stack

pair *pop(stack *st); // Prototype of function to pop off the topmost element from stack and return it's pointer

int greeting(); // Welcoming message printing function prototype

char **acceptFilesFromUser(int nOfFilesToCheck); // Prototype of function to accept filenames from user

void parentheses_check(char *textOfFile); // Prottype of function to implement the delimiter functions

void closing_remarks(); // Prototype of function to print the exit message

// Main Function
int main()
{

    int nOfFilesToCheck = greeting();

    char **arrOfWordsContainingFileNames = acceptFilesFromUser(nOfFilesToCheck);

    for (int i = 0; i < nOfFilesToCheck; ++i)
    {
        char *nameOfFile = arrOfWordsContainingFileNames[i];
        FILE *file = fopen(nameOfFile, "r");

        char *textOfFile = malloc(sizeof(char) * 10000); // Assiging this much space for safety purposes
        int cnt = 0;
        while (1)
        {
            char ch = fgetc(file);
            if (ch != EOF)
            {
                textOfFile[cnt++] = ch;
            }
            else
            {
                break;
            }
        }

        parentheses_check(textOfFile);
        free(textOfFile);
        fclose(file);
    }

    free(arrOfWordsContainingFileNames);
    closing_remarks();
    return 0;
}

// Prints the greeting/welcome messages and returns an integer containing number of files which user wants to perform the operations on
int greeting()
{

    printf("\t \t Welcome to the Delimiter Checking Program! \t \t\n");
    printf("\t \t Enter number of files to check: ");
    int numberOfFilesToCheck = 0;
    scanf("%d", &numberOfFilesToCheck);

    printf("\n\n\n");
    return numberOfFilesToCheck;
}

// Function to acept filenames from user and return the array containing the names
char **acceptFilesFromUser(int nOfFilesToCheck)
{

    char **storeFileNames = malloc(sizeof(char *) * 100);
    for (int i = 0; i < nOfFilesToCheck; ++i)
    {
        char *name = malloc(sizeof(char) * 100);
        printf("Enter name of file %d (with extension along with path for better precision): ", (i + 1));
        scanf("%s", name);
        storeFileNames[i] = name;
    }

    return storeFileNames;
}

// Function to implement delimiter in file
// Logic --> Check for pairs of {}, [], (). If pairs not found, print them on terminal
void parentheses_check(char *textOfFile)
{
    // Need to hard code pairs -- Done
    // While returning pairs from pop function, be sure to check if they are null
    // or not

    int lenOfInputText = strlen(textOfFile);
    stack *st;
    initialise_stack(st);

    int lnNumber = 1;

    for (int i = 0; i < lenOfInputText; ++i)
    {

        char symboll = textOfFile[i];
        pair *p;
        switch (symboll)
        {
        case '{':
        case '(':
        case '[':
            p = malloc(sizeof(pair));
            p->ch = symboll;
            p->line_number = lnNumber;
            push(st, p);
            break;
        case ')':
        case '}':
        case ']':
            p = pop(st);
            if (p != NULL)
                free(p);
            break;
        case '\n':
            ++lnNumber;
            break;
        default:
            break;
        }
    }

    while (!isEmpty(st))
    {
        pair *p = pop(st);
        printf("The unpaired character is %c, present at line %d of file!\n", p->ch, p->line_number);
        free(p);
    }
}

// Checks if stack is empty or not
bool isEmpty(stack *st)
{

    if (st->top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Initialises stack struct
void initialise_stack(stack *st)
{

    // Creating stack array to be capable of holding 1000 pairs of chars and
    // integers
    st->stackOfPairs = malloc(sizeof(pair *) * 1000);
    st->top = -1;
    return;
}

// Returns character present in topmost pair of char and int from stack
char top(stack *st)
{
    if (isEmpty(st))
    {
        return '\0';
    }
    else
    {
        pair *p = st->stackOfPairs[st->top];
        char chaAtTop = p->ch;
        return chaAtTop;
    }
}

// Function to push pairs of {char, int} into stack
void push(stack *st, pair *p)
{
    if (st->top > 1000)
    {
        printf("Stack overflow!\n");
        return;
    }
    else
    {
        st->stackOfPairs[++st->top] = p;
        return;
    }
}

// Function to pop off topmost pair from stack and return pointer to that pair
pair *pop(stack *st)
{
    if (isEmpty(st))
    {
        printf("Sack underflow!\n");
        return NULL;
    }
    else
    {
        pair *p = st->stackOfPairs[st->top--];
        return p;
    }
}

// Function to print exit statements
void closing_remarks()
{
    printf("\t \t Thank you for using the Delimiter Checker Program! \t \t\n");
    printf("\t \t Exiting Program \t \t\n");
    return;
}