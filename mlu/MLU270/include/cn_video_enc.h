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
#ifndef _CN_VIDEO_ENC_H
#define _CN_VIDEO_ENC_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#ifndef _CN_VIDEO_COMMON_H
#include "cn_video_common.h"
#endif

typedef void *CNVideo_Encode;

#define CNVideoEncode_MAXIMUM_SURFACE 16

/**
 * Major Version number
 */
#define CNVIDEOENCODE_VERSION_MAJOR   0

/**
 * Minor Version number
 */
#define CNVIDEOENCODE_VERSION_MINOR   1


/**
 * encode instance ID, when Auto, a best engine will be choosed.
 */
typedef enum CNVideoEncode_Instance_enum{
    CNVideoEncode_Instance_0 = 0,                /*Specifies the Encoder instance ID 0 */
    CNVideoEncode_Instance_1,                    /*Specifies the Encoder instance ID 1 */
    CNVideoEncode_Instance_2,                    /*Specifies the Encoder instance ID 2 */
    CNVideoEncode_Instance_3,                    /*Specifies the Encoder instance ID 3 */
    CNVideoEncode_Instance_4,                    /*Specifies the Encoder instance ID 4 */
    CNVideoEncode_Instance_5,                    /*Specifies the Encoder instance ID 5 */
    CNVideoEncode_Instance_Auto                  /*Encoder instanceID will be set dynamically during encoding*/
}CNVideoEncode_Instance;


/**
 * Enum for H264&H265 profile info
 */
typedef enum CNVideoEncode_Profile_enum
{
    CNVideoEncode_Profile_H264_Baseline,
    CNVideoEncode_Profile_H264_Main,
    CNVideoEncode_Profile_H264_High,
    CNVideoEncode_Profile_H264_High_10,

    CNVideoEncode_Profile_H265_Main,
    CNVideoEncode_Profile_H265_Main_Still,
    CNVideoEncode_Profile_H265_Main_Intra,
    CNVideoEncode_Profile_H265_Main_10
}CNVideoEncode_Profile;


/**
 * Enum for H264&H265 level
 */
typedef enum CNVideoEncode_Level_enum
{
    CNVideoEncode_Level_H264_1 = 0,
    CNVideoEncode_Level_H264_1b,
    CNVideoEncode_Level_H264_11,
    CNVideoEncode_Level_H264_12,
    CNVideoEncode_Level_H264_13,
    CNVideoEncode_Level_H264_2,
    CNVideoEncode_Level_H264_21,
    CNVideoEncode_Level_H264_22,
    CNVideoEncode_Level_H264_3,
    CNVideoEncode_Level_H264_31,
    CNVideoEncode_Level_H264_32,
    CNVideoEncode_Level_H264_4,
    CNVideoEncode_Level_H264_41,
    CNVideoEncode_Level_H264_42,
    CNVideoEncode_Level_H264_5,
    CNVideoEncode_Level_H264_51,

    CNVideoEncode_Level_H265_Main_1,
    CNVideoEncode_Level_H265_High_1,
    CNVideoEncode_Level_H265_Main_2,
    CNVideoEncode_Level_H265_High_2,
    CNVideoEncode_Level_H265_Main_21,
    CNVideoEncode_Level_H265_High_21,

    CNVideoEncode_Level_H265_Main_3,
    CNVideoEncode_Level_H265_High_3,
    CNVideoEncode_Level_H265_Main_31,
    CNVideoEncode_Level_H265_High_31,

    CNVideoEncode_Level_H265_Main_4,
    CNVideoEncode_Level_H265_High_4,
    CNVideoEncode_Level_H265_Main_41,
    CNVideoEncode_Level_H265_High_41,

    CNVideoEncode_Level_H265_Main_5,
    CNVideoEncode_Level_H265_High_5,
    CNVideoEncode_Level_H265_Main_51,
    CNVideoEncode_Level_H265_High_51,
    CNVideoEncode_Level_H265_Main_52,
    CNVideoEncode_Level_H265_High_52,

    CNVideoEncode_Level_H265_Main_6,
    CNVideoEncode_Level_H265_High_6,
    CNVideoEncode_Level_H265_Main_61,
    CNVideoEncode_Level_H265_High_61,
    CNVideoEncode_Level_H265_Main_62,
    CNVideoEncode_Level_H265_High_62
}CNVideoEncode_Level;

