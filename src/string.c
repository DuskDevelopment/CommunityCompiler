static int
StringLength(char *Input)
{
    int Count = 0;
    while(Input[Count])
    {
        Count++;
    }
    return Count;
}

// true if equal
// must be null terminated
static bool
StringCompare(char *String1, char* String2)
{
    bool Result = (String1 == String2);

    if(String1 && String2)
    {
        while(*String1 && *String2 && (*String1 == *String2))
        {
            ++String1;
            ++String2;
        }

        Result = ((*String1 == 0) && (*String2 == 0));
    }

    return Result;
}

static bool
StringCompareWithLength(char *String1, char *String2, int Length)
{
    bool Result = (String1 == String2);
    int Cursor = 0;
    while(Cursor != Length)
    {
        Result = (String1[Cursor] == String2[Cursor]);
        if(!Result)
            break;
        Cursor++;
    }

    return Result;
}

static char*
StringFindNext(char *Input, char *Search, int Count)
{
    char *Result = Input;

    while(*Result)
    {
        for(int i = 0; i < Count; i++)
        {
            if(*Result == Search[i])
                return Result;
        }

        Result++;
    }

    return Result;
}

static char*
StringSubstring(char *Input, int Count)
{
    char *Result = malloc(sizeof(char) * Count + 1);
    for(int i = 0; i < Count; i++)
    {
        Result[i] = Input[i];
    }

    Result[Count] = 0;

    return Result;
}