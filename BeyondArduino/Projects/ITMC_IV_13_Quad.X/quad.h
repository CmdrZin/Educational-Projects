/* 
 * File:   quad.h
 * Author: Cmdrzin
 *
 * Created on March 24, 2026, 2:35 PM
 */

#ifndef QUAD_H
#define	QUAD_H

typedef enum {D_CW, D_CCW} DIR;

void init_quad(void);
int getPosition();
DIR getDirection();

#endif	/* QUAD_H */

