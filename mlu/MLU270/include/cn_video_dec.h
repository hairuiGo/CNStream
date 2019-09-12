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
#ifndef _CN_VIDEO_DEC_H
#define _CN_VIDEO_DEC_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#ifndef _CN_VIDEO_COMMON_H
#include "cn_video_common.h"
#endif

#include "cnrt.h"

#define CN_MAXIMUM_DECODE_SURFACE 16

/**
 * Major Version number
 */
#define CNCODEC_DEC_VERSION_MAJOR   0

/**
 * Minor Version number
 */
#define CNCODEC_DEC_VERSION_MINOR   1

typedef void *CNVideo_Decode;

/**
 * decode instance ID, when Auto, a best engine will be choosed.
 */
typedef enum CNVideoDecode_Instance_enum{
    CNVideoDecode_Instance_0 = 0,                /*Specifies the decoder instance ID 0 */
    CNVideoDecode_Instance_1,                    /*Specifies the decoder instance ID 1 */
    CNVideoDecode_Instance_2,                    /*Specifies the decoder instance ID 2 */
    CNVideoDecode_Instance_3,                    /*Specifies the decoder instance ID 3 */
    CNVideoDecode_Instance_4,                    /*Specifies the decoder instance ID 4 */
    CNVideoDecode_Instance_5,                    /*Specifies the decoder instance ID 5 */
    CNVideoDecode_Instance_Auto                  /*Decoder instanceID will be set dynamically during decode*/
}CNVideoDecode_Instance;

/**
 * Data packet flags
 */
typedef enum CNVideoPacketFlag_enum{
    CNVideoPacket_EOS = 0,                      /*Set when last packet for this stream  */
    CNVideoPacket_Timestamp,                    /*Set when timestamp is valid */
    CNVideoPacket_Discontinuity                 /*Set when discontinuity is signal */
}CNVideoPacketFlag;


/**
 * structure for decode status
 */
typedef enum CNVideoDecodeStatus_enum
{
    CNVideoDecodeStatus_Running=0,              /*Deocder is still running*/
    CNVideoDecodeStatus_Success,                /*Decode succeed*/
    CNVideoDecodeStatus_Error,                  /*Error happened when decoding*/
    CNVideoDecodeStatus_Concealed               /*Frame is concealed*/
}CNVideoDecodeStatus;

/**
 * structure for decode status and ErrorMB count
 */
typedef struct _CNVideoDecodeSummary
{
    CNVideoDecodeStatus     DecodeStatus;       /* decode status */
    unsigned long           MBErrorCount;       /* Error MB count in this frame */
}CNVideoDecodeSummary;


/**
 * structure for query supported codecs
 */
typedef struct _CNVideoCodecSupportCodecs
{
    unsigned int            DecodeCodecNum;      /* supported decode codec type number*/
    CNVideoCodec            DecodeCodecArray[CNVideoCodec_NumCodecs]; /*supported decode codec type list*/
}CNVideoCodecSupportCodecs;

/**
 * structure for query codec capability
 */
typedef struct _CNVIDEODECODECAPS
{
    CNVideoCodec            CodecType;          /* In, Specify CodecType*/
    CNVideoChromaFormat     ChromaFormat;       /* In, Specify ChromaFormat*/
    unsigned int            BitDepthMinus8;     /* In, Specify BitDepth*/
    unsigned char           Supported;          /* Out, 0 not supported, otherwise supported*/
    unsigned int            MaxWidth;           /* Out, Maximum supported decode Width, in Pixel*/
    unsigned int            MaxHeight;          /* Out, Maximum supported decode Height, in Pixel*/
    unsigned short          MinWidth;           /* Out, Minimum supported decode Width, in Pixel*/
    unsigned short          MinHeight;          /* Out, Minimum supported decode Height, in Pixel*/
}CNVIDEODECODECAPS;

/**
 * structure for video Sequence Information
 */
