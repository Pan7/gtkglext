/* GdkGLExt - OpenGL Extension to GDK
 * Copyright (C) 2002  Naofumi Yasufuku
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.
 */

#ifndef __GDK_GL_GLXEXT_H__
#define __GDK_GL_GLXEXT_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/glx.h>
#include <GL/gl.h>

#include <gdk/gdkglquery.h>

G_BEGIN_DECLS

#ifndef GLX_VERSION_1_3
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXFBConfigID;
typedef XID GLXContextID;
typedef XID GLXWindow;
typedef XID GLXPbuffer;
#endif

#if !defined(__glxext_h_) && defined(GLX_ARB_get_proc_address)
/* for __GLXextFuncPtr typedef in glxext.h */
#  undef GLX_ARB_get_proc_address
#endif
#include <gdk/glext/glxext.h>

/* 
 * GLX_VERSION_1_3
 */

/* glXGetFBConfigs */
typedef GLXFBConfig * ( * GdkGLProc_glXGetFBConfigs) (Display *dpy, int screen, int *nelements);
GdkGLProc    gdk_gl_get_glXGetFBConfigs (void);
#define      gdk_gl_glXGetFBConfigs(proc, dpy, screen, nelements) \
  ( ((GdkGLProc_glXGetFBConfigs) (proc)) (dpy, screen, nelements) )

/* glXChooseFBConfig */
typedef GLXFBConfig * ( * GdkGLProc_glXChooseFBConfig) (Display *dpy, int screen, const int *attrib_list, int *nelements);
GdkGLProc    gdk_gl_get_glXChooseFBConfig (void);
#define      gdk_gl_glXChooseFBConfig(proc, dpy, screen, attrib_list, nelements) \
  ( ((GdkGLProc_glXChooseFBConfig) (proc)) (dpy, screen, attrib_list, nelements) )

/* glXGetFBConfigAttrib */
typedef int ( * GdkGLProc_glXGetFBConfigAttrib) (Display *dpy, GLXFBConfig config, int attribute, int *value);
GdkGLProc    gdk_gl_get_glXGetFBConfigAttrib (void);
#define      gdk_gl_glXGetFBConfigAttrib(proc, dpy, config, attribute, value) \
  ( ((GdkGLProc_glXGetFBConfigAttrib) (proc)) (dpy, config, attribute, value) )

/* glXGetVisualFromFBConfig */
typedef XVisualInfo * ( * GdkGLProc_glXGetVisualFromFBConfig) (Display *dpy, GLXFBConfig config);
GdkGLProc    gdk_gl_get_glXGetVisualFromFBConfig (void);
#define      gdk_gl_glXGetVisualFromFBConfig(proc, dpy, config) \
  ( ((GdkGLProc_glXGetVisualFromFBConfig) (proc)) (dpy, config) )

/* glXCreateWindow */
typedef GLXWindow ( * GdkGLProc_glXCreateWindow) (Display *dpy, GLXFBConfig config, Window win, const int *attrib_list);
GdkGLProc    gdk_gl_get_glXCreateWindow (void);
#define      gdk_gl_glXCreateWindow(proc, dpy, config, win, attrib_list) \
  ( ((GdkGLProc_glXCreateWindow) (proc)) (dpy, config, win, attrib_list) )

/* glXDestroyWindow */
typedef void ( * GdkGLProc_glXDestroyWindow) (Display *dpy, GLXWindow win);
GdkGLProc    gdk_gl_get_glXDestroyWindow (void);
#define      gdk_gl_glXDestroyWindow(proc, dpy, win) \
  ( ((GdkGLProc_glXDestroyWindow) (proc)) (dpy, win) )

/* glXCreatePixmap */
typedef GLXPixmap ( * GdkGLProc_glXCreatePixmap) (Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attrib_list);
GdkGLProc    gdk_gl_get_glXCreatePixmap (void);
#define      gdk_gl_glXCreatePixmap(proc, dpy, config, pixmap, attrib_list) \
  ( ((GdkGLProc_glXCreatePixmap) (proc)) (dpy, config, pixmap, attrib_list) )

