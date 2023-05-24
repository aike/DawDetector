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


// normValue�𐮐��������������Ԃ�
void NoteNameParameter::toString(ParamValue normValue, String128 string) const
{
	tstrncpy(string, DawDetector::getNoteName((int)(normValue * 1000000.0)), maxLength_);
	string[maxLength_] = '\0';
	return;
}

// �C���^�t�F�[�X�Ƃ��ĕK�v�Ȃ����ŉ������Ȃ��BnormValue�ɂ͕֋X��0���i�[���ĕԂ�
bool NoteNameParameter::fromString(const TChar* string, ParamValue& normValue) const
{
	normValue = 0.0;
	return true;
}