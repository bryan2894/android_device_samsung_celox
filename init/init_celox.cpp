/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "init_celox.h"
#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

int write_file_int(char const* path, int value)
{
    int fd;
    char buffer[20];
    int rc = -1, bytes;

    fd = open(path, O_WRONLY);
    if (fd >= 0) {
        bytes = snprintf(buffer, sizeof(buffer), "%d\n", value);
        rc = write(fd, buffer, bytes);
        close(fd);
    }

    return rc > 0 ? 0 : -1;
}

void vendor_load_properties()
{
    char device_variant[92];
    FILE *fp;

    fp = popen("/system/bin/strings /dev/block/mmcblk0p2 | /system/bin/grep -E ^SGH -m 1", "r");
    fgets(device_variant, sizeof(device_variant), fp);
    pclose(fp);

    if (strstr(device_variant, "SGH-T989")) {
        /* hercules */
        property_set("ro.build.fingerprint", "samsung/SGH-T989/SGH-T989:4.4/KRT16M/T989UVMC6:user/release-keys");
        property_set("ro.build.description", "SGH-T989-user 4.4 KRT16M UVMC6 release-keys");
        property_set("ro.product.model", "SGH-T989");
        property_set("ro.product.device", "SGH-T989");
        property_set("telephony.lteOnGsmDevice", "0");
        property_set("ro.telephony.default_network", "3");
        write_file_int("/sys/module/board_msm8x60_celox/parameters/model", SGH_T989);
    } else if (strstr(device_variant, "SGH-I727")) {
        /* skyrocket */
        property_set("ro.build.fingerprint", "samsung/SGH-I727/SGH-I727:4.1.2/JZO54K/I727UCMC1:user/release-keys");
        property_set("ro.build.description", "SGH-I727-user 4.1.2 JZO54K I727UCMC1 release-keys");
        property_set("ro.product.model", "SGH-I727");
        property_set("ro.product.device", "SGH-I727");
        property_set("telephony.lteOnGsmDevice", "1");
        property_set("ro.telephony.default_network", "9");
        write_file_int("/sys/module/board_msm8x60_celox/parameters/model", SGH_I727);
    }

    ERROR("Found radio image for %s setting build properties for device\n", device_variant);
}
