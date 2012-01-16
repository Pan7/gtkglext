/* GdkGLExt - OpenGL Extension to GDK
 * Copyright (C) 2002-2004  Naofumi Yasufuku
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "gdkglwin32.h"
#include "gdkglprivate-win32.h"
#include "gdkglconfig-win32.h"
#include "gdkglcontext-win32.h"

static void          gdk_gl_context_insert (GdkGLContext *glcontext);
static void          gdk_gl_context_remove (GdkGLContext *glcontext);
static GdkGLContext *gdk_gl_context_lookup (HGLRC         hglrc);

static gboolean        _gdk_win32_gl_context_copy (GdkGLContext  *glcontext,
                                                   GdkGLContext  *src,
                                                   unsigned long  mask);
static GdkGLDrawable * _gdk_win32_gl_context_get_gl_drawable (GdkGLContext *glcontext);
static GdkGLConfig *   _gdk_win32_gl_context_get_gl_config (GdkGLContext *glcontext);
static GdkGLContext *  _gdk_win32_gl_context_get_share_list (GdkGLContext *glcontext);
static gboolean        _gdk_win32_gl_context_is_direct (GdkGLContext *glcontext);
static int             _gdk_win32_gl_context_get_render_type (GdkGLContext *glcontext);


G_DEFINE_TYPE (GdkGLContextImplWin32,              \
               gdk_gl_context_impl_win32,          \
               GDK_TYPE_GL_CONTEXT)

static void
gdk_gl_context_impl_win32_init (GdkGLContextImplWin32 *self)
{
  GDK_GL_NOTE_FUNC_PRIVATE ();

  self->hglrc = NULL;
  self->share_list = NULL;
  self->render_type = 0;
  self->glconfig = NULL;
  self->gldrawable = NULL;
  self->gldrawable_read = NULL;
  self->is_destroyed = 0;
  self->is_foreign = 0;
}

void
_gdk_gl_context_destroy (GdkGLContext *glcontext)
{
  GdkGLContextImplWin32 *impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  GDK_GL_NOTE_FUNC_PRIVATE ();

  if (impl->is_destroyed)
    return;

  gdk_gl_context_remove (glcontext);

  if (impl->hglrc == wglGetCurrentContext ())
    {
      glFinish ();

      GDK_GL_NOTE_FUNC_IMPL ("wglMakeCurrent");
      wglMakeCurrent (NULL, NULL);
    }

  if (!impl->is_foreign)
    {
      GDK_GL_NOTE_FUNC_IMPL ("wglDeleteContext");
      wglDeleteContext (impl->hglrc);
      impl->hglrc = NULL;
    }

  if (impl->gldrawable != NULL)
    {
      g_object_remove_weak_pointer (G_OBJECT (impl->gldrawable),
                                    (gpointer *) &(impl->gldrawable));
      impl->gldrawable = NULL;
    }

  /* currently unused. */
  /*
  if (impl->gldrawable_read != NULL)
    {
      g_object_remove_weak_pointer (G_OBJECT (impl->gldrawable_read),
                                    (gpointer *) &(impl->gldrawable_read));
      impl->gldrawable_read = NULL;
    }
  */

  impl->is_destroyed = TRUE;
}

static void
gdk_gl_context_impl_win32_finalize (GObject *object)
{
  GdkGLContextImplWin32 *impl = GDK_GL_CONTEXT_IMPL_WIN32 (object);

  GDK_GL_NOTE_FUNC_PRIVATE ();

  _gdk_gl_context_destroy (GDK_GL_CONTEXT (object));

  g_object_unref (G_OBJECT (impl->glconfig));

  if (impl->share_list != NULL)
    g_object_unref (G_OBJECT (impl->share_list));

  G_OBJECT_CLASS (gdk_gl_context_impl_win32_parent_class)->finalize (object);
}

static void
gdk_gl_context_impl_win32_class_init (GdkGLContextImplWin32Class *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  GDK_GL_NOTE_FUNC_PRIVATE ();

  klass->parent_class.copy            = _gdk_win32_gl_context_copy;
  klass->parent_class.get_gl_drawable = _gdk_win32_gl_context_get_gl_drawable;
  klass->parent_class.get_gl_config   = _gdk_win32_gl_context_get_gl_config;
  klass->parent_class.get_share_list  = _gdk_win32_gl_context_get_share_list;
  klass->parent_class.is_direct       = _gdk_win32_gl_context_is_direct;
  klass->parent_class.get_render_type = _gdk_win32_gl_context_get_render_type;

  object_class->finalize = gdk_gl_context_impl_win32_finalize;
}

