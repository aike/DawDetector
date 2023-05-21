#pragma once

#include "public.sdk/source/vst/vstparameters.h"


using namespace Steinberg;
using namespace Vst;

class NoteNameParameter : public Parameter
{
public:
	NoteNameParameter(TChar* title, int32 id);
	void toString(ParamValue normValue, String128 string) const SMTG_OVERRIDE;
	bool fromString(const TChar* string, ParamValue& normValue) const SMTG_OVERRIDE;
protected:
	int maxLength_ = 32;
};
