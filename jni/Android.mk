LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libspotify\spotify-prebuilt
LOCAL_SRC_FILES := libspotify\libspotify.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_LDLIBS	:= -llog
LOCAL_SHARED_LIBRARIES := libspotify\spotify-prebuilt
LOCAL_MODULE    := hello_spotify
LOCAL_SRC_FILES := appkey.c hello_spotify.c callbacks.c
include $(BUILD_SHARED_LIBRARY)
