/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc.
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

/************************************************************************
 *
 *  @file cnrt.h
 *
 *  @brief Runtime APIs provide programmable interfaces for users to develop
 *  their-owned programs, which includes device management, context
 *  management, memory management of both sides (devices and hosts), etc.
 *
 **************************************************************************/

#ifndef __CNRT_H
#define __CNRT_H

/************************************************************************
 *  Include files
 ************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus*/

/************************************************************************
 *  Definitions
 ************************************************************************/
/**< DLL exports controller. */
#if defined(WIN32) || defined(WINDOWS)
#ifdef USE_CNRT_DLL
#ifdef CNRT_DLL_EXPORTS
#define CNRT_DLL_API __declspec(dllexport)
#else /*CNRT_DLL_EXPORTS*/
#define CNRT_DLL_API __declspec(dllimport)
#endif /*CNRT_DLL_EXPORTS*/
#else
#define CNRT_DLL_API
#endif /*USE_CNRT_DLL*/
#else  /*WIN32 || WINDOWS*/
#define CNRT_DLL_API
#endif /*WIN32 || WINDOWS*/

/**< struct tailed */
#define CNRT_PARAM_END (void *)0xFFFFFFFF

/************************************************************************
 *  Data type declaration
 ************************************************************************/

#ifndef __CAMB_TYPES_H
#define __CAMB_TYPES_H
#if defined(WIN32) || defined(WINDOWS)
typedef unsigned __int64 u64_t;
typedef __int64 i64_t;
typedef unsigned __int32 u32_t;
typedef unsigned __int16 u16_t;
typedef unsigned __int8 u8_t;
typedef signed __int32 i32_t;
typedef signed __int16 i16_t;
typedef signed __int8 i8_t;

#else /*!WIN32 || WINDOWS*/

typedef uint64_t u64_t;
typedef int64_t i64_t;
typedef uint32_t u32_t;
typedef uint16_t u16_t;
typedef uint8_t u8_t;
typedef int32_t i32_t;
typedef int16_t i16_t;
typedef int8_t i8_t;

#endif /*WIN32||WINDOWS*/
#endif /*__CAMB_TYPES*/

#define CNRT_CHECK(statment)                                                  \
  do {                                                                        \
    int ret_code = (statment);                                                \
    if (ret_code != CNRT_RET_SUCCESS) {                                       \
      printf("[%s:%d] CNRT error, code: %d\n", __FILE__, __LINE__, ret_code); \
      exit(1);                                                                \
    }                                                                         \
  } while (false);

/**< Return values for CNRT API calls */
//! @brief An enum describes CNRT API return values.
/*! Function return values of CNRT API interfaces. */
typedef enum {
  CNRT_RET_SUCCESS = 0,
  /*!< The operation was successful. */
  CNRT_RET_WARNING_FAKE_DEVICE = 1,
  /*!< Use fake device currently. */
  CNRT_RET_ERR_INVALID = 632007,
  /*!< The supplied argument was invalid argument. */
  CNRT_RET_ERR_NOMEM = 632008,
  /*!< Insuffcient memory for the operation. */
  CNRT_RET_ERR_NODEV = 632009,
  /*!< No such device. */
  CNRT_RET_ERR_IO = 632010,
  /*!< I/O error. */
  CNRT_RET_ERR_SYS = 632011,
  /*!< System error. */
  CNRT_RET_ERR_ACCES = 632012,
  /*!< Permission denied. */
  CNRT_RET_ERR_FAULT = 632013,
  /*!< Bad address. */
  CNRT_RET_ERR_BUSY = 632014,
  /*!< Device or resource busy. */
  CNRT_RET_ERR_TIMEOUT = 632015,
  /*!< Time expired. */
  CNRT_RET_ERR_EXIST = 632016,
  /*!< Resource or file already exists. */
  CNRT_RET_ERR_NOSYS = 632017,
  /*!< Function not implemenmted. */
  CNRT_RET_ERR_AGAIN = 632018,
  /*!< try again later. */
  CNRT_RET_ERR_NORES = 632019,
  /*!< Out of resource. */
  CNRT_RET_ERR_UNSUPPORTED = 632020,
  /*!< Unsupported operation. */
  CNRT_RET_ERR_INVALID_POINTER = 632021,
  /*!< Invalid pointer. */
  CNRT_RET_ERR_NO_EXIST = 632022,
  /*!< Resource or file doesn't exist. */
  CNRT_RET_ERR_BROKEN = 632023,
  /*!< Data transmission is broken. */
  CNRT_RET_ERR_INIT = 632024,
  /*!< Uninitialized. */
  CNRT_RET_ERR_STREAM = 632025,
  /*!< Failure on Stream. */
  CNRT_RET_ERR_QUEUE = 632025,
  /*!< Failure on Queue. */
  CNRT_RET_ERR_OUT_RANGE = 632026,
  /*!< Number out of range. */
  CNRT_RET_ERR_MATH_OVERFLOW = 632027,
  /*!< Math result not representable. */
  CNRT_RET_ERR_FUNC_CALL = 632028,
  /*!< Failure to call runtime functions. */
  CNRT_RET_ERR_UNHANDLED = 632029,
  /*!< Unhandled error. */
  CNRT_RET_ERR_INVALID_TYPE = 632030,
  /*!< Invalid type. */
  CNRT_RET_ERR_INVALID_OP = 632031,
  /*!< Invalid operation. */
  CNRT_RET_ERR_MLU = 632032,
  /*!< MLU error. */
  CNRT_RET_ERR_ONCHIP_CORE = 632033,
  /*!< Onchip core error. */
  CNRT_RET_ERR_EVENT = 632034,
  /*!< Failure on event operation. */
  CNRT_RET_ERR_NOTIFIER = 632034,
  /*!< Failure on notifier operation. */
  CNRT_RET_ERR_RESHAPE = 632035,
  /*!< Failure on data reshape. */
  CNRT_RET_ERR_MEMCPY = 632036,
  /*!< Failure on memory copy. */
  CNRT_RET_ERR_ENCRYPT = 632037,
  /*!< Failure on encrypt. */
  CNRT_RET_ERR_INVALID_DATADESC = 632038,
  /*!< Invalid data descriptor. */
  CNRT_RET_ERR_UNKNOWN = 999991,
  /*!< Unknown error. */
  CNRT_RET_ERR_MAX
  /*!< The last one. */
} cnrtRet_t;

/**< Memory types available for allocator */
//! @brief An enum describes memory types available for allocator.
/*! Enumeration types, used to represent the memory types. */
typedef enum {
  CNRT_MEMTYPE_DEFAULT = 0,
  /*!< Host user space pagable memory. */
  CNRT_MEMTYPE_LOCKED,
  /*!< Host user space pinned memory. */
  CNRT_MEMTYPE_DEV
  /*!< Device memory. */
} cnrtMemType_t;

/**< Malloc types available for cnrtMallocBufferEx. */
//! @brief An enum describes malloc types available for cnrtMallocBufferEx.
/*! Internal enum. */
typedef enum { CNRT_MALLOC_EX_PARALLEL_FRAMEBUFFER = 1 } cnrtMallocExType_t;

/**< Execution modes of tasks on MLU. */
//! @brief An enum execution modes of tasks on MLU.
/*! The number of cores running on the Function of a device. */
typedef enum {
  CNRT_FUNC_TYPE_BLOCK = 1,
  /*!< Use 1 core. */
  CNRT_FUNC_TYPE_BLOCK0 = CNRT_FUNC_TYPE_BLOCK,
  /*!< Use IP core 0. */
  CNRT_FUNC_TYPE_BLOCK1 = CNRT_FUNC_TYPE_BLOCK0 + 1,
  /*!< Use IP heterogeneous core 1. */
  CNRT_FUNC_TYPE_UNION1 = 4,
  /*!< Use 4 cores. */
  CNRT_FUNC_TYPE_UNION2,
  /*!< Use 8 cores. */
  CNRT_FUNC_TYPE_UNION4,
  /*!< Use 16 cores. */
  CNRT_FUNC_TYPE_UNION8,
  /*!< Use 32 cores. */
  CNRT_FUNC_TYPE_MUTABLE
  /*!< Flexible mode. */
} cnrtFunctionType_t;

/**< DDR Channel for tasks used on MLU. */
//! @brief An enum describe DDR Channel for tasks used on MLU..
/*! Used to represent Channel types. */
typedef enum {
  CNRT_CHANNEL_TYPE_DUPLICATE = -2,
  /*!< Duplicate data on DDR channels, used in runtime context. */
  CNRT_CHANNEL_TYPE_NONE = -1,
  /*!< Use random channel. */
  CNRT_CHANNEL_TYPE_0 = 0,
  /*!< Use DDR channel 0. */
  CNRT_CHANNEL_TYPE_1,
  /*!< Use DDR channel 1. */
  CNRT_CHANNEL_TYPE_2,
  /*!< Use DDR channel 2. */
  CNRT_CHANNEL_TYPE_3
  /*!< Use DDR channel 3. */
} cnrtChannelType_t;

