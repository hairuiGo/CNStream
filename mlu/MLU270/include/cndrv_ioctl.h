/************************************************************************
 *  @file cndrv_ioctl.h
 *
 *  @brief For sbts ioctl definitions.
 **************************************************************************/

/*************************************************************************
 * NOTICE:
 * Copyright (c) 2018 Cambricon, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CNDRV_IOCTL_H_
#define _CNDRV_IOCTL_H_

#if defined(__KERNEL__)
/*for kernel*/
#include <linux/types.h>
#include <asm/ioctl.h>

#elif defined(__linux__)
/*for userspace*/
#include <linux/types.h>
#include <asm/ioctl.h>

#else /* One of the BSDs */
/*for other BSDs*/
#include <sys/ioccom.h>
#include <sys/types.h>
typedef int8_t   __s8;
typedef uint8_t  __u8;
typedef int16_t  __s16;
typedef uint16_t __u16;
typedef int32_t  __s32;
typedef uint32_t __u32;
typedef int64_t  __s64;
typedef uint64_t __u64;
typedef size_t   __kernel_size_t;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#define DRV_SERIAL_NUM_LEN 2	/*should be define in ioctl.h*/

/*read pcie config with dword*/
struct read_pci_config_s {
	__u32 offset;
	__u32 val;
};

/*write pcie config with dword*/
struct write_pci_config_s {
	__u32 offset;
	__u32 val;
};

/*copy host data to ddr*/
struct host_to_dev_s {
	__u64 ia;/*ipu src addr*/
	__u64 ca;/*cpu dest addr*/
	__u32 total_size;
	__u32 residual_size;
};
/*copy data from ipu ddr*/
struct dev_to_host_s {
	__u64 ia;/*ipu src addr*/
	__u64 ca;/*cpu dest addr*/
	__u32 total_size;
	__u32 residual_size;
};
/*read/write ddr*/
struct wr_ddr_s {
	__u32 offset;
	__u32 val;
};

/* p2p */
struct p2p_s {
	int peer_fd;    /* peer open fd */
	__u64 src_addr; /* self ram addr */
	__u64 dst_addr; /* peer ram addr */
	__u32 count;
};

/*COPY_TO_RAM_PHY*/
struct copy_to_ram_s {
	__u32 size;
	__u64 cpu_addr;
	__u64 ram_addr;/*ipu physical addr*/
};
/*COPY_FORM_RAM_PHY*/
struct copy_from_ram_s {
	__u32 size;
	__u64 cpu_addr;
	__u64 ram_addr;/*ipu physical addr*/
};

/*MEM_ALLOC*/
struct mem_alloc_param_s {
	__u32 size;
	__u32 align;
	__u32 type;
	__u32 affinity;
	__u32 flag;
	__u64 ret_addr;
};

/*CRITICAL MEM_ALLOC*/
struct critical_mem_alloc_param_s {
	__u32 align;
	__u32 type;
	__u32 affinity;
	__u32 flag;
	__u32 cnt;
	__u32 *size_array;
	__u64 ret_addr;
};

/*MEM_FREE*/
struct mem_free_param_s {
	__u64 ret_addr;
	__u32 size;
};

/*MEM_MERGE*/
struct mem_merge_param_s {
	__u32 cnt;
	__u64 *virt_addrs;
	__u64 merged_addr;
};

/*COPY_TO_DDR*/
struct mem_copy_h2d_param_s {
	__u64 ca;
	__u64 ia;
	__u32 total_size;
	__u32 residual_size;
};

/*COPY_FROM_DDR*/
struct mem_copy_d2h_param_s {
	__u64 ca;
	__u64 ia;
	__u32 total_size;
	__u32 residual_size;
};

/*COPY_FROM_DDR_TO_DDR*/
struct mem_copy_d2d_param_s {
	__u64 src;
	__u64 dst;
	__u32 size;
//	__u32 residual_size;
};

/* p2p able */
struct p2p_able_s {
       int peer_fd;    /* peer open fd */
};

struct user_va_s {
	__u64 va;
};

#define CAMBR_BUS_MAGIC    'B'

#define _B_COPY_TO_DDR			1
#define _B_COPY_FROM_DDR		2
#define _B_COPY_TO_RAM_PHY		3
#define _B_COPY_FROM_RAM_PHY		4
#define _B_PCIE_FLR			5
#define _B_PCIE_HOT_RESET		6
#define _B_SHOW_PCIE_INFO		7
#define _B_PEER_TO_PEER			8
#define _B_PCIE_D3			9
#define _B_FREE_PINNED_MM		10
#define _B_GET_PCIE_BAR_INFO		11
#define _B_GET_PCIE_INFO		12
#define _B_PEER_ABLE                    13

#define B_COPY_TO_DDR	  \
	_IOW(CAMBR_BUS_MAGIC,  _B_COPY_TO_DDR, struct host_to_dev_s)
#define B_COPY_FROM_DDR   \
	_IOR(CAMBR_BUS_MAGIC,  _B_COPY_FROM_DDR, struct dev_to_host_s)
