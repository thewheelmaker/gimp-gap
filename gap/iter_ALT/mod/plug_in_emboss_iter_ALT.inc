/* ----------------------------------------------------------------------
 * p_plug_in_emboss_iter_ALT 
 * ----------------------------------------------------------------------
 */
gint p_plug_in_emboss_iter_ALT(GimpRunMode run_mode, gint32 total_steps, gdouble current_step, gint32 len_struct) 
{
    typedef struct t_plug_in_emboss_Vals 
    {
      gdouble   azimuth;
      gdouble   elevation;
      gint32    depth;
      gint32    embossp;
    } t_plug_in_emboss_Vals; 

    t_plug_in_emboss_Vals  buf, *buf_from, *buf_to; 

    if(len_struct != sizeof(t_plug_in_emboss_Vals)) 
    {
      fprintf(stderr, "ERROR: p_plug_in_emboss_iter_ALT  stored Data missmatch in size %d != %d\n",   
                       (int)len_struct, sizeof(t_plug_in_emboss_Vals) ); 
      return -1;  /* ERROR */ 
    }

    gimp_get_data("plug-in-emboss-ITER-FROM", g_plugin_data_from); 
    gimp_get_data("plug-in-emboss-ITER-TO",   g_plugin_data_to); 

    buf_from = (t_plug_in_emboss_Vals *)&g_plugin_data_from[0]; 
    buf_to   = (t_plug_in_emboss_Vals *)&g_plugin_data_to[0]; 
    memcpy(&buf, buf_from, sizeof(buf));

    p_delta_gdouble(&buf.azimuth, buf_from->azimuth, buf_to->azimuth, total_steps, current_step);
    p_delta_gdouble(&buf.elevation, buf_from->elevation, buf_to->elevation, total_steps, current_step);
    p_delta_gint32(&buf.depth, buf_from->depth, buf_to->depth, total_steps, current_step);
    p_delta_gint32(&buf.embossp, buf_from->embossp, buf_to->embossp, total_steps, current_step);

    gimp_set_data("plug-in-emboss", &buf, sizeof(buf)); 

    return 0; /* OK */
}
