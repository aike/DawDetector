//------------------------------------------------------------------------
// Copyright(c) 2023 aikelab.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace aikelab {
//------------------------------------------------------------------------
static const Steinberg::FUID kNoteNameDemoProcessorUID (0x6AEF81BF, 0xD80F5F42, 0xBEAEDDD3, 0x9A569FF6);
static const Steinberg::FUID kNoteNameDemoControllerUID (0x24FE0F5E, 0x8AA55CF8, 0x911FA650, 0xDB2B0BAC);

#define NoteNameDemoVST3Category "Fx|Instrument"

//------------------------------------------------------------------------
} // namespace aikelab
