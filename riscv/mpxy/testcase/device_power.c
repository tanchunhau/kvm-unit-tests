/* SPDX-License-Identifier: GPL-2.0-only */
#include "device_power.h"
#include "device_power_expected.h"
#include "../mpxy.h"
#include <asm/sbi.h>

int device_power_get_num_domains(struct sbi_mpxy* mpxy)
{
	printf("Test 01 - Get number of domains\n");
	int ret = MPXY_TEST_SUCCESS;
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_get_num_domain_rx num_domain_rx;

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
		channel_id, RPMI_DP_SRV_GET_NUM_DOMAINS, 0, 0, 0, 0);

	if (!sret.error) {
		rx_bytes = sret.value;
		rx_bytes = MIN(sizeof(num_domain_rx), rx_bytes);
		memcpy(&num_domain_rx, mpxy->shmem, rx_bytes);

		if (num_domain_rx.status != RPMI_SUCCESS)
			ret = MPXY_TEST_FAIL;
		else if (num_domain_rx.num_domains != expected_number_of_domains)
			ret = MPXY_TEST_FAIL;

		printf("RPMI status = %s(%d)\n", getRPMIString(num_domain_rx.status), num_domain_rx.status);
		printf("num_domains = %u, expected = %u\n",
			num_domain_rx.num_domains, expected_number_of_domains);

	} else {
		ret = MPXY_TEST_FAIL;
	}

	printf("Test result : %s\n", (ret == MPXY_TEST_SUCCESS) ? "PASS" : "FAIL");

	return ret;
}

int device_power_get_num_attributes(struct sbi_mpxy* mpxy)
{
	printf("device_power_get_num_attributes\n");
	int ret = MPXY_TEST_SUCCESS;
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_get_domain_attrs_tx pm_get_domain_attrs_tx;
	struct rpmi_pm_get_domain_attrs_rx pm_get_domain_attrs_rx;

	for (u32 i = 0; i < expected_number_of_domains; i++) {
		pm_get_domain_attrs_tx.domain_id = i;

		memcpy(mpxy->shmem, &pm_get_domain_attrs_tx, sizeof(pm_get_domain_attrs_tx));

		sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
			channel_id, RPMI_DP_SRV_GET_ATTRS, sizeof(pm_get_domain_attrs_tx), 0, 0, 0);

		if (!sret.error) {
			rx_bytes = sret.value;
			rx_bytes = MIN(sizeof(pm_get_domain_attrs_rx), rx_bytes);
			memcpy(&pm_get_domain_attrs_rx, mpxy->shmem, rx_bytes);
		}
		printf("name[%u] = %s\n",i, pm_get_domain_attrs_rx.name);
		printf("*** get_domain_attrs status = %d\n", pm_get_domain_attrs_rx.status);
		printf("flags = %u\n", pm_get_domain_attrs_rx.flags);
		printf("transition_latency = %u\n", pm_get_domain_attrs_rx.transition_latency);
	}

	return ret;
}

int device_power_get_state(struct sbi_mpxy* mpxy)
{
	printf("device_power_get_state\n");
	int ret = MPXY_TEST_SUCCESS;
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_get_power_state_tx pm_get_power_state_tx;
	struct rpmi_pm_get_power_state_rx pm_get_power_state_rx;

	for (u32 i = 0; i < expected_number_of_domains; i++) {
		pm_get_power_state_tx.domain_id = i;
		memcpy(mpxy->shmem, &pm_get_power_state_tx, sizeof(pm_get_power_state_tx));
		sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
			channel_id, RPMI_DP_SRV_GET_STATE, sizeof(pm_get_power_state_tx), 0, 0, 0);
		if (!sret.error) {
			rx_bytes = sret.value;
			rx_bytes = MIN(sizeof(pm_get_power_state_rx), rx_bytes);
			memcpy(&pm_get_power_state_rx, mpxy->shmem, rx_bytes);
		}
		printf("*** get_power_state status = %d\n", pm_get_power_state_rx.status);
		printf("power_state = %u\n", pm_get_power_state_rx.power_state);
	}

	return ret;
}

int device_power_set_state(struct sbi_mpxy* mpxy)
{
	printf("device_power_set_state\n");
	int ret = MPXY_TEST_SUCCESS;
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_set_power_state_tx pm_set_power_state_tx;
	struct rpmi_pm_set_power_state_rx pm_set_power_state_rx;

	for (u32 i = 0; i < expected_number_of_domains; i++) {
		pm_set_power_state_tx.domain_id = i;
		pm_set_power_state_tx.power_state = 1;
		memcpy(mpxy->shmem, &pm_set_power_state_tx, sizeof(pm_set_power_state_tx));

		sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
			channel_id, RPMI_DP_SRV_SET_STATE, sizeof(pm_set_power_state_tx), 0, 0, 0);

		if (!sret.error) {
			rx_bytes = sret.value;
			rx_bytes = MIN(sizeof(pm_set_power_state_rx), rx_bytes);
			memcpy(&pm_set_power_state_rx, mpxy->shmem, rx_bytes);
		}
		printf("*** set_power_state status = %d\n", pm_set_power_state_rx.status);
	}

	return ret;
}

void run_device_power_test(struct sbi_mpxy* mpxy)
{
	if (!has_device_power)
		return;

	printf("--- Device Power Test ---\n");
	device_power_get_num_domains(mpxy);
	device_power_get_num_attributes(mpxy);
	device_power_get_state(mpxy);
	device_power_set_state(mpxy);
}