/* glXDestroyPixmap */
typedef void ( * GdkGLProc_glXDestroyPixmap) (Display *dpy, GLXPixmap pixmap);
GdkGLProc    gdk_gl_get_glXDestroyPixmap (void);
#define      gdk_gl_glXDestroyPixmap(proc, dpy, pixmap) \
  ( ((GdkGLProc_glXDestroyPixmap) (proc)) (dpy, pixmap) )

/* glXCreatePbuffer */
typedef GLXPbuffer ( * GdkGLProc_glXCreatePbuffer) (Display *dpy, GLXFBConfig config, const int *attrib_list);
GdkGLProc    gdk_gl_get_glXCreatePbuffer (void);
#define      gdk_gl_glXCreatePbuffer(proc, dpy, config, attrib_list) \
  ( ((GdkGLProc_glXCreatePbuffer) (proc)) (dpy, config, attrib_list) )

/* glXDestroyPbuffer */
typedef void ( * GdkGLProc_glXDestroyPbuffer) (Display *dpy, GLXPbuffer pbuf);
GdkGLProc    gdk_gl_get_glXDestroyPbuffer (void);
#define      gdk_gl_glXDestroyPbuffer(proc, dpy, pbuf) \
  ( ((GdkGLProc_glXDestroyPbuffer) (proc)) (dpy, pbuf) )

/* glXQueryDrawable */
typedef void ( * GdkGLProc_glXQueryDrawable) (Display *dpy, GLXDrawable draw, int attribute, unsigned int *value);
GdkGLProc    gdk_gl_get_glXQueryDrawable (void);
#define      gdk_gl_glXQueryDrawable(proc, dpy, draw, attribute, value) \
  ( ((GdkGLProc_glXQueryDrawable) (proc)) (dpy, draw, attribute, value) )

