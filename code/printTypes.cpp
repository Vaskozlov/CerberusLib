#include <float.h>
#include <cerberus/cerbMath.h>
#include <cerberus/printTypes.h>

__BEGIN_DECLS

#define isinf(x) __builtin_isinf (x)
#define isnan(x) __builtin_isnan (x)

#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif

static const double toint = 1/EPS;

#ifndef fp_force_evalf
#define fp_force_evalf fp_force_evalf
static inline void fp_force_evalf(float x)
{
	volatile float y;
	y = x;
}
#endif

#ifndef fp_force_eval
#define fp_force_eval fp_force_eval
static inline void fp_force_eval(double x)
{
	volatile double y;
	y = x;
}
#endif

#ifndef fp_force_evall
#define fp_force_evall fp_force_evall
static inline void fp_force_evall(long double x)
{
	volatile long double y;
	y = x;
}
#endif

#define FORCE_EVAL(x) do {                        \
	if (sizeof(x) == sizeof(float)) {         \
		fp_force_evalf(x);                \
	} else if (sizeof(x) == sizeof(double)) { \
		fp_force_eval(x);                 \
	} else {                                  \
		fp_force_evall(x);                \
	}                                         \
} while(0)

enum PrintingSizes{
    SIZE_DEFAULT    = 0,
    SIZE_h          = 1,
    SIZE_hh         = 2,
    SIZE_l          = 3,
    SIZE_ll         = 4,
    SIZE_j          = 5,
    SIZE_z          = 6,
    SIZE_t          = 7,
    SIZE_L          = 8
};

