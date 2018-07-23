/*
 * Copyright (c) 1997-1999, 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Mar 24 02:06:55 EST 2003 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: /homee/stevenj/cvs/fftw/gensrc/genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -hc2real 1 */

/*
 * This function contains 0 FP additions, 0 FP multiplications,
 * (or, 0 additions, 0 multiplications, 0 fused multiply/add),
 * 1 stack variables, and 2 memory accesses
 */

/*
 * Generator Id's : 
 * $Id: fcr_1.c,v 1.2 2008/04/08 01:23:33 yanglin Exp $
 * $Id: fcr_1.c,v 1.2 2008/04/08 01:23:33 yanglin Exp $
 * $Id: fcr_1.c,v 1.2 2008/04/08 01:23:33 yanglin Exp $
 */

void fftw_hc2real_1(const fftw_real *real_input,
		    const fftw_real *imag_input, fftw_real *output,
		    int real_istride, int imag_istride, int ostride)
{
     fftw_real tmp1;
     ASSERT_ALIGNED_DOUBLE;
     tmp1 = real_input[0];
     output[0] = tmp1;
}

fftw_codelet_desc fftw_hc2real_1_desc = {
     "fftw_hc2real_1",
     (void (*)()) fftw_hc2real_1,
     1,
     FFTW_BACKWARD,
     FFTW_HC2REAL,
     37,
     0,
     (const int *) 0,
};