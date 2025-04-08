/* SPDX-License-Identifier: GPL-2.0-only */

// TODO: Temperorary declare at this file (mpxy.h) , will move to a suitable header file later.

#ifndef _MPXY_H
#define _MPXY_H

#include <libcflat.h>
#include "testcase/device_power.h"

#define MPXY_TEST_SUCCESS 0
#define MPXY_TEST_FAIL   -1

#define SBI_EXT_MPXY			0x4D505859
/* SBI function IDs for MPXY extension */
#define SBI_EXT_MPXY_SET_SHMEM			0x0
#define SBI_EXT_MPXY_GET_CHANNEL_IDS		0x1
#define SBI_EXT_MPXY_READ_ATTRS			0x2
#define SBI_EXT_MPXY_WRITE_ATTRS		0x3
#define SBI_EXT_MPXY_SEND_MSG_WITH_RESP		0x4
#define SBI_EXT_MPXY_SEND_MSG_NO_RESP		0x5
#define SBI_EXT_MPXY_GET_NOTIFICATION_EVENTS	0x6

#define MPXY_SHMEM_SIZE 4096

struct sbi_mpxy {
	void *shmem;
	unsigned long long shmem_phys;
	bool active;
};

/* SBI MPXY channel IDs data in shared memory */
struct sbi_mpxy_channel_ids_data {
	/* Remaining number of channel ids */
	u32 remaining;
	/* Returned channel ids in current function call */
	u32 returned;
	/* Returned channel id array */
	u32 channel_array[];
};

/* SBI MPXY MSI related channel attributes */
struct sbi_mpxy_msi_info {
	/* Lower 32-bits of the MSI target address */
	u32 msi_addr_lo;
	/* Upper 32-bits of the MSI target address */
	u32 msi_addr_hi;
	/* MSI data value */
	u32 msi_data;
};

struct sbi_mpxy_channel_attrs {
	/* Message protocol ID */
	u32 msg_proto_id;
	/* Message protocol Version */
	u32 msg_proto_version;
	/* Message protocol maximum message length */
	u32 msg_max_len;
	/* Message protocol message send timeout in microseconds */
	u32 msg_send_timeout;
	/* Message protocol message completion timeout in microseconds */
	u32 msg_completion_timeout;
	/* Bit array for channel capabilities */
	u32 capability;
	/* SSE Event Id */
	u32 sse_event_id;
	/* MSI enable/disable control knob */
	u32 msi_control;
	/* Channel MSI info */
	struct sbi_mpxy_msi_info msi_info;
	/* Events State Control */
	u32 events_state_ctrl;
};

struct sbi_mpxy_rpmi_channel_attrs {
	/* RPMI service group ID */
	u32 servicegroup_id;
	/* RPMI service group version */
	u32 servicegroup_version;
};

/** RPMI error codes */
enum rpmi_error_codes {
	RPMI_SUCCESS			= 0,
	RPMI_ERR_FAILED			= -1,
	RPMI_ERR_NOTSUPP		= -2,
	RPMI_ERR_INVALID_PARAM		= -3,
	RPMI_ERR_DENIED			= -4,
	RPMI_ERR_INVALID_ADDR		= -5,
	RPMI_ERR_ALREADY		= -6,
	RPMI_ERR_EXTENSION		= -7,
	RPMI_ERR_HW_FAULT		= -8,
	RPMI_ERR_BUSY			= -9,
	RPMI_ERR_INVALID_STATE		= -10,
	RPMI_ERR_BAD_RANGE		= -11,
	RPMI_ERR_TIMEOUT		= -12,
	RPMI_ERR_IO			= -13,
	RPMI_ERR_NO_DATA		= -14,
	RPMI_ERR_RESERVED_START		= -15,
	RPMI_ERR_RESERVED_END		= -127,
	RPMI_ERR_VENDOR_START		= -128,
};

const char* getRPMIString(const enum rpmi_error_codes code);

#endif // _MPXY_H
