// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "common/settings.h"

namespace Settings {

inline constexpr u64 MarioKartWorldProgramId = 0x0400C3F00006E000ULL;

inline void SetMarioKartWorldRecommendedSettings(Values& settings, bool global) {
    const auto session = [global](auto& setting, auto value) {
        setting.SetGlobal(global);
        setting.SetValue(value);
    };
    session(settings.renderer_backend, RendererBackend::Vulkan);
    session(settings.resolution_setup, ResolutionSetup::Res1X);
    session(settings.gpu_accuracy, GpuAccuracy::Low);
    session(settings.use_asynchronous_shaders, true);
    session(settings.astc_recompression, AstcRecompression::Bc3);
    session(settings.vram_usage_mode, VramUsageMode::Conservative);
    session(settings.use_reactive_flushing, false);
    session(settings.vsync_mode, VSyncMode::FifoRelaxed);
    session(settings.use_docked_mode, ConsoleMode::Handheld);
    session(settings.scaling_filter, ScalingFilter::ScaleForce);
    session(settings.anti_aliasing, AntiAliasing::Fxaa);
}

inline bool ApplyMarioKartWorldPreset(Values& settings, u64 program_id, bool accepted) {
    if (!accepted || program_id != MarioKartWorldProgramId) {
        return false;
    }
    SetMarioKartWorldRecommendedSettings(settings, false);
    return true;
}

inline constexpr u64 OcarinaOfTimeProgramId = 0x0400486024DEC000ULL;

// Ocarina of Time on a 6 GB desktop GPU (tuned on the GTX 1660 class: Turing, no native ASTC).
// Each choice follows a measurement in NX2_NOTES.md:
// - reactive flushing off: its read protection cost the main core ~12% in slow-path reads
//   (row 115); the read traps (row 150) still copy GPU-written buffers back when the game reads.
// - ASTC decoded on the GPU (row 107) and re-compressed to BC3, so streamed textures take a
//   quarter of the VRAM of RGBA8 and fit in 6 GB without the texture churn of row 114.
// - asynchronous shaders: a missing pipeline skips draws for a frame instead of stalling it.
// GPU accuracy stays as the user set it: the occlusion-query fixes for the white flashes (#121)
// depend on query results that Low accuracy can skip.
inline void SetOcarinaOfTimeRecommendedSettings(Values& settings, bool global) {
    const auto session = [global](auto& setting, auto value) {
        setting.SetGlobal(global);
        setting.SetValue(value);
    };
    session(settings.renderer_backend, RendererBackend::Vulkan);
    session(settings.resolution_setup, ResolutionSetup::Res1X);
    session(settings.use_asynchronous_shaders, true);
    session(settings.accelerate_astc, AstcDecodeMode::Gpu);
    session(settings.astc_recompression, AstcRecompression::Bc3);
    session(settings.vram_usage_mode, VramUsageMode::Conservative);
    session(settings.use_reactive_flushing, false);
    session(settings.vsync_mode, VSyncMode::FifoRelaxed);
    session(settings.use_disk_shader_cache, true);
    session(settings.use_vulkan_driver_pipeline_cache, true);
}

inline bool ApplyOcarinaOfTimePreset(Values& settings, u64 program_id, bool accepted) {
    if (!accepted || program_id != OcarinaOfTimeProgramId) {
        return false;
    }
    SetOcarinaOfTimeRecommendedSettings(settings, false);
    return true;
}

} // namespace Settings
