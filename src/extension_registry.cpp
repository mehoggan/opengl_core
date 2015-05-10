#include <core/extension_registry.h>

#include <iostream>
#include <iterator>

namespace opengl_core
{
  registry_item::registry_item(const char *extension) :
    m_extension(extension),
    m_loaded_gl_funcs(false)
  {}

  const char *registry_item::get_extension_name() const
  {
    return m_extension;
  }

  bool registry_item::get_if_loaded_funcs() const
  {
    return m_loaded_gl_funcs;
  }

  void registry_item::set_if_loaded_funcs(bool did_load)
  {
    m_loaded_gl_funcs = did_load;
  }
}

PFNGLDRAWARRAYSINSTANCEDEXTPROC glDrawArraysInstanced = 0;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC glDrawElementsInstanced = 0;

namespace
{
  /* Dependencies
   *   OpenGL 4.0 or ARB_draw_indirect is required.
   *   Written against the OpenGL 4.1 Specification, Core Profile,
   */
  bool GL_AMD_multi_draw_indirect_load()
  {
    // Could not find PFNGL functions in glext.h
    return true;
  }

  bool GL_AMD_seamless_cubemap_per_texture_load()
  {
    // No functions added
    return true;
  }

  bool GL_ARB_arrays_of_arrays_load()
  {
    // No functions added
    return true;
  }

  /* Dependencies
   *   OpenGL 2.0 is required.
   *   Written against the OpenGL 2.1 Specification.
   *   EXT_gpu_shader4 or NV_vertex_program4 or OpenGL 3.0 is required.
   */
  bool GL_ARB_base_instance_load()
  {
    return true;
  }

  bool GL_ARB_bindless_texture_load()
  {
    return true;
  }

  bool GL_ARB_blend_func_extended_load()
  {
    return true;
  }

  bool GL_ARB_buffer_storage_load()
  {
    return true;
  }

  bool GL_ARB_clear_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_clear_texture_load()
  {
    return true;
  }

  bool GL_ARB_clip_control_load()
  {
    return true;
  }

  bool GL_ARB_color_buffer_float_load()
  {
    return true;
  }

  bool GL_ARB_compressed_texture_pixel_storage_load()
  {
    return true;
  }

  bool GL_ARB_conservative_depth_load()
  {
    return true;
  }

  bool GL_ARB_compute_shader_load()
  {
    return true;
  }

  bool GL_ARB_compute_variable_group_size_load()
  {
    return true;
  }

  bool GL_ARB_conditional_render_inverted_load()
  {
    return true;
  }

  bool GL_ARB_copy_buffer_load()
  {
    return true;
  }

  bool GL_ARB_copy_image_load()
  {
    return true;
  }

  bool GL_ARB_cull_distance_load()
  {
    return true;
  }

  bool GL_ARB_debug_output_load()
  {
    return true;
  }

  bool GL_ARB_depth_buffer_float_load()
  {
    return true;
  }

  bool GL_ARB_depth_clamp_load()
  {
    return true;
  }

  bool GL_ARB_depth_texture_load()
  {
    return true;
  }

  bool GL_ARB_derivative_control_load()
  {
    return true;
  }

  bool GL_ARB_direct_state_access_load()
  {
    return true;
  }

  bool GL_ARB_draw_buffers_load()
  {
    return true;
  }

  bool GL_ARB_draw_buffers_blend_load()
  {
    return true;
  }

  bool GL_ARB_draw_indirect_load()
  {
    return true;
  }

  bool GL_ARB_draw_elements_base_vertex_load()
  {
    return true;
  }

  bool GL_ARB_draw_instanced_load()
  {
    return true;
  }

  bool GL_ARB_enhanced_layouts_load()
  {
    return true;
  }

  bool GL_ARB_ES2_compatibility_load()
  {
    return true;
  }

  bool GL_ARB_ES3_compatibility_load()
  {
    return true;
  }

  bool GL_ARB_ES3_1_compatibility_load()
  {
    return true;
  }

  bool GL_ARB_explicit_attrib_location_load()
  {
    return true;
  }

  bool GL_ARB_explicit_uniform_location_load()
  {
    return true;
  }

  bool GL_ARB_fragment_coord_conventions_load()
  {
    return true;
  }

  bool GL_ARB_fragment_layer_viewport_load()
  {
    return true;
  }

  bool GL_ARB_fragment_program_load()
  {
    return true;
  }

  bool GL_ARB_fragment_program_shadow_load()
  {
    return true;
  }

  bool GL_ARB_fragment_shader_load()
  {
    return true;
  }

  bool GL_ARB_framebuffer_no_attachments_load()
  {
    return true;
  }

  bool GL_ARB_framebuffer_object_load()
  {
    return true;
  }

  bool GL_ARB_framebuffer_sRGB_load()
  {
    return true;
  }

  bool GL_ARB_geometry_shader4_load()
  {
    return true;
  }

  bool GL_ARB_get_program_binary_load()
  {
    return true;
  }

  bool GL_ARB_get_texture_sub_image_load()
  {
    return true;
  }

  bool GL_ARB_gpu_shader5_load()
  {
    return true;
  }

  bool GL_ARB_gpu_shader_fp64_load()
  {
    return true;
  }

  bool GL_ARB_half_float_pixel_load()
  {
    return true;
  }

  bool GL_ARB_half_float_vertex_load()
  {
    return true;
  }

  bool GL_ARB_imaging_load()
  {
    return true;
  }

  bool GL_ARB_indirect_parameters_load()
  {
    return true;
  }

  bool GL_ARB_instanced_arrays_load()
  {
    return true;
  }

  bool GL_ARB_internalformat_query_load()
  {
    return true;
  }

  bool GL_ARB_internalformat_query2_load()
  {
    return true;
  }

  bool GL_NV_internalformat_sample_query_load()
  {
    return true;
  }

  bool GL_ARB_invalidate_subdata_load()
  {
    return true;
  }

  bool GL_ARB_map_buffer_alignment_load()
  {
    return true;
  }

  bool GL_ARB_map_buffer_range_load()
  {
    return true;
  }

  bool GL_ARB_multi_bind_load()
  {
    return true;
  }

