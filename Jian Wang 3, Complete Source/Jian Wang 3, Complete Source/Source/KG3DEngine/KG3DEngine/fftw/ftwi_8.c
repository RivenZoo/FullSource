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
/* Generated on Mon Mar 24 02:08:32 EST 2003 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: /homee/stevenj/cvs/fftw/gensrc/genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -twiddleinv 8 */

/*
 * This function contains 66 FP additions, 32 FP multiplications,
 * (or, 52 additions, 18 multiplications, 14 fused multiply/add),
 * 28 stack variables, and 32 memory accesses
 */
static const fftw_real K707106781 =
FFTW_KONST(+0.707106781186547524400844362104849039284835938);

/*
 * Generator Id's : 
 * $Id: ftwi_8.c,v 1.2 2008/04/08 01:23:35 yanglin Exp $
 * $Id: ftwi_8.c,v 1.2 2008/04/08 01:23:35 yanglin Exp $
 * $Id: ftwi_8.c,v 1.2 2008/04/08 01:23:35 yanglin Exp $
 */

void fftwi_twiddle_8(fftw_complex *A, const fftw_complex *W, int iostride,
		     int m, int dist)
{
     int i;
     fftw_complex *inout;
     inout = A;
     for (i = m; i > 0; i = i - 1, inout = inout + dist, W = W + 7) {
	  fftw_real tmp7;
	  fftw_real tmp43;
	  fftw_real tmp71;
	  fftw_real tmp77;
	  fftw_real tmp41;
	  fftw_real tmp53;
	  fftw_real tmp56;
	  fftw_real tmp64;
	  fftw_real tmp18;
	  fftw_real tmp76;
	  fftw_real tmp46;
	  fftw_real tmp68;
	  fftw_real tmp30;
	  fftw_real tmp48;
	  fftw_real tmp51;
	  fftw_real tmp65;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp1;
	       fftw_real tmp70;
	       fftw_real tmp6;
	       fftw_real tmp69;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp1 = c_re(inout[0]);
	       tmp70 = c_im(inout[0]);
	       {
		    fftw_real tmp3;
		    fftw_real tmp5;
		    fftw_real tmp2;
		    fftw_real tmp4;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp3 = c_re(inout[4 * iostride]);
		    tmp5 = c_im(inout[4 * iostride]);
		    tmp2 = c_re(W[3]);
		    tmp4 = c_im(W[3]);
		    tmp6 = (tmp2 * tmp3) + (tmp4 * tmp5);
		    tmp69 = (tmp2 * tmp5) - (tmp4 * tmp3);
	       }
	       tmp7 = tmp1 + tmp6;
	       tmp43 = tmp1 - tmp6;
	       tmp71 = tmp69 + tmp70;
	       tmp77 = tmp70 - tmp69;
	  }
	  {
	       fftw_real tmp35;
	       fftw_real tmp54;
	       fftw_real tmp40;
	       fftw_real tmp55;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp32;
		    fftw_real tmp34;
		    fftw_real tmp31;
		    fftw_real tmp33;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp32 = c_re(inout[7 * iostride]);
		    tmp34 = c_im(inout[7 * iostride]);
		    tmp31 = c_re(W[6]);
		    tmp33 = c_im(W[6]);
		    tmp35 = (tmp31 * tmp32) + (tmp33 * tmp34);
		    tmp54 = (tmp31 * tmp34) - (tmp33 * tmp32);
	       }
	       {
		    fftw_real tmp37;
		    fftw_real tmp39;
		    fftw_real tmp36;
		    fftw_real tmp38;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp37 = c_re(inout[3 * iostride]);
		    tmp39 = c_im(inout[3 * iostride]);
		    tmp36 = c_re(W[2]);
		    tmp38 = c_im(W[2]);
		    tmp40 = (tmp36 * tmp37) + (tmp38 * tmp39);
		    tmp55 = (tmp36 * tmp39) - (tmp38 * tmp37);
	       }
	       tmp41 = tmp35 + tmp40;
	       tmp53 = tmp35 - tmp40;
	       tmp56 = tmp54 - tmp55;
	       tmp64 = tmp54 + tmp55;
	  }
	  {
	       fftw_real tmp12;
	       fftw_real tmp44;
	       fftw_real tmp17;
	       fftw_real tmp45;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp9;
		    fftw_real tmp11;
		    fftw_real tmp8;
		    fftw_real tmp10;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp9 = c_re(inout[2 * iostride]);
		    tmp11 = c_im(inout[2 * iostride]);
		    tmp8 = c_re(W[1]);
		    tmp10 = c_im(W[1]);
		    tmp12 = (tmp8 * tmp9) + (tmp10 * tmp11);
		    tmp44 = (tmp8 * tmp11) - (tmp10 * tmp9);
	       }
	       {
		    fftw_real tmp14;
		    fftw_real tmp16;
		    fftw_real tmp13;
		    fftw_real tmp15;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp14 = c_re(inout[6 * iostride]);
		    tmp16 = c_im(inout[6 * iostride]);
		    tmp13 = c_re(W[5]);
		    tmp15 = c_im(W[5]);
		    tmp17 = (tmp13 * tmp14) + (tmp15 * tmp16);
		    tmp45 = (tmp13 * tmp16) - (tmp15 * tmp14);
	       }
	       tmp18 = tmp12 + tmp17;
	       tmp76 = tmp12 - tmp17;
	       tmp46 = tmp44 - tmp45;
	       tmp68 = tmp44 + tmp45;
	  }
	  {
	       fftw_real tmp24;
	       fftw_real tmp49;
	       fftw_real tmp29;
	       fftw_real tmp50;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp21;
		    fftw_real tmp23;
		    fftw_real tmp20;
		    fftw_real tmp22;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp21 = c_re(inout[iostride]);
		    tmp23 = c_im(inout[iostride]);
		    tmp20 = c_re(W[0]);
		    tmp22 = c_im(W[0]);
		    tmp24 = (tmp20 * tmp21) + (tmp22 * tmp23);
		    tmp49 = (tmp20 * tmp23) - (tmp22 * tmp21);
	       }
	       {
		    fftw_real tmp26;
		    fftw_real tmp28;
		    fftw_real tmp25;
		    fftw_real tmp27;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp26 = c_re(inout[5 * iostride]);
		    tmp28 = c_im(inout[5 * iostride]);
		    tmp25 = c_re(W[4]);
		    tmp27 = c_im(W[4]);
		    tmp29 = (tmp25 * tmp26) + (tmp27 * tmp28);
		    tmp50 = (tmp25 * tmp28) - (tmp27 * tmp26);
	       }
	       tmp30 = tmp24 + tmp29;
	       tmp48 = tmp24 - tmp29;
	       tmp51 = tmp49 - tmp50;
	       tmp65 = tmp49 + tmp50;
	  }
	  {
	       fftw_real tmp19;
	       fftw_real tmp42;
	       fftw_real tmp63;
	       fftw_real tmp66;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp19 = tmp7 + tmp18;
	       tmp42 = tmp30 + tmp41;
	       c_re(inout[4 * iostride]) = tmp19 - tmp42;
	       c_re(inout[0]) = tmp19 + tmp42;
	       {
		    fftw_real tmp73;
		    fftw_real tmp74;
		    fftw_real tmp67;
		    fftw_real tmp72;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp73 = tmp30 - tmp41;
		    tmp74 = tmp71 - tmp68;
		    c_im(inout[2 * iostride]) = tmp73 + tmp74;
		    c_im(inout[6 * iostride]) = tmp74 - tmp73;
		    tmp67 = tmp65 + tmp64;
		    tmp72 = tmp68 + tmp71;
		    c_im(inout[0]) = tmp67 + tmp72;
		    c_im(inout[4 * iostride]) = tmp72 - tmp67;
	       }
	       tmp63 = tmp7 - tmp18;
	       tmp66 = tmp64 - tmp65;
	       c_re(inout[6 * iostride]) = tmp63 - tmp66;
	       c_re(inout[2 * iostride]) = tmp63 + tmp66;
	       {
		    fftw_real tmp59;
		    fftw_real tmp78;
		    fftw_real tmp62;
		    fftw_real tmp75;
		    fftw_real tmp60;
		    fftw_real tmp61;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp59 = tmp43 + tmp46;
		    tmp78 = tmp76 + tmp77;
		    tmp60 = tmp56 - tmp53;
		    tmp61 = tmp48 + tmp51;
		    tmp62 = K707106781 * (tmp60 - tmp61);
		    tmp75 = K707106781 * (tmp61 + tmp60);
		    c_re(inout[7 * iostride]) = tmp59 - tmp62;
		    c_re(inout[3 * iostride]) = tmp59 + tmp62;
		    c_im(inout[iostride]) = tmp75 + tmp78;
		    c_im(inout[5 * iostride]) = tmp78 - tmp75;
	       }
	       {
		    fftw_real tmp47;
		    fftw_real tmp80;
		    fftw_real tmp58;
		    fftw_real tmp79;
		    fftw_real tmp52;
		    fftw_real tmp57;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp47 = tmp43 - tmp46;
		    tmp80 = tmp77 - tmp76;
		    tmp52 = tmp48 - tmp51;
		    tmp57 = tmp53 + tmp56;
		    tmp58 = K707106781 * (tmp52 + tmp57);
		    tmp79 = K707106781 * (tmp52 - tmp57);
		    c_re(inout[5 * iostride]) = tmp47 - tmp58;
		    c_re(inout[iostride]) = tmp47 + tmp58;
		    c_im(inout[3 * iostride]) = tmp79 + tmp80;
		    c_im(inout[7 * iostride]) = tmp80 - tmp79;
	       }
	  }
     }
}

static const int twiddle_order[] = { 1, 2, 3, 4, 5, 6, 7 };
fftw_codelet_desc fftwi_twiddle_8_desc = {
     "fftwi_twiddle_8",
     (void (*)()) fftwi_twiddle_8,
     8,
     FFTW_BACKWARD,
     FFTW_TWIDDLE,
     187,
     7,
     twiddle_order,
};
