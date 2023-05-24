#include "NoteNameParameter.h"
#include "pluginterfaces/base/ustring.h"
#include "DawDetector.h"

NoteNameParameter::NoteNameParameter(TChar* title, int32 id)
{
	UString(info.title, str16BufferSize(String128)).assign(title);
	info.flags = ParameterInfo::kCanAutomate;
	info.id = id;
	info.stepCount = 0;
	info.defaultNormalizedValue = 0.f;
	info.unitId = kRootUnitId;

	setNormalized(1.f);
}


// normValueを整数化した文字列を返す
void NoteNameParameter::toString(ParamValue normValue, String128 string) const
{
	tstrncpy(string, DawDetector::getNoteName((int)(normValue * 1000000.0)), maxLength_);
	string[maxLength_] = '\0';
	return;
}

// インタフェースとして必要なだけで何もしない。normValueには便宜上0を格納して返す
bool NoteNameParameter::fromString(const TChar* string, ParamValue& normValue) const
{
	normValue = 0.0;
	return true;
}