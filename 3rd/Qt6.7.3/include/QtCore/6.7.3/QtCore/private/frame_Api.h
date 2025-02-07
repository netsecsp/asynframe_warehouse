#ifndef __FRAME_API_H__
#define __FRAME_API_H__

#include <frame/asm/IAsynFrame.h>

QT_BEGIN_NAMESPACE

#if !defined(QT_NAMESPACE) && defined(__cplusplus)
extern "C"
#endif
/* defined in qeventdispatcher_win.cpp */
Q_CORE_EXPORT Q_DECL_CONST_FUNCTION void frame_SetInstancesManager( /* [in] */InstancesManager *lpInstancesManager );

QT_END_NAMESPACE

#endif // __FRAME_API_H__
