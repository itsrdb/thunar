/* $Id$ */
/*-
 * Copyright (c) 2006 Benedikt Meurer <benny@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __THUNAR_PRIVATE_H__
#define __THUNAR_PRIVATE_H__

#include <glib-object.h>

G_BEGIN_DECLS;

/* support macros for debugging */
#ifndef NDEBUG
#define _thunar_assert(expr)                  g_assert (expr)
#define _thunar_assert_not_reached()          g_assert_not_reached ()
#define _thunar_return_if_fail(expr)          g_return_if_fail (expr)
#define _thunar_return_val_if_fail(expr, val) g_return_val_if_fail (expr, (val))
#else
#define _thunar_assert(expr)                  G_STMT_START{ (void)0; }G_STMT_END
#define _thunar_assert_not_reached()          G_STMT_START{ (void)0; }G_STMT_END
#define _thunar_return_if_fail(expr)          G_STMT_START{ (void)0; }G_STMT_END
#define _thunar_return_val_if_fail(expr, val) G_STMT_START{ (void)0; }G_STMT_END
#endif

/* support macros for the slice allocator */
#if GLIB_CHECK_VERSION(2,10,0)
#define _thunar_slice_alloc(block_size)             (g_slice_alloc ((block_size)))
#define _thunar_slice_alloc0(block_size)            (g_slice_alloc0 ((block_size)))
#define _thunar_slice_free1(block_size, mem_block)  G_STMT_START{ g_slice_free1 ((block_size), (mem_block)); }G_STMT_END
#define _thunar_slice_new(type)                     (g_slice_new (type))
#define _thunar_slice_new0(type)                    (g_slice_new0 (type))
#define _thunar_slice_free(type, ptr)               G_STMT_START{ g_slice_free (type, (ptr)); }G_STMT_END
#else
#define _thunar_slice_alloc(block_size)             (g_malloc ((block_size)))
#define _thunar_slice_alloc0(block_size)            (g_malloc0 ((block_size)))
#define _thunar_slice_free1(block_size, mem_block)  G_STMT_START{ g_free ((mem_block)); }G_STMT_END
#define _thunar_slice_new(type)                     (g_new (type, 1))
#define _thunar_slice_new0(type)                    (g_new0 (type, 1))
#define _thunar_slice_free(type, ptr)               G_STMT_START{ g_free ((ptr)); }G_STMT_END
#endif

/* avoid trivial g_value_get_*() function calls */
#ifdef NDEBUG
#define g_value_get_boolean(v)  (((const GValue *) (v))->data[0].v_int)
#define g_value_get_char(v)     (((const GValue *) (v))->data[0].v_int)
#define g_value_get_uchar(v)    (((const GValue *) (v))->data[0].v_uint)
#define g_value_get_int(v)      (((const GValue *) (v))->data[0].v_int)
#define g_value_get_uint(v)     (((const GValue *) (v))->data[0].v_uint)
#define g_value_get_long(v)     (((const GValue *) (v))->data[0].v_long)
#define g_value_get_ulong(v)    (((const GValue *) (v))->data[0].v_ulong)
#define g_value_get_int64(v)    (((const GValue *) (v))->data[0].v_int64)
#define g_value_get_uint64(v)   (((const GValue *) (v))->data[0].v_uint64)
#define g_value_get_enum(v)     (((const GValue *) (v))->data[0].v_long)
#define g_value_get_flags(v)    (((const GValue *) (v))->data[0].v_ulong)
#define g_value_get_float(v)    (((const GValue *) (v))->data[0].v_float)
#define g_value_get_double(v)   (((const GValue *) (v))->data[0].v_double)
#define g_value_get_string(v)   (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_param(v)    (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_boxed(v)    (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_pointer(v)  (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_object(v)   (((const GValue *) (v))->data[0].v_pointer)
#endif

/* support macros for the GtkTreeModel implementations */
#ifndef NDEBUG
#define GTK_TREE_ITER_INIT(iter, iter_stamp, iter_user_data)  \
G_STMT_START{                                                 \
  (iter).stamp = iter_stamp;                                  \
  (iter).user_data = iter_user_data;                          \
}G_STMT_END
#else
#define GTK_TREE_ITER_INIT(iter, iter_stamp, iter_user_data)  \
G_STMT_START{                                                 \
  (iter).user_data = iter_user_data;                          \
}G_STMT_END
#endif

#define XDG_USER_DIRS_PACKAGE "xdg-user-dirs"
#define LOCALE_FILE_NAME      "user-dirs.locale"

typedef GUserDirectory ThunarUserDirectory;
#define THUNAR_USER_DIRECTORY_DESKTOP      G_USER_DIRECTORY_DESKTOP
#define THUNAR_USER_DIRECTORY_DOCUMENTS    G_USER_DIRECTORY_DOCUMENTS
#define THUNAR_USER_DIRECTORY_DOWNLOAD     G_USER_DIRECTORY_DOWNLOAD
#define THUNAR_USER_DIRECTORY_MUSIC        G_USER_DIRECTORY_MUSIC
#define THUNAR_USER_DIRECTORY_PICTURES     G_USER_DIRECTORY_PICTURES
#define THUNAR_USER_DIRECTORY_PUBLIC_SHARE G_USER_DIRECTORY_PUBLIC_SHARE
#define THUNAR_USER_DIRECTORY_TEMPLATES    G_USER_DIRECTORY_TEMPLATES
#define THUNAR_USER_DIRECTORY_VIDEOS       G_USER_DIRECTORY_VIDEOS
#define THUNAR_USER_N_DIRECTORIES          (8)

gchar *_thunar_get_xdg_user_dirs_locale (void);
extern const gchar *_thunar_user_directory_names[THUNAR_USER_N_DIRECTORIES+1];

G_END_DECLS;

#endif /* !__THUNAR_PRIVATE_H__ */
