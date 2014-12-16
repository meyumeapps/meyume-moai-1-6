/*
 * BlackBerryHost.h
 *
 *  Created on: Jun 2, 2013
 *      Author: nictuku
 */

#ifndef BLACKBERRYHOST_H_
#define BLACKBERRYHOST_H_

#include <screen/screen.h>
#include <bps/navigator.h>
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include "bbutil.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <moai-core/host.h>
#include <moai-sim/host.h>
#include <moai-util/host.h>

#if MOAI_WITH_BOX2D
	#include <moai-box2d/host.h>
#endif

#if MOAI_WITH_CHIPMUNK
	#include <moai-chipmunk/host.h>
#endif

#if MOAI_WITH_HARNESS
	#include <moai-harness/host.h>
#endif

#if MOAI_WITH_HTTP_CLIENT
	#include <moai-http-client/host.h>
#endif

#if MOAI_WITH_LUAEXT
	#include <moai-luaext/host.h>
#endif

#if MOAI_WITH_UNTZ
	#include <moai-untz/host.h>
#endif

namespace BB10InputDeviceID {
	enum {
		DEVICE,
		TOTAL,
	};
}

namespace BB10InputDeviceSensorID {
	enum {
		TOUCH,
		TOTAL,
	};
}

class BlackBerryHost {
public:
	BlackBerryHost();
	virtual ~BlackBerryHost();

	// This method is used to start the
	// game loop.
	void start ();

private:
	AKUContextID aku_context_id;
	screen_context_t screen_cxt;
    EGLint surface_width, surface_height;
    bool running;

    void initializeBlackBerry ();
    void initializeMoai ();
    void printMoaiVersion ();

    void render ();
    void update ();
    void processEvents ();
    void handleScreenEvent (bps_event_t *event);
    void enqueueTouch ( screen_event_t event, bool down);

    void terminate ();

};

#endif /* BLACKBERRYHOST_H_ */
