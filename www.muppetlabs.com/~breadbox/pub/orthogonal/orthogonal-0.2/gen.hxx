#ifndef __GEN_HXX__
#define __GEN_HXX__

#include <stdlib.h>
#include "limits.h"
#include "error.hxx"

// The 32-bit type for internal representation of numbers.
#if UINT_MAX == 0xFFFFFFFF
typedef int int32;
#define INT32_INT
#elif USHORT_MAX == 0xFFFFFFFF
typedef short int32;
#define INT32_SHORT
#elif ULONG_MAX == 0xFFFFFFFF
typedef long int32;
#define INT32_LONG
#else
#error "No 32-bit primitive type: Orthogonal cannot be built."
#endif

// The list of operators.
typedef enum Operator { opNop = 0,
			opPlus, opMinus, opMult, opDiv, opMod,
			opNot, opAnd, opOr, opXor,
			opExch, opDup, opDisc,
			opPush, opSet,
			opChar, opStr, opDec,
			opX, opY, opDX, opDY,
			opCW, opCCW, opRev,
			opLeft, opRight, opUp, opDown,
			opIf, opRet,
			opMax
	} Operator;


extern Err ERR;

extern bool debugging;

#endif
