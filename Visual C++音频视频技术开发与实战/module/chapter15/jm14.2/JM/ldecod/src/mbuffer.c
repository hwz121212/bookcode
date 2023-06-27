
/*!
 ***********************************************************************
 *  \file
 *      mbuffer.c
 *
 *  \brief
 *      Frame buffer functions
 *
 *  \author
 *      Main contributors (see contributors.h for copyright, address and affiliation details)
 *      - Karsten S�hring                 <suehring@hhi.de>
 *      - Alexis Tourapis                 <alexismt@ieee.org>
 *      - Jill Boyce                      <jill.boyce@thomson.net>
 *      - Saurav K Bandyopadhyay          <saurav@ieee.org>
 *      - Zhenyu Wu                       <Zhenyu.Wu@thomson.net
 *      - Purvin Pandit                   <Purvin.Pandit@thomson.net>
 *
 ***********************************************************************
 */

#include <limits.h>

#include "global.h"
#include "mbuffer.h"
#include "memalloc.h"
#include "output.h"
#include "image.h"
#include "header.h"

// picture error concealment
#include "erc_api.h"

static void insert_picture_in_dpb(FrameStore* fs, StorablePicture* p);
static void output_one_frame_from_dpb(void);
static int  is_used_for_reference(FrameStore* fs);
static void get_smallest_poc(int *poc,int * pos);
static int  remove_unused_frame_from_dpb(void);
static int  is_short_term_reference(FrameStore* fs);
static int  is_long_term_reference(FrameStore* fs);
void gen_field_ref_ids(StorablePicture *p);

DecodedPictureBuffer dpb;

StorablePicture **listX[6];

StorablePicture *no_reference_picture; //!< dummy storable picture for recovery point

ColocatedParams *Co_located = NULL;
ColocatedParams *Co_located_JV[MAX_PLANE] = { NULL, NULL, NULL };  //!< Co_located to be used during 4:4:4 independent mode decoding

extern StorablePicture *dec_picture;

int listXsize[6];

#define MAX_LIST_SIZE 33

/*!
 ************************************************************************
 * \brief
 *    Print out list of pictures in DPB. Used for debug purposes.
 ************************************************************************
 */
void dump_dpb(void)
{
#if DUMP_DPB
  unsigned i;

  for (i=0; i<dpb.used_size;i++)
  {
    printf("(");
    printf("fn=%d  ", dpb.fs[i]->frame_num);
    if (dpb.fs[i]->is_used & 1)
    {
      if (dpb.fs[i]->top_field)
        printf("T: poc=%d  ", dpb.fs[i]->top_field->poc);
      else
        printf("T: poc=%d  ", dpb.fs[i]->frame->top_poc);
    }
    if (dpb.fs[i]->is_used & 2)
    {
      if (dpb.fs[i]->bottom_field)
        printf("B: poc=%d  ", dpb.fs[i]->bottom_field->poc);
      else
        printf("B: poc=%d  ", dpb.fs[i]->frame->bottom_poc);
    }
    if (dpb.fs[i]->is_used == 3)
      printf("F: poc=%d  ", dpb.fs[i]->frame->poc);
    printf("G: poc=%d)  ", dpb.fs[i]->poc);
    if (dpb.fs[i]->is_reference) printf ("ref (%d) ", dpb.fs[i]->is_reference);
    if (dpb.fs[i]->is_long_term) printf ("lt_ref (%d) ", dpb.fs[i]->is_reference);
    if (dpb.fs[i]->is_output) printf ("out  ");
    if (dpb.fs[i]->is_used == 3)
    {
      if (dpb.fs[i]->frame->non_existing) printf ("ne  ");
    }
    printf ("\n");
  }
#endif
}

/*!
 ************************************************************************
 * \brief
 *    Returns the size of the dpb depending on level and picture size
 *
 *
 ************************************************************************
 */
int getDpbSize(void)
{
  int pic_size = (active_sps->pic_width_in_mbs_minus1 + 1) * (active_sps->pic_height_in_map_units_minus1 + 1) * (active_sps->frame_mbs_only_flag?1:2) * 384;

  int size = 0;

  switch (active_sps->level_idc)
  {
  case 9:
    size = 152064;
    break;
  case 10:
    size = 152064;
    break;
  case 11:
    if (!IS_FREXT_PROFILE(active_sps->profile_idc) && (active_sps->constrained_set3_flag == 1))
      size = 152064;
    else
      size = 345600;
    break;
  case 12:
    size = 912384;
    break;
  case 13:
    size = 912384;
    break;
  case 20:
    size = 912384;
    break;
  case 21:
    size = 1824768;
    break;
  case 22:
    size = 3110400;
    break;
  case 30:
    size = 3110400;
    break;
  case 31:
    size = 6912000;
    break;
  case 32:
    size = 7864320;
    break;
  case 40:
    size = 12582912;
    break;
  case 41:
    size = 12582912;
    break;
  case 42:
    size = 13369344;
    break;
  case 50:
    size = 42393600;
    break;
  case 51:
    size = 70778880;
    break;
  default:
    error ("undefined level", 500);
    break;
  }

  size /= pic_size;
  size = imin( size, 16);

  if (active_sps->vui_parameters_present_flag && active_sps->vui_seq_parameters.bitstream_restriction_flag)
  {
    if ((int)active_sps->vui_seq_parameters.max_dec_frame_buffering > size)
    {
      error ("max_dec_frame_buffering larger than MaxDpbSize", 500);
    }
    size = imax (1, active_sps->vui_seq_parameters.max_dec_frame_buffering);
  }

  return size;
}

/*!
 ************************************************************************
 * \brief
 *    Check then number of frames marked "used for reference" and break
 *    if maximum is exceeded
 *
 ************************************************************************
 */
void check_num_ref(void)
{
  if ((int)(dpb.ltref_frames_in_buffer +  dpb.ref_frames_in_buffer ) > (imax(1,dpb.num_ref_frames)))
  {
    error ("Max. number of reference frames exceeded. Invalid stream.", 500);
  }
}


/*!
 ************************************************************************
 * \brief
 *    Allocate memory for decoded picture buffer and initialize with sane values.
 *
 ************************************************************************
 */
void init_dpb(void)
{
  unsigned i,j;

  if (dpb.init_done)
  {
    free_dpb();
  }

  dpb.size      = getDpbSize();

  dpb.num_ref_frames = active_sps->num_ref_frames;

  if (dpb.size < active_sps->num_ref_frames)
  {
    error ("DPB size at specified level is smaller than the specified number of reference frames. This is not allowed.\n", 1000);
  }

  dpb.used_size = 0;
  dpb.last_picture = NULL;

  dpb.ref_frames_in_buffer = 0;
  dpb.ltref_frames_in_buffer = 0;

  dpb.fs = calloc(dpb.size, sizeof (FrameStore*));
  if (NULL==dpb.fs)
    no_mem_exit("init_dpb: dpb->fs");

  dpb.fs_ref = calloc(dpb.size, sizeof (FrameStore*));
  if (NULL==dpb.fs_ref)
    no_mem_exit("init_dpb: dpb->fs_ref");

  dpb.fs_ltref = calloc(dpb.size, sizeof (FrameStore*));
  if (NULL==dpb.fs_ltref)
    no_mem_exit("init_dpb: dpb->fs_ltref");

  for (i=0; i<dpb.size; i++)
  {
    dpb.fs[i]       = alloc_frame_store();
    dpb.fs_ref[i]   = NULL;
    dpb.fs_ltref[i] = NULL;
  }

  for (i=0; i<6; i++)
  {
    listX[i] = calloc(MAX_LIST_SIZE, sizeof (StorablePicture*)); // +1 for reordering
    if (NULL==listX[i])
      no_mem_exit("init_dpb: listX[i]");
  }

  /* allocate a dummy storable picture */
  no_reference_picture = alloc_storable_picture (FRAME, img->width, img->height, img->width_cr, img->height_cr);
  no_reference_picture->top_field    = no_reference_picture;
  no_reference_picture->bottom_field = no_reference_picture;
  no_reference_picture->frame        = no_reference_picture;


  for (j=0;j<6;j++)
  {
    for (i=0; i<MAX_LIST_SIZE; i++)
    {
      listX[j][i] = NULL;
    }
    listXsize[j]=0;
  }

  dpb.last_output_poc = INT_MIN;

  img->last_has_mmco_5 = 0;

  dpb.init_done = 1;

  // picture error concealment
  if(img->conceal_mode !=0)
      last_out_fs = alloc_frame_store();
}
/*!
 ************************************************************************
 * \brief
 *    Free memory for decoded picture buffer.
 ************************************************************************
 */
void free_dpb(void)
{
  unsigned i;
  if (dpb.fs)
  {
    for (i=0; i<dpb.size; i++)
    {
      free_frame_store(dpb.fs[i]);
    }
    free (dpb.fs);
    dpb.fs=NULL;
  }
  if (dpb.fs_ref)
  {
    free (dpb.fs_ref);
  }
  if (dpb.fs_ltref)
  {
    free (dpb.fs_ltref);
  }
  dpb.last_output_poc = INT_MIN;

  for (i=0; i<6; i++)
    if (listX[i])
    {
      free (listX[i]);
      listX[i] = NULL;
    }

  dpb.init_done = 0;

  // picture error concealment
  if(img->conceal_mode != 0)
      free_frame_store(last_out_fs);

  free_storable_picture(no_reference_picture);
}


/*!
 ************************************************************************
 * \brief
 *    Allocate memory for decoded picture buffer frame stores an initialize with sane values.
 *
 * \return
 *    the allocated FrameStore structure
 ************************************************************************
 */
FrameStore* alloc_frame_store(void)
{
  FrameStore *f;

  f = calloc (1, sizeof(FrameStore));
  if (NULL==f)
    no_mem_exit("alloc_frame_store: f");

  f->is_used      = 0;
  f->is_reference = 0;
  f->is_long_term = 0;
  f->is_orig_reference = 0;

  f->is_output = 0;

  f->frame        = NULL;;
  f->top_field    = NULL;
  f->bottom_field = NULL;

  return f;
}

void alloc_pic_motion(PicMotionParams *motion, int size_y, int size_x)
{
  get_mem3Dint64 (&(motion->ref_pic_id), 6, size_y, size_x);
  get_mem3Dint64 (&(motion->ref_id),     6, size_y, size_x);
  get_mem4Dshort (&(motion->mv),         2, size_y, size_x, 2);
  get_mem3D      ((byte****)(&(motion->ref_idx)),    2, size_y , size_x);

  motion->mb_field = calloc (size_y * size_x, sizeof(byte));
  if (motion->mb_field == NULL)
    no_mem_exit("alloc_storable_picture: motion->mb_field");

  get_mem2D (&(motion->field_frame), size_y, size_x);
}

/*!
 ************************************************************************
 * \brief
 *    Allocate memory for a stored picture.
 *
 * \param structure
 *    picture structure
 * \param size_x
 *    horizontal luma size
 * \param size_y
 *    vertical luma size
 * \param size_x_cr
 *    horizontal chroma size
 * \param size_y_cr
 *    vertical chroma size
 *
 * \return
 *    the allocated StorablePicture structure
 ************************************************************************
 */
StorablePicture* alloc_storable_picture(PictureStructure structure, int size_x, int size_y, int size_x_cr, int size_y_cr)
{
  StorablePicture *s;
  int   nplane;

  //printf ("Allocating (%s) picture (x=%d, y=%d, x_cr=%d, y_cr=%d)\n", (type == FRAME)?"FRAME":(type == TOP_FIELD)?"TOP_FIELD":"BOTTOM_FIELD", size_x, size_y, size_x_cr, size_y_cr);

  s = calloc (1, sizeof(StorablePicture));
  if (NULL==s)
    no_mem_exit("alloc_storable_picture: s");

  if (structure!=FRAME)
  {
    size_y    /= 2;
    size_y_cr /= 2;
  }

  s->PicSizeInMbs = (size_x*size_y)/256;
  s->imgUV = NULL;

  get_mem2Dpel (&(s->imgY), size_y, size_x);
  if (active_sps->chroma_format_idc != YUV400)
    get_mem3Dpel (&(s->imgUV), 2, size_y_cr, size_x_cr);
  
  get_mem2Dshort (&(s->slice_id), size_y / MB_BLOCK_SIZE, size_x / MB_BLOCK_SIZE);

  alloc_pic_motion(&s->motion, size_y / BLOCK_SIZE, size_x / BLOCK_SIZE);

  if( IS_INDEPENDENT(img) )
  {
    for( nplane=0; nplane<MAX_PLANE; nplane++ )
    {
      alloc_pic_motion(&s->JVmotion[nplane], size_y / BLOCK_SIZE, size_x / BLOCK_SIZE);
    }
  }

  s->pic_num=0;
  s->frame_num=0;
  s->long_term_frame_idx=0;
  s->long_term_pic_num=0;
  s->used_for_reference=0;
  s->is_long_term=0;
  s->non_existing=0;
  s->is_output = 0;
  s->max_slice_id = 0;

  s->structure=structure;

  s->size_x = size_x;
  s->size_y = size_y;
  s->size_x_cr = size_x_cr;
  s->size_y_cr = size_y_cr;
  s->size_x_m1 = size_x - 1;
  s->size_y_m1 = size_y - 1;
  s->size_x_cr_m1 = size_x_cr - 1;
  s->size_y_cr_m1 = size_y_cr - 1;

  s->top_field    = no_reference_picture;
  s->bottom_field = no_reference_picture;
  s->frame        = no_reference_picture;

  s->dec_ref_pic_marking_buffer = NULL;

  s->coded_frame                   = 0;
  s->MbaffFrameFlag                = 0;

  s->top_poc = s->bottom_poc = s->poc = 0;
  s->seiHasTone_mapping = 0;

  return s;
}

/*!
 ************************************************************************
 * \brief
 *    Free frame store memory.
 *
 * \param f
 *    FrameStore to be freed
 *
 ************************************************************************
 */
void free_frame_store(FrameStore* f)
{
  if (f)
  {
    if (f->frame)
    {
      free_storable_picture(f->frame);
      f->frame=NULL;
    }
    if (f->top_field)
    {
      free_storable_picture(f->top_field);
      f->top_field=NULL;
    }
    if (f->bottom_field)
    {
      free_storable_picture(f->bottom_field);
      f->bottom_field=NULL;
    }
    free(f);
  }
}

void free_pic_motion(PicMotionParams *motion)
{
  if (motion->ref_pic_id)
  {
    free_mem3Dint64 (motion->ref_pic_id);
    motion->ref_pic_id = NULL;
  }
  if (motion->ref_id)
  {
    free_mem3Dint64 (motion->ref_id);
    motion->ref_id = NULL;
  }

  if (motion->mv)
  {
    free_mem4Dshort (motion->mv);
    motion->mv = NULL;
  }

  if (motion->ref_idx)
  {
    free_mem3D ((byte***)motion->ref_idx);
    motion->ref_idx = NULL;
  }

  if (motion->mb_field)
  {
    free(motion->mb_field);
    motion->mb_field = NULL;
  }

  if (motion->field_frame)
  {
    free_mem2D (motion->field_frame);
    motion->field_frame=NULL;
  }
}


/*!
 ************************************************************************
 * \brief
 *    Free picture memory.
 *
 * \param p
 *    Picture to be freed
 *
 ************************************************************************
 */
void free_storable_picture(StorablePicture* p)
{
  int nplane;
  if (p)
  {
    free_pic_motion(&p->motion);

    if( IS_INDEPENDENT(img) )
    {
      for( nplane=0; nplane<MAX_PLANE; nplane++ )
      {
        free_pic_motion(&p->JVmotion[nplane]);
      }
    }

    if (p->imgY)
    {
      free_mem2Dpel (p->imgY);
      p->imgY=NULL;
    }

    if (p->imgUV)
    {
      free_mem3Dpel (p->imgUV);
      p->imgUV=NULL;
    }

    if (p->slice_id)
    {
      free_mem2Dshort(p->slice_id);
      p->slice_id=NULL;
    }

    if (p->seiHasTone_mapping)
      free(p->tone_mapping_lut);

    free(p);
    p = NULL;
  }
}

/*!
 ************************************************************************
 * \brief
 *    mark FrameStore unused for reference
 *
 ************************************************************************
 */
static void unmark_for_reference(FrameStore* fs)
{

  if (fs->is_used & 1)
  {
    if (fs->top_field)
    {
      fs->top_field->used_for_reference = 0;
    }
  }
  if (fs->is_used & 2)
  {
    if (fs->bottom_field)
    {
      fs->bottom_field->used_for_reference = 0;
    }
  }
  if (fs->is_used == 3)
  {
    if (fs->top_field && fs->bottom_field)
    {
      fs->top_field->used_for_reference = 0;
      fs->bottom_field->used_for_reference = 0;
    }
    fs->frame->used_for_reference = 0;
  }

  fs->is_reference = 0;

  if(fs->frame)
  {
    free_pic_motion(&fs->frame->motion);
  }

  if (fs->top_field)
  {
    free_pic_motion(&fs->top_field->motion);
  }

  if (fs->bottom_field)
  {
    free_pic_motion(&fs->bottom_field->motion);
  }
}


/*!
 ************************************************************************
 * \brief
 *    mark FrameStore unused for reference and reset long term flags
 *
 ************************************************************************
 */