char ConverterBuffer[OUTPUT_ARRAY_SIZE] = {0};
int (*CPutchar)(int) = NULL;
void (*CSetColor)(u8 r, u8 g, u8 b) = NULL;
const char *Chex_values = "0123456789abcdef0123456789ABCDEF";
const double PowersOf10[601] = {
    1e-300, 1e-299, 1e-298, 1e-297, 1e-296, 1e-295, 
    1e-294, 1e-293, 1e-292, 1e-291, 1e-290, 1e-289, 
    1e-288, 1e-287, 1e-286, 1e-285, 1e-284, 1e-283, 
    1e-282, 1e-281, 1e-280, 1e-279, 1e-278, 1e-277, 
    1e-276, 1e-275, 1e-274, 1e-273, 1e-272, 1e-271, 
    1e-270, 1e-269, 1e-268, 1e-267, 1e-266, 1e-265, 
    1e-264, 1e-263, 1e-262, 1e-261, 1e-260, 1e-259, 
    1e-258, 1e-257, 1e-256, 1e-255, 1e-254, 1e-253, 
    1e-252, 1e-251, 1e-250, 1e-249, 1e-248, 1e-247, 
    1e-246, 1e-245, 1e-244, 1e-243, 1e-242, 1e-241, 
    1e-240, 1e-239, 1e-238, 1e-237, 1e-236, 1e-235, 
    1e-234, 1e-233, 1e-232, 1e-231, 1e-230, 1e-229, 
    1e-228, 1e-227, 1e-226, 1e-225, 1e-224, 1e-223, 
    1e-222, 1e-221, 1e-220, 1e-219, 1e-218, 1e-217, 
    1e-216, 1e-215, 1e-214, 1e-213, 1e-212, 1e-211, 
    1e-210, 1e-209, 1e-208, 1e-207, 1e-206, 1e-205, 
    1e-204, 1e-203, 1e-202, 1e-201, 1e-200, 1e-199, 
    1e-198, 1e-197, 1e-196, 1e-195, 1e-194, 1e-193, 
    1e-192, 1e-191, 1e-190, 1e-189, 1e-188, 1e-187, 
    1e-186, 1e-185, 1e-184, 1e-183, 1e-182, 1e-181, 
    1e-180, 1e-179, 1e-178, 1e-177, 1e-176, 1e-175, 
    1e-174, 1e-173, 1e-172, 1e-171, 1e-170, 1e-169, 
    1e-168, 1e-167, 1e-166, 1e-165, 1e-164, 1e-163, 
    1e-162, 1e-161, 1e-160, 1e-159, 1e-158, 1e-157, 
    1e-156, 1e-155, 1e-154, 1e-153, 1e-152, 1e-151, 
    1e-150, 1e-149, 1e-148, 1e-147, 1e-146, 1e-145, 
    1e-144, 1e-143, 1e-142, 1e-141, 1e-140, 1e-139, 
    1e-138, 1e-137, 1e-136, 1e-135, 1e-134, 1e-133, 
    1e-132, 1e-131, 1e-130, 1e-129, 1e-128, 1e-127, 
    1e-126, 1e-125, 1e-124, 1e-123, 1e-122, 1e-121, 
    1e-120, 1e-119, 1e-118, 1e-117, 1e-116, 1e-115, 
    1e-114, 1e-113, 1e-112, 1e-111, 1e-110, 1e-109, 
    1e-108, 1e-107, 1e-106, 1e-105, 1e-104, 1e-103, 
    1e-102, 1e-101, 1e-100, 1e-99, 1e-98, 1e-97, 
    1e-96, 1e-95, 1e-94, 1e-93, 1e-92, 1e-91, 
    1e-90, 1e-89, 1e-88, 1e-87, 1e-86, 1e-85, 
    1e-84, 1e-83, 1e-82, 1e-81, 1e-80, 1e-79, 
    1e-78, 1e-77, 1e-76, 1e-75, 1e-74, 1e-73, 
    1e-72, 1e-71, 1e-70, 1e-69, 1e-68, 1e-67, 
    1e-66, 1e-65, 1e-64, 1e-63, 1e-62, 1e-61, 
    1e-60, 1e-59, 1e-58, 1e-57, 1e-56, 1e-55, 
    1e-54, 1e-53, 1e-52, 1e-51, 1e-50, 1e-49, 
    1e-48, 1e-47, 1e-46, 1e-45, 1e-44, 1e-43, 
    1e-42, 1e-41, 1e-40, 1e-39, 1e-38, 1e-37, 
    1e-36, 1e-35, 1e-34, 1e-33, 1e-32, 1e-31, 
    1e-30, 1e-29, 1e-28, 1e-27, 1e-26, 1e-25, 
    1e-24, 1e-23, 1e-22, 1e-21, 1e-20, 1e-19, 
    1e-18, 1e-17, 1e-16, 1e-15, 1e-14, 1e-13, 
    1e-12, 1e-11, 1e-10, 1e-9, 1e-8, 1e-7, 
    1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 
    1e00, 1e01, 1e2, 1e03, 1e04, 1e05, 
    1e06, 1e07, 1e08, 1e09, 1e10, 1e11, 
    1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 
    1e18, 1e19, 1e20, 1e21, 1e22, 1e23, 
    1e24, 1e25, 1e26, 1e27, 1e28, 1e29, 
    1e30, 1e31, 1e32, 1e33, 1e34, 1e35, 
    1e36, 1e37, 1e38, 1e39, 1e40, 1e41, 
    1e42, 1e43, 1e44, 1e45, 1e46, 1e47, 
    1e48, 1e49, 1e50, 1e51, 1e52, 1e53, 
    1e54, 1e55, 1e56, 1e57, 1e58, 1e59, 
    1e60, 1e61, 1e62, 1e63, 1e64, 1e65, 
    1e66, 1e67, 1e68, 1e69, 1e70, 1e71, 
    1e72, 1e73, 1e74, 1e75, 1e76, 1e77, 
    1e78, 1e79, 1e80, 1e81, 1e82, 1e83, 
    1e84, 1e85, 1e86, 1e87, 1e88, 1e89, 
    1e90, 1e91, 1e92, 1e93, 1e94, 1e95, 
    1e96, 1e97, 1e98, 1e99, 1e100, 1e101, 
    1e102, 1e103, 1e104, 1e105, 1e106, 1e107, 
    1e108, 1e109, 1e110, 1e111, 1e112, 1e113, 
    1e114, 1e115, 1e116, 1e117, 1e118, 1e119, 
    1e120, 1e121, 1e122, 1e123, 1e124, 1e125, 
    1e126, 1e127, 1e128, 1e129, 1e130, 1e131, 
    1e132, 1e133, 1e134, 1e135, 1e136, 1e137, 
    1e138, 1e139, 1e140, 1e141, 1e142, 1e143, 
    1e144, 1e145, 1e146, 1e147, 1e148, 1e149, 
    1e150, 1e151, 1e152, 1e153, 1e154, 1e155, 
    1e156, 1e157, 1e158, 1e159, 1e160, 1e161, 
    1e162, 1e163, 1e164, 1e165, 1e166, 1e167, 
    1e168, 1e169, 1e170, 1e171, 1e172, 1e173, 
    1e174, 1e175, 1e176, 1e177, 1e178, 1e179, 
    1e180, 1e181, 1e182, 1e183, 1e184, 1e185, 
    1e186, 1e187, 1e188, 1e189, 1e190, 1e191, 
    1e192, 1e193, 1e194, 1e195, 1e196, 1e197, 
    1e198, 1e199, 1e200, 1e201, 1e202, 1e203, 
    1e204, 1e205, 1e206, 1e207, 1e208, 1e209, 
    1e210, 1e211, 1e212, 1e213, 1e214, 1e215, 
    1e216, 1e217, 1e218, 1e219, 1e220, 1e221, 
    1e222, 1e223, 1e224, 1e225, 1e226, 1e227, 
    1e228, 1e229, 1e230, 1e231, 1e232, 1e233, 
    1e234, 1e235, 1e236, 1e237, 1e238, 1e239, 
    1e240, 1e241, 1e242, 1e243, 1e244, 1e245, 
    1e246, 1e247, 1e248, 1e249, 1e250, 1e251, 
    1e252, 1e253, 1e254, 1e255, 1e256, 1e257, 
    1e258, 1e259, 1e260, 1e261, 1e262, 1e263, 
    1e264, 1e265, 1e266, 1e267, 1e268, 1e269, 
    1e270, 1e271, 1e272, 1e273, 1e274, 1e275, 
    1e276, 1e277, 1e278, 1e279, 1e280, 1e281, 
    1e282, 1e283, 1e284, 1e285, 1e286, 1e287, 
    1e288, 1e289, 1e290, 1e291, 1e292, 1e293, 
    1e294, 1e295, 1e296, 1e297, 1e298, 1e299, 
    1e300
};

