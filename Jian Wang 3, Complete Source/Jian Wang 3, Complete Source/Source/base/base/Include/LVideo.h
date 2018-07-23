#ifndef __KLVIDEO_H__
#define __KLVIDEO_H__

#define KLVIDEOVERSION "1.0h"
#define KLVIDEODATE    "2002-10-11"

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KLVIDEO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KLVIDEO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef KLVIDEO_EXPORTS
#define KLVIDEO_API __declspec(dllexport)
#else
#define KLVIDEO_API __declspec(dllimport)
#endif

#ifndef __RADRES__

//#include "rad.h"

#define KLVIDEONOSOUND			0xffffffff
#define KLVIDEOSNDTRACK			0x00004000L // Set the track number to play

#define KLVIDEOSURFACE8P          0
#define KLVIDEOSURFACE24          1
#define KLVIDEOSURFACE24R         2
#define KLVIDEOSURFACE32          3
#define KLVIDEOSURFACE32R         4
#define KLVIDEOSURFACE32A         5
#define KLVIDEOSURFACE32RA        6
#define KLVIDEOSURFACE4444        7
#define KLVIDEOSURFACE5551        8
#define KLVIDEOSURFACE555         9
#define KLVIDEOSURFACE565        10
#define KLVIDEOSURFACE655        11
#define KLVIDEOSURFACE664        12
#define KLVIDEOSURFACEYUY2       13
#define KLVIDEOSURFACEUYVY       14
#define KLVIDEOSURFACEYV12       15
#define KLVIDEOSURFACEMASK       15

class KLMp4Video;
class KLMp4Audio;

extern "C"
{

struct KLVIDEO
{
	KLVIDEO(){memset(this,0,sizeof(KLVIDEO));}
	KLMp4Video* pMpeg4Video;
	KLMp4Audio* pMpeg4Audio;
	unsigned int Width;             // Width (1 based, 640 for example)
	unsigned int Height;            // Height (1 based, 480 for example)
	unsigned int Frames;            // Number of frames (1 based, 100 = 100 frames)
	unsigned int FrameNum;          // Frame to *be* displayed (1 based)
};

typedef struct KLVIDEO* HKLVIDEO;

KLVIDEO_API unsigned char KLVideoSetSoundSystem(void* dd);
KLVIDEO_API HKLVIDEO KLVideoOpen(char* name,unsigned int flags, void* hWnd);
KLVIDEO_API void KLVideoClose(HKLVIDEO bnk);
KLVIDEO_API unsigned int KLVideoWait(HKLVIDEO bnk);
KLVIDEO_API void KLVideoCopyToBuffer(HKLVIDEO bnk,void* buf,unsigned int left,unsigned int top,unsigned int Pitch,unsigned int destheight,unsigned int Flags);
KLVIDEO_API unsigned int KLVideoDoFrame(HKLVIDEO bnk);
KLVIDEO_API void KLVideoNextFrame(HKLVIDEO bnk);
KLVIDEO_API void KLVideoSetSoundVolume(HKLVIDEO bnk,unsigned int nVolume);
KLVIDEO_API void KLVideoSetSoundTrack(unsigned int track);
KLVIDEO_API unsigned int KLVideoGetCurrentFrame(HKLVIDEO bnk);

}

#endif

#endif


