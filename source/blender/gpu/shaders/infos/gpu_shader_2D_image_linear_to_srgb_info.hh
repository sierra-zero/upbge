/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright 2022 Blender Foundation. All rights reserved. */

/** \file
 * \ingroup gpu
 */

#include "gpu_interface_info.hh"
#include "gpu_shader_create_info.hh"

GPU_SHADER_CREATE_INFO(gpu_shader_2D_image_linear_to_srgb)
    .vertex_in(0, Type::VEC2, "pos")
    .vertex_in(1, Type::VEC2, "texCoord")
    .vertex_out(smooth_tex_coord_interp_iface)
    .fragment_out(0, Type::VEC4, "fragColor")
    .push_constant(Type::MAT4, "ModelViewProjectionMatrix")
    /* Sampler slots should match OCIO's. */
    .sampler(0, ImageType::FLOAT_2D, "image_texture")
    .vertex_source("gpu_shader_2D_image_vert.glsl")
    .fragment_source("gpu_shader_image_linear_frag.glsl")
    .do_static_compilation(true);
