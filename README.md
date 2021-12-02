# Data Structures

Vector, Uniform Container, Stack and Queue was in an another repo. I decided to merge
two repos together.

List struct is my attempt to replicate polymorphism in C. The main goal is providing safe
operations for these data structures. This method ensures that you cannot use other data 
structures functions with another function. Furthermore storing different types of data in 
those data structures is tricky. There is no generic type in C therefore replicating this
behaviour requires void pointers. However void pointers are risky to use because their type
is unknown. User of this library could send incompatible data to these data structures. 
This is something that user has to handle.

I've also remade my old homeworks with this implementation in order to test the codes.

---
## Using list struct to implement other data structures

***To be written***

---
## Using list struct

User has to provide 3 operations for that data structure and those are;
* Node - Node Compare
* Node - Key Compare
* Node Free

Node free operation is always optional. If you keep track the memory in your main code, then
it is not necessary to provide a free operation for node_handler function.

An example:

```c
typedef struct {
    char key[CHAR_LENGTH];
    int freq;
    int index;
} node;

int node_handler(const void *n1, const void *n2, int op) {
    switch (op) {
        case NODE_NODE_COMPARE:
            return strcasecmp(((node*)n1)->key, ((node*)n2)->key);
        case NODE_KEY_COMPARE:
            return strcasecmp(((node*)n1)->key, n2);
        default:
            return 0;
    }
}
```