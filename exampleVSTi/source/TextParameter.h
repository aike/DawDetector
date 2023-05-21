#pragma once

#include "public.sdk/source/vst/vstparameters.h"


using namespace Steinberg;
using namespace Vst;

class TextParameter : public Parameter
{
public:
	TextParameter(TChar* title, int32 id);
	void toString(ParamValue normValue, String128 string) const SMTG_OVERRIDE;
	bool fromString(const TChar* string, ParamValue& normValue) const SMTG_OVERRIDE;
	void setText(String128 text);
	void setMaxLength(int maxLength);
protected:
	String128 text_;
	int maxLength_ = 128;
};
