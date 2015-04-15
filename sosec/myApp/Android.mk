LOCAL_PATH := $(call my-dir)

local_c_includes := \
	$(NDK_PROJECT_PATH) \
	$(NDK_PROJECT_PATH)/crypto/asn1 \
	$(NDK_PROJECT_PATH)/crypto/evp \
	$(NDK_PROJECT_PATH)/include \
	$(NDK_PROJECT_PATH)/include/openssl
	
include $(CLEAR_VARS)

LOCAL_MODULE    := sosec

LOCAL_SRC_FILES := aesEncrypt.cpp aesUtil.cpp aesUtil.h

LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -llog
LOCAL_SHARED_LIBRARIES := libcrypto-static libssl-static
LOCAL_C_INCLUDES += $(local_c_includes)

include $(BUILD_SHARED_LIBRARY)