/**< Direction of data transmission. */
//! @brief An enum describes direction of data transmission.
/*! Direction of data transmission. */
typedef enum {
  CNRT_MEM_TRANS_DIR_HOST2DEV = 0,
  /*!< From host to device. */
  CNRT_MEM_TRANS_DIR_DEV2DEV,
  /*!< From device to device, not supported yet */
  CNRT_MEM_TRANS_DIR_DEV2HOST,
  /*!< From device to host */
  CNRT_MEM_TRANS_DIR_HOST2HOST,
  /*!< From host to host, not supported yet */
  CNRT_MEM_TRANS_DIR_NODIR
  /*!< no direction for init */
} cnrtMemTransDir_t;

/**< Parameter for function call */
/*!
 *  @struct cnrtDim3_t
 *  @brief A struct describes parameter for function call.
 *
 *  Dimension of task execution */
typedef struct {
  unsigned int x; /*!< x aixs */
  unsigned int y; /*!< y aixs */
  unsigned int z; /*!< z aixs */
} cnrtDim3_t;

/**< Parameter for init function call*/

/*!
 *  @struct cnrtInitFuncParam_t
 *  @brief A struct.
 *
 *  Struct called by the cnrtInitFunctionMemory_V2 interface, used for parameter transfer. */
typedef struct {
  bool *muta;             /*!< mutable option*/
  int *data_parallelism;  /*!< data parallelism*/
  unsigned int *affinity; /*!< affinity*/
  void *end;              /*!< end of struct*/
} cnrtInitFuncParam_t;

/**< Parameter for invoke function call*/
/*!
 *  @struct cnrtInvokeFuncParam_t
 *  @brief A struct.
 *
 *  Parameters of the interface cnrtInvokeFunction (), which need to be invoked by the user. */
typedef struct {
  int *data_parallelism;  /*!< data parallelism*/
  unsigned int *affinity; /*!< affinity*/
  void *end;              /*!< end of struct*/
} cnrtInvokeFuncParam_t;

/**< Data type and data order*/
//! @brief An enum.
/*! Data types */
typedef enum cnrtDataType {
  CNRT_INVALID = 0x0,
  /*!< Invalid data */
  CNRT_FLOAT16 = 0x12,
  /*!< 16-bit floating-point data */
  CNRT_FLOAT32 = 0x13,
  /*!< 32-bit floating-point data */
  CNRT_FLOAT64 = 0x14,
  /*!< 64-bit floating-point data */
  CNRT_INT8 = 0x21,
  /*!< 8-bit integer */
  CNRT_INT16 = 0x22,
  /*!< 16-bit integer */
  CNRT_INT32 = 0x23,
  /*!< 32-bit integer */
  CNRT_UINT8 = 0x31,
  /*!< 8-bit unsigned integer */
  CNRT_UINT32 = 0x33,
  /*!< 32-bit unsigned integer */
  CNRT_FIX8 = 0x41,
  /*!< 8-bit fixed-point data */
  CNRT_QUANT8 = 0x51,
  /*!< 8-bit data */
  CNRT_BOOL = 0x61
  /*!< Boolean type */
} cnrtDataType_t;

//! @brief An enum.
/*! Used to represent the format of data placement.
 * Data can be divided into at least four dimensions.
 * Take pictures as an example, the order of placement can be:
 * the number of pictures, the number of picture Channels,
 * the height of the pictures, and the width of pictures (NCHW).
 */
typedef enum cnrtDimOrder {
  CNRT_NCHW = 0x0123,
  /*!< Placed by the NCHW dimension orders */
  CNRT_NHWC = 0x0231,
  /*!< Placed by the NHWC dimension orders */
  CNRT_HWCN = 0x2310,
  /*!< Placed by the HWCN dimension orders */
  CNRT_TNC = 0x401,
  /*!< Placed by the TNC dimension orders(RNN exclusive) */
  CNRT_NTC = 0x041
  /*!< Placed by the NTC dimension orders(RNN exclusive) */
} cnrtDimOrder_t;

//! @brief An enum.
/*! Context types */
typedef enum cnrtRuntimeContextInfo {
  CNRT_RT_CTX_FUNCTION = 1,
  /*!< Computation unit */
  CNRT_RT_CTX_DEV_ORDINAL = 2,
  /*!< Device ordinal */
  CNRT_RT_CTX_CORE_NUMBER = 3,
  /*!< Core number set by compile time */
  CNRT_RT_CTX_MODEL_PARALLEL = 4,
  /*!< Degree of model parallelism */
  CNRT_RT_CTX_CHANNEL = 5,
  /*!< Channel of device memory */
  CNRT_RT_CTX_MAX_BATCH_NUM = 6,
  /*!< Maximum batch number that cnrtInvokeRuntimeContextBatch could take */
} cnrtRuntimeContextInfo_t;

//! @brief An enum.
/*! Device types */
typedef enum cnrtCoreVersion {
  CNRT_1H8 = 0,
  /*!< 1H8 hardware */
  CNRT_1H16 = 1,
  /*!< 1H16 hardware */
  CNRT_C10 = 3,
  /*!< MLU100 hardware, deprecated, use CNRT_MLU100 instead */
  CNRT_1H8MINI = 4,
  /*!< 1H8MINI hardware */
  CNRT_MLU100 = 3,
  /*!< MLU100 hardware, instead name of CNRT_C10 */
  CNRT_MLU270 = 5,
  /*!< MLU270 hardware */
  CNRT_MLU220 = 6,
  /*!< MLU220 hardware */
} cnrtCoreVersion_t;

/**< Execution priority of tasks on device,
 * only IP platform support.
 **/
//! @brief An enum.
/*! Internal enum. Priority of task execution on device (only supported on IP platform) */
typedef enum { CNRT_PRIORITY_TYPE_0 = 0, CNRT_PRIORITY_TYPE_1 = 1 } cnrtPriorityType_t;

/**< Device affinity information */
/*!
 *  @struct cnrtDeviceAffinity_t
 *  @brief A struct.
 *
 *  A struct describing the device affinity */
typedef struct {
  uint32_t cpu_count; /*!< The number of CPUs having an affinity with the specified devices */
  uint32_t cpu_affinity_bitmap[1024]; /*!< Obtain the affinity bitmask of the specified card */
} cnrtDeviceAffinity_t;

/**< topology relationship */
//! @brief An enum.
/*! Topology struct */
typedef enum {
  CNRT_TOPO_SELF = 0,
  CNRT_TOPO_INTERNAL = 1,
  /*!< devices that are on the same board */
  CNRT_TOPO_SINGLE = 2,
  /*!< all devices that only need traverse a single PCIe switch */
  CNRT_TOPO_MULTIPLE = 3,
  /*!< all devices that need not traverse a host bridge */
  CNRT_TOPO_HOST_BRIDGE = 4,
  /*!< all devices that are connected to the same host bridge */
  CNRT_TOPO_CPU = 5,
  /*!< all devices that are connected to the same CPU */
  CNRT_TOPO_SYSTEM = 6
  /*!< all device in the system */
} cnrtTopologyRelationshipEnum_t;

/**< Model and function */
/*!
 *  @struct cnrtModel
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Model */
struct cnrtModel;
/*! A pointer which points to the struct describing Model */
typedef struct cnrtModel *cnrtModel_t;

/*!
 *  @struct cnrtFunction
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Function */
struct cnrtFunction;
/*! A pointer which points to the struct describing Function */
typedef struct cnrtFunction *cnrtFunction_t;

/**< Input/Output, filter and weight data description */
/*!
 * @struct cnrtDataDesc
 * @brief A struct.
 *
 * ``cnrtDataDesc``is a structure holding tne description of
   data.*/
struct cnrtDataDesc;
/*! ``cnrtDataDesc_t`` is a pointer to ``cnrtDataDesc`` which is
     a  structure holding the description of data. */
typedef struct cnrtDataDesc *cnrtDataDesc_t;
/*! ``cnrtDataDescArray_t`` is a second rank pointer to ``cnrtDataDesc`` which is a
     structure holding the description of data. */
typedef struct cnrtDataDesc **cnrtDataDescArray_t;

/*!
 *  @struct cnrtFilterDesc
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing templates */
struct cnrtFilterDesc;
/*! A pointer which points to the struct describing templates */
typedef struct cnrtFilterDesc *cnrtFilterDesc_t;
/*! A pointer which points to the struct of templates description arrays*/
typedef struct cnrtFilterDesc **cnrtFilterDescArray_t;

/*!
 *  @struct cnrtWeightDesc
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing weights */
struct cnrtWeightDesc;
/*! A pointer which points to the struct describing weights */
typedef struct cnrtWeightDesc *cnrtWeightDesc_t;
/*! A pointer which points to the struct of weight description arrays */
typedef struct cnrtWeightDesc **cnrtWeightDescArray_t;

