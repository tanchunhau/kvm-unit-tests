/* SPDX-License-Identifier: GPL-2.0-only */

#define SHMEM_PAGE_SIZE 4096

//#define SBI_EXT_BASE            0x10
//#define RPMI_SRVGRP_VOLTAGE     0x00006
#define RPMI_SRVGRP_CLOCK       0x00007
//#define RPMI_SRVGRP_POWER_DOMAIN   0x00008
//#define RPMI_SRVGRP_PERFORMANCE    0x00009
##define SBI_EXT_RPXY            0x52505859
#define SBI_EXT_MPXY            0x4D505859

enum sbi_ext_rpxy_fid {
        SBI_EXT_RPXY_PROBE = 0,
        SBI_EXT_RPXY_SETUP_SHMEM,
        SBI_EXT_RPXY_SEND_NORMAL_MSG,
        SBI_EXT_RPXY_SEND_POSTED_MSG,
        SBI_EXT_RPXY_GET_NOTIFICATIONS,
};

struct sbi_rpxy {
        void *shmem;
        //void *shmem_phys;
        unsigned long long shmem_phys;
        bool active;
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
