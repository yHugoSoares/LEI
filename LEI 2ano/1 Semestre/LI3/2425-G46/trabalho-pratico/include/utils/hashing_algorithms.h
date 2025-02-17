#ifndef _HASHING_ALGORITHMS_H_
#define _HASHING_ALGORITHMS_H_

#include <glib.h>

// GLib GHashTable compatible function
guint murmur_hash(gconstpointer key);

// GLib GHashTable compatible function
guint fnv1a_hash(gconstpointer key);

#endif
