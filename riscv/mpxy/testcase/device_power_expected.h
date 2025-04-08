/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _MPXY_DEVICE_POWER_EXPECTED_H
#define _MPXY_DEVICE_POWER_EXPECTED_H

#include <libcflat.h>

const bool has_device_power = true;
const u32 channel_id = 4098;
const u32 expected_number_of_domain = 6;

const char* expected_device_power_names[expected_number_of_domain] =
        {"dpwr0", "dpwr1", "dpwr2", "dpwr3", "dpwr4", "dpwr5"};

const u32 expected_device_power_latencies[expected_number_of_domain] =
        {100, 120, 90, 110, 130, 140};

const u32 expected_device_power_flags[expected_number_of_domain] =
        {6, 6, 6, 6, 6, 6};

#endif // _MPXY_DEVICE_POWER_EXPECTED_H