static const double
    ivln10hi  = 4.34294481878168880939e-01, /* 0x3fdbcb7b, 0x15200000 */
    ivln10lo  = 2.50829467116452752298e-11, /* 0x3dbb9438, 0xca9aadd5 */
    log10_2hi = 3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
    log10_2lo = 3.69423907715893078616e-13, /* 0x3D59FEF3, 0x11F12B36 */
    Lg1 = 6.666666666666735130e-01,  /* 3FE55555 55555593 */
    Lg2 = 3.999999999940941908e-01,  /* 3FD99999 9997FA04 */
    Lg3 = 2.857142874366239149e-01,  /* 3FD24924 94229359 */
    Lg4 = 2.222219843214978396e-01,  /* 3FCC71C5 1D8E78AF */
    Lg5 = 1.818357216161805012e-01,  /* 3FC74664 96CB03DE */
    Lg6 = 1.531383769920937332e-01,  /* 3FC39A09 D078C69F */
    Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

double log10(double x){
	union {double f; uint64_t i;} u = {x};
	double hfsq,f,s,z,R,w,t1,t2,dk,y,hi,lo,val_hi,val_lo;
	uint32_t hx;
	int k;

	hx = u.i>>32;
	k = 0;
	if (hx < 0x00100000 || hx>>31) {
		if (u.i<<1 == 0)
			return -1/(x*x);  /* log(+-0)=-inf */
		if (hx>>31)
			return (x-x)/0.0; /* log(-#) = NaN */
		/* subnormal number, scale x up */
		k -= 54;
		x *= 0x1p54;
		u.f = x;
		hx = u.i>>32;
	} else if (hx >= 0x7ff00000) {
		return x;
	} else if (hx == 0x3ff00000 && u.i<<32 == 0)
		return 0;

	/* reduce x into [sqrt(2)/2, sqrt(2)] */
	hx += 0x3ff00000 - 0x3fe6a09e;
	k += (int)(hx>>20) - 0x3ff;
	hx = (hx&0x000fffff) + 0x3fe6a09e;
	u.i = (uint64_t)hx<<32 | (u.i&0xffffffff);
	x = u.f;

	f = x - 1.0;
	hfsq = 0.5*f*f;
	s = f/(2.0+f);
	z = s*s;
	w = z*z;
	t1 = w*(Lg2+w*(Lg4+w*Lg6));
	t2 = z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
	R = t2 + t1;

	/* See log2.c for details. */
	/* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
	hi = f - hfsq;
	u.f = hi;
	u.i &= (uint64_t)-1<<32;
	hi = u.f;
	lo = f - hi - hfsq + s*(hfsq+R);

	/* val_hi+val_lo ~ log10(1+f) + k*log10(2) */
	val_hi = hi*ivln10hi;
	dk = k;
	y = dk*log10_2hi;
	val_lo = dk*log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;

	/*
	 * Extra precision in for adding y is not strictly needed
	 * since there is no very large cancellation near x = sqrt(2) or
	 * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
	 * with some parallelism and it reduces the error for many args.
	 */
	w = y + val_hi;
	val_lo += (y - w) + val_hi;
	val_hi = w;

	return val_lo + val_hi;
}
double round(double x){
	union {double f; uint64_t i;} u = {x};
	int e = u.i >> 52 & 0x7ff;
	double y;

	if (e >= 0x3ff+52)
		return x;
	if (u.i >> 63)
		x = -x;
	if (e < 0x3ff-1) {
		/* raise inexact if x!=0 */
		FORCE_EVAL(x + toint);
		return 0*u.f;
	}
	y = x + toint - toint - x;
	if (y > 0.5)
		y = y + x - 1;
	else if (y <= -0.5)
		y = y + x + 1;
	else
		y = y + x;
	if (u.i >> 63)
		y = -y;
	return y;
}

