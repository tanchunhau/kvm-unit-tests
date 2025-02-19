/* SPDX-License-Identifier: GPL-2.0-only */

#define SHMEM_PAGE_SIZE 4096

//#define SBI_EXT_BASE            0x10
//#define RPMI_SRVGRP_VOLTAGE     0x00006
//#define RPMI_SRVGRP_CLOCK       0x00007
//#define RPMI_SRVGRP_POWER_DOMAIN   0x00008
//#define RPMI_SRVGRP_PERFORMANCE    0x00009
//#define SBI_EXT_RPXY            0x52505859
#define SBI_EXT_MPXY            0x4D505859
/* SBI function IDs for MPXY extension */
#define SBI_EXT_MPXY_SET_SHMEM			0x0
#define SBI_EXT_MPXY_GET_CHANNEL_IDS		0x1
#define SBI_EXT_MPXY_READ_ATTRS			0x2
#define SBI_EXT_MPXY_WRITE_ATTRS		0x3
#define SBI_EXT_MPXY_SEND_MSG_WITH_RESP		0x4
#define SBI_EXT_MPXY_SEND_MSG_NO_RESP		0x5
#define SBI_EXT_MPXY_GET_NOTIFICATION_EVENTS	0x6

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

enum rpmi_servicegroup_id {
	RPMI_SRVGRP_ID_MIN = 0,
	RPMI_SRVGRP_BASE = 0x0001,
	RPMI_SRVGRP_SYSTEM_RESET = 0x0003,
	RPMI_SRVGRP_SYSTEM_SUSPEND = 0x0004,
	RPMI_SRVGRP_HSM = 0x0005,
	RPMI_SRVGRP_CPPC = 0x0006,
	RPMI_SRVGRP_VOLTAGE = 0x00007,
	RPMI_SRVGRP_CLOCK = 0x0008,
	RPMI_SRVGRP_DEVICE_POWER = 0x00009,
	RPMI_SRVGRP_PERFORMANCE = 0x0000A,
	RPMI_SRVGRP_ID_MAX_COUNT,

	/* Reserved range for service groups */
	RPMI_SRVGRP_RESERVE_START = RPMI_SRVGRP_ID_MAX_COUNT,
	RPMI_SRVGRP_RESERVE_END = 0x7FFF,

	/* Vendor/Implementation-specific service groups range */
	RPMI_SRVGRP_VENDOR_START = 0x8000,
	RPMI_SRVGRP_VENDOR_END = 0xFFFF,
};

struct sbi_rpxy {
        void *shmem;
        //void *shmem_phys;
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



enum rpmi_clock_service_id {
        RPMI_CLK_SRV_ENABLE_NOTIFICATION = 0x01,
        RPMI_CLK_SRV_GET_SYSTEM_CLOCKS = 0x02,
        RPMI_CLK_SRV_GET_ATTRIBUTES = 0x03,
        RPMI_CLK_SRV_GET_SUPPORTED_RATES = 0x04,
        RPMI_CLK_SRV_SET_CONFIG = 0x05,
        RPMI_CLK_SRV_GET_CONFIG = 0x06,
        RPMI_CLK_SRV_SET_RATE = 0x07,
        RPMI_CLK_SRV_GET_RATE = 0x08,
        RPMI_CLK_SRV_ID_MAX_COUNT,
};

int check_mpxy_clock(void);

// clock service group
int clock_srvgrp_probe(void);

/*
int clock_query_quantity(void);
int clock_query_attrs(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_query_supported_rates(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_set_config(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_get_config(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_set_rate(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_get_rate(u32 clkid, struct sbi_rpxy_clk *rpxy_clk);
int clock_negative_srvgrp_probe(void);
int clock_negative_query_quantity(void);
int clock_negative_query_attrs(void);
int clock_negative_query_supported_rates(void);
int clock_negative_query_supported_rates_wrong_rate_index(void);
int clock_negative_set_config_with_wrong_id(void);
int clock_negative_set_config_with_wrong_config(void);
int clock_negative_get_config_with_wrong_id(void);
int clock_negative_set_rate_with_wrong_id(void);
int clock_negative_set_rate_with_wrong_rate(void);
int clock_negative_get_rate_with_wrong_id(void);
*/
