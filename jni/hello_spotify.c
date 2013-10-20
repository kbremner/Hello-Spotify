#include <jni.h>
#include <string.h>
#include <pthread.h>
#include <android/log.h>
#include <unistd.h>
#include "libspotify/api.h"
#include "headers/com_deftech_spotify_HelloSpotify.h"
#include "headers/callbacks.h"

static pthread_t main_thread;
static sp_session *session;
static sp_session_callbacks callbacks = {
	&logged_in,
	&logged_out,
	&metadata_updated,
	&connection_error,
	NULL,
	&notify_main_thread,
	NULL,
	NULL,
	&log_message,
	NULL
};

static void *main_loop(){
	int next_timeout = 0;
	for(;;){
		sp_session_process_events(session, &next_timeout);
	}

	return NULL;
}

JNIEXPORT jstring JNICALL Java_com_deftech_spotify_HelloSpotify_getBuildID(JNIEnv *env, jobject jObject) {
	return (*env)->NewStringUTF(env, sp_build_id());
}

JNIEXPORT int JNICALL Java_com_deftech_spotify_HelloSpotify_login(JNIEnv *env, jobject jObject, jstring username, jstring password, jstring cache_dir) {
	sp_session_config config;
	sp_error error;

    // Get the app key
	extern const char g_appkey[];
	extern const size_t g_appkey_size;

	// Clear down the config
	memset(&config, 0, sizeof(config));

	// Allow libspotify to check for header/library inconsistencies.
	config.api_version = SPOTIFY_API_VERSION;

	// Set the cache dir
	config.cache_location = (*env)->GetStringUTFChars(env, cache_dir, NULL);
	__android_log_print(ANDROID_LOG_VERBOSE, "Cache", "cache dir: %s", config.cache_location);


	// Set the settings dir
	const char *settings_path = "/settings";
	char settings[strlen(config.cache_location) + strlen(settings_path)]; 	// Create the buffer
	memset(&settings, 0, sizeof(settings)); 								// 0-initialise it
	strcat(settings, config.cache_location);								// add the cache dir path
	strcat(settings, settings_path);										// add the settings sub path
	config.settings_location = settings;									// set the settings dir
	__android_log_print(ANDROID_LOG_VERBOSE, "Settings", "settings dir: %s", settings);

	// Set the app key
	config.application_key = g_appkey;
	config.application_key_size = g_appkey_size;

	// Identify the application using some free-text string [1, 255] characters.
	config.user_agent = "Hello Spotify";

	// Set the callbacks
	config.callbacks = &callbacks;

	// Try to create the session
	if (SP_ERROR_OK != sp_session_create(&config, &session)) {
		__android_log_print(ANDROID_LOG_ERROR,
				"Create Session Error", "failed to create session: %s\n", sp_error_message(error));
		return 2;
	}

	// Convert the username and password and login with them
	const char *name = (*env)->GetStringUTFChars(env, username, NULL);
	const char *passwd = (*env)->GetStringUTFChars(env, password, NULL);
	error = sp_session_login(session, name, passwd, 0, NULL);

	// If successful, start out background thread
	if(SP_ERROR_OK == error){
		pthread_create(&main_thread, NULL, &main_loop, NULL);
	}

	return error;
}

