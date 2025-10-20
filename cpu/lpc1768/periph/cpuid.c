/*
 * SPDX-FileCopyrightText: 2015 Freie Universität Berlin
 * SPDX-License-Identifier: LGPL-2.1-only
 */

/**
 * @ingroup     cpu_lpc1768
 * @ingroup     drivers_periph_cpuid
 * @{
 *
 * @file
 * @brief       Low-level CPUID driver implementation
 *
 * @author      Paul RATHGEB <paul.rathgeb@skynet.be>
 * @author      Dinh Nguyen <nqdinhddt@gmail.com>
 * @}
 */

#include <string.h>
#include <stdint.h>
#include "periph/cpuid.h"
#include "cpu_conf.h"
/**
 * @name IAP base address
 */
#define IAP_ADDRESS     0x1FFF1FF1

void cpuid_get(void *id)
{
    uint32_t result[5];
    /* IAP command for UUID : 58 (UM10360 page 645) */
    uint32_t command = 58;
    /* Define pointer to function type */
    void (*iap)(uint32_t[], uint32_t[]);
    /* Set the function pointer */
    iap = (void (*)(uint32_t[], uint32_t[])) IAP_ADDRESS;
    /* Read UUID */
    iap(&command, result);

    if (result[0] == 0) {
        memcpy(id, &result[1], CPUID_LEN);
    }
    else {
        memset(id, 0xFF, CPUID_LEN);
    }
}
