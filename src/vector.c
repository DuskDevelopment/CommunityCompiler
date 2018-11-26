typedef struct vector
{
    int ElementSize;
    void **Elements;
    int MaxSize;
    int size;
} vector;

static void
PushVector(vector *Dest, void *Value)
{
    if(Dest->size + 1 <= Dest->MaxSize)
    {
        Dest->Elements[Dest->size] = Value;
        Dest->size+=1;
    }
}