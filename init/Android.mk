ifeq ($(TARGET_INIT_VENDOR_LIB),libinit_celox)

LOCAL_PATH := $(call my-dir)
LIBINIT_CELOX_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init
LOCAL_CFLAGS := -Wall -DANDROID_TARGET=\"$(TARGET_BOARD_PLATFORM)\"
LOCAL_SRC_FILES := init_celox.c
LOCAL_MODULE := libinit_celox
include $(BUILD_STATIC_LIBRARY)

endif