#define B_COPY_TO_RAM_PHY \
	_IOW(CAMBR_BUS_MAGIC,  _B_COPY_TO_RAM_PHY, struct copy_to_ram_s)
#define B_COPY_FROM_RAM_PHY \
	_IOR(CAMBR_BUS_MAGIC,  _B_COPY_FROM_RAM_PHY, struct copy_from_ram_s)
#define B_PCIE_FLR         _IO(CAMBR_BUS_MAGIC, _B_PCIE_FLR)
#define B_PCIE_HOT_RESET   _IO(CAMBR_BUS_MAGIC, _B_PCIE_HOT_RESET)
#define B_SHOW_PCIE_INFO   _IO(CAMBR_BUS_MAGIC, _B_SHOW_PCIE_INFO)
#define B_GET_PCIE_BAR_INFO   _IO(CAMBR_BUS_MAGIC, _B_GET_PCIE_BAR_INFO)
#define B_GET_PCIE_INFO   _IO(CAMBR_BUS_MAGIC, _B_GET_PCIE_INFO)
#define B_PEER_TO_PEER    \
	_IOW(CAMBR_BUS_MAGIC,  _B_PEER_TO_PEER, struct p2p_s)
#define B_PCIE_D3         \
	_IOW(CAMBR_BUS_MAGIC, _B_PCIE_D3, unsigned int)
#define B_FREE_PINNED_MM	  \
		_IOW(CAMBR_BUS_MAGIC,  _B_FREE_PINNED_MM, struct user_va_s)
#define B_PEER_ABLE    \
       _IOW(CAMBR_BUS_MAGIC,  _B_PEER_ABLE, struct p2p_able_s)

#define IOPARAM_SIZE_CHECK(karg)  \
	do { \
		usz = _IOC_SIZE(cmd);\
		sz = sizeof(karg);\
		pr_info("IOCTRL cmd=0x%08x,cmd#=%d,usz=%d,sz=%d\n",cmd,_IOC_NR(cmd),usz,sz);\
		if (sz != usz) { \
			sz = min(sz, usz); \
			pr_err("IOCTRL cmd=0x%08x,ioparam struct may be MISMATCH!\n",cmd); \
		} \
	} while (0)

/*for memory moudle*/
#define CAMBR_MM_MAGIC   'M'

#define _M_MEM_ALLOC				1
#define _M_MEM_FREE					2
#define _M_MEM_MERGE				3
#define _M_MEM_COPY_H2D				4
#define _M_MEM_COPY_D2H				5
#define _M_STACK_ALLOC				6
#define _M_FRAME_BUFFER_ALLOC		7
#define _M_FB_MEM_ALLOC				8
#define _M_CRITICAL_MEM_ALLOC		9
#define _M_GET_STACK_SIZE			10
#define _M_MEM_COPY_D2D				11

#define M_MEM_ALLOC				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_ALLOC, struct mem_alloc_param_s)
#define M_MEM_FREE				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_FREE, struct mem_free_param_s)
#define M_MEM_MERGE				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_MERGE, struct mem_merge_param_s)
#define M_MEM_COPY_H2D				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_COPY_H2D, struct mem_copy_h2d_param_s)
#define M_MEM_COPY_D2H				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_COPY_D2H, struct mem_copy_d2h_param_s)
#define M_STACK_ALLOC				\
	_IOW(CAMBR_MM_MAGIC, _M_STACK_ALLOC, unsigned int)
#define M_FRAME_BUFFER_ALLOC		\
	_IOW(CAMBR_MM_MAGIC, _M_FRAME_BUFFER_ALLOC, struct mem_alloc_param_s)
#define M_FB_MEM_ALLOC			\
	_IOW(CAMBR_MM_MAGIC, _M_FB_MEM_ALLOC, struct mem_alloc_param_s)
#define M_CRITICAL_MEM_ALLOC			\
	_IOW(CAMBR_MM_MAGIC, _M_CRITICAL_MEM_ALLOC, struct critical_mem_alloc_param_s)
#define M_GET_STACK_SIZE			\
	_IOR(CAMBR_MM_MAGIC, _M_GET_STACK_SIZE, unsigned int)
#define M_MEM_COPY_D2D				\
	_IOW(CAMBR_MM_MAGIC, _M_MEM_COPY_D2D, struct mem_copy_d2d_param_s)

#define CAMBRICON_MAGIC_NUM 'Y'
#define CAMB_RD_DRIVER_VERSION	_IOR(CAMBRICON_MAGIC_NUM, 38, unsigned int[DRV_SERIAL_NUM_LEN])

struct llc_st {
	__u32 id;
	__u32 type;
};

#define CAMBR_DEBUG_MAGIC   'D'

#define _DEBUG_IOMEM         1
#define _DEBUG_KERNEL_DMA    2
#define _DEBUG_SERV_STAT     3
#define _DEBUG_LLC_ECC			4
#define _DEBUG_LLC_CL_A_INV     5

