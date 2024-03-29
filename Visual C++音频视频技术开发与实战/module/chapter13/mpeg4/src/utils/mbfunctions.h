/*****************************************************************************
 *
 *  XVID MPEG-4 VIDEO CODEC
 *  - MB related header  -
 *
 *  Copyright(C) 2001 Michael Militzer <isibaar@xvid.org>
 *
 *  This program is free software ; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation ; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY ; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program ; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * $Id$
 *
 ****************************************************************************/

#ifndef _ENCORE_BLOCK_H
#define _ENCORE_BLOCK_H

#include "../encoder.h"
#include "../bitstream/bitstream.h"


/** MBTransQuant.c **/


void MBTransQuantIntra(const MBParam * const pParam,
					const FRAMEINFO * const frame,
					MACROBLOCK * const pMB,
					const uint32_t x_pos,	/* <-- The x position of the MB to be searched */
					const uint32_t y_pos,	/* <-- The y position of the MB to be searched */
					int16_t data[6 * 64],	/* <-> the data of the MB to be coded */
					int16_t qcoeff[6 * 64]);	/* <-> the quantized DCT coefficients */

uint8_t MBTransQuantInter(const MBParam * const pParam,
						const FRAMEINFO * const frame,
						MACROBLOCK * const pMB,
						const uint32_t x_pos,
						const uint32_t y_pos,
						int16_t data[6 * 64],
						int16_t qcoeff[6 * 64]);


//void MBFrameToField(int16_t data[6 * 64]);	/* de-interlace vertical Y blocks */


/** MBCoding.c **/

void MBCoding(const FRAMEINFO * const frame,	/* <-- the parameter for coding of the bitstream */
			MACROBLOCK * pMB,	/* <-- Info of the MB to be coded */
			int16_t qcoeff[6 * 64],	/* <-- the quantized DCT coefficients */
			Bitstream * bs,	/* <-> the bitstream */
			Statistics * pStat);	/* <-> statistical data collected for current frame */

#endif