typedef enum CNVideoEncode_Attribute_Enum{
    /**
     * Set stream's level
     */
    CNVideoEncode_Attr_Level = 0,

    /*
     * Set stream's profile(see CNVideoEncode_Profile)
     */
    CNVideoEncode_Attr_Profile,

    /*
     * Set stream's framerate
     */
    CNVideoEncode_Attr_Framerate,


    /**
     * Set bitrate control mode，seeCNVideoEncode_Param_RC_Mode
     */
    CNVideoEncode_Attr_Ratecontrol_Modes,


    /**
     * Set I frame's QP, only available when no bitrate control
     */
    CNVideoEncode_Attr_H264_I_FRAME_QP,

    /**
     * Set P frame's QP, only available when no bitrate control
     */
    CNVideoEncode_Attr_H264_P_FRAME_QP,

    /**
     * Set B frame's QP, only available when no bitrate control
     */
    CNVideoEncode_Attr_H264_B_FRAME_QP,

    /**
     * Set QP range.
     *
     * only available when enabling bitrate control
     */
    CNVideoEncode_Attr_QP_RANGE,

    /**
     * Set encoding's virtual buffer size
     */
    CNVideoEncode_Attr_VBV,

    /*
     * Set maximum reference Frame number for encoder
     */
    CNVideoEncode_Attr_RefFrames,

    /**
     * set infra refresh interval for encoder
     */
    CNVideoEncode_Attr_Slice_Intra_Refresh,

    /**
     * Set B frame's number
     */
    CNVideoEncode_Attr_Num_BFrames,

    /**
     * Insert SPS&PPS when IDR
     */
    CNVideoEncode_Attr_INSERT_SPS_PPS_AT_IDR,

    /**
     * Set entropy mode(CAVLC or CABAC)
     */
    CNVideoEncode_Attr_H264_Entropy_Mode,

    /**
     * Set GOP's length
     */
    CNVideoEncode_Attr_GOP_SIZE,

    /**
     * Set IDR interval
     */
    CNVideoEncode_Attr_IDR_INTERVAL,

    CNVideoEncode_Attr_NUMAttributes
}CNVideoEncode_Attribute;


/**
 * entropy mode enum.
 */
typedef enum CNVideoEncode_Entropy_Mode_enum {
    CNVideoEncode_Entropy_Mode_CAVLC = 0,
    CNVideoEncode_Entropy_Mode_CABAC,
    CNVideoEncode_Entropy_Mode_Sum
}CNVideoEncode_Entropy_Mode;


/**
 * slice mode enum
 */
typedef enum CNVideoEncode_Slice_Mode_enum {
    CNVideoEncode_Slice_Mode_Single,
    CNVideoEncode_SLICE_Mode_MAX_MB,
    CNVideoEncode_SLICE_Mode_Sum
}CNVideoEncode_Slice_Mode;


/**
 * Frame type enum
 */
typedef enum CNVideoEncode_Pic_Type_enum
{
    CNVideoEncode_Pic_Type_P = 0x0,
    CNVideoEncode_Pic_Type_B,
    CNVideoEncode_Pic_Type_I,
    CNVideoEncode_Pic_Type_IDR,
    CNVideoEncode_Pic_Type_BI,
    CNVideoEncode_Pic_Type_SKIPPED,
    CNVideoEncode_Pic_Type_INTRA_REFRESH,
    CNVideoEncode_Pic_Type_Sum
} CNVideoEncode_Pic_Type;


/**
 * rate control type enum
 */
 typedef enum CNVideoEncode_RC_Mode_enum
{
    CNVideoEncode_RC_Mode_VBR = 0,
    CNVideoEncode_RC_Mode_CBR,
    CNVideoEncode_RC_Mode_Sum
}CNVideoEncode_RC_Mode;


