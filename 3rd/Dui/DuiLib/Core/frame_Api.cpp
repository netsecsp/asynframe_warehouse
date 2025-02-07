#include "StdAfx.h"
#include "frame_Api.h"

InstancesManager *_g_lpInstancesManager = 0;
void frame_SetInstancesManager( InstancesManager *lpInstancesManager )
{
    _g_lpInstancesManager = lpInstancesManager;
}