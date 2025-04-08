/* SPDX-License-Identifier: GPL-2.0-only */

#include "mpxy.h"

const char* getRPMIString(const enum rpmi_error_codes code)
{
	switch (code) {
		case RPMI_SUCCESS:
			return "RPMI_SUCCESS";
		case RPMI_ERR_FAILED:
			return "RPMI_ERR_FAILED";
		case RPMI_ERR_NOTSUPP:
			return "RPMI_ERR_NOTSUPP";
		case RPMI_ERR_INVALID_PARAM:
			return "RPMI_ERR_INVALID_PARAM";
		case RPMI_ERR_DENIED:
			return "RPMI_ERR_DENIED";
		case RPMI_ERR_INVALID_ADDR:
			return "RPMI_ERR_INVALID_ADDR";
		case RPMI_ERR_ALREADY:
			return "RPMI_ERR_ALREADY";
		case RPMI_ERR_EXTENSION:
			return "RPMI_ERR_EXTENSION";
		case RPMI_ERR_HW_FAULT:
			return "RPMI_ERR_HW_FAULT";
		case RPMI_ERR_BUSY:
			return "RPMI_ERR_BUSY";
		case RPMI_ERR_INVALID_STATE:
			return "RPMI_ERR_INVALID_STATE";
		case RPMI_ERR_BAD_RANGE:
			return "RPMI_ERR_BAD_RANGE";
		case RPMI_ERR_TIMEOUT:
			return "RPMI_ERR_TIMEOUT";
		case RPMI_ERR_IO:
			return "RPMI_ERR_IO";
		case RPMI_ERR_NO_DATA:
			return "RPMI_ERR_NO_DATA";
		case RPMI_ERR_RESERVED_START:
			return "RPMI_ERR_RESERVED_START";
		case RPMI_ERR_RESERVED_END:
			return "RPMI_ERR_RESERVED_END";
		case RPMI_ERR_VENDOR_START:
			return "RPMI_ERR_VENDOR_START";
		default:
			return "RPMI_ERR_UNKNOWN";
	}
}