static GdkGLContext *
gdk_gl_context_new_common (GdkGLConfig   *glconfig,
                           GdkGLContext  *share_list,
                           int            render_type,
                           HGLRC          hglrc,
                           gboolean       is_foreign)
{
  GdkGLContext *glcontext;
  GdkGLContextImplWin32 *impl;

  GDK_GL_NOTE_FUNC_PRIVATE ();

  /*
   * Instantiate the GdkGLContextImplWin32 object.
   */

  glcontext = g_object_new (GDK_TYPE_GL_CONTEXT_IMPL_WIN32, NULL);
  impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  impl->hglrc = hglrc;

  if (share_list != NULL && GDK_IS_GL_CONTEXT (share_list))
    {
      impl->share_list = share_list;
      g_object_ref (G_OBJECT (impl->share_list));
    }
  else
    {
      impl->share_list = NULL;
    }

  impl->render_type = render_type;

  impl->glconfig = glconfig;
  g_object_ref (G_OBJECT (impl->glconfig));

  impl->gldrawable = NULL;
  impl->gldrawable_read = NULL;

  impl->is_foreign = is_foreign;

  impl->is_destroyed = FALSE;

  /*
   * Insert into the GL context hash table.
   */

  gdk_gl_context_insert (glcontext);

  return glcontext;
}

/*< private >*/
GdkGLContext *
_gdk_win32_gl_context_new (GdkGLDrawable *gldrawable,
                           GdkGLContext  *share_list,
                           gboolean       direct,
                           int            render_type)
{
  GdkGLConfig *glconfig;
  HDC hdc;
  HGLRC hglrc;
  GdkGLContextImplWin32 *share_impl = NULL;

  GDK_GL_NOTE_FUNC_PRIVATE ();

  /*
   * Create an OpenGL rendering context.
   */

  glconfig = gdk_gl_drawable_get_gl_config (gldrawable);

  /* Get DC. */
  hdc = gdk_win32_gl_drawable_hdc_get (gldrawable);
  if (hdc == NULL)
    return NULL;

  GDK_GL_NOTE_FUNC_IMPL ("wglCreateContext");

  hglrc = wglCreateContext (hdc);

  /* Release DC. */
  gdk_win32_gl_drawable_hdc_release (gldrawable);

  if (hglrc == NULL)
    return NULL;

  if (share_list != NULL && GDK_IS_GL_CONTEXT (share_list))
    {
      GDK_GL_NOTE_FUNC_IMPL ("wglShareLists");

      share_impl = GDK_GL_CONTEXT_IMPL_WIN32 (share_list);
      if (!wglShareLists (share_impl->hglrc, hglrc))
        {
          wglDeleteContext (hglrc);
          return NULL;
        }
    }

  /*
   * Instantiate the GdkGLContextImplWin32 object.
   */

  return gdk_gl_context_new_common (glconfig,
                                    share_list,
                                    render_type,
                                    hglrc,
                                    FALSE);
}

GdkGLContext *
gdk_win32_gl_context_foreign_new (GdkGLConfig  *glconfig,
                                  GdkGLContext *share_list,
                                  HGLRC         hglrc)
{
  GDK_GL_NOTE_FUNC ();

  g_return_val_if_fail (GDK_IS_GL_CONFIG_IMPL_WIN32 (glconfig), NULL);
  g_return_val_if_fail (hglrc != NULL, NULL);

  /*
   * Instantiate the GdkGLContextImplWin32 object.
   */

  return gdk_gl_context_new_common (glconfig,
                                    share_list,
                                    (glconfig->is_rgba) ? GDK_GL_RGBA_TYPE : GDK_GL_COLOR_INDEX_TYPE,
                                    hglrc,
                                    TRUE);
}

static gboolean
_gdk_win32_gl_context_copy (GdkGLContext  *glcontext,
                            GdkGLContext  *src,
                            unsigned long  mask)
{
  HGLRC dst_hglrc, src_hglrc;

  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), FALSE);
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (src), FALSE);

  dst_hglrc = GDK_GL_CONTEXT_HGLRC (glcontext);
  if (dst_hglrc == NULL)
    return FALSE;

  src_hglrc = GDK_GL_CONTEXT_HGLRC (src);
  if (src_hglrc == NULL)
    return FALSE;

  GDK_GL_NOTE_FUNC_IMPL ("wglCopyContext");

  return wglCopyContext (src_hglrc, dst_hglrc, mask);
}