static void unmark_for_long_term_reference(FrameStore* fs)
{

  if (fs->is_used & 1)
  {
    if (fs->top_field)
    {
      fs->top_field->used_for_reference = 0;
      fs->top_field->is_long_term = 0;
    }
  }
  if (fs->is_used & 2)
  {
    if (fs->bottom_field)
    {
      fs->bottom_field->used_for_reference = 0;
      fs->bottom_field->is_long_term = 0;
    }
  }
  if (fs->is_used == 3)
  {
    if (fs->top_field && fs->bottom_field)
    {
      fs->top_field->used_for_reference = 0;
      fs->top_field->is_long_term = 0;
      fs->bottom_field->used_for_reference = 0;
      fs->bottom_field->is_long_term = 0;
    }
    fs->frame->used_for_reference = 0;
    fs->frame->is_long_term = 0;
  }

  fs->is_reference = 0;
  fs->is_long_term = 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two stored pictures by picture number for qsort in descending order
 *
 ************************************************************************
 */
static int compare_pic_by_pic_num_desc( const void *arg1, const void *arg2 )
{
  if ( (*(StorablePicture**)arg1)->pic_num < (*(StorablePicture**)arg2)->pic_num)
    return 1;
  if ( (*(StorablePicture**)arg1)->pic_num > (*(StorablePicture**)arg2)->pic_num)
    return -1;
  else
    return 0;
}

/*!
 ************************************************************************
 * \brief
 *    compares two stored pictures by picture number for qsort in descending order
 *
 ************************************************************************
 */
static int compare_pic_by_lt_pic_num_asc( const void *arg1, const void *arg2 )
{
  if ( (*(StorablePicture**)arg1)->long_term_pic_num < (*(StorablePicture**)arg2)->long_term_pic_num)
    return -1;
  if ( (*(StorablePicture**)arg1)->long_term_pic_num > (*(StorablePicture**)arg2)->long_term_pic_num)
    return 1;
  else
    return 0;
}

/*!
 ************************************************************************
 * \brief
 *    compares two frame stores by pic_num for qsort in descending order
 *
 ************************************************************************
 */
static int compare_fs_by_frame_num_desc( const void *arg1, const void *arg2 )
{
  if ( (*(FrameStore**)arg1)->frame_num_wrap < (*(FrameStore**)arg2)->frame_num_wrap)
    return 1;
  if ( (*(FrameStore**)arg1)->frame_num_wrap > (*(FrameStore**)arg2)->frame_num_wrap)
    return -1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two frame stores by lt_pic_num for qsort in descending order
 *
 ************************************************************************
 */
static int compare_fs_by_lt_pic_idx_asc( const void *arg1, const void *arg2 )
{
  if ( (*(FrameStore**)arg1)->long_term_frame_idx < (*(FrameStore**)arg2)->long_term_frame_idx)
    return -1;
  if ( (*(FrameStore**)arg1)->long_term_frame_idx > (*(FrameStore**)arg2)->long_term_frame_idx)
    return 1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two stored pictures by poc for qsort in ascending order
 *
 ************************************************************************
 */
static int compare_pic_by_poc_asc( const void *arg1, const void *arg2 )
{
  if ( (*(StorablePicture**)arg1)->poc < (*(StorablePicture**)arg2)->poc)
    return -1;
  
  if ( (*(StorablePicture**)arg1)->poc > (*(StorablePicture**)arg2)->poc)
    return 1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two stored pictures by poc for qsort in descending order
 *
 ************************************************************************
 */
static int compare_pic_by_poc_desc( const void *arg1, const void *arg2 )
{
  if ( (*(StorablePicture**)arg1)->poc < (*(StorablePicture**)arg2)->poc)
    return 1;
  if ( (*(StorablePicture**)arg1)->poc > (*(StorablePicture**)arg2)->poc)
    return -1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two frame stores by poc for qsort in ascending order
 *
 ************************************************************************
 */
static int compare_fs_by_poc_asc( const void *arg1, const void *arg2 )
{
  if ( (*(FrameStore**)arg1)->poc < (*(FrameStore**)arg2)->poc)
    return -1;
  
  if ( (*(FrameStore**)arg1)->poc > (*(FrameStore**)arg2)->poc)
    return 1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    compares two frame stores by poc for qsort in descending order
 *
 ************************************************************************
 */
static int compare_fs_by_poc_desc( const void *arg1, const void *arg2 )
{
  if ( (*(FrameStore**)arg1)->poc < (*(FrameStore**)arg2)->poc)
    return 1;
  if ( (*(FrameStore**)arg1)->poc > (*(FrameStore**)arg2)->poc)
    return -1;
  else
    return 0;
}


/*!
 ************************************************************************
 * \brief
 *    returns true, if picture is short term reference picture
 *
 ************************************************************************
 */
int is_short_ref(StorablePicture *s)
{
  return ((s->used_for_reference) && (!(s->is_long_term)));
}


/*!
 ************************************************************************
 * \brief
 *    returns true, if picture is long term reference picture
 *
 ************************************************************************
 */
int is_long_ref(StorablePicture *s)
{
  return ((s->used_for_reference) && (s->is_long_term));
}


/*!
 ************************************************************************
 * \brief
 *    Generates a alternating field list from a given FrameStore list
 *
 ************************************************************************
 */
static void gen_pic_list_from_frame_list(PictureStructure currStrcture, FrameStore **fs_list, int list_idx, StorablePicture **list, int *list_size, int long_term)
{
  int top_idx = 0;
  int bot_idx = 0;

  int (*is_ref)(StorablePicture *s);

  if (long_term)
    is_ref=is_long_ref;
  else
    is_ref=is_short_ref;

  if (currStrcture == TOP_FIELD)
  {
    while ((top_idx<list_idx)||(bot_idx<list_idx))
    {
      for ( ; top_idx<list_idx; top_idx++)
      {
        if(fs_list[top_idx]->is_used & 1)
        {
          if(is_ref(fs_list[top_idx]->top_field))
          {
            // short term ref pic
            list[*list_size] = fs_list[top_idx]->top_field;
            (*list_size)++;
            top_idx++;
            break;
          }
        }
      }
      for ( ; bot_idx<list_idx; bot_idx++)
      {
        if(fs_list[bot_idx]->is_used & 2)
        {
          if(is_ref(fs_list[bot_idx]->bottom_field))
          {
            // short term ref pic
            list[*list_size] = fs_list[bot_idx]->bottom_field;
            (*list_size)++;
            bot_idx++;
            break;
          }
        }
      }
    }
  }
  if (currStrcture == BOTTOM_FIELD)
  {
    while ((top_idx<list_idx)||(bot_idx<list_idx))
    {
      for ( ; bot_idx<list_idx; bot_idx++)
      {
        if(fs_list[bot_idx]->is_used & 2)
        {
          if(is_ref(fs_list[bot_idx]->bottom_field))
          {
            // short term ref pic
            list[*list_size] = fs_list[bot_idx]->bottom_field;
            (*list_size)++;
            bot_idx++;
            break;
          }
        }
      }
      for ( ; top_idx<list_idx; top_idx++)
      {
        if(fs_list[top_idx]->is_used & 1)
        {
          if(is_ref(fs_list[top_idx]->top_field))
          {
            // short term ref pic
            list[*list_size] = fs_list[top_idx]->top_field;
            (*list_size)++;
            top_idx++;
            break;
          }
        }
      }
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    Initialize listX[0] and list 1 depending on current picture type
 *
 ************************************************************************
 */
void init_lists(int currSliceType, PictureStructure currPicStructure)
{
  int add_top = 0, add_bottom = 0;
  unsigned i;
  int j;
  int MaxFrameNum = 1 << (active_sps->log2_max_frame_num_minus4 + 4);
  int diff;

  int list0idx = 0;
  int list0idx_1 = 0;
  int listltidx = 0;

  FrameStore **fs_list0;
  FrameStore **fs_list1;
  FrameStore **fs_listlt;

  StorablePicture *tmp_s;

  if (currPicStructure == FRAME)
  {
    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->is_used==3)
      {
        if ((dpb.fs_ref[i]->frame->used_for_reference)&&(!dpb.fs_ref[i]->frame->is_long_term))
        {
          if( dpb.fs_ref[i]->frame_num > img->frame_num )
          {
            dpb.fs_ref[i]->frame_num_wrap = dpb.fs_ref[i]->frame_num - MaxFrameNum;
          }
          else
          {
            dpb.fs_ref[i]->frame_num_wrap = dpb.fs_ref[i]->frame_num;
          }
          dpb.fs_ref[i]->frame->pic_num = dpb.fs_ref[i]->frame_num_wrap;
        }
      }
    }
    // update long_term_pic_num
    for (i = 0; i < dpb.ltref_frames_in_buffer; i++)
    {
      if (dpb.fs_ltref[i]->is_used==3)
      {
        if (dpb.fs_ltref[i]->frame->is_long_term)
        {
          dpb.fs_ltref[i]->frame->long_term_pic_num = dpb.fs_ltref[i]->frame->long_term_frame_idx;
        }
      }
    }
  }
  else
  {
    if (currPicStructure == TOP_FIELD)
    {
      add_top    = 1;
      add_bottom = 0;
    }
    else
    {
      add_top    = 0;
      add_bottom = 1;
    }

    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->is_reference)
      {
        if( dpb.fs_ref[i]->frame_num > img->frame_num )
        {
          dpb.fs_ref[i]->frame_num_wrap = dpb.fs_ref[i]->frame_num - MaxFrameNum;
        }
        else
        {
          dpb.fs_ref[i]->frame_num_wrap = dpb.fs_ref[i]->frame_num;
        }
        if (dpb.fs_ref[i]->is_reference & 1)
        {
          dpb.fs_ref[i]->top_field->pic_num = (2 * dpb.fs_ref[i]->frame_num_wrap) + add_top;
        }
        if (dpb.fs_ref[i]->is_reference & 2)
        {
          dpb.fs_ref[i]->bottom_field->pic_num = (2 * dpb.fs_ref[i]->frame_num_wrap) + add_bottom;
        }
      }
    }
    // update long_term_pic_num
    for (i=0; i<dpb.ltref_frames_in_buffer; i++)
    {
      if (dpb.fs_ltref[i]->is_long_term & 1)
      {
        dpb.fs_ltref[i]->top_field->long_term_pic_num = 2 * dpb.fs_ltref[i]->top_field->long_term_frame_idx + add_top;
      }
      if (dpb.fs_ltref[i]->is_long_term & 2)
      {
        dpb.fs_ltref[i]->bottom_field->long_term_pic_num = 2 * dpb.fs_ltref[i]->bottom_field->long_term_frame_idx + add_bottom;
      }
    }
  }



  if ((currSliceType == I_SLICE)||(currSliceType == SI_SLICE))
  {
    listXsize[0] = 0;
    listXsize[1] = 0;
    return;
  }

  if ((currSliceType == P_SLICE)||(currSliceType == SP_SLICE))
  {
    // Calculate FrameNumWrap and PicNum
    if (currPicStructure == FRAME)
    {
      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_used==3)
        {
          if ((dpb.fs_ref[i]->frame->used_for_reference)&&(!dpb.fs_ref[i]->frame->is_long_term))
          {
            listX[0][list0idx++] = dpb.fs_ref[i]->frame;
          }
        }
      }
      // order list 0 by PicNum
      qsort((void *)listX[0], list0idx, sizeof(StorablePicture*), compare_pic_by_pic_num_desc);
      listXsize[0] = list0idx;
//      printf("listX[0] (PicNum): "); for (i=0; i<list0idx; i++){printf ("%d  ", listX[0][i]->pic_num);} printf("\n");

      // long term handling
      for (i=0; i<dpb.ltref_frames_in_buffer; i++)
      {
        if (dpb.fs_ltref[i]->is_used==3)
        {
          if (dpb.fs_ltref[i]->frame->is_long_term)
          {
            listX[0][list0idx++]=dpb.fs_ltref[i]->frame;
          }
        }
      }
      qsort((void *)&listX[0][listXsize[0]], list0idx-listXsize[0], sizeof(StorablePicture*), compare_pic_by_lt_pic_num_asc);
      listXsize[0] = list0idx;
    }
    else
    {
      fs_list0 = calloc(dpb.size, sizeof (FrameStore*));
      if (NULL==fs_list0)
         no_mem_exit("init_lists: fs_list0");
      fs_listlt = calloc(dpb.size, sizeof (FrameStore*));
      if (NULL==fs_listlt)
         no_mem_exit("init_lists: fs_listlt");

      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_reference)
        {
          fs_list0[list0idx++] = dpb.fs_ref[i];
        }
      }

      qsort((void *)fs_list0, list0idx, sizeof(FrameStore*), compare_fs_by_frame_num_desc);

//      printf("fs_list0 (FrameNum): "); for (i=0; i<list0idx; i++){printf ("%d  ", fs_list0[i]->frame_num_wrap);} printf("\n");

      listXsize[0] = 0;
      gen_pic_list_from_frame_list(currPicStructure, fs_list0, list0idx, listX[0], &listXsize[0], 0);

//      printf("listX[0] (PicNum): "); for (i=0; i<listXsize[0]; i++){printf ("%d  ", listX[0][i]->pic_num);} printf("\n");

      // long term handling
      for (i=0; i<dpb.ltref_frames_in_buffer; i++)
      {
        fs_listlt[listltidx++]=dpb.fs_ltref[i];
      }

      qsort((void *)fs_listlt, listltidx, sizeof(FrameStore*), compare_fs_by_lt_pic_idx_asc);

      gen_pic_list_from_frame_list(currPicStructure, fs_listlt, listltidx, listX[0], &listXsize[0], 1);

      free(fs_list0);
      free(fs_listlt);
    }
    listXsize[1] = 0;
  }
  else
  {
    // B-Slice
    if (currPicStructure == FRAME)
    {
      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_used==3)
        {
          if ((dpb.fs_ref[i]->frame->used_for_reference)&&(!dpb.fs_ref[i]->frame->is_long_term))
          {
            if (img->framepoc >= dpb.fs_ref[i]->frame->poc) //!KS use >= for error concealment
//            if (img->framepoc > dpb.fs_ref[i]->frame->poc)
            {
              listX[0][list0idx++] = dpb.fs_ref[i]->frame;
            }
          }
        }
      }
      qsort((void *)listX[0], list0idx, sizeof(StorablePicture*), compare_pic_by_poc_desc);
      list0idx_1 = list0idx;
      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_used==3)
        {
          if ((dpb.fs_ref[i]->frame->used_for_reference)&&(!dpb.fs_ref[i]->frame->is_long_term))
          {
            if (img->framepoc < dpb.fs_ref[i]->frame->poc)
            {
              listX[0][list0idx++] = dpb.fs_ref[i]->frame;
            }
          }
        }
      }
      qsort((void *)&listX[0][list0idx_1], list0idx-list0idx_1, sizeof(StorablePicture*), compare_pic_by_poc_asc);

      for (j=0; j<list0idx_1; j++)
      {
        listX[1][list0idx-list0idx_1+j]=listX[0][j];
      }
      for (j=list0idx_1; j<list0idx; j++)
      {
        listX[1][j-list0idx_1]=listX[0][j];
      }

      listXsize[0] = listXsize[1] = list0idx;

//      printf("listX[0] currPoc=%d (Poc): ", img->framepoc); for (i=0; i<listXsize[0]; i++){printf ("%d  ", listX[0][i]->poc);} printf("\n");
//      printf("listX[1] currPoc=%d (Poc): ", img->framepoc); for (i=0; i<listXsize[1]; i++){printf ("%d  ", listX[1][i]->poc);} printf("\n");

      // long term handling
      for (i=0; i<dpb.ltref_frames_in_buffer; i++)
      {
        if (dpb.fs_ltref[i]->is_used==3)
        {
          if (dpb.fs_ltref[i]->frame->is_long_term)
          {
            listX[0][list0idx]  =dpb.fs_ltref[i]->frame;
            listX[1][list0idx++]=dpb.fs_ltref[i]->frame;
          }
        }
      }
      qsort((void *)&listX[0][listXsize[0]], list0idx-listXsize[0], sizeof(StorablePicture*), compare_pic_by_lt_pic_num_asc);
      qsort((void *)&listX[1][listXsize[0]], list0idx-listXsize[0], sizeof(StorablePicture*), compare_pic_by_lt_pic_num_asc);
      listXsize[0] = listXsize[1] = list0idx;
    }
    else
    {
      fs_list0 = calloc(dpb.size, sizeof (FrameStore*));
      if (NULL==fs_list0)
         no_mem_exit("init_lists: fs_list0");
      fs_list1 = calloc(dpb.size, sizeof (FrameStore*));
      if (NULL==fs_list1)
         no_mem_exit("init_lists: fs_list1");
      fs_listlt = calloc(dpb.size, sizeof (FrameStore*));
      if (NULL==fs_listlt)
         no_mem_exit("init_lists: fs_listlt");

      listXsize[0] = 0;
      listXsize[1] = 1;

      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_used)
        {
          if (img->ThisPOC >= dpb.fs_ref[i]->poc)
          {
            fs_list0[list0idx++] = dpb.fs_ref[i];
          }
        }
      }
      qsort((void *)fs_list0, list0idx, sizeof(FrameStore*), compare_fs_by_poc_desc);
      list0idx_1 = list0idx;
      for (i=0; i<dpb.ref_frames_in_buffer; i++)
      {
        if (dpb.fs_ref[i]->is_used)
        {
          if (img->ThisPOC < dpb.fs_ref[i]->poc)
          {
            fs_list0[list0idx++] = dpb.fs_ref[i];
          }
        }
      }
      qsort((void *)&fs_list0[list0idx_1], list0idx-list0idx_1, sizeof(FrameStore*), compare_fs_by_poc_asc);

      for (j=0; j<list0idx_1; j++)
      {
        fs_list1[list0idx-list0idx_1+j]=fs_list0[j];
      }
      for (j=list0idx_1; j<list0idx; j++)
      {
        fs_list1[j-list0idx_1]=fs_list0[j];
      }

//      printf("fs_list0 currPoc=%d (Poc): ", img->ThisPOC); for (i=0; i<list0idx; i++){printf ("%d  ", fs_list0[i]->poc);} printf("\n");
//      printf("fs_list1 currPoc=%d (Poc): ", img->ThisPOC); for (i=0; i<list0idx; i++){printf ("%d  ", fs_list1[i]->poc);} printf("\n");

      listXsize[0] = 0;
      listXsize[1] = 0;
      gen_pic_list_from_frame_list(currPicStructure, fs_list0, list0idx, listX[0], &listXsize[0], 0);
      gen_pic_list_from_frame_list(currPicStructure, fs_list1, list0idx, listX[1], &listXsize[1], 0);

//      printf("listX[0] currPoc=%d (Poc): ", img->framepoc); for (i=0; i<listXsize[0]; i++){printf ("%d  ", listX[0][i]->poc);} printf("\n");
//      printf("listX[1] currPoc=%d (Poc): ", img->framepoc); for (i=0; i<listXsize[1]; i++){printf ("%d  ", listX[1][i]->poc);} printf("\n");

      // long term handling
      for (i=0; i<dpb.ltref_frames_in_buffer; i++)
      {
        fs_listlt[listltidx++]=dpb.fs_ltref[i];
      }

      qsort((void *)fs_listlt, listltidx, sizeof(FrameStore*), compare_fs_by_lt_pic_idx_asc);

      gen_pic_list_from_frame_list(currPicStructure, fs_listlt, listltidx, listX[0], &listXsize[0], 1);
      gen_pic_list_from_frame_list(currPicStructure, fs_listlt, listltidx, listX[1], &listXsize[1], 1);

      free(fs_list0);
      free(fs_list1);
      free(fs_listlt);
    }
  }

  if ((listXsize[0] == listXsize[1]) && (listXsize[0] > 1))
  {
    // check if lists are identical, if yes swap first two elements of listX[1]
    diff=0;
    for (j = 0; j< listXsize[0]; j++)
    {
      if (listX[0][j]!=listX[1][j])
        diff=1;
    }
    if (!diff)
    {
      tmp_s = listX[1][0];
      listX[1][0]=listX[1][1];
      listX[1][1]=tmp_s;
    }
  }
  // set max size
  listXsize[0] = imin (listXsize[0], img->num_ref_idx_l0_active);
  listXsize[1] = imin (listXsize[1], img->num_ref_idx_l1_active);

  // set the unused list entries to NULL
  for (i=listXsize[0]; i< (MAX_LIST_SIZE) ; i++)
  {
      listX[0][i] = no_reference_picture;

  }
  for (i=listXsize[1]; i< (MAX_LIST_SIZE) ; i++)
  {
      listX[1][i] = no_reference_picture;
  }
}