/**
 * Flags of encode picture
 */
typedef enum CNVideoEncode_PIC_Flags_enum
{
    CNVideoEncode_PIC_Flag_ForceIntra         = 0x1,   /* Force slice in Intra */
    CNVideoEncode_PIC_Flag_ForceIDR           = 0x2,   /* Force slice in IDR */
    CNVideoEncode_PIC_Flag_InsertSPSPPS       = 0x4,   /* Insert SPS PPS in current frame */
    CNVideoEncode_PIC_Flag_EOS                = 0x8,   /**< Indicates end of the input stream */
} CNVideoEncode_PIC_Flags;


/**
 * H265 CU(coded Unit) size type
 */
typedef enum CNVideoEncode_H265_CUSize_enum
{
    CNVideoEncode_H265_CUSize_8x8 = 0,
    CNVideoEncode_H265_CUSize_16x16,
    CNVideoEncode_H265_CUSize_32x32,
    CNVideoEncode_H265_CUSize_64x64,
    CNVideoEncode_H265_CUSize_Sum
}CNVideoEncode_H265_CUSize;

/**
 * Input buffer's parameter.
 */
typedef struct _CNVideoEncode_Input_Buffer
{
    unsigned int                                    width;                                        /* [in]Buffer's width */
    unsigned int                                    height;                                       /* [in]Buffer's height */
    CNVideo_Memory_Heap                             heap;                                         /* [in]Buffer heap */
    unsigned int                                    stride[CN_MAXIMUM_PLANE];                     /* [out]Buffer's pitch */
    unsigned long                                   inputBuffer[CN_MAXIMUM_PLANE];                /* [out]Buffer address */
} CNVideoEncode_Input_Buffer;


/**
 * parameters for video encoding rate control
 */
typedef struct _CNVideoEncode_RC_Params
{
    unsigned int                                    gopLength;          /* [in] Specify GOP length */
    CNVideoEncode_RC_Mode                           rcMode;             /* [in] Specify rate control Mode */
    unsigned int                                    constIQP;           /* [in] Specify QP for I frame */
    unsigned int                                    constPQP;           /* [in] Specify QP for P frame */
    unsigned int                                    constBQP;           /* [in] Specify QP for B frame */

    unsigned int                                    minIQP;             /* [in] Specify min QP for I frame */
    unsigned int                                    minPQP;             /* [in] Specify min QP for P frame */
    unsigned int                                    minBQP;             /* [in] Specify min QP for B frame */

    unsigned int                                    maxIQP;             /* [in] Specify max QP for I frame */
    unsigned int                                    maxPQP;             /* [in] Specify max QP for P frame */
    unsigned int                                    maxBQP;             /* [in] Specify Max QP for B frame */


    unsigned int                                    initIQP;            /* [in] Specify initial QP for I frame */
    unsigned int                                    initPQP;            /* [in] Specify initial QP for P frame */
    unsigned int                                    initBQP;            /* [in] Specify initial QP for B frame */


    unsigned int                                    targetBitrate;      /* [in] Specify target bitrate(in bits/sec) */
    unsigned int                                    peakBitrate;        /* [in] Specify peak bitrate(in bits/sec)，Available when VBR */
    unsigned int                                    virtualBufferSize;  /* [in] Specify VBV(HRD) buffer size，0, use default. */
    unsigned int                                    enableQPRange;      /* [in] 1，minX(I/B/P)QP, maxXQP work */
} CNVideoEncode_RC_Params;

/**
 * Structure of CNVideoEncode_H264_Config
 * Configration parameter for H264 to be set when initializing
 */