  bool GL_ARB_multi_draw_indirect_load()
  {
    return true;
  }

  bool GL_ARB_multisample_load()
  {
    return true;
  }

  bool GL_ARB_multitexture_load()
  {
    return true;
  }

  bool GL_ARB_occlusion_query_load()
  {
    return true;
  }

  bool GL_ARB_occlusion_query2_load()
  {
    return true;
  }

  bool GL_ARB_pipeline_statistics_query_load()
  {
    return true;
  }

  bool GL_ARB_pixel_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_point_parameters_load()
  {
    return true;
  }

  bool GL_ARB_point_sprite_load()
  {
    return true;
  }

  bool GL_ARB_program_interface_query_load()
  {
    return true;
  }

  bool GL_ARB_provoking_vertex_load()
  {
    return true;
  }

  bool GL_ARB_robust_buffer_access_behavior_load()
  {
    return true;
  }

  bool GL_ARB_robustness_load()
  {
    return true;
  }

  bool GL_ARB_sample_shading_load()
  {
    return true;
  }

  bool GL_ARB_sampler_objects_load()
  {
    return true;
  }

  bool GL_ARB_seamless_cube_map_load()
  {
    return true;
  }

  bool GL_ARB_seamless_cubemap_per_texture_load()
  {
    return true;
  }

  bool GL_ARB_separate_shader_objects_load()
  {
    return true;
  }

  bool GL_ARB_shader_atomic_counters_load()
  {
    return true;
  }

  bool GL_ARB_shader_bit_encoding_load()
  {
    return true;
  }

  bool GL_ARB_shader_draw_parameters_load()
  {
    return true;
  }

  bool GL_ARB_shader_group_vote_load()
  {
    return true;
  }

  bool GL_ARB_shader_image_load_store_load()
  {
    return true;
  }

  bool GL_ARB_shader_image_size_load()
  {
    return true;
  }

  bool GL_ARB_shader_objects_load()
  {
    return true;
  }

  bool GL_ARB_shader_precision_load()
  {
    return true;
  }

  bool GL_ARB_query_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_shader_storage_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_shader_subroutine_load()
  {
    return true;
  }

  bool GL_ARB_shader_texture_image_samples_load()
  {
    return true;
  }

  bool GL_ARB_shader_texture_lod_load()
  {
    return true;
  }

  bool GL_ARB_shading_language_100_load()
  {
    return true;
  }

  bool GL_ARB_shading_language_420pack_load()
  {
    return true;
  }

  bool GL_ARB_shading_language_include_load()
  {
    return true;
  }

  bool GL_ARB_shading_language_packing_load()
  {
    return true;
  }

  bool GL_ARB_shadow_load()
  {
    return true;
  }

  bool GL_ARB_sparse_buffer_load()
  {
    return true;
  }

  bool GL_ARB_sparse_texture_load()
  {
    return true;
  }

  bool GL_ARB_stencil_texturing_load()
  {
    return true;
  }

  bool GL_ARB_sync_load()
  {
    return true;
  }

  bool GL_ARB_tessellation_shader_load()
  {
    return true;
  }

  bool GL_ARB_texture_barrier_load()
  {
    return true;
  }

  bool GL_ARB_texture_border_clamp_load()
  {
    return true;
  }

  bool GL_ARB_texture_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_texture_buffer_object_rgb32_load()
  {
    return true;
  }

  bool GL_ARB_texture_buffer_range_load()
  {
    return true;
  }

  bool GL_ARB_texture_compression_load()
  {
    return true;
  }

  bool GL_ARB_texture_compression_bptc_load()
  {
    return true;
  }

  bool GL_ARB_texture_compression_rgtc_load()
  {
    return true;
  }

  bool GL_ARB_texture_cube_map_load()
  {
    return true;
  }

  bool GL_ARB_texture_cube_map_array_load()
  {
    return true;
  }

  bool GL_ARB_texture_env_add_load()
  {
    return true;
  }

  bool GL_ARB_texture_env_combine_load()
  {
    return true;
  }

  bool GL_ARB_texture_env_crossbar_load()
  {
    return true;
  }

  bool GL_ARB_texture_env_dot3_load()
  {
    return true;
  }

  bool GL_ARB_texture_float_load()
  {
    return true;
  }

  bool GL_ARB_texture_gather_load()
  {
    return true;
  }

  bool GL_ARB_texture_mirror_clamp_to_edge_load()
  {
    return true;
  }

  bool GL_ARB_texture_mirrored_repeat_load()
  {
    return true;
  }

  bool GL_ARB_texture_multisample_load()
  {
    return true;
  }

  bool GL_ARB_texture_non_power_of_two_load()
  {
    return true;
  }

  bool GL_ARB_texture_query_levels_load()
  {
    return true;
  }

  bool GL_ARB_texture_query_lod_load()
  {
    return true;
  }

  bool GL_ARB_texture_rectangle_load()
  {
    return true;
  }

  bool GL_ARB_texture_rg_load()
  {
    return true;
  }

  bool GL_ARB_texture_rgb10_a2ui_load()
  {
    return true;
  }

  bool GL_ARB_texture_stencil8_load()
  {
    return true;
  }

  bool GL_ARB_texture_storage_load()
  {
    return true;
  }

  bool GL_ARB_texture_storage_multisample_load()
  {
    return true;
  }

  bool GL_ARB_texture_swizzle_load()
  {
    return true;
  }

  bool GL_ARB_texture_view_load()
  {
    return true;
  }

  bool GL_ARB_timer_query_load()
  {
    return true;
  }

  bool GL_ARB_transform_feedback2_load()
  {
    return true;
  }

  bool GL_ARB_transform_feedback3_load()
  {
    return true;
  }

  bool GL_ARB_transform_feedback_instanced_load()
  {
    return true;
  }

  bool GL_ARB_transform_feedback_overflow_query_load()
  {
    return true;
  }

  bool GL_ARB_transpose_matrix_load()
  {
    return true;
  }

  bool GL_ARB_uniform_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_vertex_array_bgra_load()
  {
    return true;
  }

  bool GL_ARB_vertex_array_object_load()
  {
    return true;
  }

