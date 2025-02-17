
#include <stdint.h>
#include <string.h>

#include <glib.h>

uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed) {
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    uint32_t hash = seed;
    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) key;

    for (int i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << 15) | (k >> (32 - 15));
        k *= c2;
        hash ^= k;
        hash = (hash << 13) | (hash >> (32 - 13));
        hash = hash * 5 + 0xe6546b64;
    }

    const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
        case 3: k1 ^= tail[2] << 16; // fall through
        case 2: k1 ^= tail[1] << 8; // fall through
        case 1: k1 ^= tail[0]; break;
    }

    if (len > 0) {
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;
        hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

// GLib GHashTable compatible function
guint murmur_hash(gconstpointer key) {
    return murmur3_32((const char *)key, strlen((const char *)key), 0);
}


uint32_t fnv1a(const char *str, unsigned int length) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;

    for (unsigned int i = 0; i < length; str++, i++) {
        hash ^= (*str);
        hash *= fnv_prime;
    }
    
    return hash;
}

// GLib GHashTable compatible function
guint fnv1a_hash(gconstpointer key) {
    return fnv1a((const char *)key, strlen((const char *)key));
}