/**< Stream, Event, RuntimeContext, MLU device */
/*!
 *  @struct cnrtStream
 *  @brief A struct.
 *
 *  A struct describing Stream */
struct cnrtStream;
/*! A pointer which points to the struct describing Stream */
typedef struct cnrtStream *cnrtStream_t;

/*!
 *  @struct cnrtQueue
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Queue */
struct cnrtQueue;
/*! A pointer which points to the struct describing Queue */
typedef struct cnrtQueue *cnrtQueue_t;

/*!
 *  @struct cnrtNotifier
 *  @brief A struct.
 *
 *  Semi-internal struct. A struct describing Notifier */
struct cnrtNotifier;
/*! A pointer which points to the struct describing Notifier */
typedef struct cnrtNotifier *cnrtNotifier_t;

/*!
 *  @struct cnrtEvent
 *  @brief A struct.
 *
 *  A struct describing Event */
struct cnrtEvent;
/*! A pointer which points to the struct describing Event */
typedef struct cnrtEvent *cnrtEvent_t;

/*!
 *  @struct cnrtRuntimeContext
 *  @brief A struct.
 *
 *  A struct describing runtime context */
struct cnrtRuntimeContext;
/*! A pointer which points to the struct describing runtime context */
typedef struct cnrtRuntimeContext *cnrtRuntimeContext_t;

typedef u64_t cnrtDev_t;

/**< Compiler */
/*!
 *  @struct cnrtKernelParamsBuffer
 *  @brief A struct.
 *
 *  Internal struct.  */
struct cnrtKernelParamsBuffer;
typedef struct cnrtKernelParamsBuffer *cnrtKernelParamsBuffer_t;

struct cnrtPluginOpDimInfo;
typedef struct cnrtPluginOpDimInfo *cnrtPluginOpDimInfo_t;

typedef struct cnrtKernelParamsBuffer {
  void *host_ptr;
  unsigned int max_param;
  unsigned int cur_param;

  // for plugin op
  // mark the position of kernel input/output/static ptr in param
  int *input_index;
  int num_input;
  int *output_index;
  int num_output;
  int *static_index;
  int num_static;

  // for plugin op
  // mark the postion of tensor dim info in param.
  cnrtPluginOpDimInfo_t dim_info;
  int num_dim_info;
} * cnrtKernelParamsBuffer_t;

/************************************************************************
 * Function prototype declaration
 ************************************************************************/

/************************************************************************
 * Error handling
 ************************************************************************/

/**
 * @brief Return string pointer that describes
 *     the error code passed in the argument errCode.
 *
 * The function returns a read only string that is corresponding
 * to the argument @p errcode.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  err_code[in] the error code was returned by previous function call.
 * @return a pointer that points to a constant string.
 */
extern CNRT_DLL_API const char *cnrtGetErrorStr(cnrtRet_t err_code);

/**
 * @brief Get the error code set by any runtime calls.
 *     Its value is meaningful only when the return value indicating an error.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @return error code of the last call of runtime functions.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetLastErr(void);

/*************************************************************************
 * Initialization and destroy
 *************************************************************************/

/**
 * @brief Initialize runtime environment in current process space.
 *
 * Initializes this API must be called before any other runtime API calls.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  flags[in] reserved for further use, pass 0 as well.
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInit(unsigned int flags);

/**
 * @brief Destroy everything that allocated by runtime API calls.
 *
 * This API should be called after any other runtime API calls.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @return void (None).
 */
extern CNRT_DLL_API void cnrtDestroy(void);

/******************************************************************************
 * Version and revision
 ******************************************************************************/

/**
 * @brief Return the version of the CNRT software.
 *
 * Higher version usually offers more features provided by this library.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  ver[out] pointer to retrieve the version.
 * @return unsigned int for version number.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetVersion(unsigned int *ver);

/******************************************************************************
 * Device managment
 ******************************************************************************/

/**
 * @brief Get the device handle by a given device ordinal.
 *
 *  The function returns the device handle given a specific device ordinal.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  pdev[out] pointer to retrieve the device handle.
 * @param  ordinal[in] the device ordinal to get the device handle.
 * @note   the ordinal should be in the range [0~cnrtGetDeviceCount() - 1].
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */

extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceHandle(cnrtDev_t *pdev, int ordinal);

/**
 * @brief Set the device handle for current thread execution context.
 *
 *  It implies that any subsequent runtime API calls are for this device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  dev[in] the device handle.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentDevice(cnrtDev_t dev);

/**
 * @brief Get the cnrtDevice handle from current thread execution context.
 *
 * The handle has been set by calling cnrtSetCurrentDevice().
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  pdev[out] pointer to retrieve the device handle.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetCurrentDevice(cnrtDev_t *pdev);

/**
 * @brief Get the number of MLU devices in the system.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param  dev_num[out] pointer to retrieve the number of devices.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceCount(unsigned int *dev_num);

/**
 * @brief  Wait for the device to complete precedent tasks.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSyncDevice(void);

/******************************************************************************
 * Queue management
 ******************************************************************************/

/**
 * @brief Create a new queue after calling this function,
 *        it works in asynchronous mode by default.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pQueue[out] pointer to retrieve the new created Queue handle.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateQueue(cnrtQueue_t *pQueue);

/**
 * @brief Destroy a queue created by calling cnrtCreateQueue.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param queue[in] queue handle created by calling cnrtCreateQueue.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyQueue(cnrtQueue_t queue);

/**
 * @brief Function should be blocked until all precedent tasks in the queue are completed.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param queue[in] queue handle created by calling cnrtCreateQueue.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSyncQueue(cnrtQueue_t queue);

/******************************************************************************
 * Stream management
 ******************************************************************************/

/**
 * @brief Create a new stream after calling this funcation,
 *        it works in asynchronous mode by default.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pstream[out] pointer to retrieve the new created Stream handle.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateStream(cnrtStream_t *pstream);

/**
 * @brief Destroy a stream created by calling cnrtCreateStream or cnrtCreateStreamEx.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param stream[in] stream handle created by calling cnrtCreateStream or cnrtCreateStreamEx.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyStream(cnrtStream_t stream);

/**
 * @brief Function should be blocked until all precedent tasks in the stream are completed.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param stream[in] stream handle created by calling cnrtCreateStream or cnrtCreateStreamEx.
 * @return CNRT_RET_SUCCESS if success, otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSyncStream(cnrtStream_t stream);

/*********************************************************************************
 * Notifier, only MLU100 support
 *********************************************************************************/

/**
 * @brief Create a notifier corresponding to the current device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[out] point to an notifier handle to retrieve newly created notifier.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateNotifier(cnrtNotifier_t *notifier);

/**
 * @brief Destroy a notifier that was created by calling cnrtCreateNotifier.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[in] notifier handle to be destroyed.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyNotifier(cnrtNotifier_t *notifier);

/**
 * @brief Wait notifier which has been placed to queue by calling cnrtPlaceNotifier
 *        util it is in the signaled state or exceeds the time-out interval.
 *        This function will block CPU thread.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[in] event handle created by calling cnrtCreateNotifier.
 * @return CNRT_RET_SUCCESS if success.
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtWaitNotifier(cnrtNotifier_t notifier);

/**
 * @brief Query the status notifier which has been placed to queue by calling cnrtPlaceNotifier.
 *        This function will not block CPU thread.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[in] notifier handle created by calling cnrtCreateNotifier.
 *
 * @return CNRT_RET_SUCCESS if notification instruction has been executed,
 *         CNRT_RET_ERR_BUSY if the preceding tasks is still in progress,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryNotifier(cnrtNotifier_t notifier);

/**
 * @brief Place a notifier in specified queue. This function will not block the CPU thread.
 *        All computation tasks submitted to the queue will wait until event reports
 *        completion before starting execution.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[in] signal handle created by calling cnrtCreateNotifier.
 * @param queue[in] queue handle created by calling cnrtCreateQueue.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtPlaceNotifier(cnrtNotifier_t notifier, cnrtQueue_t queue);

/**
 * @brief Make the specified queue wait for a notifier. This function is designed for
 *        cross queue synchronization.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param notifier[in] signal handle created by calling cnrtCreateNotifier.
 * @param queue[in] queue handle created by calling cnrtCreateQueue or cnrtCreateQueueEx.
 * @param flag[in] flags control operation.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueueWaitNotifier(cnrtNotifier_t notifier,
                                                    cnrtQueue_t queue,
                                                    unsigned int flag);

/**
 * @brief Get duration time of two makers.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param start[in] notifier handle created by calling cnrtCreateNotifier.
 * @param end[in] notifier handle created by calling cnrtCreateNotifier.
 * @param us[out] duration time between start and end.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtNotifierDuration(cnrtNotifier_t start,
                                                   cnrtNotifier_t end,
                                                   float *us);

/*********************************************************************************
 * Event, only MLU100 support
 *********************************************************************************/