  bool GL_ARB_vertex_attrib_64bit_load()
  {
    return true;
  }

  bool GL_ARB_vertex_attrib_binding_load()
  {
    return true;
  }

  bool GL_ARB_vertex_buffer_object_load()
  {
    return true;
  }

  bool GL_ARB_vertex_program_load()
  {
    return true;
  }

  bool GL_ARB_vertex_shader_load()
  {
    return true;
  }

  bool GL_ARB_vertex_type_10f_11f_11f_rev_load()
  {
    return true;
  }

  bool GL_ARB_vertex_type_2_10_10_10_rev_load()
  {
    return true;
  }

  bool GL_ARB_viewport_array_load()
  {
    return true;
  }

  bool GL_ARB_window_pos_load()
  {
    return true;
  }

  bool GL_ATI_draw_buffers_load()
  {
    return true;
  }

  bool GL_ATI_texture_float_load()
  {
    return true;
  }

  bool GL_ATI_texture_mirror_once_load()
  {
    return true;
  }

  bool GL_S3_s3tc_load()
  {
    return true;
  }

  bool GL_EXT_texture_env_add_load()
  {
    return true;
  }

  bool GL_EXT_abgr_load()
  {
    return true;
  }

  bool GL_EXT_bgra_load()
  {
    return true;
  }

  bool GL_EXT_bindable_uniform_load()
  {
    return true;
  }

  bool GL_EXT_blend_color_load()
  {
    return true;
  }

  bool GL_EXT_blend_equation_separate_load()
  {
    return true;
  }

  bool GL_EXT_blend_func_separate_load()
  {
    return true;
  }

  bool GL_EXT_blend_minmax_load()
  {
    return true;
  }

  bool GL_EXT_blend_subtract_load()
  {
    return true;
  }

  bool GL_EXT_compiled_vertex_array_load()
  {
    return true;
  }

  bool GL_EXT_Cg_shader_load()
  {
    return true;
  }

  bool GL_EXT_depth_bounds_test_load()
  {
    return true;
  }

  bool GL_EXT_direct_state_access_load()
  {
    return true;
  }

  bool GL_EXT_draw_buffers2_load()
  {
    return true;
  }

  bool GL_EXT_draw_instanced_load()
  {
    return true;
  }

  bool GL_EXT_draw_range_elements_load()
  {
    return true;
  }

  bool GL_EXT_fog_coord_load()
  {
    return true;
  }

  bool GL_EXT_framebuffer_blit_load()
  {
    return true;
  }

  bool GL_EXT_framebuffer_multisample_load()
  {
    return true;
  }

  bool GL_EXTX_framebuffer_mixed_formats_load()
  {
    return true;
  }

  bool GL_EXT_framebuffer_multisample_blit_scaled_load()
  {
    return true;
  }

  bool GL_EXT_framebuffer_object_load()
  {
    return true;
  }

  bool GL_EXT_framebuffer_sRGB_load()
  {
    return true;
  }

  bool GL_EXT_geometry_shader4_load()
  {
    return true;
  }

  bool GL_EXT_gpu_program_parameters_load()
  {
    return true;
  }

  bool GL_EXT_gpu_shader4_load()
  {
    return true;
  }

  bool GL_EXT_multi_draw_arrays_load()
  {
    return true;
  }

  bool GL_EXT_packed_depth_stencil_load()
  {
    return true;
  }

  bool GL_EXT_packed_float_load()
  {
    return true;
  }

  bool GL_EXT_packed_pixels_load()
  {
    return true;
  }

  bool GL_EXT_pixel_buffer_object_load()
  {
    return true;
  }

  bool GL_EXT_point_parameters_load()
  {
    return true;
  }

  bool GL_EXT_polygon_offset_clamp_load()
  {
    return true;
  }

  bool GL_EXT_provoking_vertex_load()
  {
    return true;
  }

  bool GL_EXT_rescale_normal_load()
  {
    return true;
  }

  bool GL_EXT_secondary_color_load()
  {
    return true;
  }

  bool GL_EXT_separate_shader_objects_load()
  {
    return true;
  }

  bool GL_EXT_separate_specular_color_load()
  {
    return true;
  }

  bool GL_EXT_shader_image_load_formatted_load()
  {
    return true;
  }

  bool GL_EXT_shader_image_load_store_load()
  {
    return true;
  }

  bool GL_EXT_shader_integer_mix_load()
  {
    return true;
  }

  bool GL_EXT_shadow_funcs_load()
  {
    return true;
  }

  bool GL_EXT_stencil_two_side_load()
  {
    return true;
  }

  bool GL_EXT_stencil_wrap_load()
  {
    return true;
  }

  bool GL_EXT_texture3D_load()
  {
    return true;
  }

  bool GL_EXT_texture_array_load()
  {
    return true;
  }

  bool GL_EXT_texture_buffer_object_load()
  {
    return true;
  }

  bool GL_EXT_texture_compression_dxt1_load()
  {
    return true;
  }

  bool GL_EXT_texture_compression_latc_load()
  {
    return true;
  }

  bool GL_EXT_texture_compression_rgtc_load()
  {
    return true;
  }

  bool GL_EXT_texture_compression_s3tc_load()
  {
    return true;
  }

  bool GL_EXT_texture_cube_map_load()
  {
    return true;
  }

  bool GL_EXT_texture_edge_clamp_load()
  {
    return true;
  }

  bool GL_EXT_texture_env_combine_load()
  {
    return true;
  }

  bool GL_EXT_texture_env_dot3_load()
  {
    return true;
  }

  bool GL_EXT_texture_filter_anisotropic_load()
  {
    return true;
  }

  bool GL_EXT_texture_integer_load()
  {
    return true;
  }

  bool GL_EXT_texture_lod_load()
  {
    return true;
  }

  bool GL_EXT_texture_lod_bias_load()
  {
    return true;
  }

  bool GL_EXT_texture_mirror_clamp_load()
  {
    return true;
  }

  bool GL_EXT_texture_object_load()
  {
    return true;
  }

  bool GL_EXT_texture_shared_exponent_load()
  {
    return true;
  }

