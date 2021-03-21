#include <stdlib.h>
unsigned long hash(char *str)
{

    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
void main()
{
    unsigned long num;
    num = hash("Hello");
    printf("%d", num);
}