/* glXCreateNewContext */
typedef GLXContext ( * GdkGLProc_glXCreateNewContext) (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
GdkGLProc    gdk_gl_get_glXCreateNewContext (void);
#define      gdk_gl_glXCreateNewContext(proc, dpy, config, render_type, share_list, direct) \
  ( ((GdkGLProc_glXCreateNewContext) (proc)) (dpy, config, render_type, share_list, direct) )

/* glXMakeContextCurrent */
typedef Bool ( * GdkGLProc_glXMakeContextCurrent) (Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
GdkGLProc    gdk_gl_get_glXMakeContextCurrent (void);
#define      gdk_gl_glXMakeContextCurrent(proc, dpy, draw, read, ctx) \
  ( ((GdkGLProc_glXMakeContextCurrent) (proc)) (dpy, draw, read, ctx) )

/* glXGetCurrentReadDrawable */
typedef GLXDrawable ( * GdkGLProc_glXGetCurrentReadDrawable) (void);
GdkGLProc    gdk_gl_get_glXGetCurrentReadDrawable (void);
#define      gdk_gl_glXGetCurrentReadDrawable(proc) \
  ( ((GdkGLProc_glXGetCurrentReadDrawable) (proc)) () )

/* glXGetCurrentDisplay */
typedef Display * ( * GdkGLProc_glXGetCurrentDisplay) (void);
GdkGLProc    gdk_gl_get_glXGetCurrentDisplay (void);
#define      gdk_gl_glXGetCurrentDisplay(proc) \
  ( ((GdkGLProc_glXGetCurrentDisplay) (proc)) () )

/* glXQueryContext */
typedef int ( * GdkGLProc_glXQueryContext) (Display *dpy, GLXContext ctx, int attribute, int *value);
GdkGLProc    gdk_gl_get_glXQueryContext (void);
#define      gdk_gl_glXQueryContext(proc, dpy, ctx, attribute, value) \
  ( ((GdkGLProc_glXQueryContext) (proc)) (dpy, ctx, attribute, value) )

/* glXSelectEvent */
typedef void ( * GdkGLProc_glXSelectEvent) (Display *dpy, GLXDrawable draw, unsigned long event_mask);
GdkGLProc    gdk_gl_get_glXSelectEvent (void);
#define      gdk_gl_glXSelectEvent(proc, dpy, draw, event_mask) \
  ( ((GdkGLProc_glXSelectEvent) (proc)) (dpy, draw, event_mask) )

/* glXGetSelectedEvent */
typedef void ( * GdkGLProc_glXGetSelectedEvent) (Display *dpy, GLXDrawable draw, unsigned long *event_mask);
GdkGLProc    gdk_gl_get_glXGetSelectedEvent (void);
#define      gdk_gl_glXGetSelectedEvent(proc, dpy, draw, event_mask) \
  ( ((GdkGLProc_glXGetSelectedEvent) (proc)) (dpy, draw, event_mask) )

/* 
 * GLX_VERSION_1_4
 */

/* glXGetProcAddress */
typedef GdkGLProc ( * GdkGLProc_glXGetProcAddress) (const GLubyte *procName);
GdkGLProc    gdk_gl_get_glXGetProcAddress (void);
#define      gdk_gl_glXGetProcAddress(proc, procName) \
  ( ((GdkGLProc_glXGetProcAddress) (proc)) (procName) )

/* 
 * GLX_ARB_get_proc_address
 */

/* glXGetProcAddressARB */
typedef GdkGLProc ( * GdkGLProc_glXGetProcAddressARB) (const GLubyte *procName);
GdkGLProc    gdk_gl_get_glXGetProcAddressARB (void);
#define      gdk_gl_glXGetProcAddressARB(proc, procName) \
  ( ((GdkGLProc_glXGetProcAddressARB) (proc)) (procName) )

/* 
 * GLX_SGI_swap_control
 */

/* glXSwapIntervalSGI */
typedef int ( * GdkGLProc_glXSwapIntervalSGI) (int interval);
GdkGLProc    gdk_gl_get_glXSwapIntervalSGI (void);
#define      gdk_gl_glXSwapIntervalSGI(proc, interval) \
  ( ((GdkGLProc_glXSwapIntervalSGI) (proc)) (interval) )

/* 
 * GLX_SGI_video_sync
 */

/* glXGetVideoSyncSGI */
typedef int ( * GdkGLProc_glXGetVideoSyncSGI) (unsigned int *count);
GdkGLProc    gdk_gl_get_glXGetVideoSyncSGI (void);
#define      gdk_gl_glXGetVideoSyncSGI(proc, count) \
  ( ((GdkGLProc_glXGetVideoSyncSGI) (proc)) (count) )

/* glXWaitVideoSyncSGI */
typedef int ( * GdkGLProc_glXWaitVideoSyncSGI) (int divisor, int remainder, unsigned int *count);
GdkGLProc    gdk_gl_get_glXWaitVideoSyncSGI (void);
#define      gdk_gl_glXWaitVideoSyncSGI(proc, divisor, remainder, count) \
  ( ((GdkGLProc_glXWaitVideoSyncSGI) (proc)) (divisor, remainder, count) )

/* 
 * GLX_SGI_make_current_read
 */

/* glXMakeCurrentReadSGI */
typedef Bool ( * GdkGLProc_glXMakeCurrentReadSGI) (Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
GdkGLProc    gdk_gl_get_glXMakeCurrentReadSGI (void);
#define      gdk_gl_glXMakeCurrentReadSGI(proc, dpy, draw, read, ctx) \
  ( ((GdkGLProc_glXMakeCurrentReadSGI) (proc)) (dpy, draw, read, ctx) )

/* glXGetCurrentReadDrawableSGI */
typedef GLXDrawable ( * GdkGLProc_glXGetCurrentReadDrawableSGI) (void);
GdkGLProc    gdk_gl_get_glXGetCurrentReadDrawableSGI (void);
#define      gdk_gl_glXGetCurrentReadDrawableSGI(proc) \
  ( ((GdkGLProc_glXGetCurrentReadDrawableSGI) (proc)) () )

/* 
 * GLX_SGIX_video_source
 */

#ifdef _VL_H

/* glXCreateGLXVideoSourceSGIX */
typedef GLXVideoSourceSGIX ( * GdkGLProc_glXCreateGLXVideoSourceSGIX) (Display *display, int screen, VLServer server, VLPath path, int nodeClass, VLNode drainNode);
GdkGLProc    gdk_gl_get_glXCreateGLXVideoSourceSGIX (void);
#define      gdk_gl_glXCreateGLXVideoSourceSGIX(proc, display, screen, server, path, nodeClass, drainNode) \
  ( ((GdkGLProc_glXCreateGLXVideoSourceSGIX) (proc)) (display, screen, server, path, nodeClass, drainNode) )

/* glXDestroyGLXVideoSourceSGIX */
typedef void ( * GdkGLProc_glXDestroyGLXVideoSourceSGIX) (Display *dpy, GLXVideoSourceSGIX glxvideosource);
GdkGLProc    gdk_gl_get_glXDestroyGLXVideoSourceSGIX (void);
#define      gdk_gl_glXDestroyGLXVideoSourceSGIX(proc, dpy, glxvideosource) \
  ( ((GdkGLProc_glXDestroyGLXVideoSourceSGIX) (proc)) (dpy, glxvideosource) )

#endif /* _VL_H */

/* 
 * GLX_EXT_import_context
 */

/* glXGetCurrentDisplayEXT */
typedef Display * ( * GdkGLProc_glXGetCurrentDisplayEXT) (void);
GdkGLProc    gdk_gl_get_glXGetCurrentDisplayEXT (void);
#define      gdk_gl_glXGetCurrentDisplayEXT(proc) \
  ( ((GdkGLProc_glXGetCurrentDisplayEXT) (proc)) () )

/* glXQueryContextInfoEXT */
typedef int ( * GdkGLProc_glXQueryContextInfoEXT) (Display *dpy, GLXContext context, int attribute, int *value);
GdkGLProc    gdk_gl_get_glXQueryContextInfoEXT (void);
#define      gdk_gl_glXQueryContextInfoEXT(proc, dpy, context, attribute, value) \
  ( ((GdkGLProc_glXQueryContextInfoEXT) (proc)) (dpy, context, attribute, value) )

/* glXGetContextIDEXT */
typedef GLXContextID ( * GdkGLProc_glXGetContextIDEXT) (const GLXContext context);
GdkGLProc    gdk_gl_get_glXGetContextIDEXT (void);
#define      gdk_gl_glXGetContextIDEXT(proc, context) \
  ( ((GdkGLProc_glXGetContextIDEXT) (proc)) (context) )

/* glXImportContextEXT */
typedef GLXContext ( * GdkGLProc_glXImportContextEXT) (Display *dpy, GLXContextID contextID);
GdkGLProc    gdk_gl_get_glXImportContextEXT (void);
#define      gdk_gl_glXImportContextEXT(proc, dpy, contextID) \
  ( ((GdkGLProc_glXImportContextEXT) (proc)) (dpy, contextID) )

/* glXFreeContextEXT */
typedef void ( * GdkGLProc_glXFreeContextEXT) (Display *dpy, GLXContext context);
GdkGLProc    gdk_gl_get_glXFreeContextEXT (void);
#define      gdk_gl_glXFreeContextEXT(proc, dpy, context) \
  ( ((GdkGLProc_glXFreeContextEXT) (proc)) (dpy, context) )

/* 
 * GLX_SGIX_fbconfig
 */

/* glXGetFBConfigAttribSGIX */
typedef int ( * GdkGLProc_glXGetFBConfigAttribSGIX) (Display *dpy, GLXFBConfigSGIX config, int attribute, int *value);
GdkGLProc    gdk_gl_get_glXGetFBConfigAttribSGIX (void);
#define      gdk_gl_glXGetFBConfigAttribSGIX(proc, dpy, config, attribute, value) \
  ( ((GdkGLProc_glXGetFBConfigAttribSGIX) (proc)) (dpy, config, attribute, value) )

/* glXChooseFBConfigSGIX */
typedef GLXFBConfigSGIX * ( * GdkGLProc_glXChooseFBConfigSGIX) (Display *dpy, int screen, int *attrib_list, int *nelements);
GdkGLProc    gdk_gl_get_glXChooseFBConfigSGIX (void);
#define      gdk_gl_glXChooseFBConfigSGIX(proc, dpy, screen, attrib_list, nelements) \
  ( ((GdkGLProc_glXChooseFBConfigSGIX) (proc)) (dpy, screen, attrib_list, nelements) )

/* glXCreateGLXPixmapWithConfigSGIX */
typedef GLXPixmap ( * GdkGLProc_glXCreateGLXPixmapWithConfigSGIX) (Display *dpy, GLXFBConfigSGIX config, Pixmap pixmap);
GdkGLProc    gdk_gl_get_glXCreateGLXPixmapWithConfigSGIX (void);
#define      gdk_gl_glXCreateGLXPixmapWithConfigSGIX(proc, dpy, config, pixmap) \
  ( ((GdkGLProc_glXCreateGLXPixmapWithConfigSGIX) (proc)) (dpy, config, pixmap) )

/* glXCreateContextWithConfigSGIX */
typedef GLXContext ( * GdkGLProc_glXCreateContextWithConfigSGIX) (Display *dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct);
GdkGLProc    gdk_gl_get_glXCreateContextWithConfigSGIX (void);
#define      gdk_gl_glXCreateContextWithConfigSGIX(proc, dpy, config, render_type, share_list, direct) \
  ( ((GdkGLProc_glXCreateContextWithConfigSGIX) (proc)) (dpy, config, render_type, share_list, direct) )

/* glXGetVisualFromFBConfigSGIX */
typedef XVisualInfo * ( * GdkGLProc_glXGetVisualFromFBConfigSGIX) (Display *dpy, GLXFBConfigSGIX config);
GdkGLProc    gdk_gl_get_glXGetVisualFromFBConfigSGIX (void);
#define      gdk_gl_glXGetVisualFromFBConfigSGIX(proc, dpy, config) \
  ( ((GdkGLProc_glXGetVisualFromFBConfigSGIX) (proc)) (dpy, config) )

/* glXGetFBConfigFromVisualSGIX */
typedef GLXFBConfigSGIX ( * GdkGLProc_glXGetFBConfigFromVisualSGIX) (Display *dpy, XVisualInfo *vis);
GdkGLProc    gdk_gl_get_glXGetFBConfigFromVisualSGIX (void);
#define      gdk_gl_glXGetFBConfigFromVisualSGIX(proc, dpy, vis) \
  ( ((GdkGLProc_glXGetFBConfigFromVisualSGIX) (proc)) (dpy, vis) )

/* 
 * GLX_SGIX_pbuffer
 */

/* glXCreateGLXPbufferSGIX */
typedef GLXPbufferSGIX ( * GdkGLProc_glXCreateGLXPbufferSGIX) (Display *dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int *attrib_list);
GdkGLProc    gdk_gl_get_glXCreateGLXPbufferSGIX (void);
#define      gdk_gl_glXCreateGLXPbufferSGIX(proc, dpy, config, width, height, attrib_list) \
  ( ((GdkGLProc_glXCreateGLXPbufferSGIX) (proc)) (dpy, config, width, height, attrib_list) )

/* glXDestroyGLXPbufferSGIX */
typedef void ( * GdkGLProc_glXDestroyGLXPbufferSGIX) (Display *dpy, GLXPbufferSGIX pbuf);
GdkGLProc    gdk_gl_get_glXDestroyGLXPbufferSGIX (void);
#define      gdk_gl_glXDestroyGLXPbufferSGIX(proc, dpy, pbuf) \
  ( ((GdkGLProc_glXDestroyGLXPbufferSGIX) (proc)) (dpy, pbuf) )

/* glXQueryGLXPbufferSGIX */
typedef int ( * GdkGLProc_glXQueryGLXPbufferSGIX) (Display *dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int *value);
GdkGLProc    gdk_gl_get_glXQueryGLXPbufferSGIX (void);
#define      gdk_gl_glXQueryGLXPbufferSGIX(proc, dpy, pbuf, attribute, value) \
  ( ((GdkGLProc_glXQueryGLXPbufferSGIX) (proc)) (dpy, pbuf, attribute, value) )

/* glXSelectEventSGIX */
typedef void ( * GdkGLProc_glXSelectEventSGIX) (Display *dpy, GLXDrawable drawable, unsigned long mask);
GdkGLProc    gdk_gl_get_glXSelectEventSGIX (void);
#define      gdk_gl_glXSelectEventSGIX(proc, dpy, drawable, mask) \
  ( ((GdkGLProc_glXSelectEventSGIX) (proc)) (dpy, drawable, mask) )

/* glXGetSelectedEventSGIX */
typedef void ( * GdkGLProc_glXGetSelectedEventSGIX) (Display *dpy, GLXDrawable drawable, unsigned long *mask);
GdkGLProc    gdk_gl_get_glXGetSelectedEventSGIX (void);
#define      gdk_gl_glXGetSelectedEventSGIX(proc, dpy, drawable, mask) \
  ( ((GdkGLProc_glXGetSelectedEventSGIX) (proc)) (dpy, drawable, mask) )

/* 
 * GLX_SGI_cushion
 */

/* glXCushionSGI */
typedef void ( * GdkGLProc_glXCushionSGI) (Display *dpy, Window window, float cushion);
GdkGLProc    gdk_gl_get_glXCushionSGI (void);
#define      gdk_gl_glXCushionSGI(proc, dpy, window, cushion) \
  ( ((GdkGLProc_glXCushionSGI) (proc)) (dpy, window, cushion) )

/* 
 * GLX_SGIX_video_resize
 */

/* glXBindChannelToWindowSGIX */
typedef int ( * GdkGLProc_glXBindChannelToWindowSGIX) (Display *display, int screen, int channel, Window window);
GdkGLProc    gdk_gl_get_glXBindChannelToWindowSGIX (void);
#define      gdk_gl_glXBindChannelToWindowSGIX(proc, display, screen, channel, window) \
  ( ((GdkGLProc_glXBindChannelToWindowSGIX) (proc)) (display, screen, channel, window) )

/* glXChannelRectSGIX */
typedef int ( * GdkGLProc_glXChannelRectSGIX) (Display *display, int screen, int channel, int x, int y, int w, int h);
GdkGLProc    gdk_gl_get_glXChannelRectSGIX (void);
#define      gdk_gl_glXChannelRectSGIX(proc, display, screen, channel, x, y, w, h) \
  ( ((GdkGLProc_glXChannelRectSGIX) (proc)) (display, screen, channel, x, y, w, h) )

/* glXQueryChannelRectSGIX */
typedef int ( * GdkGLProc_glXQueryChannelRectSGIX) (Display *display, int screen, int channel, int *dx, int *dy, int *dw, int *dh);
GdkGLProc    gdk_gl_get_glXQueryChannelRectSGIX (void);
#define      gdk_gl_glXQueryChannelRectSGIX(proc, display, screen, channel, dx, dy, dw, dh) \
  ( ((GdkGLProc_glXQueryChannelRectSGIX) (proc)) (display, screen, channel, dx, dy, dw, dh) )

/* glXQueryChannelDeltasSGIX */
typedef int ( * GdkGLProc_glXQueryChannelDeltasSGIX) (Display *display, int screen, int channel, int *x, int *y, int *w, int *h);
GdkGLProc    gdk_gl_get_glXQueryChannelDeltasSGIX (void);
#define      gdk_gl_glXQueryChannelDeltasSGIX(proc, display, screen, channel, x, y, w, h) \
  ( ((GdkGLProc_glXQueryChannelDeltasSGIX) (proc)) (display, screen, channel, x, y, w, h) )

/* glXChannelRectSyncSGIX */
typedef int ( * GdkGLProc_glXChannelRectSyncSGIX) (Display *display, int screen, int channel, GLenum synctype);
GdkGLProc    gdk_gl_get_glXChannelRectSyncSGIX (void);
#define      gdk_gl_glXChannelRectSyncSGIX(proc, display, screen, channel, synctype) \
  ( ((GdkGLProc_glXChannelRectSyncSGIX) (proc)) (display, screen, channel, synctype) )

/* 
 * GLX_SGIX_dmbuffer
 */

#ifdef _DM_BUFFER_H_

/* glXAssociateDMPbufferSGIX */
typedef Bool ( * GdkGLProc_glXAssociateDMPbufferSGIX) (Display *dpy, GLXPbufferSGIX pbuffer, DMparams *params, DMbuffer dmbuffer);
GdkGLProc    gdk_gl_get_glXAssociateDMPbufferSGIX (void);
#define      gdk_gl_glXAssociateDMPbufferSGIX(proc, dpy, pbuffer, params, dmbuffer) \
  ( ((GdkGLProc_glXAssociateDMPbufferSGIX) (proc)) (dpy, pbuffer, params, dmbuffer) )

#endif /* _DM_BUFFER_H_ */

/* 
 * GLX_SGIX_swap_group
 */

/* glXJoinSwapGroupSGIX */
typedef void ( * GdkGLProc_glXJoinSwapGroupSGIX) (Display *dpy, GLXDrawable drawable, GLXDrawable member);
GdkGLProc    gdk_gl_get_glXJoinSwapGroupSGIX (void);
#define      gdk_gl_glXJoinSwapGroupSGIX(proc, dpy, drawable, member) \
  ( ((GdkGLProc_glXJoinSwapGroupSGIX) (proc)) (dpy, drawable, member) )

/* 
 * GLX_SGIX_swap_barrier
 */

/* glXBindSwapBarrierSGIX */
typedef void ( * GdkGLProc_glXBindSwapBarrierSGIX) (Display *dpy, GLXDrawable drawable, int barrier);
GdkGLProc    gdk_gl_get_glXBindSwapBarrierSGIX (void);
#define      gdk_gl_glXBindSwapBarrierSGIX(proc, dpy, drawable, barrier) \
  ( ((GdkGLProc_glXBindSwapBarrierSGIX) (proc)) (dpy, drawable, barrier) )

/* glXQueryMaxSwapBarriersSGIX */
typedef Bool ( * GdkGLProc_glXQueryMaxSwapBarriersSGIX) (Display *dpy, int screen, int *max);
GdkGLProc    gdk_gl_get_glXQueryMaxSwapBarriersSGIX (void);
#define      gdk_gl_glXQueryMaxSwapBarriersSGIX(proc, dpy, screen, max) \
  ( ((GdkGLProc_glXQueryMaxSwapBarriersSGIX) (proc)) (dpy, screen, max) )

/* 
 * GLX_SUN_get_transparent_index
 */

/* glXGetTransparentIndexSUN */
typedef Status ( * GdkGLProc_glXGetTransparentIndexSUN) (Display *dpy, Window overlay, Window underlay, long *pTransparentIndex);
GdkGLProc    gdk_gl_get_glXGetTransparentIndexSUN (void);
#define      gdk_gl_glXGetTransparentIndexSUN(proc, dpy, overlay, underlay, pTransparentIndex) \
  ( ((GdkGLProc_glXGetTransparentIndexSUN) (proc)) (dpy, overlay, underlay, pTransparentIndex) )

/*
 * GLX_MESA_copy_sub_buffer
 */

/* glXCopySubBufferMESA */
typedef void ( * GdkGLProc_glXCopySubBufferMESA) (Display *dpy, GLXDrawable drawable, int x, int y, int width, int height);
GdkGLProc    gdk_gl_get_glXCopySubBufferMESA (void);
#define      gdk_gl_glXCopySubBufferMESA(proc, dpy, drawable, x, y, width, height) \
  ( ((GdkGLProc_glXCopySubBufferMESA) (proc)) (dpy, drawable, x, y, width, height) )

/*
 * GLX_MESA_pixmap_colormap
 */

/* glXCreateGLXPixmapMESA */
typedef GLXPixmap ( * GdkGLProc_glXCreateGLXPixmapMESA) (Display *dpy, XVisualInfo *visual, Pixmap pixmap, Colormap cmap);
GdkGLProc    gdk_gl_get_glXCreateGLXPixmapMESA (void);
#define      gdk_gl_glXCreateGLXPixmapMESA(proc, dpy, visual, pixmap, cmap) \
  ( ((GdkGLProc_glXCreateGLXPixmapMESA) (proc)) (dpy, visual, pixmap, cmap) )

/*
 * GLX_MESA_release_buffers
 */

/* glXReleaseBuffersMESA */
typedef Bool ( * GdkGLProc_glXReleaseBuffersMESA) (Display *dpy, GLXDrawable drawable);
GdkGLProc    gdk_gl_get_glXReleaseBuffersMESA (void);
#define      gdk_gl_glXReleaseBuffersMESA(proc, dpy, drawable) \
  ( ((GdkGLProc_glXReleaseBuffersMESA) (proc)) (dpy, drawable) )

/*
 * GLX_MESA_set_3dfx_mode
 */

/* glXSet3DfxModeMESA */
typedef Bool ( * GdkGLProc_glXSet3DfxModeMESA) (int mode);
GdkGLProc    gdk_gl_get_glXSet3DfxModeMESA (void);
#define      gdk_gl_glXSet3DfxModeMESA(proc, mode) \
  ( ((GdkGLProc_glXSet3DfxModeMESA) (proc)) (mode) )

/* 
 * GLX_OML_sync_control
 */

/* glXGetSyncValuesOML */
typedef Bool ( * GdkGLProc_glXGetSyncValuesOML) (Display *dpy, GLXDrawable drawable, int64_t *ust, int64_t *msc, int64_t *sbc);
GdkGLProc    gdk_gl_get_glXGetSyncValuesOML (void);
#define      gdk_gl_glXGetSyncValuesOML(proc, dpy, drawable, ust, msc, sbc) \
  ( ((GdkGLProc_glXGetSyncValuesOML) (proc)) (dpy, drawable, ust, msc, sbc) )

/* glXGetMscRateOML */
typedef Bool ( * GdkGLProc_glXGetMscRateOML) (Display *dpy, GLXDrawable drawable, int32_t *numerator, int32_t *denominator);
GdkGLProc    gdk_gl_get_glXGetMscRateOML (void);
#define      gdk_gl_glXGetMscRateOML(proc, dpy, drawable, numerator, denominator) \
  ( ((GdkGLProc_glXGetMscRateOML) (proc)) (dpy, drawable, numerator, denominator) )

/* glXSwapBuffersMscOML */
typedef int64_t ( * GdkGLProc_glXSwapBuffersMscOML) (Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder);
GdkGLProc    gdk_gl_get_glXSwapBuffersMscOML (void);
#define      gdk_gl_glXSwapBuffersMscOML(proc, dpy, drawable, target_msc, divisor, remainder) \
  ( ((GdkGLProc_glXSwapBuffersMscOML) (proc)) (dpy, drawable, target_msc, divisor, remainder) )

/* glXWaitForMscOML */
typedef Bool ( * GdkGLProc_glXWaitForMscOML) (Display *dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t *ust, int64_t *msc, int64_t *sbc);
GdkGLProc    gdk_gl_get_glXWaitForMscOML (void);
#define      gdk_gl_glXWaitForMscOML(proc, dpy, drawable, target_msc, divisor, remainder, ust, msc, sbc) \
  ( ((GdkGLProc_glXWaitForMscOML) (proc)) (dpy, drawable, target_msc, divisor, remainder, ust, msc, sbc) )

/* glXWaitForSbcOML */
typedef Bool ( * GdkGLProc_glXWaitForSbcOML) (Display *dpy, GLXDrawable drawable, int64_t target_sbc, int64_t *ust, int64_t *msc, int64_t *sbc);
GdkGLProc    gdk_gl_get_glXWaitForSbcOML (void);
#define      gdk_gl_glXWaitForSbcOML(proc, dpy, drawable, target_sbc, ust, msc, sbc) \
  ( ((GdkGLProc_glXWaitForSbcOML) (proc)) (dpy, drawable, target_sbc, ust, msc, sbc) )

G_END_DECLS

#endif /* __GDK_GL_GLXEXT_H__ */
