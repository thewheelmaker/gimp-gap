/* ----------------------------------------------------------------------
 * p_plug_in_gauss_iir2_iter_ALT 
 * ----------------------------------------------------------------------
 */
gint p_plug_in_gauss_iir2_iter_ALT(GimpRunMode run_mode, gint32 total_steps, gdouble current_step, gint32 len_struct) 
{
    typedef struct t_plug_in_gauss_iir2_Vals 
    {
      gdouble   horizontal;
      gdouble   vertical;
    } t_plug_in_gauss_iir2_Vals; 

    t_plug_in_gauss_iir2_Vals  buf, *buf_from, *buf_to; 

    if(len_struct != sizeof(t_plug_in_gauss_iir2_Vals)) 
    {
      fprintf(stderr, "ERROR: p_plug_in_gauss_iir2_iter_ALT  stored Data missmatch in size %d != %d\n",   
                       (int)len_struct, sizeof(t_plug_in_gauss_iir2_Vals) ); 
      return -1;  /* ERROR */ 
    }

    gimp_get_data("plug-in-gauss-iir2-ITER-FROM", g_plugin_data_from); 
    gimp_get_data("plug-in-gauss-iir2-ITER-TO",   g_plugin_data_to); 

    buf_from = (t_plug_in_gauss_iir2_Vals *)&g_plugin_data_from[0]; 
    buf_to   = (t_plug_in_gauss_iir2_Vals *)&g_plugin_data_to[0]; 
    memcpy(&buf, buf_from, sizeof(buf));

    p_delta_gdouble(&buf.horizontal, buf_from->horizontal, buf_to->horizontal, total_steps, current_step);
    p_delta_gdouble(&buf.vertical, buf_from->vertical, buf_to->vertical, total_steps, current_step);

    gimp_set_data("plug-in-gauss-iir2", &buf, sizeof(buf)); 

    return 0; /* OK */
}