typedef struct _CNVideoEncode_H264_Config
{
    CNVideoEncode_Profile                           profile;                            /* [in]: Specify stream's profile */
    CNVideoEncode_Level                             level;                              /* [in]: Specify stream's level */
    unsigned int                                    enableAUD;                          /* [in]: 1, add access unit delimiter */

    unsigned int                                    insertSPSPPSWhenIDR;                /* [in]: 1, insert SPSPPS before IDR， 0 not */

    unsigned int                                    IframeInterval;                     /* [in]: Intra frame's interval */
    unsigned int                                    idrInterval;                        /* [in]: IDR frame's interval */

    unsigned int                                    spsId;                              /* [in]: Specify SPS ID */
    unsigned int                                    ppsId;                              /* [in]: Specify PPS ID */

    unsigned int                                    enableIR;                           /* [in]: enable intra refresh when encoding */
    unsigned int                                    IRCount;                            /* [in]: MB count of Intra refresh */

    unsigned int                                    maxNumRefFrames;                    /* [in]: Max ref number our encoder can support */

    unsigned int                                    numBFrames;                         /* [in]: B frame number encoder can support */

    unsigned int                                    hRange;                             /* [in]: mv search h range */

    unsigned int                                    vRange;                             /* [in]: mv search v range */

    unsigned int                                    cabacInitIdc;                       /* [in]: CABAC initial table, 0,1,2 for H264 and 0,1 for HEVC*/

    unsigned int                                    maxMBPerSlice;                      /* [in]: max MB in one Slice*/

    CNVideoEncode_Entropy_Mode                      entropyMode;                        /* [in]: CAVLC or CABAC*/
    CNVideoEncode_Slice_Mode                        sliceMode;                          /* [in]: Slice mode of a encoder session, single/MaxMB */

/* SEI info*/
    unsigned int                                    enableBufferingPeriodSEI;           /* [in]: 1 add SEI buffering period, 0 not */
    unsigned int                                    enablePictureTimingSEI;             /* [in]: 1 add SEI picture timing, 0 not */
    unsigned int                                    enableFramePackingSEI;              /* [in]: 1 add frame packing arrangement, 0 not */
    unsigned int                                    enableRecoveryPointSEI;             /* [in]: 1 add recovery point message, 0 not*/

/* VUI info */
    unsigned int                                    overscanInfoPresent;                /* [in]: 1 overscanInfo will be added */
    unsigned int                                    overscanInfo;                       /* [in]: specify overscan information */
    unsigned int                                    videoSignalTypePresent;             /* [in]: 1,videoFormat/videoFullRangeFlag/colourDescriptionPresentFlag will be added */
    unsigned int                                    videoFormat;                        /* [in]: specify VideoFormat information */
    unsigned int                                    videoFullRange;                     /* [in]: specify VideoFullRange information */
    unsigned int                                    colourDescriptionPresent;           /* [in]: 1 colourPrimaries, transferCharacteristics，colourMatrix info will be added  */
    unsigned int                                    colourPrimaries;                    /* [in]: specify colourPrimaries */
    unsigned int                                    transferCharacteristics;            /* [in]: specify opto-electronic transfer */
    unsigned int                                    colourMatrix;                       /* [in]: specify matrix coefficients for RGB to Luma/Chroma */
    unsigned int                                    chromaSampleLocation;               /* [in]: 1, chromaSampleLocationTop and chromaSampleLocationBot info will be added, 0 not.*/
    unsigned int                                    chromaSampleLocationTop;            /* [in]: Specify chroma sample location for top field */
    unsigned int                                    chromaSampleLocationBot;            /* [in]: Specify chroma sample location for bottom field */
    unsigned int                                    bitstreamRestrictionFlag;           /* [in]: 1, bitstreamrestriction information will be added.*/

    unsigned int                                    chromaFormatIDC;                    /* [in]: Specify chromaIDC 1 yuv420, 3 yuv444 */
    unsigned int                                    bitDepth;                           /* [in]: Specify bit depth 1 8bit, 2 10bit, 3 12bit */
} CNVideoEncode_H264_Config;


/**
 * Structure of CNVideoEncode_H265_Config
 * Configration parameter for H265 to be set when initializing
 */
