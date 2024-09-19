
/*
 * Copyright (C) Yichun Zhang (agentzh)
 */


#ifndef _NGX_HTTP_LUA_SHDICT_H_INCLUDED_
#define _NGX_HTTP_LUA_SHDICT_H_INCLUDED_


#include "ngx_http_lua_common.h"


typedef struct {
    u_char                       color;
    uint8_t                      value_type;
    u_short                      key_len;
    uint32_t                     value_len;
    uint64_t                     expires;
    ngx_queue_t                  queue;
    uint32_t                     user_flags;
    u_char                       data[1];
} ngx_http_lua_shdict_node_t;


typedef struct {
    ngx_queue_t                  queue;
    uint32_t                     value_len;
    uint8_t                      value_type;
    u_char                       data[1];
} ngx_http_lua_shdict_list_node_t;


typedef struct {
    ngx_rbtree_t                  rbtree;
    ngx_rbtree_node_t             sentinel;
    ngx_queue_t                   lru_queue;
} ngx_http_lua_shdict_shctx_t;


typedef struct {
    ngx_http_lua_shdict_shctx_t  *sh;
    ngx_slab_pool_t              *shpool;
    ngx_str_t                     name;
    ngx_http_lua_main_conf_t     *main_conf;
    ngx_log_t                    *log;
} ngx_http_lua_shdict_ctx_t;


typedef struct {
    ngx_log_t                   *log;
    ngx_http_lua_main_conf_t    *lmcf;
    ngx_cycle_t                 *cycle;
    ngx_shm_zone_t               zone;
} ngx_http_lua_shm_zone_ctx_t;


#if (NGX_DARWIN)
typedef struct {
    void                  *zone;
    u_char                *key;
    size_t                 key_len;
    int                   *value_type;
    u_char               **str_value_buf;
    size_t                *str_value_len;
    double                *num_value;
    int                   *user_flags;
    int                    get_stale;
    int                   *is_stale;
    char                 **errmsg;
} ngx_http_lua_shdict_get_params_t;


typedef struct {
    void                  *zone;
    int                    op;
    u_char                *key;
    size_t                 key_len;
    int                    value_type;
    u_char                *str_value_buf;
    size_t                 str_value_len;
    double                 num_value;
    long                   exptime;
    int                    user_flags;
    char                 **errmsg;
    int                   *forcible;
} ngx_http_lua_shdict_store_params_t;


typedef struct {
    void                  *zone;
    u_char                *key;
    size_t                 key_len;
    double                *num_value;
    char                 **errmsg;
    int                    has_init;
    double                 init;
    long                   init_ttl;
    int                   *forcible;
} ngx_http_lua_shdict_incr_params_t;
#endif


ngx_int_t ngx_http_lua_shdict_init_zone(ngx_shm_zone_t *shm_zone, void *data);
void ngx_http_lua_shdict_rbtree_insert_value(ngx_rbtree_node_t *temp,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel);
void ngx_http_lua_inject_shdict_api(ngx_http_lua_main_conf_t *lmcf,
    lua_State *L);


#endif /* _NGX_HTTP_LUA_SHDICT_H_INCLUDED_ */

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */
