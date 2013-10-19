#include <jni.h>

#ifndef _Included_com_deftech_spotify_HelloSpotify
#define _Included_com_deftech_spotify_HelloSpotify
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_com_deftech_spotify_HelloSpotify_getBuildID (JNIEnv *, jobject);
JNIEXPORT jint JNICALL Java_com_deftech_spotify_HelloSpotify_login (JNIEnv *, jobject, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