/**
 * @brief Query the status of placed event, which has been placed to stream recently by
 *        calling cnrtPlaceEvent.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param event[in] event handle created by calling cnrtCreateEvent.
 *
 * @return CNRT_RET_SUCCESS if notification instruction has been executed,
 *         CNRT_RET_ERR_BUSY if the preceding tasks is still in progress,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryEvent(cnrtEvent_t event);

/**
 * @brief Make the specified stream wait for an event. This function is designed for
 *        cross stream synchronization.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param event[in] signal handle created by calling cnrtCreateEvent.
 * @param stream[in] stream handle created by calling cnrtCreateStream or cnrtCreateStreamEx.
 * @param flag[in] flags control operation.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtStreamWaitEvent(cnrtEvent_t event,
                                                  cnrtStream_t stream,
                                                  unsigned int flag);

/**
 * @brief Wait until the specified event object is in the signaled state or exceeds the time-out
 *        interval.This function will block CPU thread.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param event[in] event handle created by calling cnrtCreateEvent.
 * @return CNRT_RET_SUCCESS if success.
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtWaitEvent(cnrtEvent_t event);

/**
 * @brief Create an event corresponding to the current device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pevent[out] point to an event handle to retrieve newly created event.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateEvent(cnrtEvent_t *pevent);

/**
 * @brief Destroy an event that was created by calling cnrtCreateEvent.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pevent[out] event handle to be destroyed.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyEvent(cnrtEvent_t *pevent);

/**
 * @brief Place an event in specified stream. This function will not block the CPU thread.
 *        All computation tasks submitted to the stream will wait until event reports
 *        completion before starting execution.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param event[in] signal handle created by calling cnrtCreateEvent.
 * @param stream[in] stream handle created by calling cnrtCreateStream or cnrtCreateStreamEx.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtPlaceEvent(cnrtEvent_t event, cnrtStream_t stream);

/**
 * @brief Get elapsed time of two events.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param event_start[in] event handle created by calling cnrtCreateEvent.
 * @param event_end[in] event handle created by calling cnrtCreateEvent.
 * @param us_ptr[out] elapsed time between event_start and event_end.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtEventElapsedTime(cnrtEvent_t event_start,
                                                   cnrtEvent_t event_end,
                                                   float *us);

/**< Compiler */
/*********************************************************************************
 * Execution control
 *********************************************************************************/

/**
 * @brief Get a parameter buffer for cnrtInvokeKernel.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] pointer to a param buffer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetKernelParamsBuffer(cnrtKernelParamsBuffer_t *params);

/**
 * @brief Copy Parambuffer from src_params_buf to dst_params_buf
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst_params_buf[in] pointer to an allocated param buffer
 * @param src_params_buf[in] pointer to an allocated param buffer
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCopyKernelParamsBuffer(cnrtKernelParamsBuffer_t dst_params_buf,
                                                         cnrtKernelParamsBuffer_t src_params_buf);

/**
 * @brief Add a parameter to a specific parameter buffer.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] destination parameter buffer
 * @param data[in] pointer to host memory
 * @param bytes[in] size in bytes
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferAddParam(cnrtKernelParamsBuffer_t params,
                                                             void *data,
                                                             size_t bytes);

/**
 * @brief Add a InputPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] destination parameter buffer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkInput(cnrtKernelParamsBuffer_t params);

/**
 * @brief Add a OutputPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] destination parameter buffer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkOutput(cnrtKernelParamsBuffer_t params);

/**
 * @brief Add a StaticPtr place holder to a specific parameter buffer.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] destination parameter buffer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtKernelParamsBufferMarkStatic(cnrtKernelParamsBuffer_t params);

/**
 * @brief Destroy a parameter buffer returned by cnrtGetKernelParamsBuffer.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param params[in] pointer to a param buffer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyKernelParamsBuffer(cnrtKernelParamsBuffer_t params);

/**
 * @brief Invoke a kernel written in Bang with given params on MLU.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in]      how many grid dimensions.
 * @param params[in]   point to arguments.
 * @param c[in]        function type. @see cnrtFunctionType_t.
 * @param stream[in]   stream associated to the function call.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeKernel(const void *function,
                                               cnrtDim3_t dim,
                                               cnrtKernelParamsBuffer_t params,
                                               cnrtFunctionType_t func_type,
                                               cnrtStream_t stream);

/**
 * @brief Invoke a kernel written in Bang with given params on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in] how many grid dimensions.
 * @param params[in] point to arguments.
 * @param func_type[in] function type. @see cnrtFunctionType_t.
 * @param queue[in] queue associated to the function call.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeKernel_V2(const void *function,
                                                  cnrtDim3_t dim,
                                                  cnrtKernelParamsBuffer_t params,
                                                  cnrtFunctionType_t func_type,
                                                  cnrtQueue_t queue);
/*********************************************************************************
 * Model load and Function call
 *********************************************************************************/

/**
 * @brief Load a model from a given model file.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pmodel[out] point to a cnrtModel_t.
 * @param fname[in]  file name of a cambricon model.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtLoadModel(cnrtModel_t *pmodel, const char *fname);

/**
 * @brief Load a model from memory
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pmodel[out] pointer to a cnrtModel_t.
 * @param ptr[in] memory pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtLoadModelFromMem(cnrtModel_t *pmodel, char *ptr);

/**
 * @brief Unload a model.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] point to a cnrtModel_t.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtUnloadModel(cnrtModel_t model);

/**
 * @brief  Get actual size of model in offline file.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param fname[in] file name of a cambricon model.
 * @param size[out] pointer to model's actual size.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelSize(const char *fname, int *size);

/**
 * @brief  Query model's core version, 1H8 or 1H16.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] pointer to a loaded model.
 * @param coreVersion[out] pointer to model's core version.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryCoreVersion(cnrtModel_t model,
                                                   cnrtCoreVersion_t *coreVersion);

/**
 * @brief  Query model's parallelism, which means the core number
 * involved to compute this model.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] point to a loaded model.
 * @param modelParallelism[out] pointer to model's parallelism.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryModelParallelism(cnrtModel_t model, int *modelParallelism);

/**
 * @brief  Query model's stack size, which is the biggest stack size(MB)
 * in all the kernels in the model.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] point to a loaded model.
 * @param size[out] pointer to the stack size.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtQueryModelStackSize(cnrtModel_t model, uint64_t *stack_size);

/**
 * @brief Get function number of a given model
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] pointer of a cambricon model
 * @param func_num[out] pointer to function number
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetFunctionNumber(cnrtModel_t model, int *func_num);

/**
 * @brief Extract the symbol from the given model if symbol exists,
 *        otherwise error code will be returned.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[out] point to a cnrtFunction_t.
 * @param model[in]  point to a loaded model.
 * @param symbol[in] symbol name.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtExtractFunction(cnrtFunction_t *pfunction,
                                                  cnrtModel_t model,
                                                  const char *symbol);

/**
 * @brief Create a MLU function.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of cnrtFunction_t.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateFunction(cnrtFunction_t *pfunction);

/**
 * @brief Destroy a function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to a function generated by cnrtExtractFunction.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyFunction(cnrtFunction_t function);

/**
 * @brief Initialize instruction and runtime data of a function on current MLU device.
 *
 *        cnrtInitFunctionMemory has two modes, distinguished by func_type.
 *        The first mode is func_type == CNRT_FUNC_TYPE_MUTABLE.
 *        The second mode is func_type != CNRT_FUNC_TYPE_MUTABLE.
 *
 *        The first mode is more flexible.
 *        Under this mode, the same function can be invoked by different
 *        cnrtInvokeFunction with different parallelism simultaneously.
 *        For example, you can write the following code:
 *        cnrtInitFunctionMemory(function, CNRT_FUNC_TYPE_MUTABLE);
 *        cnrtInvokeFunction(function, ..., CNRT_FUNC_TYPE_UNION2, ...);
 *        cnrtInvokeFunction(function, ..., CNRT_FUNC_TYPE_BLOCK, ...);
 *
 *        The second mode is more efficient.
 *        Under this mode, the same function can also be invoked by different
 *        cnrtInvokeFunction. But the parallelism is limited. It should be
 *        the same as func_type.
 *        For example, you can write the following code:
 *        cnrtInitFunctionMemory(function, CNRT_FUNC_TYPE_UNION2);
 *        cnrtInvokeFunction(function, ..., CNRT_FUNC_TYPE_UNION2, ...);
 *        cnrtInvokeFunction(function, ..., CNRT_FUNC_TYPE_UNION2, ...);
 *
 *        notice: cnrtInitFunctionMemory should be called before
 *        cnrtInvokeFunction and after cnrtSetCurrentDevice.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of cnrtFunction_t.
 * @param func_type[in] parallelism of function.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitFunctionMemory(cnrtFunction_t function,
                                                     cnrtFunctionType_t func_type);

/**
* @brief Initialize instruction and runtime data of a function on current MLU device.
*
*        cnrtInitFunctionMemory has two modes, distinguished by affinity.
*        The first mode is affinity == CNRT_FUNC_TYPE_MUTABLE.
*        The second mode is affinity != CNRT_FUNC_TYPE_MUTABLE.
*
*        The first mode is more flexible.
*        Under this mode, the same function can be invoked by different
*        cnrtInvokeFunction with different parallelism simultaneously.
*        For example, you can write the following code:
*        dataParallelism int the cnrtInitFunctionMemory_V2 is just initialization.
*        cnrtInitFuncParam_t init_func_param;
*        bool muta = true;
*        init_func_param.muta = &muta;
*        int dataParallelism = 1;
*        init_func_param.dataParallelism = &dataParallelism;
*        init_func_param.end = CNRT_PARAM_END;
*        cnrtInitFunctionMemory_V2(function, &init_func_param);
*
*        dataParallelism in the cnrtInvokeFunction is mutable.
*        cnrtInvokeFuncParam_t invoke_func_param;
*        int dataParallelism = 2;
*        invoke_func_param.dataParallelism = &dataParallelism;
*        invoke_func_param.end = CNRT_PARAM_END;
*        cnrtFunctionType_t func_type = (cnrtFunctionType_t)0;
*        cnrtInvokeFunction(function, ..., (void *)&invoke_func_param);
*
*        The second mode is more efficient.
*        Under this mode, the same function can also be invoked by different
*        cnrtInvokeFunction. But the parallelism is limited. It should be
*        the same as affinity.
*        For example, you can write the following code:
*        dataParallelism in the cnrtInvokeFunction is not mutable.
*        cnrtInitFuncParam_t init_func_param;
*        bool muta = false;
*        init_func_param.muta = &muta;
*        int dataParallelism = 1;
*        init_func_param.dataParallelism = &dataParallelism;
*        init_func_param.end = CNRT_PARAM_END;
*        cnrtInitFunctionMemory_V2(function, &init_func_param);
*
*        dataParallelism in the cnrtInvokeFunction should be same as the
*        dataParallelism int the cnrtInitFunctionMemory_V2.
*        cnrtInvokeFuncParam_t invoke_func_param;
*        int dataParallelism = 1;
*        invoke_func_param.dataParallelism = &dataParallelism;
*        invoke_func_param.end = CNRT_PARAM_END;
*        cnrtFunctionType_t func_type = (cnrtFunctionType_t)0;
*        cnrtInvokeFunction(function, ..., (void *)&invoke_func_param);
*
*        notice: cnrtInitFunctionMemory should be called before
*        cnrtInvokeFunction and after cnrtSetCurrentDevice.
*
 *  **Supports both MLU100 and MLU270**
 * 
* @param function[in] pointer of cnrtFunction_t.
* @param param[in] pointer of cnrtInitfuncParam_t.
* @return CNRT_RET_SUCCESS if success,
*         otherwise the error code is returned.
*/
extern CNRT_DLL_API cnrtRet_t cnrtInitFunctionMemory_V2(cnrtFunction_t function,
                                                        cnrtInitFuncParam_t *param);

