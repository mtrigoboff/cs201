int main ()
{
    asm("   fldpi       \n"
        "   fsqrt       \n"
        "   fld1        \n"
        "   fsubrp      \n");

    return 0;
}
