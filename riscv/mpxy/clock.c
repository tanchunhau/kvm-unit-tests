#include <asm/sbi.h>
#include <libcflat.h>
#include "mpxy.h"
#include "expected/expected_clock.h"

int clock_srvgrp_probe(void)
{
    printf("clock_srvgrp_probe\n");
    struct sbiret sret;
    unsigned long val;

    sret = sbi_ecall(SBI_EXT_RPXY, SBI_EXT_RPXY_PROBE,
                     expected_clock_tpid, RPMI_SRVGRP_CLOCK, 0, 0, 0, 0);

    val = sret.value;

    return sret.error;
}

int check_mpxy_clock(void)
{
    printf("check_mpxy_clock\n");
    if (has_clock_srvgrp) {
        clock_srvgrp_probe();
    }
}