typedef struct _CNVideoEncode_H265_Config
{
    CNVideoEncode_Profile                           profile;                            /* [in]: specify stream's profile */
    CNVideoEncode_Level                             level;                              /* [in]: specify stream's level */
    unsigned int                                    tier;                               /* [in]: specify stream's level tier */

    CNVideoEncode_H265_CUSize                       minCU;                              /* [in]: specify stream's min CU(code unit) size*/

    CNVideoEncode_H265_CUSize                       maxCU;                              /* [in]: specify stream's max CU size*/

    unsigned int                                    enableAUD;                          /* [in]: insert access unit delimiter   */

    unsigned int                                    insertSPSPPSWhenIDR;                /* [in]: 1 insert SPSPPS before IDR， 0 not */

    unsigned int                                    IframeInterval;                     /* [in]: Intra frame's interval */
    unsigned int                                    idrInterval;                        /* [in]: IDR frame's interval */

    unsigned int                                    vpsId;                              /* [in]: Specify VPS ID */
    unsigned int                                    spsId;                              /* [in]: Specify SPS ID */
    unsigned int                                    ppsId;                              /* [in]: Sepcify PPS   ID */

    unsigned int                                    enableIR;                           /* [in]: 1 enable Encode's intra refresh */
    unsigned int                                    IRCount;                            /* [in]: MB count of Intra refresh */

    unsigned int                                    maxNumRefFrames;                    /* [in]: Max Ref frame num of encoder session */

    unsigned int                                    numBFrames;                         /* [in]: Max B frame num of encode session */
    unsigned int                                    hRange;                             /* [in]: mv search h range */

    unsigned int                                    vRange;                             /* [in]: mv search v range */

    unsigned int                                    cabacInitIdc;                       /* [in]: CABAC initial table, 0,1,2 for H264 and 0,1 for HEVC*/

    unsigned int                                    maxMBPerSlice;                      /* [in]: max MB in one Slice*/

    CNVideoEncode_Slice_Mode                        sliceMode;                          /* [in]: Slice mode of a encoder session, single/MaxMB */

/* VUI info */
    unsigned int                                    overscanInfoPresent;                /* [in]: 1 overscanInfo will be added */
    unsigned int                                    overscanInfo;                       /* [in]: specify overscan information */
    unsigned int                                    videoSignalTypePresent;             /* [in]: 1,videoFormat/videoFullRangeFlag/colourDescriptionPresentFlag will be added */
    unsigned int                                    videoFormat;                        /* [in]: specify VideoFormat information */
    unsigned int                                    videoFullRange;                     /* [in]: specify VideoFullRange information */
    unsigned int                                    colourDescriptionPresent;           /* [in]: 1 colourPrimaries, transferCharacteristics，colourMatrix info will be added */
    unsigned int                                    colourPrimaries;                    /* [in]: specify colourPrimaries  */
    unsigned int                                    transferCharacteristics;            /* [in]: specify opto-electronic transfer */
    unsigned int                                    colourMatrix;                       /* [in]: specify matrix coefficients for RGB to Luma/Chroma */
    unsigned int                                    chromaSampleLocation;               /* [in]: 1, chromaSampleLocationTop and chromaSampleLocationBot info will be added, 0 not */
    unsigned int                                    chromaSampleLocationTop;            /* [in]: Specify chroma sample location for top field */
    unsigned int                                    chromaSampleLocationBot;            /* [in]: Specify chroma sample location for bottom field */
    unsigned int                                    bitstreamRestrictionFlag;           /* [in]: 1, bitstreamrestriction information will be added */
    unsigned int                                    chromaFormatIDC;                    /* [in]: Specify chromaIDC 1 yuv420, 3 yuv444 */
    unsigned int                                    bitDepth;                           /* [in]: Specify bit depth 1 8bit, 2 10bit, 3 12bit*/
} CNVideoEncode_H265_Config;

/**
 * structure of CNVideoEncode_Create_Params,
 * Initialiation paramter for encoding session
 */