typedef struct _CNVIDEOFORMAT
{
    CNVideoCodec            CodecType;          /* Out, compress type */
    CNVideoChromaFormat     ChromaFormat;       /* Out, Chroma format */
    unsigned int            Width;              /* Out, coded frame width, in pixel */
    unsigned int            Height;             /* Out, coded frame height, in pixel */
    unsigned int            Bitrate;            /* Out, bit stream's bitrate */
    unsigned int            MinInBufNum;        /* Out, minmum in buffer is required for decode */
    unsigned int            MinOutBufNum;       /* Out, minmum out buffer is requied for decode, including Refs buffer + Cache buffer */
    cnrtChannelType_t       CnrtChannel;        /* Out, current cnrtchannel in use*/
    /* Display area, example:
     * coded_width = 1920, coded_height = 1088
     * Crop_area = { 0,0,1920,1080 }
     */
    struct {
        int                 Left;               /* Out, left position of crop area */
        int                 Top;                /* Out, Top position of crop area */
        int                 Right;              /* Out, right position of crop area */
        int                 Bottom;             /* Out, Bottom position of crop area */
    } Crop_Area;

    /* Out, Display aspect ratio */
    struct {
        int                 X;
        int                 Y;
    } Display_Aspect_Ratio;

    /* Out, stream's framerate, Numerator / Denominator */
    struct {
        unsigned int        Numerator;
        unsigned int        Denominator;
    } Frame_Rate;

    /**
     * Video Signal Description
     */
    struct {
        unsigned char       Format          : 3; /* Out: 0 Component, 1 PAL, 2 NTSC, 3 SECAM, 4 MAC, 5 Unspecified, 6/7 reserved */
        unsigned char       Full_range_flag : 1; /* Out: Luma & Chroma is full range */
        unsigned char       Reserved        : 4;
        unsigned char       Color_Primaries;     /* Out: chromaticity coordinates of source primaries */
        unsigned char       Characteristics;     /* Out: opto-electronic transfer characteristic of the source picture */
        unsigned char       Coefficients;        /* Out: matrix coefficients For RGB to Luma/Chroma*/
    } Video_Signal_Info;
}CNVIDEOFORMAT;


/**
 * Structure for specifying decoder creation infomation
 */
typedef struct _CNCREATEVIDEODECODEINFO
{
    CNVideoCodec            Codectype;              /* In, See CNVideoCodec */
    CNVideoDecode_Instance  Instance;               /* In, See CNVideoCodec_Instance */
    unsigned int            CardID;                 /* In, Specify which card to use */
    CNMemoryAllocateType    MemoryAllocate;         /* In, See CNMemoryAllocateType, if Use, APP should allocate memory */
    CNVideoChromaFormat     ChromaFormat;           /* In, Specify Video chroma format */
    unsigned int            Progressive;            /* In, specify progressive or interlaced */
    unsigned long           Width;                  /* In, Specify video Width, in pixel */
    unsigned long           Height;                 /* In, Specify video Height, in Pixel */
    unsigned long           BitDepthMinus8;         /* In, Specify video bit depth, value "bitdepth - 8" */
    CNVideoSurfaceFormat    OutputFormat;           /* In, Specify Video output format */
    int                     Batch;                  /* In, for JPG only, Batch operation can improve decode performance */
    unsigned long           NumOfInputSurfaces;     /* In, Number of input surfaces */
    unsigned long           NumOfOutputSurfaces;    /* In, Number of output surfaces */
    long long               InMemoryPtr[CN_MAXIMUM_DECODE_SURFACE];                   /* available only when CNVideoMemory_Use */
    long long               MemoryPtr[CN_MAXIMUM_DECODE_SURFACE][CN_MAXIMUM_PLANE];   /* available only when CNVideoMemory_Use */
    void                    *pUserPtr;              /* In, Bypass Userptr */
    int                     SameImageSize;          /* For JPEG only, if same size, jpeg output buffer will not be allocated dynamicly.
                                                       If MemoryAllocate is CNVideoMemory_Allocate, output buffer will be allocated when start decode,
                                                       otherwise MemoryPtr will be used for JpegOutput.
                                                       If JPEG image size is not same, buffer will be allocated in Arm side.
                                                    */
} CNCREATEVIDEODECODEINFO;

/**
 * Structure for Jpeg info
 */
typedef struct _CNJPEGEXT
{
    unsigned long           Width;               /* Out, Width of decoded Jpeg, in pixel*/
    unsigned long           Height;              /* Out, Height of decoded Jpeg, in pixel*/
    CNVideoDecodeStatus     DecodeStatus;        /* Out, decode status*/
}CNJPEGEXT;

/**
 * Structure for decoded frame information
 */
typedef struct _CNPICTUREINFO
{
    unsigned long           SliceType;           /* Out, not available in C20L*/
    unsigned long           ReferenceCount;      /* Out, reference count for this frame */
    long long               Pts;                 /* Out, Presentation time for frame */
    unsigned long           Index;               /* Out, index for this frame, 0 -- NumOfOutputSurfaces -1 */
    unsigned long           Flag;                /* Out, Flag for this frame, EOS/Timestamp */
    unsigned int            Planes;              /* Out, plane count for this frame */
    unsigned int            Stride[CN_MAXIMUM_PLANE]; /*Out, stride for each plane */
    long long               MemoryPtr[CN_MAXIMUM_PLANE];/*Out, Memory address for each plane */
    CNJPEGEXT               JpegExt;             /* only available when jpeg decoding */
} CNPICTUREINFO;


