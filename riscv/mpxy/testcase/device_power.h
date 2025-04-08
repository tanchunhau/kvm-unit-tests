/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _MPXY_DEVICE_POWER_H
#define _MPXY_DEVICE_POWER_H

#include <libcflat.h>

#define RPMI_PM_DOMAIN_NAME_LEN		16

/* Service: GET_POWER_DOMAINS */
struct rpmi_pm_get_num_domain_rx {
	s32 status;
	u32 num_domains;
};

/* Service: GET_POWER_DOMAIN_ATTRS */
struct rpmi_pm_get_domain_attrs_tx {
	u32 domain_id;
};

/* pm domain attributes response data */
struct rpmi_pm_get_domain_attrs_rx {
	s32 status;
	u32 flags;
	u32 transition_latency;
	char name[RPMI_PM_DOMAIN_NAME_LEN];
};

/* Service: SET_POWER_DOMAIN_STATE */
struct rpmi_pm_set_power_state_tx {
	u32 domain_id;
	u32 power_state;
};

struct rpmi_pm_set_power_state_rx {
	s32 status;
};

/* Service: GET_POWER_DOMAIN_STATE */
struct rpmi_pm_get_power_state_tx {
	u32 domain_id;
};

struct rpmi_pm_get_power_state_rx {
	s32 status;
	u32 power_state;
};

/* RPMI Device Power Service IDs */
enum rpmi_device_power_service_id {
	RPMI_DP_SRV_ENABLE_NOTIFICATION = 0x01,
	RPMI_DP_SRV_GET_NUM_DOMAINS  = 0x02,
	RPMI_DP_SRV_GET_ATTRS = 0x03,
	RPMI_DP_SRV_SET_STATE = 0x04,
	RPMI_DP_SRV_GET_STATE = 0x05,
	RPMI_DP_SRV_ID_MAX_COUNT,
};

enum rpmi_device_power_state {
	RMPI_POWER_STATE_ON = 0x00,
	RMPI_POWER_STATE_OFF = 0x03,
};

const char* getRPMIPowerStateString(const enum rpmi_device_power_state state);

struct sbi_mpxy;  // Forward declaration

/* testcases */
int device_power_get_num_domains(struct sbi_mpxy* mpxy);
int device_power_get_num_attributes(struct sbi_mpxy* mpxy);
int device_power_get_state(struct sbi_mpxy* mpxy);
int device_power_set_state(struct sbi_mpxy* mpxy);

int device_power_get_num_attributes_with_wrong_domain_id(struct sbi_mpxy* mpxy);
int device_power_get_state_with_wrong_domain_id(struct sbi_mpxy* mpxy);

void run_device_power_test(struct sbi_mpxy* mpxy);

#endif // _MPXY_DEVICE_POWER_H