typedef struct _CNVideoEncode_Create_Params
{
    CNVideoEncode_Instance                          instance;                                    /*[in] must, default auto */
    unsigned int                                    cardid;                                      /*[in] must, default 0 */
    unsigned int                                    videoWidth;                                  /*[in] must, specify video width */
    unsigned int                                    videoHeight;                                 /*[in] must, specify video height */
    unsigned int                                    codecType;                                   /*[in] must，only support 264 H265 */
    unsigned int                                    darWidth;                                    /*[in] option，specify display aspect ratio */
    unsigned int                                    darHeight;                                   /*[in] option，specify display aspect ratio */
    unsigned int                                    frameRateNum;                                /*[in] option，specify frameRateNum，default 30 */
    unsigned int                                    frameRateDen;                                /*[in] option，specify frameRateDen, default 1，frame rate = frameRateNum / frameRateDen ). */
    CNVideoEncode_RC_Params                         RCParams;                                    /*[in] Set parameter for rate control */
    CNVideoEncode_H264_Config                       H264Config;                                  /*[in] Set parameter for H264 encoder */
    CNVideoEncode_H265_Config                       H265Config;                                  /*[in] Set parameter for H265 encoder */
    unsigned int                                    maxVideoWidth;                               /*[in] option, max video width for all supported resolution */
    unsigned int                                    maxVideoHeight;                              /*[in] option, max video height for all supported resolution  */
    CNMemoryAllocateType                            memoryType;                                  /*[in] option, specify memory allocate type, allocate/use */
    unsigned int                                    numInputBuf;                                 /*[in] must，input buffer number */
    unsigned int                                    numBitFrameBuf;                              /*[in] must，output buffer number */
    CNVideoSurfaceFormat                            bufferFmt;                                   /*[in] must，input buffer format */
    CNVideoEncode_Input_Buffer                      inputBuf[CNVideoEncode_MAXIMUM_SURFACE];     /*[in] when memoryYpe is CNVideoEncodeMemoryType_Use，it is  must */
    long long                                       BitFrameBuf[CNVideoEncode_MAXIMUM_SURFACE];  /*[in] when memoryYpe is CNVideoEncodeMemoryType_Use，it is  must */
} CNVideoEncode_Create_Params;

/**
 * Structure of CNVideoEncode_BitStreamInfo, parameter for each bitstream buffer
 */
typedef struct _CNVideoEncode_BitStreamInfo
{
    long long                                       Pts;
    unsigned long                                   Index;
    unsigned long                                   Flag;
    long long                                       MemoryPtr;
    int                                             bytesUsed;
} CNVideoEncode_BitStreamInfo;


/**
 * Structure of CNVideoEncode_PIC_Params, encoding parameter for each frame
 */
typedef struct _CNVideoEncode_PIC_Params
{
    unsigned int                                    Flags;                  /* [in]: See CNVideoEncode_PIC_Flags. */
    unsigned int                                    frameIdx;               /* [in]: inputPtr index in inputBuf，[0 - numInputBuf] */
    unsigned long long                              TimeStamp;              /* [in]: PTS of input frame*/
    unsigned long long                              Duration;               /* [in]: Duration of input frame*/
    CNVideoEncode_Input_Buffer                      inputPtr;               /* [in]: Buffer from input buffer array, in CNVideoEncode_Create_Params*/
    CNVideoEncode_Pic_Type                          picType;                /* [in]: specify which picture type will frame be encoded as */
    int                                             quality;                /* [in]: JPEG only，image quality */
    unsigned short                                  Quant[4][8 * 8];        /* [in]: JPEG only，input Quant table */
    unsigned int                                    huffCode[8][256];       /* [in]: JPEG only，input Huffman code */
    unsigned int                                    huffSize[8][256];       /* [in]: JPEG only, input Huffman size */
} CNVideoEncode_PIC_Params;


/**
 * encoder's callback
 * The encoder will call these during encoding, when a picture is encoded, or EOS event
 * First argument "void *pUserData" is used for bypass userptr
 */
typedef int (* PCNNEWBITCALLBACK)(void *, CNVideoEncode_BitStreamInfo *);
typedef int (* PCNEOSCALLBACK)(void *);
typedef void (*PCNEVENTCALLBACK)(CNVideo_EventType EventType, void *);