static unsigned convertBinNumber(uintmax_t value, char buffer[OUTPUT_ARRAY_SIZE]){
    unsigned int position = OUTPUT_ARRAY_SIZE - 2;

    do{
        buffer[position--] = (char)((value & 0b1) + '0');
        value >>= 1;
    } while (value != 0);

    return position;
}

static unsigned convertOctNumber(uintmax_t value, char buffer[OUTPUT_ARRAY_SIZE]){
    unsigned int position = OUTPUT_ARRAY_SIZE - 2;
    
    do{
        buffer[position--] = (char)((value & 0b111) + '0');
        value >>= 3;
    } while (value != 0);

    return position;
}

static unsigned convertDecNumber(uintmax_t value, char buffer[OUTPUT_ARRAY_SIZE]){
    unsigned int position = OUTPUT_ARRAY_SIZE - 2;

    do{
        buffer[position--] = (char)((value % 10) + '0');
        value /= 10;
    } while (value != 0);

    return position;
}

static unsigned convertHexNumber(uintmax_t value, char buffer[OUTPUT_ARRAY_SIZE], u16 uppercase){
    unsigned int position = OUTPUT_ARRAY_SIZE - 2;
    
    do{
        buffer[position--] = Chex_values[(uppercase * 16) + (value & 0b1111)];
        value >>= 4;
    } while (value != 0);

    return position;
}

const char *bufConvertUINT(uintmax_t value, const char printWay, char buffer[OUTPUT_ARRAY_SIZE]){
    unsigned int position;

    switch (printWay){

        case BinNum:
            position = convertBinNumber(value, buffer);
            break;

        case OctNum:
            position = convertOctNumber(value, buffer);
            break;

        case PointNum:
            if (value == 0) return "(nil)";

        case HexNumBig:
        case HexNum:
            position = convertHexNumber(value, buffer, printWay == HexNumBig);
            break;

        default:
            position = convertDecNumber(value, buffer);
            break;
    }

    buffer[OUTPUT_ARRAY_SIZE - 1] = '\0';
    return (char*)buffer + position + 1;
}

