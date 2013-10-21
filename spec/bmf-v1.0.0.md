Bakge Mesh File v1.0.0 Specification
====================================

** Data Layout

```
typedef struct
{
    char FormatName[16]; // Always BAKGEMESHFILE0000000000000000000
    union
    {
        uint32 Version;
        struct
        {
            Byte Type;
            Byte Major;
            Byte Minor;
            Byte Revision;
        }
    };
} Header;

typedef struct
{
    Scalar Position[3];
} Vertex;
```
