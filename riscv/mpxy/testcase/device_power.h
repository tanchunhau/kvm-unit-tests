/* SPDX-License-Identifier: GPL-2.0-only */

struct sbi_mpxy;  // Forward declaration
void device_power_get_num_domains(struct sbi_mpxy* mpxy);
void device_power_get_num_attributes(struct sbi_mpxy* mpxy);
void device_power_get_state(struct sbi_mpxy* mpxy);
void device_power_set_state(struct sbi_mpxy* mpxy);
void run_device_power_test(struct sbi_mpxy* mpxy);