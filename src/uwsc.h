/*
 * The Action handler is a simple libuhttpd handler that processes requests
 * by invoking registered C functions. The action handler is ideal for
 * situations when you want to generate a simple response using C code. 
 *
 * Copyright (C) 2017 Jianhui Zhao <jianhuizhao329@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UWSC_H
#define _UWSC_H

#include <libubox/uloop.h>
#include <libubox/ustream.h>
 #include <libubox/blobmsg.h>

enum client_state {
	CLIENT_STATE_INIT,
	CLIENT_STATE_HEADERS_SENT,
	CLIENT_STATE_REQUEST_DONE,
	CLIENT_STATE_RECV_HEADERS,
	CLIENT_STATE_RECV_DATA,
	CLIENT_STATE_ERROR
};

struct uwsc_client {
	struct ustream *us;
    struct ustream_fd sfd;
	enum client_state state;
	struct blob_buf meta;
	int status_code;
	unsigned int seq;
	bool eof;

	void (*onopen)(struct uwsc_client *cl);
    void (*onmessage)(struct uwsc_client *cl);
    void (*onerror)(struct uwsc_client *cl);
    void (*onclose)(struct uwsc_client *cl);
    void (*free)(struct uwsc_client *cl);
};

struct uwsc_client *uwsc_new(const char *url);

#endif