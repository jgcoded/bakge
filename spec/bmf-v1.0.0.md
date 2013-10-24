Bakge Mesh File v1.0.0 Specification
====================================

## Data Layout

```cpp
typedef struct
{
    char FormatName[32]; // Always BAKGEMESHFILE0000000000000000000
    union
    {
        uint32 Version;
        struct
        {
            Byte Type;
            Byte Major;
            Byte Minor;
            Byte Revision;
        };
    };
} Header;

uint32 NumVertices;

Scalar Position[3 * NumVertices];
Scalar Normal[3 * NumVertices];
Scalar TexCoord[2 * NumVertices];

uint32 NumTriangles;

uint32 Indices[3 * NumTriangles];
```
