#include "TextParameter.h"
#include "pluginterfaces/base/ustring.h"



TextParameter::TextParameter(TChar* title, int32 id)
{
	strcpy16(text_, STR16(""));

	UString(info.title, str16BufferSize(String128)).assign(title);
	info.flags = ParameterInfo::kCanAutomate;
	info.id = id;
	info.stepCount = 0;
	info.defaultNormalizedValue = 0.f;
	info.unitId = kRootUnitId;

	setNormalized(1.f);
}

// �����o�ϐ�text_�ɕ�����text���i�[����
void TextParameter::setText(String128 text)
{
	strncpy16(text_, text, 127);
	text_[127] = '\0';
}

// �\����̓s�����l�����āA�o�͎��̍ő啶���񒷂�ݒ肷��
void TextParameter::setMaxLength(int maxLength)
{
	maxLength_ = maxLength;
}

// ����normValue�͖����A�����o�ϐ�text_�̒l��Ԃ�
void TextParameter::toString(ParamValue normValue, String128 string) const
{
	strncpy16(string, text_, maxLength_);
	string[maxLength_] = '\0';
	return;
}

// �C���^�t�F�[�X�Ƃ��ĕK�v�Ȃ����ŉ������Ȃ��BnormValue�ɂ͕֋X��0���i�[���ĕԂ�
bool TextParameter::fromString(const TChar* string, ParamValue& normValue) const
{
	normValue = 0.0;
	return true;
}