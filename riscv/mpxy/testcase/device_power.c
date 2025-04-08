/* SPDX-License-Identifier: GPL-2.0-only */
#include "device_power.h"
#include "device_power_expected.h"
#include <asm/sbi.h>


void device_power_get_num_domains(struct sbi_mpxy* mpxy)
{
	printf("device_power_get_num_domains\n");
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_get_num_domain_rx num_domain_rx;

	//struct rpmi_pm_get_domain_attrs_tx pm_get_domain_attrs_tx;
	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
		channel_id, RPMI_DP_SRV_GET_NUM_DOMAINS, 0, 0, 0, 0);

	if (!sret.error) {
		rx_bytes = sret.value;
		rx_bytes = MIN(sizeof(num_domain_rx), rx_bytes);
		memcpy(&num_domain_rx, mpxy->shmem, rx_bytes);
	}
	printf("status = %d\n", num_domain_rx.status);
	printf("num_domains = %u\n\n", num_domain_rx.num_domains);
}

void device_power_get_num_attributes(struct sbi_mpxy* mpxy)
{
	printf("device_power_get_num_attributes\n");
	struct sbiret sret;
	unsigned long rx_bytes;
	struct rpmi_pm_get_domain_attrs_tx pm_get_domain_attrs_tx;
	struct rpmi_pm_get_domain_attrs_rx pm_get_domain_attrs_rx;

	for (u32 i = 0; i < expected_number_of_domains; i++) {
		pm_get_domain_attrs_tx.domain_id = i;

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
}

void device_power_get_state(struct sbi_mpxy* mpxy)
{
	printf("device_power_get_state\n");
}

void device_power_set_state(struct sbi_mpxy* mpxy)
{
	printf("device_power_set_state\n");
}

void run_device_power_test(struct sbi_mpxy* mpxy)
{
	if (!has_device_power)
		return;

	device_power_get_num_domains(mpxy);
	device_power_get_num_attributes(mpxy);
	device_power_get_state(mpxy);
	device_power_set_state(mpxy);
}