/*< private >*/
void
_gdk_gl_context_set_gl_drawable (GdkGLContext  *glcontext,
                                 GdkGLDrawable *gldrawable)
{
  GdkGLContextImplWin32 *impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  GDK_GL_NOTE_FUNC_PRIVATE ();

  if (impl->gldrawable == gldrawable)
    return;

  if (impl->gldrawable != NULL)
    {
      g_object_remove_weak_pointer (G_OBJECT (impl->gldrawable),
                                    (gpointer *) &(impl->gldrawable));
      impl->gldrawable = NULL;
    }

  if (gldrawable != NULL && GDK_IS_GL_DRAWABLE (gldrawable))
    {
      impl->gldrawable = gldrawable;
      g_object_add_weak_pointer (G_OBJECT (impl->gldrawable),
                                 (gpointer *) &(impl->gldrawable));
    }
}

/*< private >*/
/* currently unused. */
/*
void
_gdk_gl_context_set_gl_drawable_read (GdkGLContext  *glcontext,
                                      GdkGLDrawable *gldrawable_read)
{
  GdkGLContextImplWin32 *impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  GDK_GL_NOTE_FUNC_PRIVATE ();

  if (impl->gldrawable_read == gldrawable_read)
    return;

  if (impl->gldrawable_read != NULL)
    {
      g_object_remove_weak_pointer (G_OBJECT (impl->gldrawable_read),
                                    (gpointer *) &(impl->gldrawable_read));
      impl->gldrawable_read = NULL;
    }

  if (gldrawable_read != NULL && GDK_IS_GL_DRAWABLE (gldrawable_read))
    {
      impl->gldrawable_read = gldrawable_read;
      g_object_add_weak_pointer (G_OBJECT (impl->gldrawable_read),
                                 (gpointer *) &(impl->gldrawable_read));
    }
}
*/

static GdkGLDrawable *
_gdk_win32_gl_context_get_gl_drawable (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_WIN32 (glcontext)->gldrawable;
}

static GdkGLConfig *
_gdk_win32_gl_context_get_gl_config (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_WIN32 (glcontext)->glconfig;
}

static GdkGLContext *
_gdk_win32_gl_context_get_share_list (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_WIN32 (glcontext)->share_list;
}

static gboolean
_gdk_win32_gl_context_is_direct (GdkGLContext *glcontext)
{
  return FALSE;
}

static int
_gdk_win32_gl_context_get_render_type (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), 0);

  return GDK_GL_CONTEXT_IMPL_WIN32 (glcontext)->render_type;
}

GdkGLContext *
_gdk_win32_gl_context_get_current (void)
{
  static GdkGLContext *current = NULL;
  HGLRC hglrc;

  GDK_GL_NOTE_FUNC ();

  hglrc = wglGetCurrentContext ();

  if (hglrc == NULL)
    return NULL;

  if (current && GDK_GL_CONTEXT_HGLRC (current) == hglrc)
    return current;

  current = gdk_gl_context_lookup (hglrc);

  return current;
}

HGLRC
gdk_win32_gl_context_get_hglrc (GdkGLContext *glcontext)
{
  g_return_val_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext), NULL);

  return GDK_GL_CONTEXT_IMPL_WIN32 (glcontext)->hglrc;
}

/*
 * GdkGLContext hash table.
 */

static GHashTable *gl_context_ht = NULL;

static void
gdk_gl_context_insert (GdkGLContext *glcontext)
{
  GdkGLContextImplWin32 *impl;

  GDK_GL_NOTE_FUNC_PRIVATE ();

  g_return_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext));

  if (gl_context_ht == NULL)
    {
      GDK_GL_NOTE (MISC, g_message (" -- Create GL context hash table."));

      /* We do not know the storage type of HGLRC. We assume that it is
         a pointer as NULL values are specified for this type. */
      gl_context_ht = g_hash_table_new (g_direct_hash,
                                        g_direct_equal);
    }

  impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  g_hash_table_insert (gl_context_ht, impl->hglrc, glcontext);
}

static void
gdk_gl_context_remove (GdkGLContext *glcontext)
{
  GdkGLContextImplWin32 *impl;

  GDK_GL_NOTE_FUNC_PRIVATE ();

  g_return_if_fail (GDK_IS_GL_CONTEXT_IMPL_WIN32 (glcontext));

  if (gl_context_ht == NULL)
    return;

  impl = GDK_GL_CONTEXT_IMPL_WIN32 (glcontext);

  g_hash_table_remove (gl_context_ht, impl->hglrc);

  if (g_hash_table_size (gl_context_ht) == 0)
    {
      GDK_GL_NOTE (MISC, g_message (" -- Destroy GL context hash table."));
      g_hash_table_destroy (gl_context_ht);
      gl_context_ht = NULL;
    }
}

static GdkGLContext *
gdk_gl_context_lookup (HGLRC hglrc)
{
  GDK_GL_NOTE_FUNC_PRIVATE ();

  if (gl_context_ht == NULL)
    return NULL;

  return g_hash_table_lookup (gl_context_ht, hglrc);
}
