
/* *
 * Test various types in Bakge here.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>


int main(int argc, char* argv[])
{
    bakge::Byte* Contents;

    bakge::Init(argc, argv);

    if(argc < 2) {
        printf("Usage ./loadfile [FILEPATH]\n");
        bakge::Deinit();
        return 1;
    } else {
        Contents = bakge::LoadFileContents(argv[1]);
        if(Contents == NULL) {
            printf("Error loading file %s\n", argv[1]);
        } else {
            printf("Loaded file %s\n%s\n", argv[1], Contents);
            delete Contents;
        }
    }

    bakge::Deinit();

    return 0;
}