/**
 * @brief Invoke a function with given params on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in] how many grid dimensions.
 * @param params[in] point to arguments.
 * @param func_type[in] function type. @see cnrtFunctionType_t.
 * @param stream[in] stream associated to the function call.
 * @param extra_param[in] pointer to cnrtInvokeFuncParam_t as extra param.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeFunction(cnrtFunction_t function,
                                                 cnrtDim3_t dim,
                                                 void **params,
                                                 cnrtFunctionType_t func_type,
                                                 cnrtStream_t stream,
                                                 void *extra_param);

/**
 * @brief Invoke a function with given params on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in] how many grid dimensions.
 * @param params[in] point to arguments.
 * @param func_type[in] function type. @see cnrtFunctionType_t.
 * @param queue[in] queue associated to the function call.
 * @param extra_param[in] pointer to cnrtInvokeFuncParam_t as extra param.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeFunction_V2(cnrtFunction_t function,
                                                    cnrtDim3_t dim,
                                                    void **params,
                                                    cnrtFunctionType_t func_type,
                                                    cnrtQueue_t queue,
                                                    void *extra_param);

/**
 * @brief Generate a copy of source MLU function. src and dst function share the
 *        same kernel on host, but they have different device space, so model
 *        data(include instruction) is doubled on device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param src[in] Pointer to a source MLU function
 * @param dst[out] Pointer to a destination MLU function pointer
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCopyFunction(cnrtFunction_t *dst, cnrtFunction_t src);

/**
 * @brief Initialize instruction memory on device.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of MLU function.
 * @param inst_addr[out] get the pointer of MLU instruction memory.
 * @param param[in] pointer of cnrtInitFuncParam_t.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitFunctionInstMemory(cnrtFunction_t function,
                                                         void **inst_addr,
                                                         cnrtInitFuncParam_t *param);

/**
 * @brief Initialize constant data on device.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of MLU function.
 * @param const_addr[out] get the pointer of MLU const memory.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitFunctionConstMemory(cnrtFunction_t function,
                                                          void **const_addr);

/*
 * @brief Count the intermediate data memory size of a function.
 *        If count completely then return CNRT_RET_SUCCESS.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of MLU function.
 * @param data_parallelism[in] data_parallelism size.
 * @param intmd_memory_size[out] the pointer of intermediate memory size.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetFunctionIntmdMemorySize(cnrtFunction_t function,
                                                             int data_parallelism,
                                                             uint64_t *intmd_memory_size);

/*
 * @brief Initialize intermediate memory on device.
 *        If copy complete and return CNRT_RET_SUCCESS.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] pointer of MLU function.
 * @param intmd_addr[out] get the pointer of intermediate address.
 * @param dataParallelism[in] dataParallelism size.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitFunctionIntmdMemory(cnrtFunction_t function,
                                                          void **intmd_addr,
                                                          int dataParallelism);

/**
 * @brief Invoke a function with for data and instruction multiplexing on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in]      how many grid dimensions.
 * @param params[in]   point to arguments.
 * @param func_type[in]        function type. @see cnrtFunctionType_t.
 * @param stream[in]   stream associated to the function call.
 * @param inst_addr[in]  the instruction address.
 * @param const_addr[in] the const data address.
 * @param intmd_addr[in] the intermediate address.
 * @param cnrtInvokeFuncParam[in] private pointer that is for cnrtInvokeFuncParam_t.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeFunctionExtra(cnrtFunction_t function,
                                                      cnrtDim3_t dim,
                                                      void **params,
                                                      cnrtFunctionType_t func_type,
                                                      cnrtStream_t stream,
                                                      void *inst_addr,
                                                      void *const_addr,
                                                      void *intmd_addr,
                                                      void *cnrtInvokeFuncParam);

/**
 * @brief Invoke a function with for inst on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param function[in] point to the MLU function.
 * @param dim[in]      how many grid dimensions.
 * @param params[in]   point to arguments.
 * @param func_type[in]        function type. @see cnrtFunctionType_t.
 * @param queue[in] queue associated to the function call.
 * @param inst_addr[in]  the instruction address.
 * @param const_addr[in] the const data address.
 * @param intmd_addr[in] the intermediate address.
 * @param cnrtInvokeFuncParam[in] private pointer that is for cnrtInvokeFuncParam_t.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeFunctionExtra_V2(cnrtFunction_t function,
                                                         cnrtDim3_t dim,
                                                         void **params,
                                                         cnrtFunctionType_t func_type,
                                                         cnrtQueue_t queue,
                                                         void *inst_addr,
                                                         void *const_addr,
                                                         void *intmd_addr,
                                                         void *cnrtInvokeFuncParam);
/*********************************************************************************
 * Memory management
 *********************************************************************************/

