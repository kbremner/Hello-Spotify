#include <jni.h>

#ifndef _Included_com_deftech_wrapify_Wrapify
#define _Included_com_deftech_wrapify_Wrapify
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_com_deftech_wrapify_Wrapify_getBuildID (JNIEnv *, jobject);
JNIEXPORT jint JNICALL Java_com_deftech_wrapify_Wrapify_login (JNIEnv *, jobject, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
