/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../SDL_internal.h"

#ifndef SDL_syscamera_h_
#define SDL_syscamera_h_

#include "../SDL_list.h"

// The SDL camera driver
typedef struct SDL_CameraDevice SDL_CameraDevice;

// Define the SDL camera driver structure
struct SDL_CameraDevice
{
    // The device's current camera specification
    SDL_CameraSpec spec;

    // Device name
    char *dev_name;

    // Current state flags
    SDL_AtomicInt shutdown;
    SDL_AtomicInt enabled;
    SDL_bool is_spec_set;

    // A mutex for locking the queue buffers
    SDL_Mutex *device_lock;
    SDL_Mutex *acquiring_lock;

    // A thread to feed the camera device
    SDL_Thread *thread;
    SDL_ThreadID threadid;

    // Queued buffers (if app not using callback).
    SDL_ListNode *buffer_queue;

    // Data private to this driver
    struct SDL_PrivateCameraData *hidden;
};

extern int SDL_SYS_CameraInit(void);
extern int SDL_SYS_CameraQuit(void);

// !!! FIXME: These names need to be made camera-specific.

extern int OpenDevice(SDL_CameraDevice *_this);
extern void CloseDevice(SDL_CameraDevice *_this);

extern int InitDevice(SDL_CameraDevice *_this);

extern int GetDeviceSpec(SDL_CameraDevice *_this, SDL_CameraSpec *spec);

extern int StartCamera(SDL_CameraDevice *_this);
extern int StopCamera(SDL_CameraDevice *_this);

extern int AcquireFrame(SDL_CameraDevice *_this, SDL_CameraFrame *frame);
extern int ReleaseFrame(SDL_CameraDevice *_this, SDL_CameraFrame *frame);

extern int GetNumFormats(SDL_CameraDevice *_this);
extern int GetFormat(SDL_CameraDevice *_this, int index, Uint32 *format);

extern int GetNumFrameSizes(SDL_CameraDevice *_this, Uint32 format);
extern int GetFrameSize(SDL_CameraDevice *_this, Uint32 format, int index, int *width, int *height);

extern int GetCameraDeviceName(SDL_CameraDeviceID instance_id, char *buf, int size);
extern SDL_CameraDeviceID *GetCameraDevices(int *count);

extern SDL_bool CheckAllDeviceClosed(void);
extern SDL_bool CheckDevicePlaying(void);

#endif // SDL_syscamera_h_
