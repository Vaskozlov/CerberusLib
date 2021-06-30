#ifndef cerbPrintTypes_h
#define cerbPrintTypes_h

#include <alloca.h>
#include <cerberus/cerberus.h>

__BEGIN_DECLS

#define POWERS_POSITVE_OFFSET 300
#define OUTPUT_ARRAY_SIZE (sizeof(uintmax_t) * 9U)

enum PrintingWays{
    BinNum      = 'b',
    OctNum      = 'o',
    HexNum      = 'x',
    HexNumBig   = 'X',
    PointNum    = 'p'
};

typedef struct PrintingParams{
    u8 negative     : 1;
    u8 minus_flag   : 1;
    u8 plus_flag    : 1;
    u8 hashtag_flag : 1;
    u8 zero_flag    : 1;
    u8 whitespace   : 1;

    unsigned width;
    unsigned precision;
} __attribute__((trivial_abi)) PrintingParams_t;

#define INIT_PRINTING_PARAMS {0, 0, 0, 0, 0, 0, 0, ~0U}

extern int (*CPutchar)(int);
extern void (*CSetColor)(u8 r, u8 g, u8 b);
extern const double PowersOf10[601];
extern char ConverterBuffer[OUTPUT_ARRAY_SIZE];

double log10(double x) __attribute__((weak));
double round(double x) __attribute__((weak));

const char *bufConvertINT       (intmax_t value,    const char printWay,    char buffer[OUTPUT_ARRAY_SIZE]);
const char *bufConvertUINT      (uintmax_t value,   const char printWay,    char buffer[OUTPUT_ARRAY_SIZE]);
const char *bufConvertFloat     (double value,      /*       NO      */     char buffer[OUTPUT_ARRAY_SIZE]);
const char *bufConvertFloatMan  (double value,      /*       NO      */     char buffer[OUTPUT_ARRAY_SIZE]);

#define ConvertINT(value, printWay)     bufConvertINT       (value, printWay,   (char*) alloca(OUTPUT_ARRAY_SIZE))
#define ConvertUINT(value, printWay)    bufConvertUINT      (value, printWay,   (char*) alloca(OUTPUT_ARRAY_SIZE))
#define ConvertFloat(value)             bufConvertFloat     (value, /*  NO  */  (char*) alloca(OUTPUT_ARRAY_SIZE))
#define ConvertFloatMan(value)          bufConvertFloatMan  (value, /*  NO  */  (char*) alloca(OUTPUT_ARRAY_SIZE))

__END_DECLS

#endif /* cerbPrintTypes_h */
