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

// メンバ変数text_に文字列textを格納する
void TextParameter::setText(String128 text)
{
	strncpy16(text_, text, 127);
	text_[127] = '\0';
}

// 表示上の都合を考慮して、出力時の最大文字列長を設定する
void TextParameter::setMaxLength(int maxLength)
{
	maxLength_ = maxLength;
}

// 引数normValueは無視、メンバ変数text_の値を返す
void TextParameter::toString(ParamValue normValue, String128 string) const
{
	strncpy16(string, text_, maxLength_);
	string[maxLength_] = '\0';
	return;
}

// インタフェースとして必要なだけで何もしない。normValueには便宜上0を格納して返す
bool TextParameter::fromString(const TChar* string, ParamValue& normValue) const
{
	normValue = 0.0;
	return true;
}