/*!
 ************************************************************************
 * \brief
 *    Initialize listX[2..5] from lists 0 and 1
 *    listX[2]: list0 for current_field==top
 *    listX[3]: list1 for current_field==top
 *    listX[4]: list0 for current_field==bottom
 *    listX[5]: list1 for current_field==bottom
 *
 ************************************************************************
 */
void init_mbaff_lists(void)
{
  unsigned j;
  int i;

  for (i=2;i<6;i++)
  {
    for (j=0; j<MAX_LIST_SIZE; j++)
    {
      listX[i][j] = no_reference_picture;
    }
    listXsize[i]=0;
  }

  for (i=0; i<listXsize[0]; i++)
  {
    listX[2][2*i  ] = listX[0][i]->top_field;
    listX[2][2*i+1] = listX[0][i]->bottom_field;
    listX[4][2*i  ] = listX[0][i]->bottom_field;
    listX[4][2*i+1] = listX[0][i]->top_field;
  }
  listXsize[2]=listXsize[4]=listXsize[0] * 2;

  for (i=0; i<listXsize[1]; i++)
  {
    listX[3][2*i  ] = listX[1][i]->top_field;
    listX[3][2*i+1] = listX[1][i]->bottom_field;
    listX[5][2*i  ] = listX[1][i]->bottom_field;
    listX[5][2*i+1] = listX[1][i]->top_field;
  }
  listXsize[3]=listXsize[5]=listXsize[1] * 2;
}

 /*!
 ************************************************************************
 * \brief
 *    Returns short term pic with given picNum
 *
 ************************************************************************
 */
static StorablePicture*  get_short_term_pic(int picNum)
{
  unsigned i;

  for (i=0; i<dpb.ref_frames_in_buffer; i++)
  {
    if (img->structure==FRAME)
    {
      if (dpb.fs_ref[i]->is_reference == 3)
        if ((!dpb.fs_ref[i]->frame->is_long_term)&&(dpb.fs_ref[i]->frame->pic_num == picNum))
          return dpb.fs_ref[i]->frame;
    }
    else
    {
      if (dpb.fs_ref[i]->is_reference & 1)
        if ((!dpb.fs_ref[i]->top_field->is_long_term)&&(dpb.fs_ref[i]->top_field->pic_num == picNum))
          return dpb.fs_ref[i]->top_field;
      if (dpb.fs_ref[i]->is_reference & 2)
        if ((!dpb.fs_ref[i]->bottom_field->is_long_term)&&(dpb.fs_ref[i]->bottom_field->pic_num == picNum))
          return dpb.fs_ref[i]->bottom_field;
    }
  }

  return no_reference_picture;
}

/*!
 ************************************************************************
 * \brief
 *    Returns short term pic with given LongtermPicNum
 *
 ************************************************************************
 */
static StorablePicture*  get_long_term_pic(int LongtermPicNum)
{
  unsigned i;

  for (i=0; i<dpb.ltref_frames_in_buffer; i++)
  {
    if (img->structure==FRAME)
    {
      if (dpb.fs_ltref[i]->is_reference == 3)
        if ((dpb.fs_ltref[i]->frame->is_long_term)&&(dpb.fs_ltref[i]->frame->long_term_pic_num == LongtermPicNum))
          return dpb.fs_ltref[i]->frame;
    }
    else
    {
      if (dpb.fs_ltref[i]->is_reference & 1)
        if ((dpb.fs_ltref[i]->top_field->is_long_term)&&(dpb.fs_ltref[i]->top_field->long_term_pic_num == LongtermPicNum))
          return dpb.fs_ltref[i]->top_field;
      if (dpb.fs_ltref[i]->is_reference & 2)
        if ((dpb.fs_ltref[i]->bottom_field->is_long_term)&&(dpb.fs_ltref[i]->bottom_field->long_term_pic_num == LongtermPicNum))
          return dpb.fs_ltref[i]->bottom_field;
    }
  }
  return NULL;
}

/*!
 ************************************************************************
 * \brief
 *    Reordering process for short-term reference pictures
 *
 ************************************************************************
 */
static void reorder_short_term(StorablePicture **RefPicListX, int num_ref_idx_lX_active_minus1, int picNumLX, int *refIdxLX)
{
  int cIdx, nIdx;

  StorablePicture *picLX;

  picLX = get_short_term_pic(picNumLX);

  for( cIdx = num_ref_idx_lX_active_minus1+1; cIdx > *refIdxLX; cIdx-- )
    RefPicListX[ cIdx ] = RefPicListX[ cIdx - 1];

  RefPicListX[ (*refIdxLX)++ ] = picLX;

  nIdx = *refIdxLX;

  for( cIdx = *refIdxLX; cIdx <= num_ref_idx_lX_active_minus1+1; cIdx++ )
    if (RefPicListX[ cIdx ])
      if( (RefPicListX[ cIdx ]->is_long_term ) ||  (RefPicListX[ cIdx ]->pic_num != picNumLX ))
        RefPicListX[ nIdx++ ] = RefPicListX[ cIdx ];

}


/*!
 ************************************************************************
 * \brief
 *    Reordering process for short-term reference pictures
 *
 ************************************************************************
 */
static void reorder_long_term(StorablePicture **RefPicListX, int num_ref_idx_lX_active_minus1, int LongTermPicNum, int *refIdxLX)
{
  int cIdx, nIdx;

  StorablePicture *picLX;

  picLX = get_long_term_pic(LongTermPicNum);

  for( cIdx = num_ref_idx_lX_active_minus1+1; cIdx > *refIdxLX; cIdx-- )
    RefPicListX[ cIdx ] = RefPicListX[ cIdx - 1];

  RefPicListX[ (*refIdxLX)++ ] = picLX;

  nIdx = *refIdxLX;

  for( cIdx = *refIdxLX; cIdx <= num_ref_idx_lX_active_minus1+1; cIdx++ )
    if (RefPicListX[ cIdx ])
      if( (!RefPicListX[ cIdx ]->is_long_term ) ||  (RefPicListX[ cIdx ]->long_term_pic_num != LongTermPicNum ))
        RefPicListX[ nIdx++ ] = RefPicListX[ cIdx ];
}


/*!
 ************************************************************************
 * \brief
 *    Reordering process for reference picture lists
 *
 ************************************************************************
 */
void reorder_ref_pic_list(StorablePicture **list, int *list_size, int num_ref_idx_lX_active_minus1, int *reordering_of_pic_nums_idc, int *abs_diff_pic_num_minus1, int *long_term_pic_idx)
{
  int i;

  int maxPicNum, currPicNum, picNumLXNoWrap, picNumLXPred, picNumLX;
  int refIdxLX = 0;

  if (img->structure==FRAME)
  {
    maxPicNum  = img->MaxFrameNum;
    currPicNum = img->frame_num;
  }
  else
  {
    maxPicNum  = 2 * img->MaxFrameNum;
    currPicNum = 2 * img->frame_num + 1;
  }

  picNumLXPred = currPicNum;

  for (i=0; reordering_of_pic_nums_idc[i]!=3; i++)
  {
    if (reordering_of_pic_nums_idc[i]>3)
      error ("Invalid remapping_of_pic_nums_idc command", 500);

    if (reordering_of_pic_nums_idc[i] < 2)
    {
      if (reordering_of_pic_nums_idc[i] == 0)
      {
        if( picNumLXPred - ( abs_diff_pic_num_minus1[i] + 1 ) < 0 )
          picNumLXNoWrap = picNumLXPred - ( abs_diff_pic_num_minus1[i] + 1 ) + maxPicNum;
        else
          picNumLXNoWrap = picNumLXPred - ( abs_diff_pic_num_minus1[i] + 1 );
      }
      else // (remapping_of_pic_nums_idc[i] == 1)
      {
        if( picNumLXPred + ( abs_diff_pic_num_minus1[i] + 1 )  >=  maxPicNum )
          picNumLXNoWrap = picNumLXPred + ( abs_diff_pic_num_minus1[i] + 1 ) - maxPicNum;
        else
          picNumLXNoWrap = picNumLXPred + ( abs_diff_pic_num_minus1[i] + 1 );
      }
      picNumLXPred = picNumLXNoWrap;

      if( picNumLXNoWrap > currPicNum )
        picNumLX = picNumLXNoWrap - maxPicNum;
      else
        picNumLX = picNumLXNoWrap;

      reorder_short_term(list, num_ref_idx_lX_active_minus1, picNumLX, &refIdxLX);
    }
    else //(remapping_of_pic_nums_idc[i] == 2)
    {
      reorder_long_term(list, num_ref_idx_lX_active_minus1, long_term_pic_idx[i], &refIdxLX);
    }

  }
  // that's a definition
  *list_size = num_ref_idx_lX_active_minus1 + 1;
}



/*!
 ************************************************************************
 * \brief
 *    Update the list of frame stores that contain reference frames/fields
 *
 ************************************************************************
 */
void update_ref_list(void)
{
  unsigned i, j;
  for (i=0, j=0; i<dpb.used_size; i++)
  {
    if (is_short_term_reference(dpb.fs[i]))
    {
      dpb.fs_ref[j++]=dpb.fs[i];
    }
  }

  dpb.ref_frames_in_buffer = j;

  while (j<dpb.size)
  {
    dpb.fs_ref[j++]=NULL;
  }
}


/*!
 ************************************************************************
 * \brief
 *    Update the list of frame stores that contain long-term reference
 *    frames/fields
 *
 ************************************************************************
 */
void update_ltref_list(void)
{
  unsigned i, j;
  for (i=0, j=0; i<dpb.used_size; i++)
  {
    if (is_long_term_reference(dpb.fs[i]))
    {
      dpb.fs_ltref[j++]=dpb.fs[i];
    }
  }

  dpb.ltref_frames_in_buffer=j;

  while (j<dpb.size)
  {
    dpb.fs_ltref[j++]=NULL;
  }
}

/*!
 ************************************************************************
 * \brief
 *    Perform Memory management for idr pictures
 *
 ************************************************************************
 */
static void idr_memory_management(StorablePicture* p)
{
  unsigned i;

  assert (p->idr_flag);

  if (p->no_output_of_prior_pics_flag)
  {
    // free all stored pictures
    for (i=0; i<dpb.used_size; i++)
    {
      // reset all reference settings
      free_frame_store(dpb.fs[i]);
      dpb.fs[i] = alloc_frame_store();
    }
    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      dpb.fs_ref[i]=NULL;
    }
    for (i=0; i<dpb.ltref_frames_in_buffer; i++)
    {
      dpb.fs_ltref[i]=NULL;
    }
    dpb.used_size=0;
  }
  else
  {
    flush_dpb();
  }
  dpb.last_picture = NULL;

  update_ref_list();
  update_ltref_list();
  dpb.last_output_poc = INT_MIN;

  if (p->long_term_reference_flag)
  {
    dpb.max_long_term_pic_idx = 0;
    p->is_long_term           = 1;
    p->long_term_frame_idx    = 0;
  }
  else
  {
    dpb.max_long_term_pic_idx = -1;
    p->is_long_term           = 0;
  }
}

/*!
 ************************************************************************
 * \brief
 *    Perform Sliding window decoded reference picture marking process
 *
 ************************************************************************
 */
static void sliding_window_memory_management(StorablePicture* p)
{
  unsigned i;

  assert (!p->idr_flag);
  // if this is a reference pic with sliding sliding window, unmark first ref frame
  if (dpb.ref_frames_in_buffer==dpb.num_ref_frames - dpb.ltref_frames_in_buffer)
  {
    for (i=0; i<dpb.used_size;i++)
    {
      if (dpb.fs[i]->is_reference  && (!(dpb.fs[i]->is_long_term)))
      {
        unmark_for_reference(dpb.fs[i]);
        update_ref_list();
        break;
      }
    }
  }

  p->is_long_term = 0;
}

/*!
 ************************************************************************
 * \brief
 *    Calculate picNumX
 ************************************************************************
 */
static int get_pic_num_x (StorablePicture *p, int difference_of_pic_nums_minus1)
{
  int currPicNum;

  if (p->structure == FRAME)
    currPicNum = p->frame_num;
  else
    currPicNum = 2 * p->frame_num + 1;

  return currPicNum - (difference_of_pic_nums_minus1 + 1);
}


/*!
 ************************************************************************
 * \brief
 *    Adaptive Memory Management: Mark short term picture unused
 ************************************************************************
 */
static void mm_unmark_short_term_for_reference(StorablePicture *p, int difference_of_pic_nums_minus1)
{
  int picNumX;

  unsigned i;

  picNumX = get_pic_num_x(p, difference_of_pic_nums_minus1);

  for (i=0; i<dpb.ref_frames_in_buffer; i++)
  {
    if (p->structure == FRAME)
    {
      if ((dpb.fs_ref[i]->is_reference==3) && (dpb.fs_ref[i]->is_long_term==0))
      {
        if (dpb.fs_ref[i]->frame->pic_num == picNumX)
        {
          unmark_for_reference(dpb.fs_ref[i]);
          return;
        }
      }
    }
    else
    {
      if ((dpb.fs_ref[i]->is_reference & 1) && (!(dpb.fs_ref[i]->is_long_term & 1)))
      {
        if (dpb.fs_ref[i]->top_field->pic_num == picNumX)
        {
          dpb.fs_ref[i]->top_field->used_for_reference = 0;
          dpb.fs_ref[i]->is_reference &= 2;
          if (dpb.fs_ref[i]->is_used == 3)
          {
            dpb.fs_ref[i]->frame->used_for_reference = 0;
          }
          return;
        }
      }
      if ((dpb.fs_ref[i]->is_reference & 2) && (!(dpb.fs_ref[i]->is_long_term & 2)))
      {
        if (dpb.fs_ref[i]->bottom_field->pic_num == picNumX)
        {
          dpb.fs_ref[i]->bottom_field->used_for_reference = 0;
          dpb.fs_ref[i]->is_reference &= 1;
          if (dpb.fs_ref[i]->is_used == 3)
          {
            dpb.fs_ref[i]->frame->used_for_reference = 0;
          }
          return;
        }
      }
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    Adaptive Memory Management: Mark long term picture unused
 ************************************************************************
 */
static void mm_unmark_long_term_for_reference(StorablePicture *p, int long_term_pic_num)
{
  unsigned i;
  for (i=0; i<dpb.ltref_frames_in_buffer; i++)
  {
    if (p->structure == FRAME)
    {
      if ((dpb.fs_ltref[i]->is_reference==3) && (dpb.fs_ltref[i]->is_long_term==3))
      {
        if (dpb.fs_ltref[i]->frame->long_term_pic_num == long_term_pic_num)
        {
          unmark_for_long_term_reference(dpb.fs_ltref[i]);
        }
      }
    }
    else
    {
      if ((dpb.fs_ltref[i]->is_reference & 1) && ((dpb.fs_ltref[i]->is_long_term & 1)))
      {
        if (dpb.fs_ltref[i]->top_field->long_term_pic_num == long_term_pic_num)
        {
          dpb.fs_ltref[i]->top_field->used_for_reference = 0;
          dpb.fs_ltref[i]->top_field->is_long_term = 0;
          dpb.fs_ltref[i]->is_reference &= 2;
          dpb.fs_ltref[i]->is_long_term &= 2;
          if (dpb.fs_ltref[i]->is_used == 3)
          {
            dpb.fs_ltref[i]->frame->used_for_reference = 0;
            dpb.fs_ltref[i]->frame->is_long_term = 0;
          }
          return;
        }
      }
      if ((dpb.fs_ltref[i]->is_reference & 2) && ((dpb.fs_ltref[i]->is_long_term & 2)))
      {
        if (dpb.fs_ltref[i]->bottom_field->long_term_pic_num == long_term_pic_num)
        {
          dpb.fs_ltref[i]->bottom_field->used_for_reference = 0;
          dpb.fs_ltref[i]->bottom_field->is_long_term = 0;
          dpb.fs_ltref[i]->is_reference &= 1;
          dpb.fs_ltref[i]->is_long_term &= 1;
          if (dpb.fs_ltref[i]->is_used == 3)
          {
            dpb.fs_ltref[i]->frame->used_for_reference = 0;
            dpb.fs_ltref[i]->frame->is_long_term = 0;
          }
          return;
        }
      }
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    Mark a long-term reference frame or complementary field pair unused for referemce
 ************************************************************************
 */
static void unmark_long_term_frame_for_reference_by_frame_idx(int long_term_frame_idx)
{
  unsigned i;
  for(i=0; i<dpb.ltref_frames_in_buffer; i++)
  {
    if (dpb.fs_ltref[i]->long_term_frame_idx == long_term_frame_idx)
      unmark_for_long_term_reference(dpb.fs_ltref[i]);
  }
}

/*!
 ************************************************************************
 * \brief
 *    Mark a long-term reference field unused for reference only if it's not
 *    the complementary field of the picture indicated by picNumX
 ************************************************************************
 */
static void unmark_long_term_field_for_reference_by_frame_idx(PictureStructure structure, int long_term_frame_idx, int mark_current, unsigned curr_frame_num, int curr_pic_num)
{
  unsigned i;

  assert(structure!=FRAME);
  if (curr_pic_num<0)
    curr_pic_num+=(2*img->MaxFrameNum);

  for(i=0; i<dpb.ltref_frames_in_buffer; i++)
  {
    if (dpb.fs_ltref[i]->long_term_frame_idx == long_term_frame_idx)
    {
      if (structure == TOP_FIELD)
      {
        if ((dpb.fs_ltref[i]->is_long_term == 3))
        {
          unmark_for_long_term_reference(dpb.fs_ltref[i]);
        }
        else
        {
          if ((dpb.fs_ltref[i]->is_long_term == 1))
          {
            unmark_for_long_term_reference(dpb.fs_ltref[i]);
          }
          else
          {
            if (mark_current)
            {
              if (dpb.last_picture)
              {
                if ( ( dpb.last_picture != dpb.fs_ltref[i] )|| dpb.last_picture->frame_num != curr_frame_num)
                  unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
              else
              {
                unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
            }
            else
            {
              if ((dpb.fs_ltref[i]->frame_num) != (unsigned)(curr_pic_num/2))
              {
                unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
            }
          }
        }
      }
      if (structure == BOTTOM_FIELD)
      {
        if ((dpb.fs_ltref[i]->is_long_term == 3))
        {
          unmark_for_long_term_reference(dpb.fs_ltref[i]);
        }
        else
        {
          if ((dpb.fs_ltref[i]->is_long_term == 2))
          {
            unmark_for_long_term_reference(dpb.fs_ltref[i]);
          }
          else
          {
            if (mark_current)
            {
              if (dpb.last_picture)
              {
                if ( ( dpb.last_picture != dpb.fs_ltref[i] )|| dpb.last_picture->frame_num != curr_frame_num)
                  unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
              else
              {
                unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
            }
            else
            {
              if ((dpb.fs_ltref[i]->frame_num) != (unsigned)(curr_pic_num/2))
              {
                unmark_for_long_term_reference(dpb.fs_ltref[i]);
              }
            }
          }
        }
      }
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    mark a picture as long-term reference
 ************************************************************************
 */
static void mark_pic_long_term(StorablePicture* p, int long_term_frame_idx, int picNumX)
{
  unsigned i;
  int add_top, add_bottom;

  if (p->structure == FRAME)
  {
    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->is_reference == 3)
      {
        if ((!dpb.fs_ref[i]->frame->is_long_term)&&(dpb.fs_ref[i]->frame->pic_num == picNumX))
        {
          dpb.fs_ref[i]->long_term_frame_idx = dpb.fs_ref[i]->frame->long_term_frame_idx
                                             = long_term_frame_idx;
          dpb.fs_ref[i]->frame->long_term_pic_num = long_term_frame_idx;
          dpb.fs_ref[i]->frame->is_long_term = 1;

          if (dpb.fs_ref[i]->top_field && dpb.fs_ref[i]->bottom_field)
          {
            dpb.fs_ref[i]->top_field->long_term_frame_idx = dpb.fs_ref[i]->bottom_field->long_term_frame_idx
                                                          = long_term_frame_idx;
            dpb.fs_ref[i]->top_field->long_term_pic_num = long_term_frame_idx;
            dpb.fs_ref[i]->bottom_field->long_term_pic_num = long_term_frame_idx;

            dpb.fs_ref[i]->top_field->is_long_term = dpb.fs_ref[i]->bottom_field->is_long_term
                                                   = 1;

          }
          dpb.fs_ref[i]->is_long_term = 3;
          return;
        }
      }
    }
    printf ("Warning: reference frame for long term marking not found\n");
  }
  else
  {
    if (p->structure == TOP_FIELD)
    {
      add_top    = 1;
      add_bottom = 0;
    }
    else
    {
      add_top    = 0;
      add_bottom = 1;
    }
    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->is_reference & 1)
      {
        if ((!dpb.fs_ref[i]->top_field->is_long_term)&&(dpb.fs_ref[i]->top_field->pic_num == picNumX))
        {
          if ((dpb.fs_ref[i]->is_long_term) && (dpb.fs_ref[i]->long_term_frame_idx != long_term_frame_idx))
          {
              printf ("Warning: assigning long_term_frame_idx different from other field\n");
          }

          dpb.fs_ref[i]->long_term_frame_idx = dpb.fs_ref[i]->top_field->long_term_frame_idx
                                             = long_term_frame_idx;
          dpb.fs_ref[i]->top_field->long_term_pic_num = 2 * long_term_frame_idx + add_top;
          dpb.fs_ref[i]->top_field->is_long_term = 1;
          dpb.fs_ref[i]->is_long_term |= 1;
          if (dpb.fs_ref[i]->is_long_term == 3)
          {
            dpb.fs_ref[i]->frame->is_long_term = 1;
            dpb.fs_ref[i]->frame->long_term_frame_idx = dpb.fs_ref[i]->frame->long_term_pic_num = long_term_frame_idx;
          }
          return;
        }
      }
      if (dpb.fs_ref[i]->is_reference & 2)
      {
        if ((!dpb.fs_ref[i]->bottom_field->is_long_term)&&(dpb.fs_ref[i]->bottom_field->pic_num == picNumX))
        {
          if ((dpb.fs_ref[i]->is_long_term) && (dpb.fs_ref[i]->long_term_frame_idx != long_term_frame_idx))
          {
              printf ("Warning: assigning long_term_frame_idx different from other field\n");
          }

          dpb.fs_ref[i]->long_term_frame_idx = dpb.fs_ref[i]->bottom_field->long_term_frame_idx
                                             = long_term_frame_idx;
          dpb.fs_ref[i]->bottom_field->long_term_pic_num = 2 * long_term_frame_idx + add_bottom;
          dpb.fs_ref[i]->bottom_field->is_long_term = 1;
          dpb.fs_ref[i]->is_long_term |= 2;
          if (dpb.fs_ref[i]->is_long_term == 3)
          {
            dpb.fs_ref[i]->frame->is_long_term = 1;
            dpb.fs_ref[i]->frame->long_term_frame_idx = dpb.fs_ref[i]->frame->long_term_pic_num = long_term_frame_idx;
          }
          return;
        }
      }
    }
    printf ("Warning: reference field for long term marking not found\n");
  }
}


/*!
 ************************************************************************
 * \brief
 *    Assign a long term frame index to a short term picture
 ************************************************************************
 */
static void mm_assign_long_term_frame_idx(StorablePicture* p, int difference_of_pic_nums_minus1, int long_term_frame_idx)
{
  int picNumX;

  picNumX = get_pic_num_x(p, difference_of_pic_nums_minus1);

  // remove frames/fields with same long_term_frame_idx
  if (p->structure == FRAME)
  {
    unmark_long_term_frame_for_reference_by_frame_idx(long_term_frame_idx);
  }
  else
  {
    unsigned i;
    PictureStructure structure = FRAME;

    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->is_reference & 1)
      {
        if (dpb.fs_ref[i]->top_field->pic_num == picNumX)
        {
          structure = TOP_FIELD;
          break;
        }
      }
      if (dpb.fs_ref[i]->is_reference & 2)
      {
        if (dpb.fs_ref[i]->bottom_field->pic_num == picNumX)
        {
          structure = BOTTOM_FIELD;
          break;
        }
      }
    }
    if (structure==FRAME)
    {
      error ("field for long term marking not found",200);
    }

    unmark_long_term_field_for_reference_by_frame_idx(structure, long_term_frame_idx, 0, 0, picNumX);
  }

  mark_pic_long_term(p, long_term_frame_idx, picNumX);
}

/*!
 ************************************************************************
 * \brief
 *    Set new max long_term_frame_idx
 ************************************************************************
 */
void mm_update_max_long_term_frame_idx(int max_long_term_frame_idx_plus1)
{
  unsigned i;

  dpb.max_long_term_pic_idx = max_long_term_frame_idx_plus1 - 1;

  // check for invalid frames
  for (i=0; i<dpb.ltref_frames_in_buffer; i++)
  {
    if (dpb.fs_ltref[i]->long_term_frame_idx > dpb.max_long_term_pic_idx)
    {
      unmark_for_long_term_reference(dpb.fs_ltref[i]);
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    Mark all long term reference pictures unused for reference
 ************************************************************************
 */
static void mm_unmark_all_long_term_for_reference (void)
{
  mm_update_max_long_term_frame_idx(0);
}

/*!
 ************************************************************************
 * \brief
 *    Mark all short term reference pictures unused for reference
 ************************************************************************
 */
static void mm_unmark_all_short_term_for_reference (void)
{
  unsigned int i;
  for (i=0; i<dpb.ref_frames_in_buffer; i++)
  {
    unmark_for_reference(dpb.fs_ref[i]);
  }
  update_ref_list();
}


/*!
 ************************************************************************
 * \brief
 *    Mark the current picture used for long term reference
 ************************************************************************
 */
static void mm_mark_current_picture_long_term(StorablePicture *p, int long_term_frame_idx)
{
  // remove long term pictures with same long_term_frame_idx
  if (p->structure == FRAME)
  {
    unmark_long_term_frame_for_reference_by_frame_idx(long_term_frame_idx);
  }
  else
  {
    unmark_long_term_field_for_reference_by_frame_idx(p->structure, long_term_frame_idx, 1, p->pic_num, 0);
  }

  p->is_long_term = 1;
  p->long_term_frame_idx = long_term_frame_idx;
}


/*!
 ************************************************************************
 * \brief
 *    Perform Adaptive memory control decoded reference picture marking process
 ************************************************************************
 */
static void adaptive_memory_management(StorablePicture* p)
{
  DecRefPicMarking_t *tmp_drpm;

  img->last_has_mmco_5 = 0;

  assert (!p->idr_flag);
  assert (p->adaptive_ref_pic_buffering_flag);

  while (p->dec_ref_pic_marking_buffer)
  {
    tmp_drpm = p->dec_ref_pic_marking_buffer;
    switch (tmp_drpm->memory_management_control_operation)
    {
      case 0:
        if (tmp_drpm->Next != NULL)
        {
          error ("memory_management_control_operation = 0 not last operation in buffer", 500);
        }
        break;
      case 1:
        mm_unmark_short_term_for_reference(p, tmp_drpm->difference_of_pic_nums_minus1);
        update_ref_list();
        break;
      case 2:
        mm_unmark_long_term_for_reference(p, tmp_drpm->long_term_pic_num);
        update_ltref_list();
        break;
      case 3:
        mm_assign_long_term_frame_idx(p, tmp_drpm->difference_of_pic_nums_minus1, tmp_drpm->long_term_frame_idx);
        update_ref_list();
        update_ltref_list();
        break;
      case 4:
        mm_update_max_long_term_frame_idx (tmp_drpm->max_long_term_frame_idx_plus1);
        update_ltref_list();
        break;
      case 5:
        mm_unmark_all_short_term_for_reference();
        mm_unmark_all_long_term_for_reference();
       img->last_has_mmco_5 = 1;
        break;
      case 6:
        mm_mark_current_picture_long_term(p, tmp_drpm->long_term_frame_idx);
        check_num_ref();
        break;
      default:
        error ("invalid memory_management_control_operation in buffer", 500);
    }
    p->dec_ref_pic_marking_buffer = tmp_drpm->Next;
    free (tmp_drpm);
  }
  if ( img->last_has_mmco_5 )
  {
    p->pic_num = p->frame_num = 0;

    switch (p->structure)
    {
    case TOP_FIELD:
      {
        p->poc = p->top_poc = img->toppoc =0;
        break;
      }
    case BOTTOM_FIELD:
      {
        p->poc = p->bottom_poc = img->bottompoc = 0;
        break;
      }
    case FRAME:
      {
        p->top_poc    -= p->poc;
        p->bottom_poc -= p->poc;

        img->toppoc = p->top_poc;
        img->bottompoc = p->bottom_poc;

        p->poc = imin (p->top_poc, p->bottom_poc);
        img->framepoc = p->poc;
        break;
      }
    }
    img->ThisPOC = p->poc;
    flush_dpb();
  }
}


/*!
 ************************************************************************
 * \brief
 *    Store a picture in DPB. This includes cheking for space in DPB and
 *    flushing frames.
 *    If we received a frame, we need to check for a new store, if we
 *    got a field, check if it's the second field of an already allocated
 *    store.
 *
 * \param p
 *    Picture to be stored
 *
 ************************************************************************
 */
void store_picture_in_dpb(StorablePicture* p)
{
  unsigned i;
  int poc, pos;
  // picture error concealment
  extern int pocs_in_dpb[100];
  // diagnostics
  //printf ("Storing (%s) non-ref pic with frame_num #%d\n", (p->type == FRAME)?"FRAME":(p->type == TOP_FIELD)?"TOP_FIELD":"BOTTOM_FIELD", p->pic_num);
  // if frame, check for new store,
  assert (p!=NULL);

  img->last_has_mmco_5=0;
  img->last_pic_bottom_field = (p->structure == BOTTOM_FIELD);

  if (p->idr_flag)
  {
    idr_memory_management(p);
  // picture error concealment
    memset(pocs_in_dpb, 0, sizeof(int)*100);
  }
  else
  {
    // adaptive memory management
    if (p->used_for_reference && (p->adaptive_ref_pic_buffering_flag))
      adaptive_memory_management(p);
  }

  if ((p->structure==TOP_FIELD)||(p->structure==BOTTOM_FIELD))
  {
    // check for frame store with same pic_number
    if (dpb.last_picture)
    {
      if ((int)dpb.last_picture->frame_num == p->pic_num)
      {
        if (((p->structure==TOP_FIELD)&&(dpb.last_picture->is_used==2))||((p->structure==BOTTOM_FIELD)&&(dpb.last_picture->is_used==1)))
        {
          if ((p->used_for_reference && (dpb.last_picture->is_orig_reference!=0))||
              (!p->used_for_reference && (dpb.last_picture->is_orig_reference==0)))
          {
            insert_picture_in_dpb(dpb.last_picture, p);
            update_ref_list();
            update_ltref_list();
            dump_dpb();
            dpb.last_picture = NULL;
            return;
          }
        }
      }
    }
  }

  // this is a frame or a field which has no stored complementary field

  // sliding window, if necessary
  if ((!p->idr_flag)&&(p->used_for_reference && (!p->adaptive_ref_pic_buffering_flag)))
  {
    sliding_window_memory_management(p);
  }

  // picture error concealment
  if(img->conceal_mode != 0)
    for(i=0;i<dpb.size;i++)
      if(dpb.fs[i]->is_reference)
        dpb.fs[i]->concealment_reference = 1;

  // first try to remove unused frames
  if (dpb.used_size==dpb.size)
  {
    // picture error concealment
    if (img->conceal_mode != 0)
      conceal_non_ref_pics(2);
    remove_unused_frame_from_dpb();

    if(img->conceal_mode != 0)
      sliding_window_poc_management(p);
  }

  // then output frames until one can be removed
  while (dpb.used_size==dpb.size)
  {
    // non-reference frames may be output directly
    if (!p->used_for_reference)
    {
      get_smallest_poc(&poc, &pos);
      if ((-1==pos) || (p->poc < poc))
      {
        direct_output(p, p_out);
        return;
      }
    }
    // flush a frame
    output_one_frame_from_dpb();
  }

  // check for duplicate frame number in short term reference buffer
  if ((p->used_for_reference)&&(!p->is_long_term))
  {
    for (i=0; i<dpb.ref_frames_in_buffer; i++)
    {
      if (dpb.fs_ref[i]->frame_num == p->frame_num)
      {
        error("duplicate frame_num in short-term reference picture buffer", 500);
      }
    }

  }
  // store at end of buffer
//  printf ("store frame/field at pos %d\n",dpb.used_size);
  insert_picture_in_dpb(dpb.fs[dpb.used_size],p);

  // picture error concealment
  if (p->idr_flag)
  {
      img->earlier_missing_poc = 0;
  }

  if (p->structure != FRAME)
  {
    dpb.last_picture = dpb.fs[dpb.used_size];
  }
  else
  {
    dpb.last_picture = NULL;
  }

  dpb.used_size++;

  if(img->conceal_mode != 0)
      pocs_in_dpb[dpb.used_size-1] = p->poc;

  update_ref_list();
  update_ltref_list();

  check_num_ref();

  dump_dpb();
}

/*!
 ************************************************************************
 * \brief
 *    Insert the picture into the DPB. A free DPB position is necessary
 *    for frames, .
 *
 * \param fs
 *    FrameStore into which the picture will be inserted
 * \param p
 *    StorablePicture to be inserted
 *
 ************************************************************************
 */
static void insert_picture_in_dpb(FrameStore* fs, StorablePicture* p)
{
//  printf ("insert (%s) pic with frame_num #%d, poc %d\n", (p->structure == FRAME)?"FRAME":(p->structure == TOP_FIELD)?"TOP_FIELD":"BOTTOM_FIELD", p->pic_num, p->poc);
  assert (p!=NULL);
  assert (fs!=NULL);
  switch (p->structure)
  {
  case FRAME:
    fs->frame = p;
    fs->is_used = 3;
    if (p->used_for_reference)
    {
      fs->is_reference = 3;
      fs->is_orig_reference = 3;
      if (p->is_long_term)
      {
        fs->is_long_term = 3;
        fs->long_term_frame_idx = p->long_term_frame_idx;
      }
    }
    // generate field views
    dpb_split_field(fs);
    break;
  case TOP_FIELD:
    fs->top_field = p;
    fs->is_used |= 1;
    if (p->used_for_reference)
    {
      fs->is_reference |= 1;
      fs->is_orig_reference |= 1;
      if (p->is_long_term)
      {
        fs->is_long_term |= 1;
        fs->long_term_frame_idx = p->long_term_frame_idx;
      }
    }
    if (fs->is_used == 3)
    {
      // generate frame view
      dpb_combine_field(fs);
    } else
    {
      fs->poc = p->poc;
      gen_field_ref_ids(p);
    }
    break;
  case BOTTOM_FIELD:
    fs->bottom_field = p;
    fs->is_used |= 2;
    if (p->used_for_reference)
    {
      fs->is_reference |= 2;
      fs->is_orig_reference |= 2;
      if (p->is_long_term)
      {
        fs->is_long_term |= 2;
        fs->long_term_frame_idx = p->long_term_frame_idx;
      }
    }
    if (fs->is_used == 3)
    {
      // generate frame view
      dpb_combine_field(fs);
    } 
    else
    {
      fs->poc = p->poc;
      gen_field_ref_ids(p);
    }
    break;
  }
  fs->frame_num = p->pic_num;
  fs->recovery_frame = p->recovery_frame;

  fs->is_output = p->is_output;

  if (fs->is_used==3)
  {
    calculate_frame_no(p);
    if (-1!=p_ref && !params->silent)
      find_snr(snr, fs->frame, p_ref);
  }
}

/*!
 ************************************************************************
 * \brief
 *    Check if one of the frames/fields in frame store is used for reference
 ************************************************************************
 */
static int is_used_for_reference(FrameStore* fs)
{
  if (fs->is_reference)
  {
    return 1;
  }

  if (fs->is_used == 3) // frame
  {
    if (fs->frame->used_for_reference)
    {
      return 1;
    }
  }

  if (fs->is_used & 1) // top field
  {
    if (fs->top_field)
    {
      if (fs->top_field->used_for_reference)
      {
        return 1;
      }
    }
  }

  if (fs->is_used & 2) // bottom field
  {
    if (fs->bottom_field)
    {
      if (fs->bottom_field->used_for_reference)
      {
        return 1;
      }
    }
  }
  return 0;
}


/*!
 ************************************************************************
 * \brief
 *    Check if one of the frames/fields in frame store is used for short-term reference
 ************************************************************************
 */
static int is_short_term_reference(FrameStore* fs)
{

  if (fs->is_used==3) // frame
  {
    if ((fs->frame->used_for_reference)&&(!fs->frame->is_long_term))
    {
      return 1;
    }
  }

  if (fs->is_used & 1) // top field
  {
    if (fs->top_field)
    {
      if ((fs->top_field->used_for_reference)&&(!fs->top_field->is_long_term))
      {
        return 1;
      }
    }
  }

  if (fs->is_used & 2) // bottom field
  {
    if (fs->bottom_field)
    {
      if ((fs->bottom_field->used_for_reference)&&(!fs->bottom_field->is_long_term))
      {
        return 1;
      }
    }
  }
  return 0;
}


/*!
 ************************************************************************
 * \brief
 *    Check if one of the frames/fields in frame store is used for short-term reference
 ************************************************************************
 */
static int is_long_term_reference(FrameStore* fs)
{

  if (fs->is_used==3) // frame
  {
    if ((fs->frame->used_for_reference)&&(fs->frame->is_long_term))
    {
      return 1;
    }
  }

  if (fs->is_used & 1) // top field
  {
    if (fs->top_field)
    {
      if ((fs->top_field->used_for_reference)&&(fs->top_field->is_long_term))
      {
        return 1;
      }
    }
  }

  if (fs->is_used & 2) // bottom field
  {
    if (fs->bottom_field)
    {
      if ((fs->bottom_field->used_for_reference)&&(fs->bottom_field->is_long_term))
      {
        return 1;
      }
    }
  }
  return 0;
}


/*!
 ************************************************************************
 * \brief
 *    remove one frame from DPB
 ************************************************************************
 */
static void remove_frame_from_dpb(int pos)
{
  FrameStore* fs = dpb.fs[pos];
  FrameStore* tmp;
  unsigned i;

//  printf ("remove frame with frame_num #%d\n", fs->frame_num);
  switch (fs->is_used)
  {
  case 3:
    free_storable_picture(fs->frame);
    free_storable_picture(fs->top_field);
    free_storable_picture(fs->bottom_field);
    fs->frame=NULL;
    fs->top_field=NULL;
    fs->bottom_field=NULL;
    break;
  case 2:
    free_storable_picture(fs->bottom_field);
    fs->bottom_field=NULL;
    break;
  case 1:
    free_storable_picture(fs->top_field);
    fs->top_field=NULL;
    break;
  case 0:
    break;
  default:
    error("invalid frame store type",500);
  }
  fs->is_used = 0;
  fs->is_long_term = 0;
  fs->is_reference = 0;
  fs->is_orig_reference = 0;

  // move empty framestore to end of buffer
  tmp = dpb.fs[pos];

  for (i=pos; i<dpb.used_size-1;i++)
  {
    dpb.fs[i] = dpb.fs[i+1];
  }
  dpb.fs[dpb.used_size-1] = tmp;
  dpb.used_size--;
}

/*!
 ************************************************************************
 * \brief
 *    find smallest POC in the DPB.
 ************************************************************************
 */
static void get_smallest_poc(int *poc,int * pos)
{
  unsigned i;

  if (dpb.used_size<1)
  {
    error("Cannot determine smallest POC, DPB empty.",150);
  }

  *pos=-1;
  *poc = INT_MAX;
  for (i=0; i<dpb.used_size; i++)
  {
    if ((*poc>dpb.fs[i]->poc)&&(!dpb.fs[i]->is_output))
    {
      *poc = dpb.fs[i]->poc;
      *pos=i;
    }
  }
}

/*!
 ************************************************************************
 * \brief
 *    Remove a picture from DPB which is no longer needed.
 ************************************************************************
 */
static int remove_unused_frame_from_dpb(void)
{
  unsigned i;

  // check for frames that were already output and no longer used for reference
  for (i=0; i<dpb.used_size; i++)
  {
    if (dpb.fs[i]->is_output && (!is_used_for_reference(dpb.fs[i])))
    {
      remove_frame_from_dpb(i);
      return 1;
    }
  }
  return 0;
}

/*!
 ************************************************************************
 * \brief
 *    Output one picture stored in the DPB.
 ************************************************************************
 */
static void output_one_frame_from_dpb(void)
{
  int poc, pos;
  //diagnostics
  if (dpb.used_size<1)
  {
    error("Cannot output frame, DPB empty.",150);
  }

  // find smallest POC
  get_smallest_poc(&poc, &pos);

  if(pos==-1)
  {
    error("no frames for output available", 150);
  }

  // call the output function
//  printf ("output frame with frame_num #%d, poc %d (dpb. dpb.size=%d, dpb.used_size=%d)\n", dpb.fs[pos]->frame_num, dpb.fs[pos]->frame->poc, dpb.size, dpb.used_size);

  // picture error concealment
  if(img->conceal_mode != 0)
  {
    if(dpb.last_output_poc == 0)
    {
      write_lost_ref_after_idr(pos);
    }
    write_lost_non_ref_pic(poc, p_out);
  }

// JVT-P072 ends

  write_stored_frame(dpb.fs[pos], p_out);

  // picture error concealment
  if(img->conceal_mode == 0)
    if (dpb.last_output_poc >= poc)
    {
      error ("output POC must be in ascending order", 150);
    }
  dpb.last_output_poc = poc;
  // free frame store and move empty store to end of buffer
  if (!is_used_for_reference(dpb.fs[pos]))
  {
    remove_frame_from_dpb(pos);
  }
}



/*!
 ************************************************************************
 * \brief
 *    All stored picture are output. Should be called to empty the buffer
 ************************************************************************
 */
void flush_dpb(void)
{
  unsigned i;

  //diagnostics
//  printf("Flush remaining frames from dpb. dpb.size=%d, dpb.used_size=%d\n",dpb.size,dpb.used_size);

//  if(img->conceal_mode == 0)
  if (img->conceal_mode != 0)
    conceal_non_ref_pics(0);

  // mark all frames unused
  for (i=0; i<dpb.used_size; i++)
  {
    unmark_for_reference (dpb.fs[i]);
  }

  while (remove_unused_frame_from_dpb()) ;

  // output frames in POC order
  while (dpb.used_size)
  {
    output_one_frame_from_dpb();
  }

  dpb.last_output_poc = INT_MIN;
}


void gen_field_ref_ids(StorablePicture *p)
{
  int i,j, dummylist0, dummylist1;
   //! Generate Frame parameters from field information.
  for (i=0 ; i<p->size_x/4 ; i++)
  {
    for (j=0 ; j<p->size_y/4 ; j++)
    {
        dummylist0= p->motion.ref_idx[LIST_0][j][i];
        dummylist1= p->motion.ref_idx[LIST_1][j][i];
        //! association with id already known for fields.
        p->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? p->ref_pic_num[p->slice_id[j>>2][i>>2]][LIST_0][dummylist0] : 0;
        p->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? p->ref_pic_num[p->slice_id[j>>2][i>>2]][LIST_1][dummylist1] : 0;
        p->motion.field_frame[j][i]=1;
    }
  }
}

/*!
 ************************************************************************
 * \brief
 *    Extract top field from a frame
 ************************************************************************
 */
void dpb_split_field(FrameStore *fs)
{
  int i, j, ii, jj, jj4;
  int idiv,jdiv;
  int currentmb;
  int dummylist0, dummylist1;
  int twosz16 = 2 * (fs->frame->size_x >> 4);

  fs->poc = fs->frame->poc;

  if (!fs->frame->frame_mbs_only_flag)
  {
    fs->top_field    = alloc_storable_picture(TOP_FIELD,    fs->frame->size_x, fs->frame->size_y, fs->frame->size_x_cr, fs->frame->size_y_cr);
    fs->bottom_field = alloc_storable_picture(BOTTOM_FIELD, fs->frame->size_x, fs->frame->size_y, fs->frame->size_x_cr, fs->frame->size_y_cr);

    for (i = 0; i < (fs->frame->size_y>>1); i++)
    {
      memcpy(fs->top_field->imgY[i], fs->frame->imgY[i*2], fs->frame->size_x*sizeof(imgpel));
    }

    for (i = 0; i< (fs->frame->size_y_cr>>1); i++)
    {
      memcpy(fs->top_field->imgUV[0][i], fs->frame->imgUV[0][i*2], fs->frame->size_x_cr*sizeof(imgpel));
      memcpy(fs->top_field->imgUV[1][i], fs->frame->imgUV[1][i*2], fs->frame->size_x_cr*sizeof(imgpel));
    }

    for (i = 0; i < (fs->frame->size_y>>1); i++)
    {
      memcpy(fs->bottom_field->imgY[i], fs->frame->imgY[i*2 + 1], fs->frame->size_x*sizeof(imgpel));
    }

    for (i = 0; i < (fs->frame->size_y_cr>>1); i++)
    {
      memcpy(fs->bottom_field->imgUV[0][i], fs->frame->imgUV[0][i*2 + 1], fs->frame->size_x_cr*sizeof(imgpel));
      memcpy(fs->bottom_field->imgUV[1][i], fs->frame->imgUV[1][i*2 + 1], fs->frame->size_x_cr*sizeof(imgpel));
    }

    fs->top_field->poc = fs->frame->top_poc;
    fs->bottom_field->poc =  fs->frame->bottom_poc;

    fs->top_field->frame_poc =  fs->frame->frame_poc;

    fs->top_field->bottom_poc =fs->bottom_field->bottom_poc =  fs->frame->bottom_poc;
    fs->top_field->top_poc =fs->bottom_field->top_poc =  fs->frame->top_poc;
    fs->bottom_field->frame_poc =  fs->frame->frame_poc;

    fs->top_field->used_for_reference = fs->bottom_field->used_for_reference
                                      = fs->frame->used_for_reference;
    fs->top_field->is_long_term = fs->bottom_field->is_long_term
                                = fs->frame->is_long_term;
    fs->long_term_frame_idx = fs->top_field->long_term_frame_idx
                            = fs->bottom_field->long_term_frame_idx
                            = fs->frame->long_term_frame_idx;

    fs->top_field->coded_frame = fs->bottom_field->coded_frame = 1;
    fs->top_field->MbaffFrameFlag = fs->bottom_field->MbaffFrameFlag
                                  = fs->frame->MbaffFrameFlag;

    fs->frame->top_field    = fs->top_field;
    fs->frame->bottom_field = fs->bottom_field;

    fs->top_field->bottom_field = fs->bottom_field;
    fs->top_field->frame        = fs->frame;
    fs->bottom_field->top_field = fs->top_field;
    fs->bottom_field->frame     = fs->frame;

    fs->top_field->chroma_format_idc = fs->bottom_field->chroma_format_idc = fs->frame->chroma_format_idc;

    //store reference picture index
    for (j=0; j<=fs->frame->max_slice_id; j++)
    {
      memcpy(&fs->top_field->ref_pic_num   [j][LIST_0][0], &fs->frame->ref_pic_num[j][2 + LIST_0][0], 66 * sizeof(int64));
      memcpy(&fs->top_field->ref_pic_num   [j][LIST_1][0], &fs->frame->ref_pic_num[j][2 + LIST_1][0], 33 * sizeof(int64));            
      memcpy(&fs->bottom_field->ref_pic_num[j][LIST_0][0], &fs->frame->ref_pic_num[j][4 + LIST_0][0], 33 * sizeof(int64));
      memcpy(&fs->bottom_field->ref_pic_num[j][LIST_1][0], &fs->frame->ref_pic_num[j][4 + LIST_1][0], 33 * sizeof(int64));
    }
  }
  else
  {
    fs->top_field=NULL;
    fs->bottom_field=NULL;
    fs->frame->top_field=NULL;
    fs->frame->bottom_field=NULL;
  }

  for (j = 0; (j < fs->frame->size_y >> 2) ; j++)
  {
    jdiv = j >> 2;
    for (i = 0 ; i < (fs->frame->size_x >> 2) ; i++)
    {
      idiv = (i >> 2);
      currentmb = twosz16*(jdiv >> 1)+ (idiv)*2 + (jdiv & 0x01);

      if (fs->frame->MbaffFrameFlag && fs->frame->motion.mb_field[currentmb])
      {
        int list_offset = currentmb%2? 4: 2;
        dummylist0 = fs->frame->motion.ref_idx[LIST_0][j][i];
        dummylist1 = fs->frame->motion.ref_idx[LIST_1][j][i];
        //! association with id already known for fields.
        fs->frame->motion.ref_id[LIST_0 + list_offset][j][i] = (dummylist0>=0)? fs->frame->ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_0 + list_offset][dummylist0] : 0;
        fs->frame->motion.ref_id[LIST_1 + list_offset][j][i] = (dummylist1>=0)? fs->frame->ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_1 + list_offset][dummylist1] : 0;
        //! need to make association with frames
        fs->frame->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->frame->frm_ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_0 + list_offset][dummylist0] : 0;
        fs->frame->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->frame->frm_ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_1 + list_offset][dummylist1] : 0;

      }
      else
      {
        dummylist0 = fs->frame->motion.ref_idx[LIST_0][j][i];
        dummylist1 = fs->frame->motion.ref_idx[LIST_1][j][i];
        fs->frame->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->frame->ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_0][dummylist0] : -1;
        fs->frame->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->frame->ref_pic_num[fs->frame->slice_id[jdiv][idiv]][LIST_1][dummylist1] : -1;
      }
    }
  }

  if (!fs->frame->frame_mbs_only_flag && fs->frame->MbaffFrameFlag)
  {
    for (j=0 ; j< (fs->frame->size_y >> 3); j++)
    {
      jj = (j >> 2)*8 + (j & 0x03);
      jj4 = jj + 4;
      jdiv = (j >> 1);
      for (i=0 ; i < (fs->frame->size_x>>2); i++)
      {
        idiv = (i >> 2);

        currentmb = twosz16*(jdiv >> 1)+ (idiv)*2 + (jdiv & 0x01);
        // Assign field mvs attached to MB-Frame buffer to the proper buffer
        if (fs->frame->motion.mb_field[currentmb])
        {
          fs->bottom_field->motion.field_frame[j][i] = fs->top_field->motion.field_frame[j][i]=1;
          fs->frame->motion.field_frame[2*j][i] = fs->frame->motion.field_frame[2*j+1][i]=1;

          fs->bottom_field->motion.mv[LIST_0][j][i][0] = fs->frame->motion.mv[LIST_0][jj4][i][0];
          fs->bottom_field->motion.mv[LIST_0][j][i][1] = fs->frame->motion.mv[LIST_0][jj4][i][1];
          fs->bottom_field->motion.mv[LIST_1][j][i][0] = fs->frame->motion.mv[LIST_1][jj4][i][0];
          fs->bottom_field->motion.mv[LIST_1][j][i][1] = fs->frame->motion.mv[LIST_1][jj4][i][1];
          fs->bottom_field->motion.ref_idx[LIST_0][j][i] = fs->frame->motion.ref_idx[LIST_0][jj4][i];
          fs->bottom_field->motion.ref_idx[LIST_1][j][i] = fs->frame->motion.ref_idx[LIST_1][jj4][i];
          fs->bottom_field->motion.ref_id[LIST_0][j][i] = fs->frame->motion.ref_id[LIST_0+4][jj4][i];
          fs->bottom_field->motion.ref_id[LIST_1][j][i] = fs->frame->motion.ref_id[LIST_1+4][jj4][i];


          fs->top_field->motion.mv[LIST_0][j][i][0] = fs->frame->motion.mv[LIST_0][jj][i][0];
          fs->top_field->motion.mv[LIST_0][j][i][1] = fs->frame->motion.mv[LIST_0][jj][i][1];
          fs->top_field->motion.mv[LIST_1][j][i][0] = fs->frame->motion.mv[LIST_1][jj][i][0];
          fs->top_field->motion.mv[LIST_1][j][i][1] = fs->frame->motion.mv[LIST_1][jj][i][1];
          fs->top_field->motion.ref_idx[LIST_0][j][i] = fs->frame->motion.ref_idx[LIST_0][jj][i];
          fs->top_field->motion.ref_idx[LIST_1][j][i] = fs->frame->motion.ref_idx[LIST_1][jj][i];
          fs->top_field->motion.ref_id[LIST_0][j][i] = fs->frame->motion.ref_id[LIST_0+2][jj][i];
          fs->top_field->motion.ref_id[LIST_1][j][i] = fs->frame->motion.ref_id[LIST_1+2][jj][i];
        }
      }
    }
  }

  //! Generate field MVs from Frame MVs
  if (!fs->frame->frame_mbs_only_flag)
  {
    for (j=0 ; j < (fs->frame->size_y >> 3) ; j++)
    {
      jj = 2* RSD(j);
      jdiv = (j >> 1);
      for (i=0 ; i < (fs->frame->size_x >> 2) ; i++)
      {
        ii = RSD(i);
        idiv = (i >> 2);

        currentmb = twosz16 * (jdiv >> 1)+ (idiv)*2 + (jdiv & 0x01);

        if (!fs->frame->MbaffFrameFlag  || !fs->frame->motion.mb_field[currentmb])
        {
          fs->frame->motion.field_frame[2*j+1][i] = fs->frame->motion.field_frame[2*j][i]=0;

          fs->top_field->motion.field_frame[j][i] = fs->bottom_field->motion.field_frame[j][i] = 0;

          fs->top_field->motion.mv[LIST_0][j][i][0] = fs->bottom_field->motion.mv[LIST_0][j][i][0] = fs->frame->motion.mv[LIST_0][jj][ii][0];
          fs->top_field->motion.mv[LIST_0][j][i][1] = fs->bottom_field->motion.mv[LIST_0][j][i][1] = fs->frame->motion.mv[LIST_0][jj][ii][1];
          fs->top_field->motion.mv[LIST_1][j][i][0] = fs->bottom_field->motion.mv[LIST_1][j][i][0] = fs->frame->motion.mv[LIST_1][jj][ii][0];
          fs->top_field->motion.mv[LIST_1][j][i][1] = fs->bottom_field->motion.mv[LIST_1][j][i][1] = fs->frame->motion.mv[LIST_1][jj][ii][1];

          // Scaling of references is done here since it will not affect spatial direct (2*0 =0)
          if (fs->frame->motion.ref_idx[LIST_0][jj][ii] == -1)
            fs->top_field->motion.ref_idx[LIST_0][j][i] = fs->bottom_field->motion.ref_idx[LIST_0][j][i] = - 1;
          else
          {
            dummylist0=fs->top_field->motion.ref_idx[LIST_0][j][i] = fs->bottom_field->motion.ref_idx[LIST_0][j][i] = fs->frame->motion.ref_idx[LIST_0][jj][ii] ;
            fs->top_field   ->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->frame->top_ref_pic_num[fs->frame->slice_id[jj>>2][ii>>2]][LIST_0][dummylist0] : 0;
            fs->bottom_field->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->frame->bottom_ref_pic_num[fs->frame->slice_id[jj>>2][ii>>2]][LIST_0][dummylist0] : 0;
          }

          if (fs->frame->motion.ref_idx[LIST_1][jj][ii] == -1)
            fs->top_field->motion.ref_idx[LIST_1][j][i] = fs->bottom_field->motion.ref_idx[LIST_1][j][i] = - 1;
          else
          {
            dummylist1=fs->top_field->motion.ref_idx[LIST_1][j][i] = fs->bottom_field->motion.ref_idx[LIST_1][j][i] = fs->frame->motion.ref_idx[LIST_1][jj][ii];

            fs->top_field   ->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->frame->top_ref_pic_num[fs->frame->slice_id[jj>>2][ii>>2]][LIST_1][dummylist1] : 0;
            fs->bottom_field->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->frame->bottom_ref_pic_num[fs->frame->slice_id[jj>>2][ii>>2]][LIST_1][dummylist1] : 0;
          }
        }
        else
        {
          fs->frame->motion.field_frame[2*j+1][i] = fs->frame->motion.field_frame[2*j][i]= fs->frame->motion.mb_field[currentmb];
        }
      }
    }
  }
  else
  {
    memset( &(fs->frame->motion.field_frame[0][0]), 0, (fs->frame->size_y * fs->frame->size_x >> 4) * sizeof(byte));
  }
}


/*!
 ************************************************************************
 * \brief
 *    Generate a frame from top and bottom fields,
 *    YUV components and display information only
 ************************************************************************
 */
void dpb_combine_field_yuv(FrameStore *fs)
{
  int i;

  fs->frame = alloc_storable_picture(FRAME, fs->top_field->size_x, fs->top_field->size_y*2, fs->top_field->size_x_cr, fs->top_field->size_y_cr*2);

  for (i=0; i<fs->top_field->size_y; i++)
  {
    memcpy(fs->frame->imgY[i*2],     fs->top_field->imgY[i]   , fs->top_field->size_x*sizeof(imgpel));     // top field
    memcpy(fs->frame->imgY[i*2 + 1], fs->bottom_field->imgY[i], fs->bottom_field->size_x*sizeof(imgpel)); // bottom field
  }

  for (i=0; i<fs->top_field->size_y_cr; i++)
  {
    memcpy(fs->frame->imgUV[0][i*2],     fs->top_field->imgUV[0][i],    fs->top_field->size_x_cr*sizeof(imgpel));
    memcpy(fs->frame->imgUV[0][i*2 + 1], fs->bottom_field->imgUV[0][i], fs->bottom_field->size_x_cr*sizeof(imgpel));
    memcpy(fs->frame->imgUV[1][i*2],     fs->top_field->imgUV[1][i],    fs->top_field->size_x_cr*sizeof(imgpel));
    memcpy(fs->frame->imgUV[1][i*2 + 1], fs->bottom_field->imgUV[1][i], fs->bottom_field->size_x_cr*sizeof(imgpel));
  }

  fs->poc=fs->frame->poc =fs->frame->frame_poc = imin (fs->top_field->poc, fs->bottom_field->poc);

  fs->bottom_field->frame_poc=fs->top_field->frame_poc=fs->frame->poc;

  fs->bottom_field->top_poc=fs->frame->top_poc=fs->top_field->poc;
  fs->top_field->bottom_poc=fs->frame->bottom_poc=fs->bottom_field->poc;

  fs->frame->used_for_reference = (fs->top_field->used_for_reference && fs->bottom_field->used_for_reference );
  fs->frame->is_long_term = (fs->top_field->is_long_term && fs->bottom_field->is_long_term );

  if (fs->frame->is_long_term)
    fs->frame->long_term_frame_idx = fs->long_term_frame_idx;

  fs->frame->top_field    = fs->top_field;
  fs->frame->bottom_field = fs->bottom_field;

  fs->frame->coded_frame = 0;

  fs->frame->chroma_format_idc = fs->top_field->chroma_format_idc;
  fs->frame->frame_cropping_flag = fs->top_field->frame_cropping_flag;
  if (fs->frame->frame_cropping_flag)
  {
    fs->frame->frame_cropping_rect_top_offset = fs->top_field->frame_cropping_rect_top_offset;
    fs->frame->frame_cropping_rect_bottom_offset = fs->top_field->frame_cropping_rect_bottom_offset;
    fs->frame->frame_cropping_rect_left_offset = fs->top_field->frame_cropping_rect_left_offset;
    fs->frame->frame_cropping_rect_right_offset = fs->top_field->frame_cropping_rect_right_offset;
  }

  fs->top_field->frame = fs->bottom_field->frame = fs->frame;
}


/*!
 ************************************************************************
 * \brief
 *    Generate a frame from top and bottom fields
 ************************************************************************
 */
void dpb_combine_field(FrameStore *fs)
{
  int i,j, jj, jj4;
  int dummylist0, dummylist1;

  dpb_combine_field_yuv(fs);


  //combine field for frame
  for (j=0; j<=(imax(fs->top_field->max_slice_id, fs->bottom_field->max_slice_id)); j++)
  {
    for (i=0;i<16;i++)
    {
      fs->frame->ref_pic_num[j][LIST_1][i]=  i64min ((fs->top_field->ref_pic_num[j][LIST_1][2*i]/2)*2, (fs->bottom_field->ref_pic_num[j][LIST_1][2*i]/2)*2);
    }

    for (i=0;i<16;i++)
    {
      fs->frame->ref_pic_num[j][LIST_0][i] = i64min((fs->top_field->ref_pic_num[j][LIST_0][2*i]/2)*2, (fs->bottom_field->ref_pic_num[j][LIST_0][2*i]/2)*2);
    }
  }

   //! Use inference flag to remap mvs/references

  //! Generate Frame parameters from field information.
  for (j=0 ; j < (fs->top_field->size_y >> 2) ; j++)
  {
    jj = 8*(j >> 2) + (j & 0x03);
    jj4 = jj + 4;
    for (i=0 ; i< (fs->top_field->size_x >> 2) ; i++)
    {
      fs->frame->motion.field_frame[jj][i]= fs->frame->motion.field_frame[jj4][i]=1;

      fs->frame->motion.mv[LIST_0][jj][i][0] = fs->top_field->motion.mv[LIST_0][j][i][0];
      fs->frame->motion.mv[LIST_0][jj][i][1] = fs->top_field->motion.mv[LIST_0][j][i][1];
      fs->frame->motion.mv[LIST_1][jj][i][0] = fs->top_field->motion.mv[LIST_1][j][i][0];
      fs->frame->motion.mv[LIST_1][jj][i][1] = fs->top_field->motion.mv[LIST_1][j][i][1];

      dummylist0=fs->frame->motion.ref_idx[LIST_0][jj][i]  = fs->top_field->motion.ref_idx[LIST_0][j][i];
      dummylist1=fs->frame->motion.ref_idx[LIST_1][jj][i]  = fs->top_field->motion.ref_idx[LIST_1][j][i];

      //! association with id already known for fields.
      fs->top_field->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->top_field->ref_pic_num[fs->top_field->slice_id[j>>2][i>>2]][LIST_0][dummylist0] : 0;
      fs->top_field->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->top_field->ref_pic_num[fs->top_field->slice_id[j>>2][i>>2]][LIST_1][dummylist1] : 0;

      //! need to make association with frames
      fs->frame->motion.ref_id[LIST_0][jj][i] = (dummylist0>=0)? fs->top_field->frm_ref_pic_num[fs->top_field->slice_id[j>>2][i>>2]][LIST_0][dummylist0] : 0;
      fs->frame->motion.ref_id[LIST_1][jj][i] = (dummylist1>=0)? fs->top_field->frm_ref_pic_num[fs->top_field->slice_id[j>>2][i>>2]][LIST_1][dummylist1] : 0;

      fs->frame->motion.mv[LIST_0][jj4][i][0] = fs->bottom_field->motion.mv[LIST_0][j][i][0];
      fs->frame->motion.mv[LIST_0][jj4][i][1] = fs->bottom_field->motion.mv[LIST_0][j][i][1] ;
      fs->frame->motion.mv[LIST_1][jj4][i][0] = fs->bottom_field->motion.mv[LIST_1][j][i][0];
      fs->frame->motion.mv[LIST_1][jj4][i][1] = fs->bottom_field->motion.mv[LIST_1][j][i][1] ;

      dummylist0=fs->frame->motion.ref_idx[LIST_0][jj4][i]  = fs->bottom_field->motion.ref_idx[LIST_0][j][i];
      dummylist1=fs->frame->motion.ref_idx[LIST_1][jj4][i]  = fs->bottom_field->motion.ref_idx[LIST_1][j][i];

      fs->bottom_field->motion.ref_id[LIST_0][j][i] = (dummylist0>=0)? fs->bottom_field->ref_pic_num[fs->bottom_field->slice_id[j>>2][i>>2]][LIST_0][dummylist0] : 0;
      fs->bottom_field->motion.ref_id[LIST_1][j][i] = (dummylist1>=0)? fs->bottom_field->ref_pic_num[fs->bottom_field->slice_id[j>>2][i>>2]][LIST_1][dummylist1] : 0;

      //! need to make association with frames
      fs->frame->motion.ref_id[LIST_0][jj4][i] = (dummylist0>=0)? fs->bottom_field->frm_ref_pic_num[fs->bottom_field->slice_id[j>>2][i>>2]][LIST_0][dummylist0] : -1;
      fs->frame->motion.ref_id[LIST_1][jj4][i] = (dummylist1>=0)? fs->bottom_field->frm_ref_pic_num[fs->bottom_field->slice_id[j>>2][i>>2]][LIST_1][dummylist1] : -1;

      fs->top_field->motion.field_frame[j][i]=1;
      fs->bottom_field->motion.field_frame[j][i]=1;
    }
  }
}


/*!
 ************************************************************************
 * \brief
 *    Allocate memory for buffering of reference picture reordering commands
 ************************************************************************
 */
void alloc_ref_pic_list_reordering_buffer(Slice *currSlice)
{
  int size = img->num_ref_idx_l0_active+1;

  if (img->type!=I_SLICE && img->type!=SI_SLICE)
  {
    if ((currSlice->reordering_of_pic_nums_idc_l0 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: reordering_of_pic_nums_idc_l0");
    if ((currSlice->abs_diff_pic_num_minus1_l0 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: abs_diff_pic_num_minus1_l0");
    if ((currSlice->long_term_pic_idx_l0 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: long_term_pic_idx_l0");
  }
  else
  {
    currSlice->reordering_of_pic_nums_idc_l0 = NULL;
    currSlice->abs_diff_pic_num_minus1_l0 = NULL;
    currSlice->long_term_pic_idx_l0 = NULL;
  }

  size = img->num_ref_idx_l1_active+1;

  if (img->type==B_SLICE)
  {
    if ((currSlice->reordering_of_pic_nums_idc_l1 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: reordering_of_pic_nums_idc_l1");
    if ((currSlice->abs_diff_pic_num_minus1_l1 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: abs_diff_pic_num_minus1_l1");
    if ((currSlice->long_term_pic_idx_l1 = calloc(size,sizeof(int)))==NULL) no_mem_exit("alloc_ref_pic_list_reordering_buffer: long_term_pic_idx_l1");
  }
  else
  {
    currSlice->reordering_of_pic_nums_idc_l1 = NULL;
    currSlice->abs_diff_pic_num_minus1_l1 = NULL;
    currSlice->long_term_pic_idx_l1 = NULL;
  }
}


/*!
 ************************************************************************
 * \brief
 *    Free memory for buffering of reference picture reordering commands
 ************************************************************************
 */
void free_ref_pic_list_reordering_buffer(Slice *currSlice)
{

  if (currSlice->reordering_of_pic_nums_idc_l0)
    free(currSlice->reordering_of_pic_nums_idc_l0);
  if (currSlice->abs_diff_pic_num_minus1_l0)
    free(currSlice->abs_diff_pic_num_minus1_l0);
  if (currSlice->long_term_pic_idx_l0)
    free(currSlice->long_term_pic_idx_l0);

  currSlice->reordering_of_pic_nums_idc_l0 = NULL;
  currSlice->abs_diff_pic_num_minus1_l0 = NULL;
  currSlice->long_term_pic_idx_l0 = NULL;

  if (currSlice->reordering_of_pic_nums_idc_l1)
    free(currSlice->reordering_of_pic_nums_idc_l1);
  if (currSlice->abs_diff_pic_num_minus1_l1)
    free(currSlice->abs_diff_pic_num_minus1_l1);
  if (currSlice->long_term_pic_idx_l1)
    free(currSlice->long_term_pic_idx_l1);

  currSlice->reordering_of_pic_nums_idc_l1 = NULL;
  currSlice->abs_diff_pic_num_minus1_l1 = NULL;
  currSlice->long_term_pic_idx_l1 = NULL;
}

/*!
 ************************************************************************
 * \brief
 *      Tian Dong
 *          June 13, 2002, Modifed on July 30, 2003
 *
 *      If a gap in frame_num is found, try to fill the gap
 * \param img
 *
 ************************************************************************
 */
void fill_frame_num_gap(ImageParameters *img)
{
  int CurrFrameNum;
  int UnusedShortTermFrameNum;
  StorablePicture *picture = NULL;
  int tmp1 = img->delta_pic_order_cnt[0];
  int tmp2 = img->delta_pic_order_cnt[1];
  img->delta_pic_order_cnt[0] = img->delta_pic_order_cnt[1] = 0;

//  printf("A gap in frame number is found, try to fill it.\n");


  UnusedShortTermFrameNum = (img->pre_frame_num + 1) % img->MaxFrameNum;
  CurrFrameNum = img->frame_num;

  while (CurrFrameNum != UnusedShortTermFrameNum)
  {
    picture = alloc_storable_picture (FRAME, img->width, img->height, img->width_cr, img->height_cr);
    picture->coded_frame = 1;
    picture->pic_num = UnusedShortTermFrameNum;
    picture->frame_num = UnusedShortTermFrameNum;
    picture->non_existing = 1;
    picture->is_output = 1;
    picture->used_for_reference = 1;

    picture->adaptive_ref_pic_buffering_flag = 0;

    img->frame_num = UnusedShortTermFrameNum;
    if (active_sps->pic_order_cnt_type!=0)
    {
      decode_poc(img);
    }
    picture->top_poc=img->toppoc;
    picture->bottom_poc=img->bottompoc;
    picture->frame_poc=img->framepoc;
    picture->poc=img->framepoc;

    store_picture_in_dpb(picture);

    picture=NULL;
    img->pre_frame_num = UnusedShortTermFrameNum;
    UnusedShortTermFrameNum = (UnusedShortTermFrameNum + 1) % img->MaxFrameNum;
  }
  img->delta_pic_order_cnt[0] = tmp1;
  img->delta_pic_order_cnt[1] = tmp2;
  img->frame_num = CurrFrameNum;

}

/*!
 ************************************************************************
 * \brief
 *    Allocate motion parameter memory for colocated structure
 *
 ************************************************************************
 */
void alloc_motion_params(MotionParams *ftype, int size_y, int size_x)
{
  get_mem3Dint64 (&(ftype->ref_pic_id), 2, size_y, size_x);
  get_mem4Dshort (&(ftype->mv)        , 2, size_y, size_x, 2);
  get_mem3D      ((byte****)(&(ftype->ref_idx)) , 2, size_y, size_x);
  get_mem2D      (&(ftype->moving_block) , size_y, size_x);
}

/*!
 ************************************************************************
 * \brief
 *    Allocate co-located memory
 *
 * \param size_x
 *    horizontal luma size
 * \param size_y
 *    vertical luma size
 * \param mb_adaptive_frame_field_flag
 *    flag that indicates macroblock adaptive frame/field coding
 *
 * \return
 *    the allocated StorablePicture structure
 ************************************************************************
 */
ColocatedParams* alloc_colocated(int size_x, int size_y, int mb_adaptive_frame_field_flag)
{
  ColocatedParams *s;

  s = calloc(1, sizeof(ColocatedParams));
  if (NULL == s)
    no_mem_exit("alloc_colocated: s");

  s->size_x = size_x;
  s->size_y = size_y;

  alloc_motion_params(&s->frame, size_y / BLOCK_SIZE, size_x / BLOCK_SIZE);

  if (mb_adaptive_frame_field_flag)
  {
    alloc_motion_params(&s->top   , size_y / (BLOCK_SIZE * 2), size_x / BLOCK_SIZE);
    alloc_motion_params(&s->bottom, size_y / (BLOCK_SIZE * 2), size_x / BLOCK_SIZE);
  }

  s->mb_adaptive_frame_field_flag  = mb_adaptive_frame_field_flag;

  return s;
}

/*!
 ************************************************************************
 * \brief
 *    Free co-located memory.
 *
 * \param p
 *    Picture to be freed
 *
 ************************************************************************
 */
void free_colocated(ColocatedParams* p)
{
  if (p)
  {
    free_mem3D      ((byte***)p->frame.ref_idx);
    free_mem3Dint64 (p->frame.ref_pic_id);
    free_mem4Dshort (p->frame.mv);

    if (p->frame.moving_block)
    {
      free_mem2D (p->frame.moving_block);
      p->frame.moving_block=NULL;
    }

    if (p->mb_adaptive_frame_field_flag)
    {
      free_mem3D      ((byte***)p->top.ref_idx);
      free_mem3Dint64 (p->top.ref_pic_id);
      free_mem4Dshort (p->top.mv);


      if (p->top.moving_block)
      {
        free_mem2D (p->top.moving_block);
        p->top.moving_block=NULL;
      }

      free_mem3D      ((byte***)p->bottom.ref_idx);
      free_mem3Dint64 (p->bottom.ref_pic_id);
      free_mem4Dshort (p->bottom.mv);


      if (p->bottom.moving_block)
      {
        free_mem2D (p->bottom.moving_block);
        p->bottom.moving_block=NULL;
      }

    }

    free(p);

    p=NULL;
  }
}

/*!
 ************************************************************************
 * \brief
 *    Compute co-located motion info
 *
 ************************************************************************
 */

void compute_colocated(ColocatedParams* p, StorablePicture **listX[6])
{
  StorablePicture *fs = listX[LIST_1 ][0];
  StorablePicture *fs_top = fs, *fs_bottom = fs;
  int i,j, ii, jj, jdiv;
  int fs_size_x4 = (fs->size_x >> 2);
  int fs_size_y4 = (fs->size_y >> 2);

  if (img->MbaffFrameFlag)
  {
    fs_top= listX[LIST_1 + 2][0];
    fs_bottom= listX[LIST_1 + 4][0];
  }
  else
  {
    if (img->field_pic_flag)
    {
      if ((img->structure != fs->structure) && (fs->coded_frame))
      {
        if (img->structure==TOP_FIELD)
        {
          fs_top=fs_bottom=fs = listX[LIST_1 ][0]->top_field;
        }
        else
        {
          fs_top=fs_bottom=fs = listX[LIST_1 ][0]->bottom_field;
        }
      }
    }
  }

  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    for (j=0 ; j < (fs->size_y>>2); j++)
    {
      jdiv = (j>>1);
      jj = jdiv + ((j>>3)<<1);
      for (i=0 ; i < fs_size_x4 ; i++)
      {

        if (img->MbaffFrameFlag && fs->motion.field_frame[j][i])
        {
          //! Assign frame buffers for field MBs
          //! Check whether we should use top or bottom field mvs.
          //! Depending on the assigned poc values.

          if (iabs(dec_picture->poc - fs_bottom->poc)> iabs(dec_picture->poc -fs_top->poc) )
          {
            p->frame.mv[LIST_0][j][i][0]      = fs_top->motion.mv[LIST_0][jdiv][i][0];
            p->frame.mv[LIST_0][j][i][1]      = fs_top->motion.mv[LIST_0][jdiv][i][1] ;
            p->frame.mv[LIST_1][j][i][0]      = fs_top->motion.mv[LIST_1][jdiv][i][0];
            p->frame.mv[LIST_1][j][i][1]      = fs_top->motion.mv[LIST_1][jdiv][i][1] ;
            p->frame.ref_idx[LIST_0][j][i]    = fs_top->motion.ref_idx[LIST_0][jdiv][i];
            p->frame.ref_idx[LIST_1][j][i]    = fs_top->motion.ref_idx[LIST_1][jdiv][i];
            p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id[LIST_0][jj][i];
            p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id[LIST_1][jj][i];

            p->is_long_term             = fs_top->is_long_term;
          }
          else
          {
            p->frame.mv[LIST_0][j][i][0]      = fs_bottom->motion.mv[LIST_0][jdiv][i][0];
            p->frame.mv[LIST_0][j][i][1]      = fs_bottom->motion.mv[LIST_0][jdiv][i][1] ;
            p->frame.mv[LIST_1][j][i][0]      = fs_bottom->motion.mv[LIST_1][jdiv][i][0];
            p->frame.mv[LIST_1][j][i][1]      = fs_bottom->motion.mv[LIST_1][jdiv][i][1] ;
            p->frame.ref_idx[LIST_0][j][i]    = fs_bottom->motion.ref_idx[LIST_0][jdiv][i];
            p->frame.ref_idx[LIST_1][j][i]    = fs_bottom->motion.ref_idx[LIST_1][jdiv][i];
            p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id[LIST_0][jj + 4][i];
            p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id[LIST_1][jj + 4][i];

            p->is_long_term             = fs_bottom->is_long_term;
          }
        }
        else
        {
          p->frame.mv[LIST_0][j][i][0]      = fs->motion.mv[LIST_0][j][i][0];
          p->frame.mv[LIST_0][j][i][1]      = fs->motion.mv[LIST_0][j][i][1] ;
          p->frame.mv[LIST_1][j][i][0]      = fs->motion.mv[LIST_1][j][i][0];
          p->frame.mv[LIST_1][j][i][1]      = fs->motion.mv[LIST_1][j][i][1] ;
          p->frame.ref_idx[LIST_0][j][i]    = fs->motion.ref_idx[LIST_0][j][i];
          p->frame.ref_idx[LIST_1][j][i]    = fs->motion.ref_idx[LIST_1][j][i];
          p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id[LIST_0][j][i];
          p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id[LIST_1][j][i];

          p->is_long_term             = fs->is_long_term;
        }
      }
    }
  }


  //! Generate field MVs from Frame MVs
  if (img->structure || img->MbaffFrameFlag)
  {
    for (j=0 ; j<fs->size_y/8 ; j++)
    {
      jj = RSD(j);
      for (i=0 ; i<fs->size_x/4 ; i++)
      {
        ii = RSD(i);
        //! Do nothing if macroblock as field coded in MB-AFF
        if (!img->MbaffFrameFlag )
        {
          p->frame.mv[LIST_0][j][i][0] = fs->motion.mv[LIST_0][jj][ii][0];
          p->frame.mv[LIST_0][j][i][1] = fs->motion.mv[LIST_0][jj][ii][1];
          p->frame.mv[LIST_1][j][i][0] = fs->motion.mv[LIST_1][jj][ii][0];
          p->frame.mv[LIST_1][j][i][1] = fs->motion.mv[LIST_1][jj][ii][1];

          // Scaling of references is done here since it will not affect spatial direct (2*0 =0)

          if (fs->motion.ref_idx[LIST_0][jj][ii] == -1)
          {
            p->frame.ref_idx   [LIST_0][j][i] = -1;
            p->frame.ref_pic_id[LIST_0][j][i] = -1;
          }
          else
          {
            p->frame.ref_idx   [LIST_0][j][i] = fs->motion.ref_idx[LIST_0][jj][ii] ;
            p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id [LIST_0][jj][ii];
          }

          if (fs->motion.ref_idx[LIST_1][jj][ii] == -1)
          {
            p->frame.ref_idx   [LIST_1][j][i] = -1;
            p->frame.ref_pic_id[LIST_1][j][i] = -1;
          }
          else
          {
            p->frame.ref_idx   [LIST_1][j][i] = fs->motion.ref_idx[LIST_1][jj][ii];
            p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id [LIST_1][jj][ii];
          }

          p->is_long_term = fs->is_long_term;

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->frame.moving_block[j][i] =
              !((!p->is_long_term
              && ((p->frame.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->frame.ref_idx[LIST_0][j][i] == -1)
              &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0)));
          }
        }
        else
        {
          p->bottom.mv[LIST_0][j][i][0] = fs_bottom->motion.mv[LIST_0][jj][ii][0];
          p->bottom.mv[LIST_0][j][i][1] = fs_bottom->motion.mv[LIST_0][jj][ii][1];
          p->bottom.mv[LIST_1][j][i][0] = fs_bottom->motion.mv[LIST_1][jj][ii][0];
          p->bottom.mv[LIST_1][j][i][1] = fs_bottom->motion.mv[LIST_1][jj][ii][1];
          p->bottom.ref_idx[LIST_0][j][i] = fs_bottom->motion.ref_idx[LIST_0][jj][ii];
          p->bottom.ref_idx[LIST_1][j][i] = fs_bottom->motion.ref_idx[LIST_1][jj][ii];
          p->bottom.ref_pic_id[LIST_0][j][i] = fs_bottom->motion.ref_id[LIST_0][jj][ii];
          p->bottom.ref_pic_id[LIST_1][j][i] = fs_bottom->motion.ref_id[LIST_1][jj][ii];

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->bottom.moving_block[j][i] =
              !((!fs_bottom->is_long_term
              && ((p->bottom.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->bottom.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->bottom.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->bottom.ref_idx[LIST_0][j][i] == -1)
              &&  (p->bottom.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->bottom.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->bottom.mv[LIST_1][j][i][1])>>1 == 0)));
          }

          p->top.mv[LIST_0][j][i][0] = fs_top->motion.mv[LIST_0][jj][ii][0];
          p->top.mv[LIST_0][j][i][1] = fs_top->motion.mv[LIST_0][jj][ii][1];
          p->top.mv[LIST_1][j][i][0] = fs_top->motion.mv[LIST_1][jj][ii][0];
          p->top.mv[LIST_1][j][i][1] = fs_top->motion.mv[LIST_1][jj][ii][1];
          p->top.ref_idx[LIST_0][j][i] = fs_top->motion.ref_idx[LIST_0][jj][ii];
          p->top.ref_idx[LIST_1][j][i] = fs_top->motion.ref_idx[LIST_1][jj][ii];
          p->top.ref_pic_id[LIST_0][j][i] = fs_top->motion.ref_id[LIST_0][jj][ii];
          p->top.ref_pic_id[LIST_1][j][i] = fs_top->motion.ref_id[LIST_1][jj][ii];

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->top.moving_block[j][i] =
              !((!fs_top->is_long_term
              && ((p->top.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->top.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->top.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->top.ref_idx[LIST_0][j][i] == -1)
              &&  (p->top.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->top.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->top.mv[LIST_1][j][i][1])>>1 == 0)));
          }

          if ((img->direct_spatial_mv_pred_flag == 0 ) && !fs->motion.field_frame[2*j][i])
          {
            p->top.mv[LIST_0][j][i][1] /= 2;
            p->top.mv[LIST_1][j][i][1] /= 2;
            p->bottom.mv[LIST_0][j][i][1] /= 2;
            p->bottom.mv[LIST_1][j][i][1] /= 2;
          }

        }
      }
    }
  }


  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    //! Use inference flag to remap mvs/references
    //! Frame with field co-located

    if (!img->structure)
    {
      for (j=0 ; j < fs_size_y4; j++)
      {
        jdiv = (j >> 1);
        jj   = jdiv + ((j >> 3) << 2);
        for (i = 0 ; i < fs_size_x4; i++)
        {

          if (fs->motion.field_frame[j][i])
          {
            if (iabs(dec_picture->poc - fs->bottom_field->poc) > iabs(dec_picture->poc - fs->top_field->poc))
            {
              p->frame.mv[LIST_0][j][i][0] = fs->top_field->motion.mv[LIST_0][jdiv][i][0];
              p->frame.mv[LIST_0][j][i][1] = fs->top_field->motion.mv[LIST_0][jdiv][i][1] ;
              p->frame.mv[LIST_1][j][i][0] = fs->top_field->motion.mv[LIST_1][jdiv][i][0];
              p->frame.mv[LIST_1][j][i][1] = fs->top_field->motion.mv[LIST_1][jdiv][i][1] ;

              p->frame.ref_idx[LIST_0][j][i]    = fs->top_field->motion.ref_idx[LIST_0][jdiv][i];
              p->frame.ref_idx[LIST_1][j][i]    = fs->top_field->motion.ref_idx[LIST_1][jdiv][i];
              p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id[LIST_0][jj][i];
              p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id[LIST_1][jj][i];
              p->is_long_term             = fs->top_field->is_long_term;
            }
            else
            {
              p->frame.mv[LIST_0][j][i][0] = fs->bottom_field->motion.mv[LIST_0][jdiv][i][0];
              p->frame.mv[LIST_0][j][i][1] = fs->bottom_field->motion.mv[LIST_0][jdiv][i][1] ;
              p->frame.mv[LIST_1][j][i][0] = fs->bottom_field->motion.mv[LIST_1][jdiv][i][0];
              p->frame.mv[LIST_1][j][i][1] = fs->bottom_field->motion.mv[LIST_1][jdiv][i][1] ;

              p->frame.ref_idx[LIST_0][j][i]  = fs->bottom_field->motion.ref_idx[LIST_0][jdiv][i];
              p->frame.ref_idx[LIST_1][j][i]  = fs->bottom_field->motion.ref_idx[LIST_1][jdiv][i];
              p->frame.ref_pic_id[LIST_0][j][i] = fs->motion.ref_id[LIST_0][jj + 4][i];
              p->frame.ref_pic_id[LIST_1][j][i] = fs->motion.ref_id[LIST_1][jj + 4][i];
              p->is_long_term             = fs->bottom_field->is_long_term;
            }
          }
        }
      }
    }
  }


  p->is_long_term = fs->is_long_term;

  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    if (img->direct_spatial_mv_pred_flag == 1)
    {
      for (j=0 ; j < (fs->size_y>>2); j++)
      {
        jj = RSD(j);
        for (i=0 ; i < (fs->size_x>>2); i++)
        {
          ii = RSD(i);

          p->frame.mv[LIST_0][j][i][0]=p->frame.mv[LIST_0][jj][ii][0];
          p->frame.mv[LIST_0][j][i][1]=p->frame.mv[LIST_0][jj][ii][1];
          p->frame.mv[LIST_1][j][i][0]=p->frame.mv[LIST_1][jj][ii][0];
          p->frame.mv[LIST_1][j][i][1]=p->frame.mv[LIST_1][jj][ii][1];

          p->frame.ref_idx[LIST_0][j][i]=p->frame.ref_idx[LIST_0][jj][ii];
          p->frame.ref_idx[LIST_1][j][i]=p->frame.ref_idx[LIST_1][jj][ii];
          p->frame.ref_pic_id[LIST_0][j][i] = p->frame.ref_pic_id[LIST_0][jj][ii];
          p->frame.ref_pic_id[LIST_1][j][i] = p->frame.ref_pic_id[LIST_1][jj][ii];

          p->frame.moving_block[j][i]=
            !((!p->is_long_term
            && ((p->frame.ref_idx[LIST_0][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
            || ((p->frame.ref_idx[LIST_0][j][i] == -1)
            &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0)));
        }
      }
    }
    else
    {
      for (j=0 ; j < (fs->size_y>>2); j++)
      {
        jj = RSD(j);
        for (i=0 ; i < (fs->size_x>>2); i++)
        {
          ii = RSD(i);

          p->frame.mv[LIST_0][j][i][0]=p->frame.mv[LIST_0][jj][ii][0];
          p->frame.mv[LIST_0][j][i][1]=p->frame.mv[LIST_0][jj][ii][1];
          p->frame.mv[LIST_1][j][i][0]=p->frame.mv[LIST_1][jj][ii][0];
          p->frame.mv[LIST_1][j][i][1]=p->frame.mv[LIST_1][jj][ii][1];

          p->frame.ref_idx[LIST_0][j][i]=p->frame.ref_idx[LIST_0][jj][ii];
          p->frame.ref_idx[LIST_1][j][i]=p->frame.ref_idx[LIST_1][jj][ii];
          p->frame.ref_pic_id[LIST_0][j][i] = p->frame.ref_pic_id[LIST_0][jj][ii];
          p->frame.ref_pic_id[LIST_1][j][i] = p->frame.ref_pic_id[LIST_1][jj][ii];
        }
      }
    }
  }
  else
  {
    if (img->direct_spatial_mv_pred_flag == 1)
    {
      for (j=0 ; j < fs_size_y4; j++)
      {
        memcpy(&p->frame.mv[LIST_0][j][0][0], &fs->motion.mv[LIST_0][j][0][0], 2 * fs_size_x4 * sizeof(short));
        memcpy(&p->frame.mv[LIST_1][j][0][0], &fs->motion.mv[LIST_1][j][0][0], 2 * fs_size_x4 * sizeof(short));
        memcpy(p->frame.ref_idx[LIST_0][j], fs->motion.ref_idx[LIST_0][j], fs_size_x4 * sizeof(char));
        memcpy(p->frame.ref_idx[LIST_1][j], fs->motion.ref_idx[LIST_1][j], fs_size_x4 * sizeof(char));
        memcpy(p->frame.ref_pic_id[LIST_0][j], fs->motion.ref_id[LIST_0][j], fs_size_x4 * sizeof(int64));
        memcpy(p->frame.ref_pic_id[LIST_1][j], fs->motion.ref_id[LIST_1][j], fs_size_x4 * sizeof(int64));

        for (i=0 ; i < fs_size_x4; i++)
        {
          p->frame.moving_block[j][i]=
            !((!p->is_long_term
            && ((p->frame.ref_idx[LIST_0][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
            || ((p->frame.ref_idx[LIST_0][j][i] == -1)
            &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0)));
        }
      }
    }
    else
    {
      for (j=0 ; j < fs_size_y4; j++)
      {
        memcpy(&p->frame.mv[LIST_0][j][0][0], &fs->motion.mv[LIST_0][j][0][0], 2 * fs_size_x4 * sizeof(short));
        memcpy(&p->frame.mv[LIST_1][j][0][0], &fs->motion.mv[LIST_1][j][0][0], 2 * fs_size_x4 * sizeof(short));
        memcpy(p->frame.ref_idx[LIST_0][j], fs->motion.ref_idx[LIST_0][j], fs_size_x4 * sizeof(char));
        memcpy(p->frame.ref_idx[LIST_1][j], fs->motion.ref_idx[LIST_1][j], fs_size_x4 * sizeof(char));
        memcpy(p->frame.ref_pic_id[LIST_0][j], fs->motion.ref_id[LIST_0][j], fs_size_x4 * sizeof(int64));
        memcpy(p->frame.ref_pic_id[LIST_1][j], fs->motion.ref_id[LIST_1][j], fs_size_x4 * sizeof(int64));   
      }
    }
  }

  if (img->direct_spatial_mv_pred_flag == 0)
  {    
    if (img->MbaffFrameFlag || !img->structure)
    {
      for (j=0 ; j < fs_size_y4; j++)
      {
        for (i=0 ; i < fs_size_x4 ; i++)
        {
          if (fs->motion.field_frame[j][i])
          {
            p->frame.mv[LIST_0][j][i][1] *= 2;
            p->frame.mv[LIST_1][j][i][1] *= 2;
          }
        }
      }
    }
    else  if (img->structure)
    {
      for (j=0 ; j < fs_size_y4; j++)
      {
        for (i=0 ; i < fs_size_x4 ; i++)
        {
          if (!fs->motion.field_frame[j][i])
          {
            p->frame.mv[LIST_0][j][i][1] /= 2;
            p->frame.mv[LIST_1][j][i][1] /= 2;
          }
        }
      }
    }

    for (j=0; j<2 + (img->MbaffFrameFlag * 4);j+=2)
    {
      for (i=0; i<listXsize[j];i++)
      {
        int prescale, iTRb, iTRp;

        if (j==0)
        {
          iTRb = iClip3( -128, 127, dec_picture->poc - listX[LIST_0 + j][i]->poc );
        }
        else if (j == 2)
        {
          iTRb = iClip3( -128, 127, dec_picture->top_poc - listX[LIST_0 + j][i]->poc );
        }
        else
        {
          iTRb = iClip3( -128, 127, dec_picture->bottom_poc - listX[LIST_0 + j][i]->poc );
        }

        iTRp = iClip3( -128, 127,  listX[LIST_1 + j][0]->poc - listX[LIST_0 + j][i]->poc);

        if (iTRp!=0)
        {
          prescale = ( 16384 + iabs( iTRp / 2 ) ) / iTRp;
          img->mvscale[j][i] = iClip3( -1024, 1023, ( iTRb * prescale + 32 ) >> 6 ) ;
        }
        else
        {
          img->mvscale[j][i] = 9999;
        }
      }
    }
  }
}

/*!
 ************************************************************************
 * \brief
 *    Compute co-located motion info
 *    for 4:4:4 Independent mode
 *
 ************************************************************************
 */

void compute_colocated_JV(ColocatedParams* p, StorablePicture **listX[6])
{
  StorablePicture *fs, *fs_top, *fs_bottom;
  int i,j, ii, jj, jdiv;
  int np = img->colour_plane_id;

  fs_top = fs_bottom = fs = listX[LIST_1 ][0];

  if (img->MbaffFrameFlag)
  {
    fs_top= listX[LIST_1 + 2][0];
    fs_bottom= listX[LIST_1 + 4][0];
  }
  else
  {
    if (img->field_pic_flag)
    {
      if ((img->structure != fs->structure) && (fs->coded_frame))
      {
        if (img->structure==TOP_FIELD)
        {
          fs_top=fs_bottom=fs = listX[LIST_1 ][0]->top_field;
        }
        else
        {
          fs_top=fs_bottom=fs = listX[LIST_1 ][0]->bottom_field;
        }
      }
    }
  }

  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    for (j=0 ; j<fs->size_y/4 ; j++)
    {
      jdiv = j/2;
      jj = j/2 + 4 * (j/8);
      for (i=0 ; i<fs->size_x/4 ; i++)
      {

        if (img->MbaffFrameFlag && fs->motion.field_frame[j][i])
        {
          //! Assign frame buffers for field MBs
          //! Check whether we should use top or bottom field mvs.
          //! Depending on the assigned poc values.

          if (iabs(dec_picture->poc - fs_bottom->poc)> iabs(dec_picture->poc -fs_top->poc) )
          {
            p->frame.mv[LIST_0][j][i][0]    = fs_top->JVmotion[np].mv[LIST_0][jdiv][i][0];
            p->frame.mv[LIST_0][j][i][1]    = fs_top->JVmotion[np].mv[LIST_0][jdiv][i][1] ;
            p->frame.mv[LIST_1][j][i][0]    = fs_top->JVmotion[np].mv[LIST_1][jdiv][i][0];
            p->frame.mv[LIST_1][j][i][1]    = fs_top->JVmotion[np].mv[LIST_1][jdiv][i][1] ;
            p->frame.ref_idx[LIST_0][j][i]  = fs_top->JVmotion[np].ref_idx[LIST_0][jdiv][i];
            p->frame.ref_idx[LIST_1][j][i]  = fs_top->JVmotion[np].ref_idx[LIST_1][jdiv][i];
            p->frame.ref_pic_id[LIST_0][j][i]   = fs->JVmotion[np].ref_id[LIST_0][jj][i];
            p->frame.ref_pic_id[LIST_1][j][i]   = fs->JVmotion[np].ref_id[LIST_1][jj][i];

            p->is_long_term             = fs_top->is_long_term;
          }
          else
          {
            p->frame.mv[LIST_0][j][i][0]      = fs_bottom->JVmotion[np].mv[LIST_0][jdiv][i][0];
            p->frame.mv[LIST_0][j][i][1]      = fs_bottom->JVmotion[np].mv[LIST_0][jdiv][i][1] ;
            p->frame.mv[LIST_1][j][i][0]      = fs_bottom->JVmotion[np].mv[LIST_1][jdiv][i][0];
            p->frame.mv[LIST_1][j][i][1]      = fs_bottom->JVmotion[np].mv[LIST_1][jdiv][i][1] ;
            p->frame.ref_idx[LIST_0][j][i]    = fs_bottom->JVmotion[np].ref_idx[LIST_0][jdiv][i];
            p->frame.ref_idx[LIST_1][j][i]    = fs_bottom->JVmotion[np].ref_idx[LIST_1][jdiv][i];
            p->frame.ref_pic_id[LIST_0][j][i] = fs->JVmotion[np].ref_id[LIST_0][jj + 4][i];
            p->frame.ref_pic_id[LIST_1][j][i] = fs->JVmotion[np].ref_id[LIST_1][jj + 4][i];

            p->is_long_term             = fs_bottom->is_long_term;
          }
        }
        else
        {
          p->frame.mv[LIST_0][j][i][0]      = fs->JVmotion[np].mv[LIST_0][j][i][0];
          p->frame.mv[LIST_0][j][i][1]      = fs->JVmotion[np].mv[LIST_0][j][i][1] ;
          p->frame.mv[LIST_1][j][i][0]      = fs->JVmotion[np].mv[LIST_1][j][i][0];
          p->frame.mv[LIST_1][j][i][1]      = fs->JVmotion[np].mv[LIST_1][j][i][1] ;
          p->frame.ref_idx[LIST_0][j][i]    = fs->JVmotion[np].ref_idx[LIST_0][j][i];
          p->frame.ref_idx[LIST_1][j][i]    = fs->JVmotion[np].ref_idx[LIST_1][j][i];
          p->frame.ref_pic_id[LIST_0][j][i] = fs->JVmotion[np].ref_id[LIST_0][j][i];
          p->frame.ref_pic_id[LIST_1][j][i] = fs->JVmotion[np].ref_id[LIST_1][j][i];

          p->is_long_term             = fs->is_long_term;
        }
      }
    }
  }


  //! Generate field MVs from Frame MVs
  if (img->structure || img->MbaffFrameFlag)
  {
    for (j=0 ; j<fs->size_y/8 ; j++)
    {
      jj = RSD(j);
      for (i=0 ; i<fs->size_x/4 ; i++)
      {
        ii = RSD(i);
        //! Do nothing if macroblock as field coded in MB-AFF
        if (!img->MbaffFrameFlag )
        {
          p->frame.mv[LIST_0][j][i][0] = fs->JVmotion[np].mv[LIST_0][jj][ii][0];
          p->frame.mv[LIST_0][j][i][1] = fs->JVmotion[np].mv[LIST_0][jj][ii][1];
          p->frame.mv[LIST_1][j][i][0] = fs->JVmotion[np].mv[LIST_1][jj][ii][0];
          p->frame.mv[LIST_1][j][i][1] = fs->JVmotion[np].mv[LIST_1][jj][ii][1];

          // Scaling of references is done here since it will not affect spatial direct (2*0 =0)

          if (fs->JVmotion[np].ref_idx[LIST_0][jj][ii] == -1)
          {
            p->frame.ref_idx   [LIST_0][j][i] = -1;
            p->frame.ref_pic_id[LIST_0][j][i] = -1;
          }
          else
          {
            p->frame.ref_idx   [LIST_0][j][i] = fs->JVmotion[np].ref_idx[LIST_0][jj][ii] ;
            p->frame.ref_pic_id[LIST_0][j][i] = fs->JVmotion[np].ref_id [LIST_0][jj][ii];
          }

          if (fs->JVmotion[np].ref_idx[LIST_1][jj][ii] == -1)
          {
            p->frame.ref_idx   [LIST_1][j][i] = -1;
            p->frame.ref_pic_id[LIST_1][j][i] = -1;
          }
          else
          {
            p->frame.ref_idx   [LIST_1][j][i] = fs->JVmotion[np].ref_idx[LIST_1][jj][ii];
            p->frame.ref_pic_id[LIST_1][j][i] = fs->JVmotion[np].ref_id [LIST_1][jj][ii];
          }

          p->is_long_term = fs->is_long_term;

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->frame.moving_block[j][i] =
              !((!p->is_long_term
              && ((p->frame.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->frame.ref_idx[LIST_0][j][i] == -1)
              &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0)));
          }
        }
        else
        {
          p->bottom.mv[LIST_0][j][i][0] = fs_bottom->JVmotion[np].mv[LIST_0][jj][ii][0];
          p->bottom.mv[LIST_0][j][i][1] = fs_bottom->JVmotion[np].mv[LIST_0][jj][ii][1];
          p->bottom.mv[LIST_1][j][i][0] = fs_bottom->JVmotion[np].mv[LIST_1][jj][ii][0];
          p->bottom.mv[LIST_1][j][i][1] = fs_bottom->JVmotion[np].mv[LIST_1][jj][ii][1];
          p->bottom.ref_idx[LIST_0][j][i] = fs_bottom->JVmotion[np].ref_idx[LIST_0][jj][ii];
          p->bottom.ref_idx[LIST_1][j][i] = fs_bottom->JVmotion[np].ref_idx[LIST_1][jj][ii];
          p->bottom.ref_pic_id[LIST_0][j][i] = fs_bottom->JVmotion[np].ref_id[LIST_0][jj][ii];
          p->bottom.ref_pic_id[LIST_1][j][i] = fs_bottom->JVmotion[np].ref_id[LIST_1][jj][ii];

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->bottom.moving_block[j][i] =
              !((!fs_bottom->is_long_term
              && ((p->bottom.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->bottom.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->bottom.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->bottom.ref_idx[LIST_0][j][i] == -1)
              &&  (p->bottom.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->bottom.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->bottom.mv[LIST_1][j][i][1])>>1 == 0)));
          }

          p->top.mv[LIST_0][j][i][0] = fs_top->JVmotion[np].mv[LIST_0][jj][ii][0];
          p->top.mv[LIST_0][j][i][1] = fs_top->JVmotion[np].mv[LIST_0][jj][ii][1];
          p->top.mv[LIST_1][j][i][0] = fs_top->JVmotion[np].mv[LIST_1][jj][ii][0];
          p->top.mv[LIST_1][j][i][1] = fs_top->JVmotion[np].mv[LIST_1][jj][ii][1];
          p->top.ref_idx[LIST_0][j][i] = fs_top->JVmotion[np].ref_idx[LIST_0][jj][ii];
          p->top.ref_idx[LIST_1][j][i] = fs_top->JVmotion[np].ref_idx[LIST_1][jj][ii];
          p->top.ref_pic_id[LIST_0][j][i] = fs_top->JVmotion[np].ref_id[LIST_0][jj][ii];
          p->top.ref_pic_id[LIST_1][j][i] = fs_top->JVmotion[np].ref_id[LIST_1][jj][ii];

          if (img->direct_spatial_mv_pred_flag == 1)
          {
            p->top.moving_block[j][i] =
              !((!fs_top->is_long_term
              && ((p->top.ref_idx[LIST_0][j][i] == 0)
              &&  (iabs(p->top.mv[LIST_0][j][i][0])>>1 == 0)
              &&  (iabs(p->top.mv[LIST_0][j][i][1])>>1 == 0)))
              || ((p->top.ref_idx[LIST_0][j][i] == -1)
              &&  (p->top.ref_idx[LIST_1][j][i] == 0)
              &&  (iabs(p->top.mv[LIST_1][j][i][0])>>1 == 0)
              &&  (iabs(p->top.mv[LIST_1][j][i][1])>>1 == 0)));
          }

          if ((img->direct_spatial_mv_pred_flag == 0 ) && !fs->motion.field_frame[2*j][i])
          {
            p->top.mv[LIST_0][j][i][1] /= 2;
            p->top.mv[LIST_1][j][i][1] /= 2;
            p->bottom.mv[LIST_0][j][i][1] /= 2;
            p->bottom.mv[LIST_1][j][i][1] /= 2;
          }

        }
      }
    }
  }


  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    //! Use inference flag to remap mvs/references
    //! Frame with field co-located

    if (!img->structure)
    {
      for (j=0 ; j<fs->size_y/4 ; j++)
      {
        jdiv = j/2;
        jj = j/2 + 4*(j/8);
        for (i=0 ; i<fs->size_x/4 ; i++)
        {

          if (fs->motion.field_frame[j][i])
          {
            if (iabs(dec_picture->poc - fs->bottom_field->poc) > iabs(dec_picture->poc - fs->top_field->poc))
            {
              p->frame.mv[LIST_0][j][i][0] = fs->top_field->JVmotion[np].mv[LIST_0][jdiv][i][0];
              p->frame.mv[LIST_0][j][i][1] = fs->top_field->JVmotion[np].mv[LIST_0][jdiv][i][1] ;
              p->frame.mv[LIST_1][j][i][0] = fs->top_field->JVmotion[np].mv[LIST_1][jdiv][i][0];
              p->frame.mv[LIST_1][j][i][1] = fs->top_field->JVmotion[np].mv[LIST_1][jdiv][i][1] ;

              p->frame.ref_idx[LIST_0][j][i]  = fs->top_field->JVmotion[np].ref_idx[LIST_0][jdiv][i];
              p->frame.ref_idx[LIST_1][j][i]  = fs->top_field->JVmotion[np].ref_idx[LIST_1][jdiv][i];
              p->frame.ref_pic_id[LIST_0][j][i]   = fs->JVmotion[np].ref_id[LIST_0][jj][i];
              p->frame.ref_pic_id[LIST_1][j][i]   = fs->JVmotion[np].ref_id[LIST_1][jj][i];
              p->is_long_term               = fs->top_field->is_long_term;
            }
            else
            {
              p->frame.mv[LIST_0][j][i][0] = fs->bottom_field->JVmotion[np].mv[LIST_0][jdiv][i][0];
              p->frame.mv[LIST_0][j][i][1] = fs->bottom_field->JVmotion[np].mv[LIST_0][jdiv][i][1] ;
              p->frame.mv[LIST_1][j][i][0] = fs->bottom_field->JVmotion[np].mv[LIST_1][jdiv][i][0];
              p->frame.mv[LIST_1][j][i][1] = fs->bottom_field->JVmotion[np].mv[LIST_1][jdiv][i][1] ;

              p->frame.ref_idx[LIST_0][j][i]  = fs->bottom_field->JVmotion[np].ref_idx[LIST_0][jdiv][i];
              p->frame.ref_idx[LIST_1][j][i]  = fs->bottom_field->JVmotion[np].ref_idx[LIST_1][jdiv][i];
              p->frame.ref_pic_id[LIST_0][j][i] = fs->JVmotion[np].ref_id[LIST_0][jj + 4][i];
              p->frame.ref_pic_id[LIST_1][j][i] = fs->JVmotion[np].ref_id[LIST_1][jj + 4][i];
              p->is_long_term             = fs->bottom_field->is_long_term;
            }
          }
        }
      }
    }
  }

  p->is_long_term = fs->is_long_term;

  if (!active_sps->frame_mbs_only_flag || active_sps->direct_8x8_inference_flag)
  {
    for (j=0 ; j<fs->size_y/4 ; j++)
    {
      jj = RSD(j);
      for (i=0 ; i<fs->size_x/4 ; i++)
      {
        ii = RSD(i);

        p->frame.mv[LIST_0][j][i][0] = p->frame.mv[LIST_0][jj][ii][0];
        p->frame.mv[LIST_0][j][i][1] = p->frame.mv[LIST_0][jj][ii][1];
        p->frame.mv[LIST_1][j][i][0] = p->frame.mv[LIST_1][jj][ii][0];
        p->frame.mv[LIST_1][j][i][1] = p->frame.mv[LIST_1][jj][ii][1];

        p->frame.ref_idx[LIST_0][j][i]=p->frame.ref_idx[LIST_0][jj][ii];
        p->frame.ref_idx[LIST_1][j][i]=p->frame.ref_idx[LIST_1][jj][ii];
        p->frame.ref_pic_id[LIST_0][j][i] = p->frame.ref_pic_id[LIST_0][jj][ii];
        p->frame.ref_pic_id[LIST_1][j][i] = p->frame.ref_pic_id[LIST_1][jj][ii];

        if (img->direct_spatial_mv_pred_flag == 1)
        {
          p->frame.moving_block[j][i]= (byte) (
            !((!p->is_long_term
            && ((p->frame.ref_idx[LIST_0][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
            || ((p->frame.ref_idx[LIST_0][j][i] == -1)
            &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0))));
        }
      }
    }
  }
  else
  {
    for (j=0 ; j<fs->size_y/4 ; j++)
    {
      jj = RSD(j);
      for (i=0 ; i<fs->size_x/4 ; i++)
      {
        ii = RSD(i);
        //! Use inference flag to remap mvs/references
        p->frame.mv[LIST_0][j][i][0] = fs->JVmotion[np].mv[LIST_0][j][i][0];
        p->frame.mv[LIST_0][j][i][1] = fs->JVmotion[np].mv[LIST_0][j][i][1];
        p->frame.mv[LIST_1][j][i][0] = fs->JVmotion[np].mv[LIST_1][j][i][0];
        p->frame.mv[LIST_1][j][i][1] = fs->JVmotion[np].mv[LIST_1][j][i][1];

        p->frame.ref_idx[LIST_0][j][i] = fs->JVmotion[np].ref_idx[LIST_0][j][i];
        p->frame.ref_idx[LIST_1][j][i] = fs->JVmotion[np].ref_idx[LIST_1][j][i];
        p->frame.ref_pic_id[LIST_0][j][i] = fs->JVmotion[np].ref_id[LIST_0][j][i];
        p->frame.ref_pic_id[LIST_1][j][i] = fs->JVmotion[np].ref_id[LIST_1][j][i];

        if (img->direct_spatial_mv_pred_flag == 1)
        {
          p->frame.moving_block[j][i]= (byte) (
            !((!p->is_long_term
            && ((p->frame.ref_idx[LIST_0][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_0][j][i][1])>>1 == 0)))
            || ((p->frame.ref_idx[LIST_0][j][i] == -1)
            &&  (p->frame.ref_idx[LIST_1][j][i] == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][0])>>1 == 0)
            &&  (iabs(p->frame.mv[LIST_1][j][i][1])>>1 == 0))));
        }
      }
    }
  }


  if (img->direct_spatial_mv_pred_flag ==0)
  {
    for (j=0 ; j<fs->size_y/4 ; j++)
    {
      for (i=0 ; i<fs->size_x/4 ; i++)
      {
        if ((!img->MbaffFrameFlag &&!img->structure && fs->motion.field_frame[j][i]) || (img->MbaffFrameFlag && fs->motion.field_frame[j][i]))
        {
          p->frame.mv[LIST_0][j][i][1] *= 2;
          p->frame.mv[LIST_1][j][i][1] *= 2;
        }
        else  if (img->structure && !fs->motion.field_frame[j][i])
        {
          p->frame.mv[LIST_0][j][i][1] /= 2;
          p->frame.mv[LIST_1][j][i][1] /= 2;
        }

      }
    }

    for (j=0; j<2 + (img->MbaffFrameFlag * 4);j+=2)
    {
      for (i=0; i<listXsize[j];i++)
      {
        int prescale, iTRb, iTRp;

        if (j==0)
        {
          iTRb = iClip3( -128, 127, dec_picture->poc - listX[LIST_0 + j][i]->poc );
        }
        else if (j == 2)
        {
          iTRb = iClip3( -128, 127, dec_picture->top_poc - listX[LIST_0 + j][i]->poc );
        }
        else
        {
          iTRb = iClip3( -128, 127, dec_picture->bottom_poc - listX[LIST_0 + j][i]->poc );
        }

        iTRp = iClip3( -128, 127,  listX[LIST_1 + j][0]->poc - listX[LIST_0 + j][i]->poc);

        if (iTRp!=0)
        {
          prescale = ( 16384 + iabs( iTRp / 2 ) ) / iTRp;
          img->mvscale[j][i] = iClip3( -1024, 1023, ( iTRb * prescale + 32 ) >> 6 ) ;
        }
        else
        {
          img->mvscale[j][i] = 9999;
        }
      }
    }
  }
}

void copy_storable_param_JV( PicMotionParams *JVplane, PicMotionParams *motion )
{
  // copy ref_idx
  memcpy( JVplane->ref_idx[0][0], motion->ref_idx[0][0], 2 * (img->height / BLOCK_SIZE) * (img->width / BLOCK_SIZE) * sizeof(byte));

  // copy ref_pic_id
  memcpy( JVplane->ref_pic_id[0][0], motion->ref_pic_id[0][0], 6 * (img->height / BLOCK_SIZE) * (img->width / BLOCK_SIZE) * sizeof(int64));

  // copy motion.ref_id
  memcpy( JVplane->ref_id[0][0], motion->ref_id[0][0], 6 * (img->height / BLOCK_SIZE) * (img->width / BLOCK_SIZE) * sizeof(int64));

  // copy mv
  memcpy( JVplane->mv[0][0][0], motion->mv[0][0][0], 2 * (img->height / BLOCK_SIZE) * (img->width / BLOCK_SIZE) * 2 * sizeof(short) );
}