#define DEBUG_IOMEM       _IO(CAMBR_DEBUG_MAGIC, _DEBUG_IOMEM)
#define DEBUG_KERNEL_DMA  _IO(CAMBR_DEBUG_MAGIC, _DEBUG_KERNEL_DMA)
#define DEBUG_SERV_STAT   _IOR(CAMBR_DEBUG_MAGIC, _DEBUG_SERV_STAT, struct wr_ddr_s)
#define DEBUG_LLC_ECC   _IOW(CAMBR_DEBUG_MAGIC, _DEBUG_LLC_ECC, struct llc_st)
#define DEBUG_LLC_CL_A_INV   _IOW(CAMBR_DEBUG_MAGIC, _DEBUG_LLC_CL_A_INV, struct llc_st)

struct function_st {
	__u64 static_data_addr;
	__u32 inst_off;
	__u32 inst_size;
	__u32 inst_config;
	__u32 param_num;
	__u32 invalid_llc;

	__u32 local_memory_count;
	__u64 *local_memory_size;
};

struct param_st {
	__u64 value;
	__u64 increment;
};

struct sbts_create_stream {
	void *hstream;
	__u64 dump_uvaddr;
	__u32 flags;
	__u32 priority;
};

struct sbts_destroy_stream {
	void *hstream;
};

struct sbts_stream_sync {
	void *hstream;
};

struct sbts_launch_kernel {
	void *f;/*temporary parameter*/
	__u32 dimx;
	__u32 dimy;
	__u32 dimz;
	__u32 kernel_class;
	void *hstream;
	void *param;/*temporary parmeter*/
	void **priv; /* reserve */
};

struct sbts_stream_dump {
	void *hstream;
};

/* event */
struct sbts_create_event {
	void *hevent;
	__u32 flags;
};

struct sbts_destroy_event {
	void *hevent;
};

struct sbts_wait_event {
	void *hevent;
};

struct sbts_query_event {
	void *hevent;
};

struct sbts_stream_wait_event {
	void *hstream;
	void *hevent;
};

struct sbts_place_notify_event {
	void *hevent;
	void *hstream;
};

struct sbts_event_elapsed_time {
	__u64 tv_sec;    /**<sconds */
	__u64 tv_usec;   /**<microseconds */
	void *hstart;
	void *hend;
};

struct sbts_query_stream {
	void *hstream;
};

enum sbts_cmd_type {
	_SBTS_CREATE_STREAM = 0,
	_SBTS_DESTROY_STREAM,
	_SBTS_LAUNCH_KERNEL,
	_SBTS_STREAM_SYNC,
	_SBTS_CORE_DUMP,
	_SBTS_EVENT_CREATE,
	_SBTS_EVENT_DESTROY,
	_SBTS_EVENT_PLACE,
	_SBTS_EVENT_WAIT,
	_SBTS_EVENT_QUERY,
	_SBTS_EVENT_ELAPSED_TIME,
	_SBTS_EVENT_STREAM_WAIT,
	_SBTS_STREAM_QUERY,
	_SBTS_SET_LOCAL_MEM,
	_SBTS_GET_LOCAL_MEM,
	_SBTS_CMD_NUM,
};

/**
 * Declaration of sbts module
 */
#define CAMBR_SBTS_MAGIC   'S'

#define SBTS_CREATE_STREAM		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_CREATE_STREAM,	\
		struct sbts_create_stream)
#define SBTS_DESTROY_STREAM		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_DESTROY_STREAM,	\
		struct sbts_destroy_stream)
#define SBTS_LAUNCH_KERNEL		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_LAUNCH_KERNEL,	\
		struct sbts_launch_kernel)
#define SBTS_STREAM_SYNC		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_STREAM_SYNC,	\
		struct sbts_stream_sync)
#define SBTS_CORE_DUMP			\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_CORE_DUMP,	\
		struct sbts_stream_dump)

#define SBTS_EVENT_CREATE		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_CREATE,		\
		struct sbts_create_event)
#define SBTS_EVENT_DESTROY		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_DESTROY,	\
		struct sbts_destroy_event)
#define SBTS_EVENT_PLACE		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_PLACE,		\
		struct sbts_place_notify_event)
#define SBTS_EVENT_WAIT			\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_WAIT,		\
		struct sbts_wait_event)
#define SBTS_EVENT_QUERY		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_QUERY,		\
		struct sbts_query_event)
#define SBTS_EVENT_ELAPSED_TIME	\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_ELAPSED_TIME,\
		struct sbts_event_elapsed_time)
#define SBTS_EVENT_STREAM_WAIT	\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_EVENT_STREAM_WAIT,\
		struct sbts_stream_wait_event)
#define SBTS_STREAM_QUERY		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_STREAM_QUERY,	\
		struct sbts_query_stream)

#define SBTS_SET_LOCAL_MEM		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_SET_LOCAL_MEM,	\
		unsigned int)
#define SBTS_GET_LOCAL_MEM		\
		_IOW(CAMBR_SBTS_MAGIC,	\
		_SBTS_GET_LOCAL_MEM,	\
		unsigned int)

#if defined(__cplusplus)
}
#endif

#endif /*_sbts_IOCTL_H_*/


