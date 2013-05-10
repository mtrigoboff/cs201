#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// code for the floating point formats defined in
// Bryant & O'Hallaron, section 2.4.3:
//
//  float6:
//      |sign(1)|exponent(3)|fraction(2)|
//
//  float8:
//      |sign(1)|exponent(4)|fraction(3)|
//
// exponents are biased by (2^(expBits - 1) - 1) in both cases
//
// this code is written to allow experimentation with other floating
// point formats as well.  It is called from the command line with
// the following 4 arguments:
//
//      <number of bits for exponent>
//      <number of bits for fraction>
//      <width for printing a floating point value>
//      <precision for printing a floating point value>

// arguments from the command line
static int      fractNBits;         // number of fraction bits in the float
static int      expNBits;           // number of exponent bits in the float
static int      printWidth;         // width for printing a floating point number
static int      printPrecision;     // precision for printing a floating point number

// values computed by initial setup
static int      numberNBits;        // total number of bits in this format
static int      numberHexChars;     // number of characters to print the hex representation of a number
static unsigned long nFloats;       // total number of values expressed in this format
static int      expBias;            // amount to subtract from field to get true exponent
static int      expMask;            // mask for the exponent field
                                            // (also value of an exponent that's all 1's)
static int      fractMask;          // mask for the fraction field
static int      leftBitMask;        // mask for left bit of an int

// previously printed value, used to compute difference with following value
static double           prevValue = 0.0;

// initial setup ---------------------------------------------------------------

// produce an integer whose rightmost n bits are 1
static int concatNOnes (int n)
{
    int     value = 0;
    int     i;

    // concatenate n ones
    for (i = 0; i < n; i++) {
        value <<= 1;
        value |= 1;
        }
    return value;
}

static void setup ()
{
    printf("length of type 'int' = %d\n", sizeof(int));
    printf("exponent bits: %d, fraction bits: %d\n", expNBits, fractNBits);

    numberNBits = 1 + expNBits + fractNBits;
    nFloats = pow(2.0, numberNBits);
    numberHexChars = numberNBits / 4 + (numberNBits % 4 ? 1 : 0);

    expBias = pow(2.0, expNBits - 1) - 1;

    expMask = concatNOnes(expNBits);

    fractMask = concatNOnes(fractNBits);

    leftBitMask = 1 << (sizeof(int) * 8 - 1);

    printf("numberNBits = %d, nFloats = %lu, expBias = %d, expMask = 0x%X, fractMask = 0x%x\n\n",
            numberNBits, nFloats, expBias, expMask, fractMask);
}

// extract fields of the floating point number ---------------------------------

static int signField (int n)
{
    return (n >> (expNBits + fractNBits)) & 0x01;
}

static int fractField (int n)
{
    return n & fractMask;
}

static int expField (int n)
{
    return (n >> fractNBits) & expMask;
}

static void printSpecialValue (char *value)
{
    printf("%*s\n", printWidth, value);
}

// print floating point value of the bits contained in n -----------------------
static void printValue (int n)
{
    // flags
    char        normalized = 0;

    // fields of the floating point number
    int         signBit = signField(n);
    int         expBits = expField(n);
    int         fractBits = fractField(n) << (sizeof(int) * 8 - fractNBits);
                    // shift field all the way left inside int

    int         exp;
    double      fract;
    double      value;
    int         i;

    printf("0x%-*.*X =  ", numberHexChars, numberHexChars, n);

    // break down behavior based on values of exponent, fraction
    if (expBits == 0) {                     // zero or denormalized
        if (fractBits == 0) {                   // zero
            printSpecialValue(signBit ? "-zero" : "+zero");
            prevValue = 0.0;
            return;
            }
        else {                                  // denormalized
            normalized = 0;
            exp = 1 - expBias;
            }
        }
    else if (expBits == expMask) {          // infinity or NaN
        if (fractBits == 0)
            printSpecialValue(signBit ? "-infinity" : "+infinity");
        else
            printSpecialValue(fractBits & leftBitMask ? "QNaN" : "SNaN");
                // fractBits is shifted all the way to the left
        prevValue = 0.0;
        return;
        }
    else {                                  // normalized
        normalized = 1;
        exp = expBits - expBias;
        }

    // compute fraction value, based on bits of the fraction field
    // (add appropriate power of 1/2 if a bit is present)
    {
    double      pow2 = 0.5;

    fract = 0.0;
    for (i = 0; i < fractNBits; i++) {
        if (fractBits & leftBitMask)
            fract += pow2;
        pow2 *= 0.5;
        fractBits <<= 1;
        }
    }

    // if normalized, add 1 because normalized fractions start 1.xxxx...
    // while denormalized fractions start 0.xxxx...
    if (normalized)
        fract += 1.0;

    // compute value specified by sign, fraction, exponent fields
    value = (signBit == 0 ? 1.0 : -1.0) * fract * pow(2, exp);

    // print value and difference with previous value
    if (expNBits > 4)
        printf("%*.*e %*.*e %*d %*s\n",
                printWidth, printPrecision, value,
                printWidth, printPrecision, fabs(value - prevValue),
                printWidth, exp,
                printWidth, normalized ? "" : "denorm");
    else
        printf("%*.*f %*.*f %*d %*s\n",
                printWidth, printPrecision, value,
                printWidth, printPrecision, fabs(value - prevValue),
                printWidth, exp,
                printWidth, normalized ? "" : "denorm");

    prevValue = value;
}

int main (int argc, char **argv)
{
    unsigned long   i;

    if (argc == 5) {
        expNBits = atoi(argv[1]);
        fractNBits = atoi(argv[2]);
        printWidth = atoi(argv[3]);
        printPrecision = atoi(argv[4]);
        }
    else {
        printf("required arguments:\n");
        printf("    <number of bits for exponent>\n");
        printf("    <number of bits for fraction>\n");
        printf("    <width for printing a floating point value>\n");
        printf("    <precision for printing a floating point value>\n");
        return -1;
        }

    setup();

    // print context information
    printf("%*s%*s%*s%*s%*s\n\n",
            numberHexChars + 6, "hex    ",
            printWidth, "number",
            printWidth + 1, "delta",
            printWidth + 1, "exp",
            printWidth + 1, "denorm?");

    // print the set of floating point values
    for (i = 0; i < nFloats; i++)
        printValue(i);

    printf("\n");
    return 0;
}