/**
 * @brief Allocate nByte bytes and place a pointer to pointer
 *        in pPtr to the allocated host memory. If bytes is 0, then
 *        cnrtMallocHost returns either NULL, or a unique pointer value
 *        that can later be passed to cnrtFreeHost.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out]  a pointer to pointer for retrieving allocated host memory.
 * @param bytes[in] number bytes of memory to be allocated.
 * @param type[in]   memory type to be allocated,
 *                   @see CNRT_HOST_MEMORY_TYPE_LOCK and CNRT_HOST_MEMORY_TYPE_MAPPED.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocHost(void **pPtr, size_t bytes, cnrtMemType_t type);

/**
 * @brief Free the memory space pointed by ptr, which must be
 *        returned by a previous call of cnrtMallocHost.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param ptr[in]  point to the address of memory to be free.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFreeHost(void *ptr);

/**
 * @brief Allocate memory on MLU device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out] a pointer to pointer for retrieving allocated device memory.
 * @param bytes[in] allocate size.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMalloc(void **pPtr, size_t bytes);

/**
 * @brief Allocate continuous memory for multi-way data on MLU device.
 *        This API should be used under data parallel mode.
 *        Data size of each way will be aligned automatically for sake of
 *        high performance memory access. So the actual allocate size is
 *        align(bytes) * dataParallelism.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out] a pointer to pointer for retrieving allocated device memory.
 * @param bytes[in] allocate size.
 * @param dataParallelism[in] data parallelism
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocBatch(void **pPtr, size_t bytes, int dataParallelism);

/**
 * @brief Allocate memory on MLU device.
 *        Compared with cnrtMalloc, cnrtMallocByDesc use cnrtDataDesc_t
 *        object to determine the allocate size.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out] point to allocated memory.
 * @param dataDesc[in] data descriptor.
 * @return CNRT_RET_SUCCESS if success.
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocByDesc(void **pPtr, cnrtDataDesc_t dataDesc);

/**
 * @brief Allocate continuous memory for multi-way data on MLU device.
 *        Compared with cnrtMallocBatch, cnrtMallocBatchByDesc use
 *        cnrtDataDesc_t object to determine the allocate size.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out] point to allocated memory.
 * @param dataDesc[in] data descriptor.
 * @param dataParallelism[in] data parallelism
 * @return CNRT_RET_SUCCESS if success.
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocBatchByDesc(void **pPtr,
                                                    cnrtDataDesc_t dataDesc,
                                                    int dataParallelism);

/**
 * @brief Allocate multiple addresses for multiple data objects on MLU device.
 *        Multiple addresses and data descriptors is present in array format.
 *        This API is a reinforced version of cnrtMallocByDesc. You can call
 *        cnrtMallocByDesc more than once to realize the same function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtrArray[out] point to the allocated memory array.
 * @param dataDescArray[in] data descriptor array.
 * @param length[in] array length.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocByDescArray(void ***pPtrArray,
                                                    cnrtDataDescArray_t dataDescArray,
                                                    int length);

/**
 * @brief Allocate multiple addresses for multiple data objects
 *        of multiple way on MLU device. This API is a multi-way
 *        version of cnrtMallocByDescArray.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtrArray[out] point to the allocated memory array.
 * @param dataDescArray[in] data descriptor array.
 * @param length[in] array length.
 * @param dataParallelism[in] way size of data.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocBatchByDescArray(void ***pPtrArray,
                                                         cnrtDataDescArray_t dataDescArray,
                                                         int length,
                                                         int dataParallelism);

/**
 * @brief Allocate memory on MLU device. For P2P.
 *
 *  **Supports only MLU100**
 * 
 * @param pPtr[out] a pointer to pointer for retrieving allocated device memory.
 * @param bytes[in] allocate size.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocFrameBuffer(void **pPtr, size_t bytes);

/**
 * @brief Allocate memory on MLU device, for extension
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pPtr[out] a pointer to pointer for retrieving allocated device memory.
 * @param param[in] parameter buffer allocated by cnrtAllocParam
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMallocBufferEx(void **pPtr, void *param);

/**
 * @brief Deallocate MLU device Memory.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param ptr[in] point to the memory to be free.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFree(void *ptr);

/**
 * @brief Deallocate MLU multiple device memory addresses allocated
 *        by cnrtMallocBatchByDescArray, cnrtMallocByDescArray.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param ptr[in] a pointer array.
 * @param length[in] array length.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtFreeArray(void **ptr, int length);

/**
 * @brief Copy data from src address to dst address. The copy direction
 *        is specified by input parameter dir. The copy operation is
 *        always performed on current device which is set by cnrtSetCurrentDevice.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[in] destination address.
 * @param src[in] source address.
 * @param bytes[in] number of bytes to be copied.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpy(void *dst, void *src, size_t bytes, cnrtMemTransDir_t dir);

/**
 * @brief Copy multi-way data from src address to dst address.
 *        The device address should be allocated by cnrtMallocBatch.
 *        The host address should contain dataParallelism number of data arranged
 *        continuously. This API should be used under data parallel mode.
 *        More information about device address @see cnrtMallocBatch.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[in] destination address.
 * @param src[in] source address.
 * @param bytes[in] size of single way data.
 * @param dataParallelism[in] data parallelism.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtMemcpyBatch(void *dst, void *src, size_t bytes, int dataParallelism, cnrtMemTransDir_t dir);

/**
 * @brief Copy data from src address to dst address.
 *        Compared with cnrtMemcpy, cnrtMemcpyByDesc receives data descriptor as
 *        a input parameter. Because we need to carry out data layout optimization
 *        for MLU device. This API is typically used in image process situation.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[in] destination address.
 * @param src[in] source address.
 * @param dataDesc[in] data descriptor.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpyByDesc(void *dst,
                                               void *src,
                                               cnrtDataDesc_t dataDesc,
                                               cnrtMemTransDir_t dir);

/**
 * @brief Copy multi-way data from src address to dst address.
 *        This is a multi-way version of cnrtMemcpyByDesc.
 *        The host address should contain dataParallelism number of data arranged
 *        continuously.
 *        The device address should be allocated by cnrtMallocBatchByDesc.
 *        To get more information about multi-way, @see cnrtMallocBatchByDesc.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[in] destination address.
 * @param src[in] source address.
 * @param dataDesc[in] data descriptor.
 * @param dataParallelism[in] data parallelism.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpyBatchByDesc(void *dst,
                                                    void *src,
                                                    cnrtDataDesc_t dataDesc,
                                                    int dataParallelism,
                                                    cnrtMemTransDir_t dir);

/**
 * @brief Copy multiple data objects from src addresses to dst addresses.
 *        Multiple addresses and data descriptors is present in array format.
 *        This API is a reinforced version of cnrtMemcpyByDesc. You can call
 *        cnrtMemcpyByDesc more than once to realize the same function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dstArray[in] pointer to destination address array.
 * @param srcArray[in] pointer to source address array.
 * @param dataDescArray[in] data descriptor array.
 * @param length[in] array length.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpyByDescArray(void **dstArray,
                                                    void **srcArray,
                                                    cnrtDataDescArray_t dataDescArray,
                                                    int length,
                                                    cnrtMemTransDir_t dir);

/**
 * @brief Copy multiple data objects of multi-way from src
 *        addresses to dst addresses.
 *        This API is the multi-way of cnrtMemcpyByDescArray.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dstArray[in] pointer to destination address array.
 * @param srcArray[in] pointer to source address array.
 * @param dataDescArray[in] data descriptor array.
 * @param length[in] array length.
 * @param dataParallelism[in] data parallelism.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemcpyBatchByDescArray(void **dstArray,
                                                         void **srcArray,
                                                         cnrtDataDescArray_t dataDescArray,
                                                         int length,
                                                         int dataParallelism,
                                                         cnrtMemTransDir_t dir);

/**
 * @brief Get the batch alignment for cnrtMemcpy
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dataDesc[in] data descriptor.
 * @param bytes[out] alignment bytes for each batch.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetMemcpyBatchAlignment(cnrtDataDesc_t desc, unsigned int *bytes);

/**
 * @brief Fill the bytes of the device memory space
 *        pointed by devPtr with the constant value c.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param ptr[in] device memory address.
 * @param c[in] value to be filled.
 * @param bytes[in] number of bytes to be filled.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtMemset(void *ptr, int c, size_t bytes);

/**
 * @brief set MLU stack space memory to stack_size(MB).
 *        Only MLU100 support.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param stacksize[in] the size of MLU stack space memory will be set.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise CNRT_RET_ERR_MLU is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetStackMem(unsigned int stacksize);

/**
 * @brief get MLU stack space memory to stack_size(MB).
 *        Only MLU100 support.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pStacksize[out] the size of MLU stack space memory will be get.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise CNRT_RET_ERR_MLU is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetStackMem(unsigned int *pStacksize);

/**
 * @brief get max memory used of function
 * 
 *  **Supports both MLU100 and MLU270**
 *
 * @param function[in] point to the MLU function.
 * @param pMemused[out] return value.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetFunctionMemUsed(cnrtFunction_t function, int64_t *pMemused);

/**
 * @brief get max memory used of model
 *  **Supports both MLU100 and MLU270**
 * 
 * @param model[in] point to the model.
 * @param pMemused[out] return value.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelMemUsed(cnrtModel_t model, int64_t *pMemused);

/*********************************************************************************
 * Channel control, only MLU100 support
 *********************************************************************************/

