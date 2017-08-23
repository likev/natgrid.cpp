/*
 * $Id: nngheads.h,v 1.6 2008-07-27 04:02:37 haley Exp $
 */
/************************************************************************
*                                                                       *
*                Copyright (C)  2000                                    *
*        University Corporation for Atmospheric Research                *
*                All Rights Reserved                                    *
*                                                                       *
*    The use of this Software is governed by a License Agreement.       *
*                                                                       *
************************************************************************/

namespace natgrid {
	void    Initialize(int, float[], float[], int, int,
		float[], float[]);

	double  armin(int, float *);
	double  armax(int, float *);

	int ReadData(int numdat, float *xin, float *yin, float *zin);
	extern float  **MakeGrid(int, int, float *, float *);

	extern void   c_nnsetr(char *, float);
	extern void   c_nngetr(char *, float *);

	extern void   Terminate();

	extern int    cull_striples(int, float *);
	extern int    comp_striples(const void *, const void *);

}