/**
 * Structure for input stream information
 */
typedef struct _CNSTREAMINFO
{
    long long               Pts;                 /* In, frame's Presentation time stamp, available when CNVideoPacket_Timestamp is set */
    unsigned long           Flag;                /* In, See CNVideoPacketFlag */
    unsigned long           BitSize;             /* In, Specify bitstream buffer */
    void *                  Data;                /* In, Address for bitstream buffer */
    unsigned long           BufLength;           /* In, device buffer length */
}CNSTREAMINFO;


/** 
 * decoder callbacks
 * The decoder will call these during decode, when a picture is decoded, or sequence info parsed, or EOS
 * First argument "void *pUserData" is used for bypass userptr
 */
typedef int (* PCNSEQUENCECALLBACK)(void *, CNVIDEOFORMAT *);
typedef int (* PCNNEWFRAMECALLBACK)(void *, CNPICTUREINFO *);
typedef int (* PCNEOSCALLBACK)(void*);
typedef void (* PCNEVENTCALLBACK)(CNVideo_EventType EventType, void *);

/**
 * \brief Returns the version information for the cncodec library.
 *
 * @param version[out], return version of cncodec library
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_GetVersion(CNCodecVersion *version);

/**
 * @brief Get supported codectype list
 *
 * @param CodecSummary[out], return supported codectype list
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_GetSupportCodecs(CNVideoCodecSupportCodecs *SupportCodecs);


/**
 * @brief Get codec detail info
 *
 * @param CodecCaps[out], return HW's capability for this codec
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_GetCodecCap(CNVIDEODECODECAPS *CodecCaps);


/**
 * @brief create decoder
 *
 * @param handle[out], return decode's handle
 * @param pSequence[in], give sequence callback to decode
 * @param PCNNEWFRAMECALLBACK[in], give new frame callback to decode
 * @param PCNEOSCALLBACK[in], give eos callback to decode
 * @param CNCREATEVIDEODECODEINFO[in], specify decode's parameter
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_Create(CNVideo_Decode         *handle,
                                        PCNSEQUENCECALLBACK pSequence,
                                        PCNNEWFRAMECALLBACK pNewFrame,
                                        PCNEOSCALLBACK pEOS,
                                        PCNEVENTCALLBACK pEvent,
                                        CNCREATEVIDEODECODEINFO* CreateInfo);

/**
 * @brief Destroy decoder
 * 
 * @param handle[in], decode handle to be destroy
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_Destroy(CNVideo_Decode handle);


/**
 * @brief Abort decoder
 *
 * @param handle[in], decode handle to be abort.
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_Abort(CNVideo_Decode handle);


/**
 * @brief start decode, shall be called when sequence callback be called
 * 
 * @param handle[in], decode handle to be started
 * @param CreateInfo[in], config decoder again according to sequence information.
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_Start(CNVideo_Decode handle, CNCREATEVIDEODECODEINFO *CreateInfo);


/**
 * @brief, stop decode, invoked when eos callback get called
 *
 * @param handle[in], decode handle to be stopped
 * @return CNVideoCodec_Success if success, else failed.*/ 
int CN_Decode_Stop(CNVideo_Decode handle);


//ARM not provide,   to be defined  TODO add callback
int CN_Decode_GetStatus(CNVideo_Decode handle, unsigned int index, CNVideoDecodeSummary *decodeStatus);


/**
 * @brief, feed data to decoder
 *
 * @param handle[in], decode's handle
 * @param pStream[in], stream to be feeded to decoder
 * @param timeout[in], in ms, -1 wait infinitely
 * @return if CNVideoCodec_Timeout timeout, else if CNVideoCodec_Success success, else failed.
 */
int CN_Decode_FeedData(CNVideo_Decode handle, CNSTREAMINFO *pStream, int timeout);

/**
 * @brief, add reference count to a decoded buffer
 * 
 * @param handle[in], decode's handle
 * @param index[in],index of buffer to be hold
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_AddRef(CNVideo_Decode handle, unsigned int index);

/**
 * @brief, decrease reference count to a decoded buffer
 *
 * @param handle[in], decoder's handle
 * @param index[in], index of buffer to be decreased
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Decode_ReleaseRef(CNVideo_Decode handle, unsigned int index);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif
