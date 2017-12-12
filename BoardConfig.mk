# Copyright (C) 2014 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
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

# inherit from common msm8660
-include device/samsung/msm8660-common/BoardConfigCommon.mk

# inherit from the proprietary version
-include vendor/samsung/celox/BoardConfigVendor.mk

# Assert
TARGET_OTA_ASSERT_DEVICE := SGH-T989,hercules,SGH-I727,skyrocket

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/samsung/celox/bluetooth

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := MSM8660_SURF

# Init
TARGET_INIT_VENDOR_LIB := libinit_celox

# Kernel
BOARD_KERNEL_BASE := 0x40400000
BOARD_KERNEL_CMDLINE := androidboot.hardware=qcom usb_id_pin_rework=true no_console_suspend=true
BOARD_KERNEL_IMAGE_NAME := zImage
BOARD_KERNEL_PAGESIZE := 2048
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x01400000
TARGET_KERNEL_CONFIG := celox_defconfig
TARGET_KERNEL_SOURCE := kernel/samsung/msm8660-common

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 627048448
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16776192
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2149580800
BOARD_USERDATAIMAGE_PARTITION_SIZE := 20044316672

# Recovery
BOARD_HAS_NO_SELECT_BUTTON := true
BOARD_SUPPRESS_EMMC_WIPE := true
TARGET_USERIMAGES_USE_EXT4 := true

# SELinux
BOARD_SEPOLICY_DIRS += device/samsung/celox/sepolicy