  bool GL_EXT_texture_sRGB_load()
  {
    return true;
  }

  bool GL_EXT_texture_sRGB_decode_load()
  {
    return true;
  }

  bool GL_EXT_texture_storage_load()
  {
    return true;
  }

  bool GL_EXT_texture_swizzle_load()
  {
    return true;
  }

  bool GL_EXT_timer_query_load()
  {
    return true;
  }

  bool GL_EXT_transform_feedback2_load()
  {
    return true;
  }

  bool GL_EXT_vertex_array_load()
  {
    return true;
  }

  bool GL_EXT_vertex_array_bgra_load()
  {
    return true;
  }

  bool GL_EXT_vertex_attrib_64bit_load()
  {
    return true;
  }

  bool GL_EXT_x11_sync_object_load()
  {
    return true;
  }

  bool GL_EXT_import_sync_object_load()
  {
    return true;
  }

  bool GL_IBM_rasterpos_clip_load()
  {
    return true;
  }

  bool GL_IBM_texture_mirrored_repeat_load()
  {
    return true;
  }

  bool GL_KHR_context_flush_control_load()
  {
    return true;
  }

  bool GL_KHR_debug_load()
  {
    return true;
  }

  bool GL_KHR_robust_buffer_access_behavior_load()
  {
    return true;
  }

  bool GL_KHR_robustness_load()
  {
    return true;
  }

  bool GL_KTX_buffer_region_load()
  {
    return true;
  }

  bool GL_NV_bindless_multi_draw_indirect_load()
  {
    return true;
  }

  bool GL_NV_bindless_multi_draw_indirect_count_load()
  {
    return true;
  }

  bool GL_NV_bindless_texture_load()
  {
    return true;
  }

  bool GL_NV_blend_equation_advanced_load()
  {
    return true;
  }

  bool GL_NV_blend_equation_advanced_coherent_load()
  {
    return true;
  }

  bool GL_NV_blend_square_load()
  {
    return true;
  }

  bool GL_NV_command_list_load()
  {
    return true;
  }

  bool GL_NV_compute_program5_load()
  {
    return true;
  }

  bool GL_NV_conditional_render_load()
  {
    return true;
  }

  bool GL_NV_copy_depth_to_color_load()
  {
    return true;
  }

  bool GL_NV_copy_image_load()
  {
    return true;
  }

  bool GL_NV_depth_buffer_float_load()
  {
    return true;
  }

  bool GL_NV_depth_clamp_load()
  {
    return true;
  }

  bool GL_NV_draw_texture_load()
  {
    return true;
  }

  bool GL_NV_ES1_1_compatibility_load()
  {
    return true;
  }

  bool GL_NV_ES3_1_compatibility_load()
  {
    return true;
  }

  bool GL_NV_explicit_multisample_load()
  {
    return true;
  }

  bool GL_NV_fence_load()
  {
    return true;
  }

  bool GL_NV_float_buffer_load()
  {
    return true;
  }

  bool GL_NV_fog_distance_load()
  {
    return true;
  }

  bool GL_NV_fragment_program_load()
  {
    return true;
  }

  bool GL_NV_fragment_program_option_load()
  {
    return true;
  }

  bool GL_NV_fragment_program2_load()
  {
    return true;
  }

  bool GL_NV_framebuffer_multisample_coverage_load()
  {
    return true;
  }

  bool GL_NV_geometry_shader4_load()
  {
    return true;
  }

  bool GL_NV_gpu_program4_load()
  {
    return true;
  }

  bool GL_NV_gpu_program4_1_load()
  {
    return true;
  }

  bool GL_NV_gpu_program5_load()
  {
    return true;
  }

  bool GL_NV_gpu_program5_mem_extended_load()
  {
    return true;
  }

  bool GL_NV_gpu_program_fp64_load()
  {
    return true;
  }

  bool GL_NV_gpu_shader5_load()
  {
    return true;
  }

  bool GL_NV_half_float_load()
  {
    return true;
  }

  bool GL_NV_light_max_exponent_load()
  {
    return true;
  }

  bool GL_NV_multisample_coverage_load()
  {
    return true;
  }

  bool GL_NV_multisample_filter_hint_load()
  {
    return true;
  }

  bool GL_NV_occlusion_query_load()
  {
    return true;
  }

  bool GL_NV_packed_depth_stencil_load()
  {
    return true;
  }

  bool GL_NV_parameter_buffer_object_load()
  {
    return true;
  }

  bool GL_NV_parameter_buffer_object2_load()
  {
    return true;
  }

  bool GL_NV_path_rendering_load()
  {
    return true;
  }

  bool GL_NV_pixel_data_range_load()
  {
    return true;
  }

  bool GL_NV_point_sprite_load()
  {
    return true;
  }

  bool GL_NV_primitive_restart_load()
  {
    return true;
  }

  bool GL_NV_register_combiners_load()
  {
    return true;
  }

  bool GL_NV_register_combiners2_load()
  {
    return true;
  }

  bool GL_NV_shader_atomic_counters_load()
  {
    return true;
  }

  bool GL_NV_shader_atomic_float_load()
  {
    return true;
  }

  bool GL_NV_shader_atomic_int64_load()
  {
    return true;
  }

  bool GL_NV_shader_buffer_load_load()
  {
    return true;
  }

  bool GL_NV_shader_storage_buffer_object_load()
  {
    return true;
  }

  bool GL_NV_texgen_reflection_load()
  {
    return true;
  }

  bool GL_NV_texture_barrier_load()
  {
    return true;
  }

  bool GL_NV_texture_compression_vtc_load()
  {
    return true;
  }

  bool GL_NV_texture_env_combine4_load()
  {
    return true;
  }

  bool GL_NV_texture_multisample_load()
  {
    return true;
  }

  bool GL_NV_texture_rectangle_load()
  {
    return true;
  }

  bool GL_NV_texture_shader_load()
  {
    return true;
  }

  bool GL_NV_texture_shader2_load()
  {
    return true;
  }

  bool GL_NV_texture_shader3_load()
  {
    return true;
  }

  bool GL_NV_transform_feedback_load()
  {
    return true;
  }

