# Copyright (C) 2012 The Android Open Source Project
# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import common
import struct

"""Custom OTA commands for celox devices"""

def FullOTA_Assertions(info):
	info.script.AppendExtra("ifelse(!is_mounted(\"/data\"), run_program(\"/sbin/busybox\", \"mount\", \"/data\"));")
	info.script.AppendExtra("ifelse(!is_mounted(\"/system\"), run_program(\"/sbin/busybox\", \"mount\", \"/system\"));")
	info.script.AppendExtra(
		('package_extract_file("install/bin/partitioncheck.sh", "/tmp/partitioncheck.sh");\n'
		'set_metadata("/tmp/partitioncheck.sh", "uid", 0, "gid", 0, "mode", 0777);'))
	info.script.AppendExtra('assert(run_program("/tmp/partitioncheck.sh") == 0);')

def FullOTA_PostValidate(info):
	# run e2fsck
	info.script.AppendExtra('run_program("/sbin/e2fsck", "-fy", "/dev/block/mmcblk0p25");');
	# resize2fs: run and delete
	info.script.AppendExtra('run_program("/tmp/install/bin/resize2fs_static", "/dev/block/mmcblk0p25");');
	# run e2fsck
	info.script.AppendExtra('run_program("/sbin/e2fsck", "-fy", "/dev/block/mmcblk0p25");');

def FullOTA_InstallEnd(info):
	info.script.Mount("/system")
	info.script.AppendExtra('run_program("/sbin/sh", "-c", "busybox echo BOOTIMAGE=/dev/block/mmcblk0p8 > /system/.supersu");')
	info.script.AppendExtra('ifelse(is_substring("SGH-T989", getprop("ro.product.device")) || is_substring("SGH-T989", getprop("ro.build.product")) || is_substring("SGH-T989D", getprop("ro.product.device")) || is_substring("SGH-T989D", getprop("ro.build.product")) || is_substring("hercules", getprop("ro.product.device")) || is_substring("hercules", getprop("ro.build.product")), run_program("/sbin/sh", "-c", "busybox cp /system/lib/hercules/* /system/lib/"));')
	info.script.AppendExtra('ifelse(is_substring("SGH-T989", getprop("ro.product.device")) || is_substring("SGH-T989", getprop("ro.build.product")) || is_substring("SGH-T989D", getprop("ro.product.device")) || is_substring("SGH-T989D", getprop("ro.build.product")) || is_substring("hercules", getprop("ro.product.device")) || is_substring("hercules", getprop("ro.build.product")), run_program("/sbin/sh", "-c", "busybox echo SGH-T989 > /system/variant.prop"));')
	info.script.AppendExtra('ifelse(is_substring("SGH-I727", getprop("ro.product.device")) || is_substring("SGH-I727", getprop("ro.build.product")) || is_substring("SGH-I727R", getprop("ro.product.device")) || is_substring("SGH-I727R", getprop("ro.build.product")) || is_substring("skyrocket", getprop("ro.product.device")) || is_substring("skyrocket", getprop("ro.build.product")), run_program("/sbin/sh", "-c", "busybox echo SGH-I727 > /system/variant.prop"));')
	info.script.AppendExtra('delete_recursive("/system/lib/hercules/");')
	info.script.Unmount("/system")