/**
 * @brief Set memory and computation channel on current MLU device. Once
 *        a channel is configured, all memory allocation(eg. cnrtMalloc)
 *        will be performed on this channel. And all function invokation
 *        (cnrtInvokeFunction) will be performed on this channel too.
 *        Attention: The above policy only take effect when model parallelism
 *        is 1.
 *        This function is base on CPU thread context. So it's action scope
 *        is within current CPU thread. This function should be called after
 *        cnrtSetCurrentDevice;
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param cnrtChannelType_t[in] channel.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentChannel(cnrtChannelType_t channel);

/**
* @brief Get current channel of current CPU thread.
*
 *  **Supports both MLU100 and MLU270**
 * 
* @param pChannel[out] Pointer to channel.
* @return CNRT_RET_SUCCESS if success,
*         otherwise the error code is returned.
*/
extern CNRT_DLL_API cnrtRet_t cnrtGetCurrentChannel(cnrtChannelType_t *pChannel);

/*********************************************************************************
 * Data descriptor
 *********************************************************************************/

/**
 * @brief Get a series of input data descriptors from a given function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param descArray[out] point to Data descriptor array.
 * @param num[out] length of the data descriptor array.
 * @param function[in] MLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetInputDataDesc(cnrtDataDescArray_t *descArray,
                                                   int *num,
                                                   cnrtFunction_t function);

/**
 * @brief Get a series of input data descriptors from a given function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param descArray[out] point to the data descriptor array.
 * @param num[out] length of the data descriptor array.
 * @param function[in] MLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetOutputDataDesc(cnrtDataDescArray_t *descArray,
                                                    int *num,
                                                    cnrtFunction_t function);

/**
 * @brief Set data layout(e.g. type, dim order) on the host according to the data descriptor.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param desc[in] point to data descriptor.
 * @param dtype[in] host data type. @see cnrtDataDesc_t.
 * @param order[in] host data dim order. @see cnrtDimOrder_t.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetHostDataLayout(cnrtDataDesc_t desc,
                                                    cnrtDataType_t dtype,
                                                    cnrtDimOrder_t order);

/**
 * @brief get a DataDesc's n, c, h ,w.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param desc[in] point to the data descriptor pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtGetDataShape(cnrtDataDesc_t desc, unsigned *n, unsigned *c, unsigned *h, unsigned *w);

/**
 * @brief Get host data count (e.g. for tensor with dim nchw, the count is n*c*h*w).
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param count[out] host data count.
 * @param desc[in] point to the data descriptor.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetHostDataCount(cnrtDataDesc_t desc, int *count);

/**
 * @brief Set weight layout(e.g. type, dim order) on the host according to the weight descriptor.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param desc[out] point to weight descriptor.
 * @param dtype[in] host weight type. @see cnrtDataDesc_t.
 * @param order[in] host weight dim order. @see cnrtDimOrder_t.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetHostWeightLayout(cnrtWeightDesc_t desc,
                                                      cnrtDataType_t dtype,
                                                      cnrtDimOrder_t order);

/**
 * @brief Get host weight count (e.g. dim NCHW, count is n*c*h*w).
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param count[out] host weight count.
 * @param desc[in]   point to the weight descriptor.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetHostWeightCount(cnrtWeightDesc_t desc, int *count);

/**
 * @brief Get a weight descriptors from a given function by name.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param weightDesc[out] point to weight descriptor.
 * @param update_name[in] name of weight desc that you want to update.
 * @param function[in]    MLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetWeightDesc(cnrtWeightDesc_t *weightDesc,
                                                char *update_name,
                                                cnrtFunction_t function);

/**
 * @brief update weight data in given function.

 *  **Supports both MLU100 and MLU270**
 * 
 * @param weightDesc[in]   the weight descriptor that you want to update.
 * @param weightCpuPtr[in] the weight data that you want to update
 * @param function[in]     NLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtUpdateWeightData(cnrtWeightDesc_t weightDesc,
                                                   void *weightCpuPtr,
                                                   cnrtFunction_t function);

/**
 * @brief Get a series of weight descriptors from a given function by name array.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param descArray[out] point to weight descriptor array.
 * @param name_num[in]   length of the weight descriptor array.
 * @param name_array[in] a array of name you want to update
 * @param function[in]   MLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetWeightDescArray(cnrtWeightDescArray_t descArray,
                                                     int num,
                                                     char **name_array,
                                                     cnrtFunction_t function);

/**
 * @brief update a series of weight data in given function.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param descArray[in]  a series of weight descriptors that you want to update.
 * @param weightCpuPtrS[in] the weight data that you want to update.
 * @param update_num[in] the number of weight data array that you want to update.
 * @param function[in]   MLU function pointer.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtUpdateWeightDataArray(cnrtWeightDescArray_t descArray,
                                                        void **weightCpuPtrS,
                                                        int update_num,
                                                        cnrtFunction_t function);

/*********************************************************************************
 * Task Priority control, only specific IP platform support
 *********************************************************************************/

/**
 * @brief Set the priority of task on  device. Once This function is base on
 *        CPU thread context. So it's action scope is within current CPU thread.
 *        This function should be called after cnrtSetCurrentDevice;
 *
 *  **Supports only MLU100**
 * 
 * @param cnrtPriorityType_t[in] priority.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetTaskPriority(cnrtPriorityType_t priority);

/**
 * @brief Get current priority of task.
 *
 *  **Supports only MLU100**
 * 
 * @param pPriority[out] Pointer to channel.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetTaskPriority(cnrtPriorityType_t *pPriority);

/**
 * @brief Reshape filter data from src address to dst address.
 *        The origin src data layout is src[N][H][W][C]
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[out] destination address.
 * @param src[in] source address.
 * @param n/h/w/c[in] the origin data layout.
 * @param type[in] the data type of dst[out] and src[in].
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtFilterReshape(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

/**
 * @brief Reshape data from src address to dst address.
 *        only between NHWC and NCHW
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dst[out] destination address.
 * @param src[in] source address.
 * @param n/h/w/c[in] the origin data layout.
 * @param type[in] the data type of dst[out] and src[in].
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtReshapeNCHWToNHWC(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

extern CNRT_DLL_API cnrtRet_t
cnrtReshapeNHWCToNCHW(void *dst, void *src, int n, int h, int w, int c, cnrtDataType_t type);

/**
 * @brief get model level from offline file.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param fname[in] offline file name.
 * @param model_level[out] model level.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetModelLevelFromFile(const char *fname, int *model_level);

/****************************************************************************
 * Generic parameters handling
 ***************************************************************************/

/**
 * @brief Allocate a CNRT parameter context buffer
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pParam[out] pointer to the parameter context buffer pointer
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtAllocParam(void **pParam);

/**
 * @brief Destroy a CNRT parameter context buffer
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param param[in] the parameter context buffer pointer
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestoryParam(void *param);

/**
 * @brief Add one parameter to parameter context buffer
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param param[in] the parameter context buffer pointer
 * @param name[in] name of the parameter
 * @param len[in] length of the parameter
 * @param data[in] pointer to the parameter
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtAddParam(void *param, char *name, int len, void *data);

/**
 * @brief Get one parameter from parameter context buffer
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param param[in] the parameter context buffer pointer
 * @param name[in] name of the parameter
 * @param out[out] result buffer
 * @param outlen[in] result buffer length
 *
 *
 * @return CNRT_RET_SUCCESS if success,
 *         CNRT_RET_ERR_MEMCPY if parameter actual length is larger than result buffer length
 *         CNRT_RET_ERR_NO_EXIST if "name" is not found in param context
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetParam(void *param, char *name, void *out, int outlen);

/**
 * @brief Convert a float/double to float16, store it at specific position (*f16 = (f16)d)
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param d[in] number to convert
 * @param f16[out] place to store
 * @return error code of the last call of runtime functions
 */
extern CNRT_DLL_API cnrtRet_t cnrtConvertDoubleToHalf(uint16_t *f16, double x);

extern CNRT_DLL_API cnrtRet_t cnrtConvertFloatToHalf(uint16_t *f16, float d);

/**
 * @brief Convert a float16 to float/double, store it at specific position (*d = (float/double)(f16))
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param f16[in] number to convert
 * @param d[out] place to store
 * @return error code of the last call of runtime functions
 */

extern CNRT_DLL_API cnrtRet_t cnrtConvertHalfToDouble(double *d, uint16_t f16);

extern CNRT_DLL_API cnrtRet_t cnrtConvertHalfToFloat(float *d, uint16_t f16);

/**
 * @brief Get datatype's size.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dt[in] enum cnrtDataType variable.
 * @return size of DataType,
 */
extern CNRT_DLL_API int cnrtDataTypeSize(cnrtDataType_t dt);

