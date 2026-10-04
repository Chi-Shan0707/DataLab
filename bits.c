/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
// ac
/* 
  * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return (~0)<<31;
}

// P2
// ac
/* 
  * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
//	return (x&(!y))|((!x)&y);
 // return (x&y) &((~x)&(~y));
  return ~(~(x&(~y)) & ~(y&(~x)));
}

// P3
// ac
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return  (~((x>>31)&x))+1;
}


// P4
// ac
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
// 首先注意这里是 要乘上8？

// <<3 

// 我希望能点对点地算增量？
  return (((x>>(src<<3))&0xff)<<(dst<<3))|(x&(~(0xff<<(dst<<3))));
}

// P5
// ac
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  // 右移，高位1我要处理。
  // 我只用确保前面的0都会被我消掉。所以只用 前面都1 后面都是0的一串掩码
  //都取反？
  return ((x>>n) ) & (~(((1<<n)+ (~1+1))<<(32+(~n+1))));
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
//  return ((x>>2)&(15+((15+((15+(15+((15+((15+(15<<4))<<4))<<4))<<4)<<4))<<4) ))^(x&((15+((15+((15+(15+((15+((15+(15<<4))<<4))<<4))<<4)<<4))<<4))<<2));
//  用好的mask来获得4位 4位间隔的
// mask = (0b11111111) ...

// mask = 0xff+(0xff<<8)+(0xff<<16)+(0xff<<24)

  //return ((255+(255<<8)+(255<<16)+(255<<24))&x)<<4 | ((255+(255<<8)+(255<<16)+(255<<24))&(x>>4));
// 绷不住了， 竟然允许赋值，那还说啥了
  int mask = 15+(15<<8)+(15<<16)+(15<<24);// 间隔掩码

  return ((mask&x)<<4) | ((mask&(x>>4)));
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {

// 取反就是
// x & (-x) 最低的1位代表的值
// 树状数组经典trick，lowbit
// return (~x) & ( (~x)+1) ;
// 上面求的是第1个0，题目要第2个0
// 取反后变成找第2个1：先 x&(x-1) 抹掉最低的1，再 lowbit 一次
  x=~x;
  x=x&(x+(~0));
  return x&(~x+1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  // 呃啊， 显然要折叠信息
  ////x ^(x>>16), 虽然最高的16位我删不掉，但不重要，我的后16位已经折叠了，有足够的32位信息了

  // 如果能赋值那还不好说？？？
  x=x^(x>>16);
  x=x^(x>> 8);
  x=x^(x>> 4);
  x=x^(x>> 2);
  x=x^(x>> 1);
  return !(x & 1);
}
// P9
/* 
  * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
//  return ((x>>n) ) & (~(((1<<n)+ (~1+1))<<(32+(~n+1))));
  // 总会溢出
  // anyway
  //  不管了

//  n = n & 31;// 取余数

// 上面只是逻辑右移，掉出去的低位没接回高位
// 而且 n=0 时 32-n 会移32位，x86 上等于没移，炸了 -> 拆成先移 31-n 再移 1
  int mask;
  n=n &31;// 取余数
  mask=~(((1<<31)>>n)<<1);// 高n位是0，其余是1，消掉算术右移补的1
  return ((x>>n)&mask)  |((x<<(31+(~n+1)))<<1);
  //防止算术右移高位的11111填补恶心到我们
}

// P10
// ac
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
 // i MADE IT!!!! 
  return ((x+ (1 <<(n+ (~1+1)))+ ((x&(1<<n))>>n)+(~1+1))>>n)<<n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
//  return ((x>>1)+(y>>1)) + ((((x&1)^(y&1))) & ((y + ( ~x+1))>>31));

//  return (x&y) + ((x^y)>>1) + (((x^y)&1)&((y+(~x+1))>>31));
// 问题出在 y-x, 大正- 大负还会溢出mmd 会溢出（INT_MAX - INT_MIN）
// 异号：x>y 当且仅当 y是负的，直接看y的符号
// 同号：减法不会溢出，还是看 y-x 的符号
  int difference_sign = (x^y)>>31;
  //符号差异
  int sub = (difference_sign&y)|(~difference_sign&(y+(~x+1)));
  return (x&y) + ((x^y)>>1) + (((x^y)&1)&(sub>>31));
// 
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
//  return (!(x^a)) | (!(x^b)) | ((~((x+(~a+1))>>31)+1) ^ (~((x+(~b+1)) >>31)+1));
// ：x-a 会溢出
// 在区间外 = 同时小于a,b 或者 同时大于a,b
  

//    int signa = (a>>31)&1;
//    int signb = (b>>31)&1;
// //负数为1，正数为0
//   int signx=(x>>31)&1;

//   int res_1 = (signa^signb) |  (!(signa^signx));
//   // a,b同号，  并且 a，x异号，就一定是 0 | 0 =0 
//   // res_1 只有等于0才有意义

//回到最初的语句
//return (!(x^a)) | (!(x^b)) | ((~((x+(~a+1))>>31)+1) ^ (~((x+(~b+1)) >>31)+1));
//只要修正减法就是对的了！
 

//int delta_a  = (x+(~a+1)

  //int delta_a = (((x>>31)&1)^((a>>31)&1))  (~((x+(~a+1))>>31)+1);
  //int delta_b = (((x>>31)&1)^((b>>31)&1))  (~((x+(~b+1))>>31)+1);
  // 先把正-负或者负-正的情况给特判了

  //剩下如出一辙

  //return (!(x^a)) | (!(x^b)) | (delta_a ^ delta_b);
   // diff_a: 异号为全1(-1)，同号为0
   int diff_a = (x^a)>>31;    int diff_b = (x^b)>>31;
  
      // 异号直接取 x 的符号(若x负则全1)；同号时做减法不会溢出，取减法符号
  int sign_a = ((diff_a&x) | (~diff_a&(x+(~a+1))))>>31;
  int sign_b = ((diff_b&x) | (~diff_b&(x+(~b+1))))>>31;
  
  // 端点相等，或者两侧符号严格一正一负
  return (!(x^a)) | (!(x^b)) | ((sign_a^sign_b)&1);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
//  return x+(x<<2);
// x*5 = x+(x<<2)，两种溢出：
// 1. 左移2位就溢出了：移回来和x不一样
// 2. 相加溢出：结果和x符号不同
// 溢出了就按x的符号选 INT_MAX / INT_MIN
  int x4 = x<<2;



// 第一次判*4溢出与否
  int over = !!((x4>>2)^x);

  int res= x4+x;

  over = over |(((res^x)>>31)&1);
  
  int mask = ~over+1;// 溢出变全1，不溢出全0
  int INF = (1<<31)^(~(x>>31));

  return ((~mask)&res)|(mask&INF);//!!想了好久
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
//  return 14;
// 分两步加，每一步记一下溢出方向：正溢出 +1，负溢出 -1
// 两步加起来 >0 就是大于INT_MAX，<0 就是小于INT_MIN，=0 说明没溢出或者正好抵消
 int sum1 = x + y;     
  int sum2 = sum1 + z;
//最烦的是这个溢出
    // 计算x+y的溢出

    // 再计算 (x+y)和z求和的溢出
      int c1 = 
         ((((~x )& (~y) & sum1) >> 31) & 1) 
      + ((x & y & (~sum1)) >> 31);

    //对称的

      int c2 = 
      ((((~sum1) & (~z) & sum2) >> 31) & 1) + 
           ((sum1 & z & (~sum2)) >> 31);
  
     int c = c1 + c2;
  
  return (c >> 31)| (!!c);

}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
//  return 15;
;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
//  return 16;
  
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
//  return 17;
 
  
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {

//  int res = 0;
//  return 18;

// 分治：相邻1位两两相加 -> 每2位存个数；再相邻2位相加 -> 每4位存个数 ……
  int mask_1 = 85+(85<<8);// 0x5555
  int mask_2 = 51+(51<<8);// 0x3333
  int mask_4 = 15+(15<<8);// 0x0f0f
  mask_1 = mask_1+(mask_1<<16);
  mask_2 = mask_2+(mask_2<<16);
  mask_4 = mask_4+(mask_4<<16);

  x=(x&mask_1)+((x>>1)&mask_1);
  x=(x&mask_2)+((x>>2)&mask_2);
  x=(x+(x>>4))&mask_4;// 4位最多是8，加起来不会溢出到隔壁，可以先加再mask
  x=x+(x>>8);
  x=x+(x>>16);
  return x&63;// 最多32个，低6位够了
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
//归并排序？


// 上下半区交换
//  4444交换？

//递归！

 int mask_16 = (1<<16) + (~1+1);
 x=(x>>16) &  mask_16|((x&mask_16)<< 16);

 int mask_8 = 255+ (255<<16) ;

 x = ( (x>>8) & mask_8 )| ((x&mask_8)<<8);
 
 int mask_4 = 15 + (15<<8) + (15<<16) + (15<<24);
 x = ((x>>4) & mask_4 )| ((x&mask_4)<<4);

 int mask_2 = 3 + (3<<4) + (3<<8) + (3<<12) + (3<<16) + (3<<20) + (3<<24) + (3<<28);

 x = ((x>>2) & mask_2 )| ((x&mask_2)<<2);

 int mask_1 = 1 + (1<<2) + (1<<4) + (1<<6) + (1<<8) + (1<<10) + (1<<12) + (1<<14) + (1<<16) + (1<<18) + (1<<20) + (1<<22) + (1<<24) + (1<<26) + (1<<28) + (1<<30);

 x = ((x>>1) & mask_1) | ((x&mask_1)<<1);

 



  return x;
}
