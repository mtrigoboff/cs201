// demo of GCC inline assembler and various data movement instructions

char    charArray[] =    {0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
int        intArray[] =  {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int main (int argc, char **argv)
{
    int         localVar =  0x12345678;
    double      fpVar =     16.0;

    // embedded assembly language
    asm("        mov      $0x89ABCDEF, %%eax          \n"
        "        mov      $0xFF, %%bl                 \n"
        "        movsx    %%bl, %%eax                 \n"
        "        movzx    %%bl, %%eax                 \n"

        // two instructions in one asm statement
        // (not a good idea, but interesting that you can do this)
        "        mov     $0x12, %%al     \n        mov     $0x34, %%ah\n"

        // swapping two values
        "        mov     $0xBBBBBBBB, %%ebx           \n"
        "        mov     $0xAAAAAAAA, %%eax           \n"
        "        xchg    %%ebx, %%eax                 \n"

        // extended asm
        "        mov     %[localVarIn], %%eax         \n" // store localVar into eax
        "        mov     $4, %%ecx                    \n" // load register
        "        add     %%ecx, %[localVarOut]        \n" // add register to localVar

        // int array
        "        lea     %[intArray], %%ebx           \n" // load address of start of array
        "        mov     (%%ebx), %%eax               \n" // get first element of array
        "        mov     (%%ebx, %%ecx, 4), %%eax     \n" // get indexed element of array

        // char array
        "        mov     $0, %%eax                    \n" // clear eax
        "        lea     %[charArray], %%ebx          \n" // load address of start of array
        "        mov     (%%ebx), %%al                \n" // get first element of array
        "        mov     (%%ebx, %%ecx, 1), %%al      \n" // get indexed element of array

        // conditional statement
        "        cmp     $3, %[localVarIn]            \n" // comparison operation
        "        jg      gt                           \n" // conditional jump if > 3
        "        nop                                  \n" // didn't jump
        "gt:     nop                                  \n" // conditional jump target

        // floating point load, store
        "        fldl    %[fpVarIn]                   \n" // load fpVar onto floating point stack
        "        fld     %%st                         \n" // duplicate value on top of fp stack
        "        faddp                                \n" // add the two values on the fp stack
        "        fstpl   %[fpVarOut]                  \n" // store the sum back into fpVar

        : [localVarOut]    "=m"    (localVar),     // outputs
          [fpVarOut]       "=m"    (fpVar)
        : [localVarIn]     "m"     (localVar),     // inputs
          [intArray]       "m"     (intArray[0]),
          [charArray]      "m"     (charArray[0]),
          [fpVarIn]        "m"     (fpVar)
        : "eax", "ebx", "ecx"                      // clobbers
    );

    return 0;
}
