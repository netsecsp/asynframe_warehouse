#ifndef __FRAME_API_H__
#define __FRAME_API_H__

#pragma once

#include <frame/asm/IAsynFrame.h>

#ifdef __cplusplus 
extern "C" { 
#endif

DUILIB_API void frame_SetInstancesManager( /*[in ]*/InstancesManager *lpInstancesManager );

#ifdef __cplusplus 
}
#endif

#endif // __FRAME_API_H__