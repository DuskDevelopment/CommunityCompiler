typedef struct Vector
{
    int ElementSize;
    void **Elements;
    int MaxSize;
    int Location;
} Vector;

static void
PushVector(Vector *Dest, void *Value)
{
    if(Dest->Location + 1 <= Dest->MaxSize)
    {
        Dest->Elements[Dest->Location] = Value;
        Dest->Location+=1;
    }
}