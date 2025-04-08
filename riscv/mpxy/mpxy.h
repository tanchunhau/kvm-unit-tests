/* SPDX-License-Identifier: GPL-2.0-only */

// TODO: Temperorary declare at this file (mpxy.h) , will move to a suitable header file later.

#ifndef _MPXY_H
#define _MPXY_H

#include "testcase/device_power.h"
#include <libcflat.h>


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

enum sbi_mpxy_attribute_id {
	/* Standard channel attributes managed by MPXY framework */
	SBI_MPXY_ATTR_MSG_PROT_ID		= 0x00000000,
	SBI_MPXY_ATTR_MSG_PROT_VER		= 0x00000001,
	SBI_MPXY_ATTR_MSG_MAX_LEN		= 0x00000002,
	SBI_MPXY_ATTR_MSG_SEND_TIMEOUT		= 0x00000003,
	SBI_MPXY_ATTR_MSG_COMPLETION_TIMEOUT	= 0x00000004,
	SBI_MPXY_ATTR_CHANNEL_CAPABILITY	= 0x00000005,
	SBI_MPXY_ATTR_SSE_EVENT_ID		= 0x00000006,
	SBI_MPXY_ATTR_MSI_CONTROL		= 0x00000007,
	SBI_MPXY_ATTR_MSI_ADDR_LO		= 0x00000008,
	SBI_MPXY_ATTR_MSI_ADDR_HI		= 0x00000009,
	SBI_MPXY_ATTR_MSI_DATA			= 0x0000000A,
	SBI_MPXY_ATTR_EVENTS_STATE_CONTROL	= 0x0000000B,
	SBI_MPXY_ATTR_STD_ATTR_MAX_IDX,
	/*
	 * Message protocol specific attributes, managed by
	 * the message protocol specification.
	 */
	SBI_MPXY_ATTR_MSGPROTO_ATTR_START	= 0x80000000,
	SBI_MPXY_ATTR_MSGPROTO_ATTR_END		= 0xffffffff
};

// from linux:
/* RPMI linux mailbox attribute IDs */
enum rpmi_mbox_attribute_id {
	RPMI_MBOX_ATTR_SPEC_VERSION = 0,
	RPMI_MBOX_ATTR_MAX_MSG_DATA_SIZE,
	RPMI_MBOX_ATTR_SERVICEGROUP_ID,
	RPMI_MBOX_ATTR_SERVICEGROUP_VERSION,
	RPMI_MBOX_ATTR_MAX_ID,
};

/**RPMI linux mailbox message types */
enum rpmi_mbox_message_type {
	RPMI_MBOX_MSG_TYPE_GET_ATTRIBUTE = 0,
	RPMI_MBOX_MSG_TYPE_SET_ATTRIBUTE,
	RPMI_MBOX_MSG_TYPE_SEND_WITH_RESPONSE,
	RPMI_MBOX_MSG_TYPE_SEND_WITHOUT_RESPONSE,
	RPMI_MBOX_MSG_TYPE_NOTIFICATION_EVENT,
	RPMI_MBOX_MSG_MAX_TYPE,
};

/* RPMI linux mailbox message instance */
struct rpmi_mbox_message {
	enum rpmi_mbox_message_type type;
	union {
		struct {
			enum rpmi_mbox_attribute_id id;
			u32 value;
		} attr;

		struct {
			u32 service_id;
			void *request;
			unsigned long request_len;
			void *response;
			unsigned long max_response_len;
			unsigned long out_response_len;
		} data;

		struct rpmi_notification_event *notif_event;
	};
	int error;
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

#endif // MPXY_H