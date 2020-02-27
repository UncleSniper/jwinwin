#ifndef JWINWIN_JNI_WINEVENT_H
#define JWINWIN_JNI_WINEVENT_H

#include <windows.h>

typedef struct winevent_t {
	DWORD event;
	HWND hwnd;
	LONG idObject;
	LONG idChild;
	DWORD idEventThread;
	DWORD dwmsEventTime;
} winevent_t;

#endif /* JWINWIN_JNI_WINEVENT_H */
