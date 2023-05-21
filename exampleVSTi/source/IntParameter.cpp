#include "IntParameter.h"
#include "pluginterfaces/base/ustring.h"

IntParameter::IntParameter(TChar* title, int32 id)
{
	UString(info.title, str16BufferSize(String128)).assign(title);
	info.flags = ParameterInfo::kCanAutomate;
	info.id = id;
	info.stepCount = 0;
	info.defaultNormalizedValue = 0.5f;
	info.unitId = kRootUnitId;

	setNormalized(1.f);
}

void IntParameter::toString(ParamValue normValue, String128 string) const
{
	if (normValue * 1000000.0 > 128.0) {
		strcpy16(string, STR("-"));
		return;
	}

	// 0.0�`1.0�̎���normValue��0�`1000000�̐����ɕϊ�����string�Ɋi�[���ĕԂ�
	char text[32];
	sprintf(text, "%.0f", (float)(normValue * 1000000.f));
	Steinberg::UString(string, 128).fromAscii(text);
}

bool IntParameter::fromString(const TChar* string, ParamValue& normValue) const
{
	// 0�`1000000�̐���������string��0.0�`1.0�̎����ɕϊ�����normValue�Ɋi�[���ĕԂ�
	Steinberg::UString wrapper((TChar*)string, -1);
	double tmp = 0.0;
	if (wrapper.scanFloat(tmp))
	{
		normValue = (float)(tmp / 1000000.f);
		return true;
	}
	return false;
}