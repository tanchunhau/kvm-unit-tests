/* SPDX-License-Identifier: GPL-2.0-only */
#include "../mpxy.h"
#include "device_power_expected.h"


void device_power_get_num_domains()
{
	printf("device_power_get_num_domains\n");
}

void device_power_get_num_attributes()
{
	printf("device_power_get_num_attributes\n");
}

void device_power_get_state()
{
	printf("device_power_get_state\n");
}

void device_power_set_state()
{
	printf("device_power_set_state\n");
}

void run_device_power_test()
{
	device_power_get_num_domains();
	device_power_get_num_attributes();
	device_power_get_state();
	device_power_set_state();
}