const char *bufConvertINT(intmax_t value, const char printWay, char buffer[OUTPUT_ARRAY_SIZE]){
    const char lazy_char = (value < 0) * '-';
    value = cerb::ABS(value);

    char *_ptr = (char*) bufConvertUINT(value, printWay, buffer);
    if (lazy_char == '-') *(--_ptr) = '-';

    return _ptr;
}

const char *bufConvertFloatMan(double value, char buffer[OUTPUT_ARRAY_SIZE]){
    if (isinf(value)) return "inf";
    else if (isnan(value)) return "nan";
    else if (value == 0.0) return "0.0e+00";
    
    unsigned position = 0;
    if (value < 0) buffer[position++] = '-'; // add '-' if value is negative
    
    value = cerb::ABS(value);
    int digits = (int)log10(value); // get exponent of number

    value *= PowersOf10[POWERS_POSITVE_OFFSET - digits + (digits < 0)];
    
    uintmax_t firstDigit = (uintmax_t)value;
    buffer[position++] = (char)firstDigit + '0';
    buffer[position++] = '.';

    value -= firstDigit; // now value is smaller than 1.0
    uintmax_t afterPoint = round(value * 1e5);
    char *_ptr = (char*) bufConvertUINT(afterPoint, 'u', buffer);
    
    for ( char *__ptr = buffer + OUTPUT_ARRAY_SIZE - 2; *__ptr == '0'; *(__ptr--) = '\0');
    if (*_ptr == '\0') buffer[position++] = '0';
    for (; *_ptr != '\0'; _ptr++) buffer[position++] = *_ptr;
    
    {
        static const char sign[] = {'-', '+'};
        buffer[position++] = 'e';
        buffer[position++] = sign[digits >= 0];
    }

    if (digits < 0) digits--;
    if (digits < 10 && digits > -10) buffer[position++] = '0';
    
    digits = cerb::ABS(digits);
    _ptr = (char*) bufConvertUINT(digits, 'u', buffer);
    
    for (; *_ptr != '\0'; _ptr++) buffer[position++] = *_ptr;

    buffer[position] = '\0';
    return buffer;
}

const char *bufConvertFloat(double value, char buffer[OUTPUT_ARRAY_SIZE]){
    // check if number is inf or nan
    if (isinf(value)) return "inf";
    else if (isnan(value)) return "nan";
    else if (value == 0.0) return "0.0";
    
    unsigned position = 0;
    if (value < 0) buffer[position++] = '-'; // add '-' if value is negative
    
    value = cerb::ABS(value);
    int digits = (int)log10(value); // get exponent of number

    if (digits > 5 || digits <= -5) // if value is greater than 9.99e+05 it is converted like 1.313e+03
        return bufConvertFloatMan(value, buffer);
    else{ // if value is not so big and is not so small it is converted like a normal float 1313.14
        uintmax_t beforePoint = value, afterPoint;
        value -= beforePoint; // now value is smaller than 1.0 and just contains digits after '.'
        value *= PowersOf10[POWERS_POSITVE_OFFSET + (8 - digits)]; // add some extra values after '.'
        afterPoint = round(value);

        char *_ptr = (char*) bufConvertUINT(beforePoint, 'u', buffer);
        for (; *_ptr != '\0'; _ptr++) buffer[position++] = *_ptr;
        if (afterPoint == 0) return buffer; // if there is no values after '.' we just skeep them

        buffer[position++] = '.';
        {
            unsigned digitsAfterPoint = log10(value); // if there is number like 0.0031 we need to add some extra '0' after point, because int will not hold them
            for (unsigned i = 1; i < (8 - digits) - digitsAfterPoint; i++) buffer[position++] = '0';
        }

        _ptr = (char*) bufConvertUINT(afterPoint, 'u', buffer);
        for ( char *__ptr = buffer + OUTPUT_ARRAY_SIZE - 2; *__ptr == '0'; *(__ptr--) = '\0');
        for (; *_ptr != '\0'; _ptr++) buffer[position++] = *_ptr;
    }

    buffer[position] = '\0';
    return buffer;
}

__END_DECLS
