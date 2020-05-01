/*
 * bit_math.h
 *
 * Created: 04/04/2020 02:10:22 م
 *  Author: MAGED
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define CLEAR_BIT(var,bit)   var&=~(1<<bit)
#define SET_BIT(var,bit)     var|=(1<<bit)

#define GET_BIT(var,bit)     ((var>>bit)&1)
#define TOGGLE(var,bit)      var^=(1<<bit)
      


#endif /* BIT_MATH_H_ */