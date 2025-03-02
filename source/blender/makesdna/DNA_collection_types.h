/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright 2001-2002 NaN Holding BV. All rights reserved. */

/** \file
 * \ingroup DNA
 *
 * \brief Object groups, one object can be in many groups at once.
 */

#pragma once

#include "DNA_ID.h"
#include "DNA_defs.h"
#include "DNA_listBase.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Collection;
struct Object;

typedef struct CollectionObject {
  struct CollectionObject *next, *prev;
  struct Object *ob;
} CollectionObject;

typedef struct CollectionChild {
  struct CollectionChild *next, *prev;
  struct Collection *collection;
} CollectionChild;

enum eCollectionLineArt_Usage {
  COLLECTION_LRT_INCLUDE = 0,
  COLLECTION_LRT_OCCLUSION_ONLY = (1 << 0),
  COLLECTION_LRT_EXCLUDE = (1 << 1),
  COLLECTION_LRT_INTERSECTION_ONLY = (1 << 2),
  COLLECTION_LRT_NO_INTERSECTION = (1 << 3),
  COLLECTION_LRT_FORCE_INTERSECTION = (1 << 4),
};

enum eCollectionLineArt_Flags {
  COLLECTION_LRT_USE_INTERSECTION_MASK = (1 << 0),
  COLLECTION_LRT_USE_INTERSECTION_PRIORITY = (1 << 1),
};

typedef struct Collection_Runtime {
  /** The ID owning this collection, in case it is an embedded one. */
  ID *owner_id;

  /**
   * Cache of objects in this collection and all its children.
   * This is created on demand when e.g. some physics simulation needs it,
   * we don't want to have it for every collections due to memory usage reasons.
   */
  ListBase object_cache;

  /** Need this for line art sub-collection selections. */
  ListBase object_cache_instanced;

  /** List of collections that are a parent of this data-block. */
  ListBase parents;

  uint8_t tag;

  char _pad0[7];
} Collection_Runtime;

typedef struct Collection {
  ID id;

  /** CollectionObject. */
  ListBase gobject;
  /** CollectionChild. */
  ListBase children;

  struct PreviewImage *preview;

  unsigned int layer DNA_DEPRECATED;
  float instance_offset[3];

  uint16_t flag;
  int8_t color_tag;

  char _pad0;

  uint8_t lineart_usage; /* #eCollectionLineArt_Usage */
  uint8_t lineart_flags; /* #eCollectionLineArt_Flags */
  uint8_t lineart_intersection_mask;
  uint8_t lineart_intersection_priority;

  struct SceneCollection *collection DNA_DEPRECATED;
  struct ViewLayer *view_layer DNA_DEPRECATED;

  /* Keep last. */
  Collection_Runtime runtime;
} Collection;

/** #Collection.flag */
enum {
  /** Disable in viewports. */
  COLLECTION_HIDE_VIEWPORT = (1 << 0),
  /** Not selectable in viewport. */
  COLLECTION_HIDE_SELECT = (1 << 1),
  // COLLECTION_DISABLED_DEPRECATED = (1 << 2), /* DIRTY */
  /** Disable in renders. */
  COLLECTION_HIDE_RENDER = (1 << 3),
  /** Runtime: object_cache is populated. */
  COLLECTION_HAS_OBJECT_CACHE = (1 << 4),
  /** Is master collection embedded in the scene. */
  COLLECTION_IS_MASTER = (1 << 5),
  /** for object_cache_instanced. */
  COLLECTION_HAS_OBJECT_CACHE_INSTANCED = (1 << 6),
  /** UPBGE to alternate between old spawn method */
  COLLECTION_IS_SPAWNED = (1 << 14),
};

#define COLLECTION_FLAG_ALL_RUNTIME \
  (COLLECTION_HAS_OBJECT_CACHE | COLLECTION_HAS_OBJECT_CACHE_INSTANCED)

/** #Collection_Runtime.tag */
enum {
  /**
   * That code (#BKE_main_collections_parent_relations_rebuild and the like)
   * is called from very low-level places, like e.g ID remapping...
   * Using a generic tag like #LIB_TAG_DOIT for this is just impossible, we need our very own.
   */
  COLLECTION_TAG_RELATION_REBUILD = (1 << 0),
};

/** #Collection.color_tag */
typedef enum CollectionColorTag {
  COLLECTION_COLOR_NONE = -1,
  COLLECTION_COLOR_01,
  COLLECTION_COLOR_02,
  COLLECTION_COLOR_03,
  COLLECTION_COLOR_04,
  COLLECTION_COLOR_05,
  COLLECTION_COLOR_06,
  COLLECTION_COLOR_07,
  COLLECTION_COLOR_08,

  COLLECTION_COLOR_TOT,
} CollectionColorTag;

#ifdef __cplusplus
}
#endif