/**
 * @brief Create and deploy a runtime context on specified MLU device.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[out] receiver pointer of runtime context
 * @param function[in] point to the MLU function. Function must be initialized from a compiled OP or
 *        from an offline model(cnrtExtractFunction)
 * @param extra[in]  Reserved for future use.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtCreateRuntimeContext(cnrtRuntimeContext_t *pctx,
                                                       cnrtFunction_t function,
                                                       void *extra);
/**
 * @brief Set channel on the specified MLU device.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] receiver pointer of runtime context
 * @param channel[in] Assign the DDR channel of the runtime context.
 *        CNRT_CHANNEL_TYPE_NONE: Let CNRT decide channel. It is recommended for most users.
 *        CNRT_CHANNEL_TYPE_DUPLICATE: Const memory will be duplicated on DDR channels.
 *        It could improve concurrency performance when you have multiple threads or
 *        streams associating with this runtime context with the cost of memory consumption.
 *        For advanced users, you could assign channel manually.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetRuntimeContextChannel(cnrtRuntimeContext_t pctx,
                                                           cnrtChannelType_t channel);

/**
 * @brief Set device id on the specified MLU device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] receiver pointer of runtime context
 * @param dev_ordinal[in] The device ordinal of which the runtime context is deployed.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetRuntimeContextDeviceId(cnrtRuntimeContext_t pctx,
                                                            int dev_ordinal);

/**
 * @brief Enable mutable batch size for the runtime context.
 *        Once enabled, user could call cnrtInvokeRuntimeContextBatch interface to
 *        launch mutable batch size request.
 *        A maximum batch is returned. The parameter "batch" passed to cnrtInvokeRuntimeContextBatch
 *        should not exceed the maximum batch.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] receiver pointer of runtime context
*  @param max_batch[out] The maximum batch that cnrtInvokeRuntimeContextBatch could take.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetRuntimeContextMutableBatch(cnrtRuntimeContext_t pctx,
                                                                int *max_batch);

/**
 * @brief Initialize runtime context on the specified MLU device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer of runtime context.
 * @param extra[in] for expand.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInitRuntimeContext(cnrtRuntimeContext_t pctx, void *extra);

/**
 * @brief Create a runtime context queue.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer of runtime context.
 * @param queue[out] get a queue.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextCreateQueue(cnrtRuntimeContext_t pctx,
                                                            cnrtQueue_t *queue);

/**
 * @brief Create an event corresponding to a specified runtime context.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer of runtime context.
 * @param pnotifier[out] point to a notifier handle to retrieve newly created notifier.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextCreateNotifier(cnrtRuntimeContext_t pctx,
                                                               cnrtNotifier_t *pnotifier);

/**
 * @brief Allocate memory on the specified MLU device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param pPtr[out] point to allocated memory.
 * @param dataDesc[in] data descriptor.
 * @return CNRT_RET_SUCCESS if success.
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextMallocByDesc(cnrtRuntimeContext_t pctx,
                                                             void **ptr,
                                                             cnrtDataDesc_t dataDesc);

/**
 * @brief Allocate multiple addresses for multiple data objects on the specified MLU device.
 *        Multiple addresses and data descriptors is present in array format.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param pPtrArray[out] point to the allocated memory array.
 * @param dataDescArray[in] data descriptor array.
 * @param lentgh[in] array length.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextMallocByDescArray(cnrtRuntimeContext_t pctx,
                                                                  void ***ptr,
                                                                  cnrtDataDescArray_t dataDescArray,
                                                                  int length);

/**
 * @brief Copy data from src address to dst address.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param dest[in] destination address.
 * @param src[in] source address.
 * @param dataDesc[in] data descriptor.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextMemcpyByDesc(cnrtRuntimeContext_t pctx,
                                                             void *dest,
                                                             void *src,
                                                             cnrtDataDesc_t dataDesc,
                                                             cnrtMemTransDir_t dir);

/**
 * @brief Copy multi-way data from src address to dst address.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param dest[in] destination address.
 * @param src[in] source address.
 * @param dataDesc[in] data descriptor.
 * @param data_parallelism[in] data parallelism.
 * @param dir[in] direction of transfer.
 *                @see  CNRT_MEM_TRANS_DIR_HOST2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2DEV,
 *                      CNRT_MEM_TRANS_DIR_DEV2HOST,
 *                      CNRT_MEM_TRANS_DIR_HOST2HOST,
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextMemcpyByDescArray(cnrtRuntimeContext_t pctx,
                                                                  void **destArray,
                                                                  void *srcArray,
                                                                  cnrtDataDescArray_t dataDescArray,
                                                                  int length,
                                                                  cnrtMemTransDir_t dir);

/**
 * @brief Free the memory space pointed by ptr, which must
 *        be returned by a previous call to cnrtRuntimeContextMemcpyByDesc.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param ptr[in] point to the memory to be free.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextFree(cnrtRuntimeContext_t pctx, void *ptr);

/**
 * @brief Free the memory space array pointed by ptr, which must
 *        be returned by a previous call to cnrtRuntimeContextMallocByDescArray.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param ptr[in] a pointer array.
 * @param length[in] array lenght.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtRuntimeContextFreeArray(cnrtRuntimeContext_t pctx,
                                                          void **ptr,
                                                          int length);

/**
 * @brief Destroy a runtime context.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtDestroyRuntimeContext(cnrtRuntimeContext_t pctx);

/**
 * @brief Invoke a runtime context on MLU.
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param params[in]  point to arguments.
 * @param queue[in] queue associated to the function call.
 * @param extra[in]  Reserved for future use.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtInvokeRuntimeContext(cnrtRuntimeContext_t pctx,
                                                       void **params,
                                                       cnrtQueue_t queue,
                                                       void *extra);

/**
 * @brief Invoke a runtime context on MLU with mutable batchsize
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer to runtime context
 * @param params[in]  point to arguments.
 * @param queue[in] queue associated to the function call.
 * @param batch[in] batch number to invoke
 * @param extra[in]  Reserved for future use.
 *
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
cnrtRet_t cnrtInvokeRuntimeContextBatch(cnrtRuntimeContext_t pctx,
                                        void **params,
                                        cnrtQueue_t queue,
                                        int batch,
                                        void *extra);

/**
 * @brief Get the runtime context info on the specified MLU device.
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer of runtime context.
 * @param key[in] the key of the runtime context.
 * @param out[out] the value of the key.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetRuntimeContextInfo(cnrtRuntimeContext_t pctx,
                                                        cnrtRuntimeContextInfo_t key,
                                                        void **out);

/**
 * @brief Set current device to runtime context binded device
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param pctx[in] pointer of runtime context.
 * @return CNRT_RET_SUCCESS if success,
 *         otherwise the error code is returned.
 */
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentContextDevice(cnrtRuntimeContext_t pctx);

/**
 * @brief Get the specific CPU bitmap according to the device index write to
 *        the struct DeviceAffinity
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param affinity[out] array reference in which to return a bitmask of CPUS, 64
 *        CPUS per unsigned long on 32 bit
 * @param dev_ordinal[in] the device dev_ordinal
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t cnrtGetDeviceAffinity(cnrtDeviceAffinity_t *affinity,
                                                    int dev_ordinal);

/**
 * @brief Clear the current thread affinity binding
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dev_ordinal[in] the device ordinal
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t cnrtClearCurrentThreadAffinity(int dev_ordinal);

/**
* @brief Set the Current thread to the specific cpu according to the device affinity
*
 *  **Supports both MLU100 and MLU270**
 * 
 * @param dev_ordinal[in] the device ordinal
* @return CNRT_RET_SUCCESS if success, otherwise with the error code.
*/
extern CNRT_DLL_API cnrtRet_t cnrtSetCurrentThreadAffinity(int dev_ordinal);

/**
 * @brief Get the ordinal1 topology relationship with the ordinal2
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param relationship[out] the relationship of two device'topology
 * @param dev_ordinal1[in] the first device ordinal
 * @param dev_ordinal2[in] the second device ordinal
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtTopologyGetRelationship(cnrtTopologyRelationshipEnum_t *relationship,
                            int dev_ordinal1,
                            int dev_ordinal2);

/**
 * @brief Retrieve the set of devices that nearest to a given device at a specific
 *        interconnectivity level for all products
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param relationship[in] specified relationship
 * @param count[out] ordinalArray' size
 * @param ordinalArray[out] get the related devices's id
 * @param dev_ordinal[in] the device ordinal
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t
cnrtTopologyGetNearestDevices(cnrtTopologyRelationshipEnum_t relationship,
                              uint64_t *count,
                              uint64_t *ordinal_array,
                              int dev_ordinal);

/**
 * @brieif Retrieve the set of devices that have a CPU affinity with the given CPU number
 *         for all products
 *
 *  **Supports both MLU100 and MLU270**
 * 
 * @param cpuid[in] specified cpu id
 * @param count[out] ordinalArray's size
 * @param ordinalArray[out] get related devices's id
 * @return CNRT_RET_SUCCESS if success, otherwise with the error code.
 */
extern CNRT_DLL_API cnrtRet_t cnrtTopologyGetCpuRelatedDevices(int cpuid,
                                                               uint64_t *count,
                                                               uint64_t *ordinal_array);

#if defined(__cplusplus)
}
#endif /*__cplusplus*/
#endif /*__CNRT_H*/
