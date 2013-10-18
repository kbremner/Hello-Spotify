#include <jni.h>
#include <string.h>
#include <pthread.h>
#include <android/log.h>
#include <unistd.h>
#include "libspotify/api.h"
#include "headers/com_deftech_wrapify_Wrapify.h"
#include "headers/callbacks.h"

static sp_session_callbacks callbacks;

JNIEXPORT jstring JNICALL Java_com_deftech_wrapify_Wrapify_getBuildID(JNIEnv *env, jobject jObject) {
	return (*env)->NewStringUTF(env, sp_build_id());
}

JNIEXPORT int JNICALL Java_com_deftech_wrapify_Wrapify_login(JNIEnv *env, jobject jObject, jstring username, jstring password, jstring cache_dir) {
		sp_session_config config;
		sp_error error;
		sp_session *session;

	        /// The application key is specific to each project, and allows Spotify
	        /// to produce statistics on how our service is used.
		extern const char g_appkey[];
	        /// The size of the application key.
		extern const size_t g_appkey_size;

		// Clear down the config
		memset(&config, 0, sizeof(config));

		// Always do this. It allows libspotify to check for
		// header/library inconsistencies.
		config.api_version = SPOTIFY_API_VERSION;

		// The path of the directory to store the cache. This must be specified.
		// Please read the documentation on preferred values.
		config.cache_location = cache_dir;

		// The path of the directory to store the settings.
		// This must be specified.
		// Please read the documentation on preferred values.
		config.settings_location = cache_dir;

		// The key of the application. They are generated by Spotify,
		// and are specific to each application using libspotify.
		config.application_key = g_appkey;
		config.application_key_size = g_appkey_size;

		// This identifies the application using some
		// free-text string [1, 255] characters.
		config.user_agent = "Wrapify Android";


		// Register the callbacks.
		callbacks.logged_in = logged_in;
		callbacks.logged_out = logged_out;
		callbacks.metadata_updated = metadata_updated;
		callbacks.connection_error = connection_error;
		callbacks.notify_main_thread = notify_main_thread;

		callbacks.log_message = log_message;
		callbacks.offline_status_updated = offline_status_updated;
		callbacks.credentials_blob_updated = credentials_blob_updated;

		config.callbacks = &callbacks;

		error = sp_session_create(&config, &session);

		if (SP_ERROR_OK != error) {
			__android_log_print(ANDROID_LOG_ERROR,
					"Create Session Error", "failed to create session: %s\n", sp_error_message(error));
			return 2;
		}

		// Convert the username and password and login with them
		const char *name = (*env)->GetStringUTFChars(env, username, NULL);
		const char *passwd = (*env)->GetStringUTFChars(env, password, NULL);
		error = sp_session_login(session, name, passwd, 1, NULL);

		return 0;
}
