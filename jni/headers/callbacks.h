/*
 * spotify_callbacks.h
 *
 *  Created on: 18 Oct 2013
 *      Author: Kyle
 */

#ifndef SPOTIFY_CALLBACKS_H_
#define SPOTIFY_CALLBACKS_H_

#include "libspotify/api.h"

#ifdef __cplusplus
extern "C" {
#endif

void SP_CALLCONV connection_error(sp_session *session, sp_error error);
void SP_CALLCONV logged_in(sp_session *session, sp_error error);
void SP_CALLCONV logged_out(sp_session *session);
void SP_CALLCONV credentials_blob_updated(sp_session *session, const char *blob);
void SP_CALLCONV log_message(sp_session *session, const char *data);
void SP_CALLCONV metadata_updated(sp_session *sess);
void SP_CALLCONV offline_status_updated(sp_session *sess);
void SP_CALLCONV notify_main_thread(sp_session *sess);

#ifdef __cplusplus
}
#endif
#endif /* SPOTIFY_CALLBACKS_H_ */