  bool GL_NV_transform_feedback2_load()
  {
    return true;
  }

  bool GL_NV_uniform_buffer_unified_memory_load()
  {
    return true;
  }

  bool GL_NV_vdpau_interop_load()
  {
    return true;
  }

  bool GL_NV_vertex_array_range_load()
  {
    return true;
  }

  bool GL_NV_vertex_array_range2_load()
  {
    return true;
  }

  bool GL_NV_vertex_attrib_integer_64bit_load()
  {
    return true;
  }

  bool GL_NV_vertex_buffer_unified_memory_load()
  {
    return true;
  }

  bool GL_NV_vertex_program_load()
  {
    return true;
  }

  bool GL_NV_vertex_program1_1_load()
  {
    return true;
  }

  bool GL_NV_vertex_program2_load()
  {
    return true;
  }

  bool GL_NV_vertex_program2_option_load()
  {
    return true;
  }

  bool GL_NV_vertex_program3_load()
  {
    return true;
  }

  bool GL_NVX_conditional_render_load()
  {
    return true;
  }

  bool GL_NVX_gpu_memory_info_load()
  {
    return true;
  }

  bool GL_NVX_nvenc_interop_load()
  {
    return true;
  }

  bool GL_NV_shader_thread_group_load()
  {
    return true;
  }

  bool GL_NV_shader_thread_shuffle_load()
  {
    return true;
  }

  bool GL_KHR_blend_equation_advanced_load()
  {
    return true;
  }

  bool GL_KHR_blend_equation_advanced_coherent_load()
  {
    return true;
  }

  bool GL_SGIS_generate_mipmap_load()
  {
    return true;
  }

  bool GL_SGIS_texture_lod_load()
  {
    return true;
  }

  bool GL_SGIX_depth_texture_load()
  {
    return true;
  }

  bool GL_SGIX_shadow_load()
  {
    return true;
  }

  bool GL_SUN_slice_accum_load()
  {
    return true;
  }
}

