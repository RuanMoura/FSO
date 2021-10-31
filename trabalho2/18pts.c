#include <stdio.h>
#include <stdlib.h>
#define MAX_ROWS 100000

typedef struct FILA
{
    int n;
    struct FILA *prev;
    struct FILA *next;
} fila;

int page_fault = 0;

fila *verif(fila *, int, int);
fila *insert(fila *, int);
void clear_frames(fila *, int);
int belady(int *, int *, int);

int main()
{
    int n, p, i, j;
    int used_frames[MAX_ROWS];
    int page_faults[MAX_ROWS];
    int *entry;
    fila *frames = NULL;

    // init entries
    scanf("%d", &n);
    entry = (int *)malloc(sizeof(int) * n);

    // read entries
    for (i = 0; i < n; i++)
        scanf("%d", &entry[i]);

    // create fila
    for (i = 0; i < 100000; i++)
        frames = insert(frames, -1);
    fila *node;
    for (node = frames; node->next != NULL; node = node->next);
    node->next = frames;
    frames->prev = node;

    j = 0;
    while (scanf("%d", &p) == 1)
    {
        clear_frames(frames, p);
        page_fault = 0;
        for (i = 0; i < n; i++)
            frames = verif(frames, entry[i], p);
        printf("%d %d\n", p, page_fault);
        used_frames[j] = p;
        page_faults[j] = page_fault;
        j++;
    }

    if(belady(used_frames, page_faults, j))
        printf("Belady detectado\n");
    else
        printf("Sem anomalia\n");

    return 0;
}

fila *verif(fila *init, int n, int p)
{
    fila *node;
    int i;
    for(node=init, i=0; i<p; node=node->next, i++)
    {
        if(n == node->n)
            return init;
    }
    page_fault++;
    init->prev->n = n;
    return init->prev;
}

fila *insert(fila *init, int n)
{
    fila *node;
    node = (fila *)malloc(sizeof(fila));
    node->n = n;
    node->prev = NULL;
    node->next = init;
    if(init != NULL)
    {
        init->prev = node;
    }
    return node;
}

void clear_frames(fila *init, int p)
{
    fila *aux;
    int i = 0;
    for (aux = init; aux != NULL && i < p; aux = aux->next, i++)
        aux->n = -1;
}

int belady(int *used_frames, int *page_faults, int limit){
    int i, j;
    
    for(i=0; i<limit; i++)
    {
        for(j=i+1; j<limit; j++)
        {
            if(used_frames[i] < used_frames[j] && page_faults[i] < page_faults[j])
            {
                return 1;
            }
        }
    }

    return 0;
}
