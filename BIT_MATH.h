/*
 * BIT_MATH.h
 *
 * Created: 23/08/2022 09:30:35
 *  Author: emada
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define  SET_BIT(REG , BIT) (REG |=  (1<< BIT))
#define  CLR_BIT(REG , BIT) (REG &=~ (1<<BIT))
#define  TOGGLE_BIT(REG , BIT) (REG^= (1<<BIT))
#define  GET_BIT(REG , BIT) ( (REG>>BIT) & (0x01))


#endif /* BIT_MATH_H_ */