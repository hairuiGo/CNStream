/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc. All rights reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *************************************************************************/
#ifndef _CN_VIDEO_COMMON_H
#define _CN_VIDEO_COMMON_H

#define CN_MAXIMUM_PLANE          6

/**
 * Error Code
 */
typedef enum CNVideoCodec_Error_Type_Enum{
    CNVideoCodec_Success       = 0,       /* No error */
    CNVideoCodec_Invalid_value = -1,      /* Parameter error */
    CNVideoCodec_Not_Supported = -2,      /* Function not implemented */
    CNVideoCodec_Invalid_Handle = -3,     /* Invalid handle passed to codec */
    CNVideoCodec_Timeout       = -4,      /* Time out */
    CNVideoCodec_Err_Unknown   = -999     /* Unknown error */
}CNVideoCodec_Error_Type;


/**
 * Codec type for all decode & encode
 */
typedef enum CNVideoCodec_Enum{
    CNVideoCodec_MPEG2 = 0,               /* MPEG2  */
    CNVideoCodec_MPEG4,                   /* MPEG4  */
    CNVideoCodec_VC1,                     /* VC1    */
    CNVideoCodec_H264,                    /* H264   */
    CNVideoCodec_HEVC,                    /* HEVC   */
    CNVideoCodec_JPEG,                    /* JPEG   */
    CNVideoCodec_VP8,                     /* VP8    */
    CNVideoCodec_VP9,                     /* VP9    */
    CNVideoCodec_AVS,                     /* AVS    */
    CNVideoCodec_NumCodecs                /* Max Codec */
}CNVideoCodec;

/**
 * Video surface format
 */
typedef enum CNVideoSurfaceFormat_enum{
    CNVideoSurfaceFormat_NV12 = 0,        /* Semi-Planar Y4-U1V1 */
    CNVideoSurfaceFormat_YV12,            /* Planar Y4-V1-U1 */
    CNVideoSurfaceFormat_YUYV,            /* 8 bit packed Y2U1Y2V1 */
    CNVideoSurfaceFormat_UYVY,            /* 8 bit packed U1Y2V1Y2 */
    CNVideoSurfaceFormat_P010,            /* 10 bit Semi-Planar Y4-U1V1. Each pixel of size 2 bytes, 10 bits contain pixel data. */
    CNVideoSurfaceFormat_I420,            /* Planar Y4-U1-V1 */
    CNVideoSurfaceFormat_NV21,            /* Semi-Planar Y4-V1U1 */
    CNVideoSurfaceFormat_YUV420_10BIT,    /* 10 bit Semi-Planar Y4-U1-V1. Each pixel of size 2 bytes, 10 bits contain pixel data. */
    CNVideoSurfaceFormat_YUV444_10BIT,    /* 10 bit Planar Y4-U4-V4. Each pixel of size 2 bytes, 10 bits contain pixel data.  */
    CNVideoSurfaceFormat_ARGB,            /* 8 bit Packed A8R8G8B8. B in the lowest 8 bits, G in the next 8 bits, R in the
                                             8 bits after that and A in the highest 8 bits. */
    CNVideoSurfaceFormat_AYUV,            /* 8 bit Packed A8Y8U8V8. V in the lowest 8 bits, U in the next 8 bits, Y in the
                                             8 bits after that and A in the highest 8 bits. */
    CNVideoSurfaceFormat_ABGR,            /* 8 bit Packed A8B8G8R8. R in the lowest 8 bits, G in the next 8 bits, B in the
                                             8 bits after that and A in the highest 8 bits. */
    CNVideoSurfaceFormat_BGRA,            /* 8 bit Packed B8G8R8A8. A in the lowest 8 bits, R in the next 8 bits, G in the
                                             8 bits after that and B in the highest 8 bits. */
    CNVideoSurfaceFormat_RGBA,            /* 8 bit Packed A8B8G8R8. A in the lowest 8 bits, B in the next 8 bits, G in the
                                             8 bits after that and R in the highest 8 bits. */
}CNVideoSurfaceFormat;


/**
 * Chroma format
 */
typedef enum CNVideoChromaFormat_enum{
    CNVideoChromaFormat_Monochrome = 0,   /* MonoChrome */
    CNVideoChromaFormat_420,              /* YUV 4:2:0  */
    CNVideoChromaFormat_422,              /* YUV 4:2:2  */
    CNVideoChromaFormat_444               /* YUV 4:4:4  */
}CNVideoChromaFormat;

/**
 * Enum to decide where In/Out Memory is from
 */
typedef enum CNMemoryAllocateType_enum{
    CNVideoMemory_Allocate=0,             /* CNCodec will prepare memory */
    CNVideoMemory_Use,                    /* CNCodec will use memory from APP */
}CNMemoryAllocateType;

/**
 * Memory heap to allocate input and output buffers.
 */
typedef enum CNVideo_Memory_Heap_enum
{
    CNVideo_Memory_Heap_AutoSelect = 0, /* Memory can be in VPU/IPU heap */
    CNVideo_Memory_Heap_VPU,            /* Memory will locate in VPU heap */
    CNVideo_Memory_Heap_IPU,            /* Memory will locate in IPU heap */
} CNVideo_Memory_Heap;

/**
 * System Event Type.
 */
typedef enum CNVideo_EventType_enum
{
    CNVideo_Fimrware_Crash = 0,         /* Firmware crash, all Codec instance will down */
    CNVideo_Forced_Reset,               /* Soft/HW reset, all Codec instance will down */
}CNVideo_EventType;

/**
 * Provide version information for the CNCodec library.
 */
typedef struct {
    char Major;                         /* Major version */
    char Minor;                         /* Minor version */
} CNCodecVersion;


#endif
