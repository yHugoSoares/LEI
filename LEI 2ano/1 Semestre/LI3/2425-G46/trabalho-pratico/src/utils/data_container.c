
#include <glib.h>

typedef struct data_container {
    int i;
    double d;
    void *data;
    void **data_array;
    GHashTable *hashtable;
} *DataContainer;

DataContainer init_data_container(int i, double d, void *data, void **data_array, GHashTable *hashtable) {
    DataContainer data_container = g_new(struct data_container, 1);
    data_container->i = i;
    data_container->d = d;
    data_container->data = data;
    data_container->data_array = data_array;
    data_container->hashtable = hashtable;
    return data_container;
}

void set_i(DataContainer data_container, int i) {
    data_container->i = i;
}

void set_d(DataContainer data_container, double d) {
    data_container->d = d;
}

void set_data(DataContainer data_container, void *data) {
    data_container->data = data;
}

void set_data_array(DataContainer data_container, void **data_array) {
    data_container->data_array = data_array;
}

void set_hashtable(DataContainer data_container, GHashTable *hashtable) {
    data_container->hashtable = hashtable;
}

int get_i(DataContainer data_container) {
    return data_container->i;
}

double get_d(DataContainer data_container) {
    return data_container->d;
}

void *get_data(DataContainer data_container) {
    return data_container->data;
}

void **get_data_array(DataContainer data_container) {
    return data_container->data_array;
}

GHashTable *get_hashtable(DataContainer data_container) {
    return data_container->hashtable;
}

void destroy_data_container(DataContainer data_container) {
    g_free(data_container);
}