#include "s__string_helpers.h"

long long convert_string_to_long_long(const char* string){
    long long result=0;
    int index=0;
    int continue_loop=1;
    for (;string[index] != '\0' && continue_loop; index++) 
        if (string[index] >= 48 && string[index] <= 57) 
            result = result * 10 + (string[index] - 48);
        else 
            continue_loop=0;

    return result;
}