/**
 * \brief Returns the version information for the cncodec library.
 *
 * @param version[out], return version of cncodec library
 * @return CNVideoCodec_Success if success, else failed.
 */
int CN_Encode_GetVersion(CNCodecVersion *version);


/**
 * @brief create encoder
 *
 * @param handle[out], return encoder's handle
 * @param type[in], Specify which codec type: H264/H265/JPEG
 * @param pNewFrame[in], give new bit frame callback to encoder
 * @param pEOS[in],  give eos callback to encoder
 * @param userPTR[in], bypass user's pointer
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Create(CNVideo_Encode         *handle,
                                        CNVideoCodec type,
                                        PCNNEWBITCALLBACK pNewFrame,
                                        PCNEOSCALLBACK pEOS,
                                        PCNEVENTCALLBACK pEvent,
                                        void *userPTR);


/**
 * @brief get the number of input formats
 *
 * @param handle[in],encoder's handle
 * @param inputFmtCount[out], number of input formats supported
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Get_Inputformat_Count(CNVideo_Encode handle, unsigned int *inputFmtCount);


/**
 * @brief get the list of supported format
 *
 * @param handle[in], encoder's handle
 * @param inputFmts[out], list of supported format
 * @param inputFmtArraySize[in], tell encoder inputFmts buffer size
 * @param inputFmtCount[out], number of input formats supported
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Get_Inputformat(CNVideo_Encode handle, CNVideoSurfaceFormat *inputFmts, unsigned int inputFmtArraySize, unsigned int *inputFmtCount);


/**
 * @brief, set encoder's attribute
 *
 * @param handle[in], encoder's handle
 * @param attribute[in], specify the attribute to be set
 * @param value[in], set the value for specified attribute
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Set_Attributes(CNVideo_Encode handle, CNVideoEncode_Attribute attribute, long long *value);

/**
 * @brief, feed frame to encoder
 *
 * @param handle[in], encoder's handle
 * @param encodePicParams[in], pass frame to encoder, frame related info will be given to encoder too
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Feed_Frame(CNVideo_Encode handle, CNVideoEncode_PIC_Params *encodePicParams);

/**
 * @brief, create inputbuffer for encoder
 *
 * @param handle[in], encoder's handle
 * @param pInput[out], return the buffer info created
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Create_InputBuffer(CNVideo_Encode handle, CNVideoEncode_Input_Buffer **pInput);

/**
 * @brief, wait for available input buffer
 *
 * @param handle[in], encoder's handle
 * @param index[out], return available buffer index[0 - numInputBuf]
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Available_InputBuffer(CNVideo_Encode handle, int *index, CNVideoEncode_Input_Buffer *pInput);

/**
 * @brief, destroy inputbuffer for encoder
 *
 * @param handle[in], encoder's handle
 * @param pInput[in], buffer to be destroyed
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Destroy_InputBuffer(CNVideo_Encode handle, CNVideoEncode_Input_Buffer *pInput);

/**
 * @brief, create bitStream(output) buffer for encoder
 *
 * @param handle[in], encoder's handle
 * @param ptr[out], return the buffer address created
 * @param size[in], size of buffer to be created
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Create_BitStreamBuffer(CNVideo_Encode handle, long long **ptr, int size);

/**
 * @brief destroy bitstream(output) buffer for encoder
 *
 * @param handle[in], encoder's handle
 * @param ptr[in], buffer address to be destroyed
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Destroy_BitStreamBuffer(CNVideo_Encode handle, long long *ptr);

/**
 * @brief config encoder's parameter
 *
 * @param handle[in], encoder's handle
 * @param createEncodeParams[in], config encoder's parameter before start
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Initialize(CNVideo_Encode handle, CNVideoEncode_Create_Params *createEncodeParams);


/**
 * @brief destroy encoder
 *
 * @param handle[in], encoder's handle
 * @return CNVideoCodec_Success if success, else fail.*/
int CN_Encode_Destroy(CNVideo_Encode handle);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif
