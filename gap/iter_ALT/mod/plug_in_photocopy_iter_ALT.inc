/* ----------------------------------------------------------------------
 * p_plug_in_photocopy_iter_ALT 
 * ----------------------------------------------------------------------
 */
gint p_plug_in_photocopy_iter_ALT(GimpRunMode run_mode, gint32 total_steps, gdouble current_step, gint32 len_struct) 
{
    typedef struct t_plug_in_photocopy_Vals 
    {
      gdouble  mask_radius;
      gdouble  sharpness;
      gdouble  threshold;
      gdouble  pct_black;
      gdouble  pct_white;
      gboolean  update_preview;
    } t_plug_in_photocopy_Vals; 

    t_plug_in_photocopy_Vals  buf, *buf_from, *buf_to; 

    if(len_struct != sizeof(t_plug_in_photocopy_Vals)) 
    {
      fprintf(stderr, "ERROR: p_plug_in_photocopy_iter_ALT  stored Data missmatch in size %d != %d\n",   
                       (int)len_struct, sizeof(t_plug_in_photocopy_Vals) ); 
      return -1;  /* ERROR */ 
    }

    gimp_get_data("plug_in_photocopy_ITER_FROM", g_plugin_data_from); 
    gimp_get_data("plug_in_photocopy_ITER_TO",   g_plugin_data_to); 

    buf_from = (t_plug_in_photocopy_Vals *)&g_plugin_data_from[0]; 
    buf_to   = (t_plug_in_photocopy_Vals *)&g_plugin_data_to[0]; 
    memcpy(&buf, buf_from, sizeof(buf));

    p_delta_gdouble(&buf.mask_radius, buf_from->mask_radius, buf_to->mask_radius, total_steps, current_step);
    p_delta_gdouble(&buf.sharpness, buf_from->sharpness, buf_to->sharpness, total_steps, current_step);
    p_delta_gdouble(&buf.threshold, buf_from->threshold, buf_to->threshold, total_steps, current_step);
    p_delta_gdouble(&buf.pct_black, buf_from->pct_black, buf_to->pct_black, total_steps, current_step);
    p_delta_gdouble(&buf.pct_white, buf_from->pct_white, buf_to->pct_white, total_steps, current_step);

    buf.update_preview = FALSE;
    gimp_set_data("plug_in_photocopy", &buf, sizeof(buf)); 

    return 0; /* OK */
}