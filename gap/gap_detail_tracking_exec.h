/*  gap_detail_tracking_exec.h
 *    This filter locates the position of one or 2 small areas
 *    of a reference layer within a target layer and logs the coordinates
 *    as XML file. It is intended to track details in a frame sequence.
 *
 *  2011/12/01
 */
/* The GIMP -- an image manipulation program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Revision history
 *  (2011/12/01)  2.7.0       hof: created
 */

#ifndef _GAP_DETAIL_TRACKING_EXEC_H
#define _GAP_DETAIL_TRACKING_EXEC_H


#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include "gap_geo.h"
#include "gap_libgapbase.h"
#include "gap_locate.h"
#include "gap_colordiff.h"
#include "gap_image.h"
#include "gap_layer_copy.h"
#include "gap_arr_dialog.h"

#include "gap-intl.h"



#define GAP_DETAIL_FRAME_HISTORY_INFO     "GAP_DETAIL_FRAME_HISTORY_INFO"
#define GAP_DETAIL_TRACKING_PLUG_IN_NAME  "gap-detail-tracking"

#define VECTORS_NAME_TRACKING_POINTS          "TrackingPoints"
#define VECTORS_NAME_REFERENCE_POINTS         "ReferencePoints"
#define VECTORS_NAME_START_REFERENCE_POINTS   "StartReferencePoints"


typedef struct FilterValues {
   gint32     refShapeRadius;
   gint32     targetMoveRadius;
   gdouble    loacteColodiffThreshold;
   gint32     numPointsSelect;     /* 1,2 or 4 maximum number of recorded controlpoints 
                                    * (the best n points out of all available will be selected for 
                                    * logging and camera shake compensation)
                                    */

   gboolean   coordsRelToFrame1;   /* subtract coords of frame 1 when logging coords */
   gint32     offsX;               /* add this value when logging coords */
   gint32     offsY;
   gdouble    offsRotate;          /* additional rotation angle, to be added in all controlpoints */
   gboolean   enableScaling;       /* on: use rotation and scaling  off: rotate only  */
   gboolean   bgLayerIsReference;
   gboolean   removeMidlayers;     /* on: keep 2 top layers and Bg layer, remove other layers  off: keep all layers  */
   gboolean   addTransformedLayer; /* add layer and apply detail_align transformation when tracking to XCF image */
   char       moveLogFile[1600];
} FilterValues;


#define MAX_PIXEL_COORDS_ARRAY 32

typedef struct PixelCoordsArray
{
  GapPixelCoords  pixCoord[MAX_PIXEL_COORDS_ARRAY];
  int          numberOfCoords;           /* number of used pixelCoord elements in the array */
  gint32       numValidOffsets;          /* number of valid coords involved in average Offset calculation */
  gdouble      avgOffsX;                 /* average horizontal movement vektor (extreme values are not included) */ 
  gdouble      avgOffsY;                 /* average vertical movement vektor (extreme values are not included) */ 
} PixelCoordsArray;


typedef struct FrameHistInfo
{
  gint32       workImageId;
  gint32       frameNr;      /* last handled frameNr */
  PixelCoordsArray startCoordsArray;  /* coords of first processed frame */
  PixelCoordsArray prevCoordsArray;   /* coords of the previous processed frame */

  gint32       lostTraceCount;        /* count frames where the required number of detailspoints could not be located */
  gint32       trackedFramesCount;
  gint32       bestIdx[4];            /* best indexes that were picked while processing the previous frame */
} FrameHistInfo;


/* -----------------------------------
 * gap_track_detail_on_top_layers
 * -----------------------------------
 * This procedure is typically called
 * on the snapshot image created by the Player.
 * This image has one layer at the first snapshot
 * and each further snapshot adds one layer on top of the layerstack.
 *
 * The start is detected when the image has only one layer.
 * optionally the numer of layers can be limted
 * to 2 (or more) layers.
 */
gint32      gap_track_detail_on_top_layers(gint32 imageId, gboolean doProgress, FilterValues *valPtr);
void        gap_detail_tracking_get_values(FilterValues *fiVals);
gboolean    gap_detail_tracking_dialog(FilterValues *fiVals);


/* procedure variants intended for use in the player plug-in */
gint32      gap_track_detail_on_top_layers_lastvals(gint32 imageId);
gboolean    gap_detail_tracking_dialog_cfg_set_vals(gint32 imageId);



#endif
