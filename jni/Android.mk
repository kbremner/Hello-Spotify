LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libspotify\spotify-prebuilt
LOCAL_SRC_FILES := libspotify\libspotify.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_LDLIBS	:= -llog
LOCAL_SHARED_LIBRARIES := libspotify\spotify-prebuilt
LOCAL_MODULE    := Wrapify
LOCAL_SRC_FILES := appkey.c Wrapify.c spotify_callbacks.c
include $(BUILD_SHARED_LIBRARY)