namespace opengl_core
{
  void extension_registry::init()
  {
    m_table.insert(std::make_pair(registry_item(
      "GL_AMD_multi_draw_indirect"),
      GL_AMD_multi_draw_indirect_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_AMD_seamless_cubemap_per_texture"),
      GL_AMD_seamless_cubemap_per_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_arrays_of_arrays"),
      GL_ARB_arrays_of_arrays_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_base_instance"),
      GL_ARB_base_instance_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_bindless_texture"),
      GL_ARB_bindless_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_blend_func_extended"),
      GL_ARB_blend_func_extended_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_buffer_storage"),
      GL_ARB_buffer_storage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_clear_buffer_object"),
      GL_ARB_clear_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_clear_texture"),
      GL_ARB_clear_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_clip_control"),
      GL_ARB_clip_control_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_color_buffer_float"),
      GL_ARB_color_buffer_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_compressed_texture_pixel_storage"),
      GL_ARB_compressed_texture_pixel_storage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_conservative_depth"),
      GL_ARB_conservative_depth_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_compute_shader"),
      GL_ARB_compute_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_compute_variable_group_size"),
      GL_ARB_compute_variable_group_size_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_conditional_render_inverted"),
      GL_ARB_conditional_render_inverted_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_copy_buffer"),
      GL_ARB_copy_buffer_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_copy_image"),
      GL_ARB_copy_image_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_cull_distance"),
      GL_ARB_cull_distance_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_debug_output"),
      GL_ARB_debug_output_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_depth_buffer_float"),
      GL_ARB_depth_buffer_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_depth_clamp"),
      GL_ARB_depth_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_depth_texture"),
      GL_ARB_depth_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_derivative_control"),
      GL_ARB_derivative_control_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_direct_state_access"),
      GL_ARB_direct_state_access_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_draw_buffers"),
      GL_ARB_draw_buffers_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_draw_buffers_blend"),
      GL_ARB_draw_buffers_blend_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_draw_indirect"),
      GL_ARB_draw_indirect_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_draw_elements_base_vertex"),
      GL_ARB_draw_elements_base_vertex_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_draw_instanced"),
      GL_ARB_draw_instanced_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_enhanced_layouts"),
      GL_ARB_enhanced_layouts_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_ES2_compatibility"),
      GL_ARB_ES2_compatibility_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_ES3_compatibility"),
      GL_ARB_ES3_compatibility_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_ES3_1_compatibility"),
      GL_ARB_ES3_1_compatibility_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_explicit_attrib_location"),
      GL_ARB_explicit_attrib_location_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_explicit_uniform_location"),
      GL_ARB_explicit_uniform_location_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_fragment_coord_conventions"),
      GL_ARB_fragment_coord_conventions_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_fragment_layer_viewport"),
      GL_ARB_fragment_layer_viewport_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_fragment_program"),
      GL_ARB_fragment_program_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_fragment_program_shadow"),
      GL_ARB_fragment_program_shadow_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_fragment_shader"),
      GL_ARB_fragment_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_framebuffer_no_attachments"),
      GL_ARB_framebuffer_no_attachments_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_framebuffer_object"),
      GL_ARB_framebuffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_framebuffer_sRGB"),
      GL_ARB_framebuffer_sRGB_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_geometry_shader4"),
      GL_ARB_geometry_shader4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_get_program_binary"),
      GL_ARB_get_program_binary_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_get_texture_sub_image"),
      GL_ARB_get_texture_sub_image_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_gpu_shader5"),
      GL_ARB_gpu_shader5_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_gpu_shader_fp64"),
      GL_ARB_gpu_shader_fp64_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_half_float_pixel"),
      GL_ARB_half_float_pixel_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_half_float_vertex"),
      GL_ARB_half_float_vertex_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_imaging"),
      GL_ARB_imaging_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_indirect_parameters"),
      GL_ARB_indirect_parameters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_instanced_arrays"),
      GL_ARB_instanced_arrays_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_internalformat_query"),
      GL_ARB_internalformat_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_internalformat_query2"),
      GL_ARB_internalformat_query2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_internalformat_sample_query"),
      GL_NV_internalformat_sample_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_invalidate_subdata"),
      GL_ARB_invalidate_subdata_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_map_buffer_alignment"),
      GL_ARB_map_buffer_alignment_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_map_buffer_range"),
      GL_ARB_map_buffer_range_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_multi_bind"),
      GL_ARB_multi_bind_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_multi_draw_indirect"),
      GL_ARB_multi_draw_indirect_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_multisample"),
      GL_ARB_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_multitexture"),
      GL_ARB_multitexture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_occlusion_query"),
      GL_ARB_occlusion_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_occlusion_query2"),
      GL_ARB_occlusion_query2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_pipeline_statistics_query"),
      GL_ARB_pipeline_statistics_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_pixel_buffer_object"),
      GL_ARB_pixel_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_point_parameters"),
      GL_ARB_point_parameters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_point_sprite"),
      GL_ARB_point_sprite_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_program_interface_query"),
      GL_ARB_program_interface_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_provoking_vertex"),
      GL_ARB_provoking_vertex_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_robust_buffer_access_behavior"),
      GL_ARB_robust_buffer_access_behavior_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_robustness"),
      GL_ARB_robustness_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_sample_shading"),
      GL_ARB_sample_shading_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_sampler_objects"),
      GL_ARB_sampler_objects_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_seamless_cube_map"),
      GL_ARB_seamless_cube_map_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_seamless_cubemap_per_texture"),
      GL_ARB_seamless_cubemap_per_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_separate_shader_objects"),
      GL_ARB_separate_shader_objects_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_atomic_counters"),
      GL_ARB_shader_atomic_counters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_bit_encoding"),
      GL_ARB_shader_bit_encoding_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_draw_parameters"),
      GL_ARB_shader_draw_parameters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_group_vote"),
      GL_ARB_shader_group_vote_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_image_load_store"),
      GL_ARB_shader_image_load_store_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_image_size"),
      GL_ARB_shader_image_size_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_objects"),
      GL_ARB_shader_objects_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_precision"),
      GL_ARB_shader_precision_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_query_buffer_object"),
      GL_ARB_query_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_storage_buffer_object"),
      GL_ARB_shader_storage_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_subroutine"),
      GL_ARB_shader_subroutine_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_texture_image_samples"),
      GL_ARB_shader_texture_image_samples_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shader_texture_lod"),
      GL_ARB_shader_texture_lod_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shading_language_100"),
      GL_ARB_shading_language_100_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shading_language_420pack"),
      GL_ARB_shading_language_420pack_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shading_language_include"),
      GL_ARB_shading_language_include_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shading_language_packing"),
      GL_ARB_shading_language_packing_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_shadow"),
      GL_ARB_shadow_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_sparse_buffer"),
      GL_ARB_sparse_buffer_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_sparse_texture"),
      GL_ARB_sparse_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_stencil_texturing"),
      GL_ARB_stencil_texturing_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_sync"),
      GL_ARB_sync_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_tessellation_shader"),
      GL_ARB_tessellation_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_barrier"),
      GL_ARB_texture_barrier_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_border_clamp"),
      GL_ARB_texture_border_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_buffer_object"),
      GL_ARB_texture_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_buffer_object_rgb32"),
      GL_ARB_texture_buffer_object_rgb32_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_buffer_range"),
      GL_ARB_texture_buffer_range_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_compression"),
      GL_ARB_texture_compression_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_compression_bptc"),
      GL_ARB_texture_compression_bptc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_compression_rgtc"),
      GL_ARB_texture_compression_rgtc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_cube_map"),
      GL_ARB_texture_cube_map_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_cube_map_array"),
      GL_ARB_texture_cube_map_array_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_env_add"),
      GL_ARB_texture_env_add_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_env_combine"),
      GL_ARB_texture_env_combine_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_env_crossbar"),
      GL_ARB_texture_env_crossbar_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_env_dot3"),
      GL_ARB_texture_env_dot3_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_float"),
      GL_ARB_texture_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_gather"),
      GL_ARB_texture_gather_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_mirror_clamp_to_edge"),
      GL_ARB_texture_mirror_clamp_to_edge_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_mirrored_repeat"),
      GL_ARB_texture_mirrored_repeat_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_multisample"),
      GL_ARB_texture_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_non_power_of_two"),
      GL_ARB_texture_non_power_of_two_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_query_levels"),
      GL_ARB_texture_query_levels_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_query_lod"),
      GL_ARB_texture_query_lod_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_rectangle"),
      GL_ARB_texture_rectangle_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_rg"),
      GL_ARB_texture_rg_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_rgb10_a2ui"),
      GL_ARB_texture_rgb10_a2ui_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_stencil8"),
      GL_ARB_texture_stencil8_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_storage"),
      GL_ARB_texture_storage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_storage_multisample"),
      GL_ARB_texture_storage_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_swizzle"),
      GL_ARB_texture_swizzle_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_texture_view"),
      GL_ARB_texture_view_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_timer_query"),
      GL_ARB_timer_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_transform_feedback2"),
      GL_ARB_transform_feedback2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_transform_feedback3"),
      GL_ARB_transform_feedback3_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_transform_feedback_instanced"),
      GL_ARB_transform_feedback_instanced_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_transform_feedback_overflow_query"),
      GL_ARB_transform_feedback_overflow_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_transpose_matrix"),
      GL_ARB_transpose_matrix_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_uniform_buffer_object"),
      GL_ARB_uniform_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_array_bgra"),
      GL_ARB_vertex_array_bgra_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_array_object"),
      GL_ARB_vertex_array_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_attrib_64bit"),
      GL_ARB_vertex_attrib_64bit_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_attrib_binding"),
      GL_ARB_vertex_attrib_binding_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_buffer_object"),
      GL_ARB_vertex_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_program"),
      GL_ARB_vertex_program_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_shader"),
      GL_ARB_vertex_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_type_10f_11f_11f_rev"),
      GL_ARB_vertex_type_10f_11f_11f_rev_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_vertex_type_2_10_10_10_rev"),
      GL_ARB_vertex_type_2_10_10_10_rev_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_viewport_array"),
      GL_ARB_viewport_array_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ARB_window_pos"),
      GL_ARB_window_pos_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ATI_draw_buffers"),
      GL_ATI_draw_buffers_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ATI_texture_float"),
      GL_ATI_texture_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_ATI_texture_mirror_once"),
      GL_ATI_texture_mirror_once_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_S3_s3tc"),
      GL_S3_s3tc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_env_add"),
      GL_EXT_texture_env_add_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_abgr"),
      GL_EXT_abgr_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_bgra"),
      GL_EXT_bgra_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_bindable_uniform"),
      GL_EXT_bindable_uniform_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_blend_color"),
      GL_EXT_blend_color_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_blend_equation_separate"),
      GL_EXT_blend_equation_separate_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_blend_func_separate"),
      GL_EXT_blend_func_separate_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_blend_minmax"),
      GL_EXT_blend_minmax_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_blend_subtract"),
      GL_EXT_blend_subtract_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_compiled_vertex_array"),
      GL_EXT_compiled_vertex_array_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_Cg_shader"),
      GL_EXT_Cg_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_depth_bounds_test"),
      GL_EXT_depth_bounds_test_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_direct_state_access"),
      GL_EXT_direct_state_access_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_draw_buffers2"),
      GL_EXT_draw_buffers2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_draw_instanced"),
      GL_EXT_draw_instanced_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_draw_range_elements"),
      GL_EXT_draw_range_elements_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_fog_coord"),
      GL_EXT_fog_coord_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_framebuffer_blit"),
      GL_EXT_framebuffer_blit_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_framebuffer_multisample"),
      GL_EXT_framebuffer_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXTX_framebuffer_mixed_formats"),
      GL_EXTX_framebuffer_mixed_formats_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_framebuffer_multisample_blit_scaled"),
      GL_EXT_framebuffer_multisample_blit_scaled_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_framebuffer_object"),
      GL_EXT_framebuffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_framebuffer_sRGB"),
      GL_EXT_framebuffer_sRGB_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_geometry_shader4"),
      GL_EXT_geometry_shader4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_gpu_program_parameters"),
      GL_EXT_gpu_program_parameters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_gpu_shader4"),
      GL_EXT_gpu_shader4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_multi_draw_arrays"),
      GL_EXT_multi_draw_arrays_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_packed_depth_stencil"),
      GL_EXT_packed_depth_stencil_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_packed_float"),
      GL_EXT_packed_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_packed_pixels"),
      GL_EXT_packed_pixels_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_pixel_buffer_object"),
      GL_EXT_pixel_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_point_parameters"),
      GL_EXT_point_parameters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_polygon_offset_clamp"),
      GL_EXT_polygon_offset_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_provoking_vertex"),
      GL_EXT_provoking_vertex_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_rescale_normal"),
      GL_EXT_rescale_normal_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_secondary_color"),
      GL_EXT_secondary_color_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_separate_shader_objects"),
      GL_EXT_separate_shader_objects_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_separate_specular_color"),
      GL_EXT_separate_specular_color_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_shader_image_load_formatted"),
      GL_EXT_shader_image_load_formatted_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_shader_image_load_store"),
      GL_EXT_shader_image_load_store_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_shader_integer_mix"),
      GL_EXT_shader_integer_mix_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_shadow_funcs"),
      GL_EXT_shadow_funcs_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_stencil_two_side"),
      GL_EXT_stencil_two_side_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_stencil_wrap"),
      GL_EXT_stencil_wrap_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture3D"),
      GL_EXT_texture3D_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_array"),
      GL_EXT_texture_array_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_buffer_object"),
      GL_EXT_texture_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_compression_dxt1"),
      GL_EXT_texture_compression_dxt1_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_compression_latc"),
      GL_EXT_texture_compression_latc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_compression_rgtc"),
      GL_EXT_texture_compression_rgtc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_compression_s3tc"),
      GL_EXT_texture_compression_s3tc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_cube_map"),
      GL_EXT_texture_cube_map_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_edge_clamp"),
      GL_EXT_texture_edge_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_env_combine"),
      GL_EXT_texture_env_combine_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_env_dot3"),
      GL_EXT_texture_env_dot3_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_filter_anisotropic"),
      GL_EXT_texture_filter_anisotropic_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_integer"),
      GL_EXT_texture_integer_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_lod"),
      GL_EXT_texture_lod_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_lod_bias"),
      GL_EXT_texture_lod_bias_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_mirror_clamp"),
      GL_EXT_texture_mirror_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_object"),
      GL_EXT_texture_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_shared_exponent"),
      GL_EXT_texture_shared_exponent_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_sRGB"),
      GL_EXT_texture_sRGB_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_sRGB_decode"),
      GL_EXT_texture_sRGB_decode_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_storage"),
      GL_EXT_texture_storage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_texture_swizzle"),
      GL_EXT_texture_swizzle_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_timer_query"),
      GL_EXT_timer_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_transform_feedback2"),
      GL_EXT_transform_feedback2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_vertex_array"),
      GL_EXT_vertex_array_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_vertex_array_bgra"),
      GL_EXT_vertex_array_bgra_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_vertex_attrib_64bit"),
      GL_EXT_vertex_attrib_64bit_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_x11_sync_object"),
      GL_EXT_x11_sync_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_EXT_import_sync_object"),
      GL_EXT_import_sync_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_IBM_rasterpos_clip"),
      GL_IBM_rasterpos_clip_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_IBM_texture_mirrored_repeat"),
      GL_IBM_texture_mirrored_repeat_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_context_flush_control"),
      GL_KHR_context_flush_control_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_debug"),
      GL_KHR_debug_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_robust_buffer_access_behavior"),
      GL_KHR_robust_buffer_access_behavior_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_robustness"),
      GL_KHR_robustness_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KTX_buffer_region"),
      GL_KTX_buffer_region_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_bindless_multi_draw_indirect"),
      GL_NV_bindless_multi_draw_indirect_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_bindless_multi_draw_indirect_count"),
      GL_NV_bindless_multi_draw_indirect_count_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_bindless_texture"),
      GL_NV_bindless_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_blend_equation_advanced"),
      GL_NV_blend_equation_advanced_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_blend_equation_advanced_coherent"),
      GL_NV_blend_equation_advanced_coherent_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_blend_square"),
      GL_NV_blend_square_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_command_list"),
      GL_NV_command_list_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_compute_program5"),
      GL_NV_compute_program5_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_conditional_render"),
      GL_NV_conditional_render_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_copy_depth_to_color"),
      GL_NV_copy_depth_to_color_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_copy_image"),
      GL_NV_copy_image_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_depth_buffer_float"),
      GL_NV_depth_buffer_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_depth_clamp"),
      GL_NV_depth_clamp_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_draw_texture"),
      GL_NV_draw_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_ES1_1_compatibility"),
      GL_NV_ES1_1_compatibility_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_ES3_1_compatibility"),
      GL_NV_ES3_1_compatibility_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_explicit_multisample"),
      GL_NV_explicit_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_fence"),
      GL_NV_fence_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_float_buffer"),
      GL_NV_float_buffer_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_fog_distance"),
      GL_NV_fog_distance_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_fragment_program"),
      GL_NV_fragment_program_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_fragment_program_option"),
      GL_NV_fragment_program_option_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_fragment_program2"),
      GL_NV_fragment_program2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_framebuffer_multisample_coverage"),
      GL_NV_framebuffer_multisample_coverage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_geometry_shader4"),
      GL_NV_geometry_shader4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_program4"),
      GL_NV_gpu_program4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_program4_1"),
      GL_NV_gpu_program4_1_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_program5"),
      GL_NV_gpu_program5_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_program5_mem_extended"),
      GL_NV_gpu_program5_mem_extended_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_program_fp64"),
      GL_NV_gpu_program_fp64_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_gpu_shader5"),
      GL_NV_gpu_shader5_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_half_float"),
      GL_NV_half_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_light_max_exponent"),
      GL_NV_light_max_exponent_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_multisample_coverage"),
      GL_NV_multisample_coverage_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_multisample_filter_hint"),
      GL_NV_multisample_filter_hint_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_occlusion_query"),
      GL_NV_occlusion_query_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_packed_depth_stencil"),
      GL_NV_packed_depth_stencil_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_parameter_buffer_object"),
      GL_NV_parameter_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_parameter_buffer_object2"),
      GL_NV_parameter_buffer_object2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_path_rendering"),
      GL_NV_path_rendering_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_pixel_data_range"),
      GL_NV_pixel_data_range_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_point_sprite"),
      GL_NV_point_sprite_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_primitive_restart"),
      GL_NV_primitive_restart_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_register_combiners"),
      GL_NV_register_combiners_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_register_combiners2"),
      GL_NV_register_combiners2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_atomic_counters"),
      GL_NV_shader_atomic_counters_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_atomic_float"),
      GL_NV_shader_atomic_float_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_atomic_int64"),
      GL_NV_shader_atomic_int64_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_buffer_load"),
      GL_NV_shader_buffer_load_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_storage_buffer_object"),
      GL_NV_shader_storage_buffer_object_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texgen_reflection"),
      GL_NV_texgen_reflection_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_barrier"),
      GL_NV_texture_barrier_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_compression_vtc"),
      GL_NV_texture_compression_vtc_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_env_combine4"),
      GL_NV_texture_env_combine4_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_multisample"),
      GL_NV_texture_multisample_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_rectangle"),
      GL_NV_texture_rectangle_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_shader"),
      GL_NV_texture_shader_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_shader2"),
      GL_NV_texture_shader2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_texture_shader3"),
      GL_NV_texture_shader3_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_transform_feedback"),
      GL_NV_transform_feedback_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_transform_feedback2"),
      GL_NV_transform_feedback2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_uniform_buffer_unified_memory"),
      GL_NV_uniform_buffer_unified_memory_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vdpau_interop"),
      GL_NV_vdpau_interop_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_array_range"),
      GL_NV_vertex_array_range_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_array_range2"),
      GL_NV_vertex_array_range2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_attrib_integer_64bit"),
      GL_NV_vertex_attrib_integer_64bit_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_buffer_unified_memory"),
      GL_NV_vertex_buffer_unified_memory_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_program"),
      GL_NV_vertex_program_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_program1_1"),
      GL_NV_vertex_program1_1_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_program2"),
      GL_NV_vertex_program2_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_program2_option"),
      GL_NV_vertex_program2_option_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_vertex_program3"),
      GL_NV_vertex_program3_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NVX_conditional_render"),
      GL_NVX_conditional_render_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NVX_gpu_memory_info"),
      GL_NVX_gpu_memory_info_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NVX_nvenc_interop"),
      GL_NVX_nvenc_interop_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_thread_group"),
      GL_NV_shader_thread_group_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_NV_shader_thread_shuffle"),
      GL_NV_shader_thread_shuffle_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_blend_equation_advanced"),
      GL_KHR_blend_equation_advanced_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_KHR_blend_equation_advanced_coherent"),
      GL_KHR_blend_equation_advanced_coherent_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_SGIS_generate_mipmap"),
      GL_SGIS_generate_mipmap_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_SGIS_texture_lod"),
      GL_SGIS_texture_lod_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_SGIX_depth_texture"),
      GL_SGIX_depth_texture_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_SGIX_shadow"),
      GL_SGIX_shadow_load));
    m_table.insert(std::make_pair(registry_item(
      "GL_SUN_slice_accum"),
      GL_SUN_slice_accum_load));
  }

  bool extension_registry::has_extension_loaded(const char *extension) const
  {
    registry_item item(extension);
    return (m_table.find(item) != m_table.end() &&
      m_table.find(item)->first.get_if_loaded_funcs());
  }

  bool extension_registry::load_extension(const char *extension)
  {
    registry_item item(extension);
    auto it = m_table.find(item);
    if (it != m_table.end()) {
      if ((it->second)()) {
        const_cast<registry_item &>(it->first).set_if_loaded_funcs(true);
        return true;
      } else {
        std::cerr << "Failed to load " << extension << std::endl;
        const_cast<registry_item &>(it->first).set_if_loaded_funcs(false);
      }
    } else {
      std::cerr << "Failed to find " << extension << std::endl;
    }

    return false;
  }
}
