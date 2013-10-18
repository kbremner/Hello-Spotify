/*
 * spotify_callbacks.c
 *
 *  Created on: 18 Oct 2013
 *      Author: Kyle
 */
#include <android/log.h>
#include "headers/callbacks.h"

void SP_CALLCONV notify_main_thread(sp_session *sess){
	log_message(sess, "notify main thread");
}

/**
 * This callback is called when the user was logged in, but the connection to
 * Spotify was dropped for some reason.
 *
 * @sa sp_session_callbacks#connection_error
 */
void SP_CALLCONV connection_error(sp_session *session, sp_error error)
{
	__android_log_print(ANDROID_LOG_VERBOSE,"ConnectionError", "Connection to Spotify failed: %s\n",
	                sp_error_message(error));
}

/**
 * This callback is called when an attempt to login has succeeded or failed.
 *
 * @sa sp_session_callbacks#logged_in
 */
void SP_CALLCONV logged_in(sp_session *session, sp_error error)
{
	sp_user *me;
	const char *display_name, *username;
	int cc;

	if (SP_ERROR_OK != error) {
		__android_log_print(ANDROID_LOG_ERROR,"Login Error", "failed to log in to Spotify: %s\n",
		                sp_error_message(error));
		sp_session_release(session);
	}
	else {
		// Let us print the nice message...
		me = sp_session_user(session);
		display_name = (sp_user_is_loaded(me) ? sp_user_display_name(me) : sp_user_canonical_name(me));
		username = sp_session_user_name (session);
		cc = sp_session_user_country(session);
		__android_log_print(ANDROID_LOG_VERBOSE, "Logged in", "Logged in to Spotify as user %s [%s] (registered in country: %c%c)\n", username, display_name, cc >> 8, cc & 0xff);
	}
}

/**
 * This callback is called when the session has logged out of Spotify.
 *
 * @sa sp_session_callbacks#logged_out
 */
void SP_CALLCONV logged_out(sp_session *session)
{
	log_message(session, "logged out");
}


/**
 * This callback is called when the session have recieved a credential
 * that could be stored safely on disk
 *
 * @sa sp_session_callbacks#credentials_blob_updated
 */
void SP_CALLCONV credentials_blob_updated(sp_session *session, const char *blob)
{
	__android_log_print(ANDROID_LOG_VERBOSE, "Blog Updated", "blob for storage: %s\n", blob);
}

/**
 * This callback is called for log messages.
 *
 * @sa sp_session_callbacks#log_message
 */
void SP_CALLCONV log_message(sp_session *session, const char *data)
{
		__android_log_print(ANDROID_LOG_VERBOSE, "Spotimsg", "%s", data);
}



/**
 * Callback called when libspotify has new metadata available
 *
 * Not used in this example (but available to be able to reuse the session.c file
 * for other examples.)
 *
 * @sa sp_session_callbacks#metadata_updated
 */
void SP_CALLCONV metadata_updated(sp_session *sess)
{
	log_message(sess, "metadata updated");
}


/**
 *
 */
void SP_CALLCONV offline_status_updated(sp_session *sess)
{
	sp_offline_sync_status status;
	sp_offline_sync_get_status(sess, &status);
	if(status.syncing) {
		__android_log_print(ANDROID_LOG_VERBOSE,"Offline Status Updated",
			"Offline status: queued:%d:%zd done:%d:%zd copied:%d:%zd nocopy:%d err:%d\n",
		    status.queued_tracks,
		    (size_t)status.queued_bytes,
		    status.done_tracks,
		    (size_t)status.done_bytes,
		    status.copied_tracks,
		    (size_t)status.copied_bytes,
		    status.willnotcopy_tracks,
		    status.error_tracks);
	} else {
		__android_log_print(ANDROID_LOG_VERBOSE, "Offline Status Updated", "Offline status: Idle\n");
	}
}

