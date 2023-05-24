#include <tchar.h>

#include "public.sdk/source/vst/vstparameters.h"
#include "pluginterfaces/base/ustring.h"
#include "DawDetector.h"

DawDetector::DawID DawDetector::dawId_;
TChar DawDetector::hostString_[64];
TChar DawDetector::dawName_[64];
TChar DawDetector::noteName_[16];
DawDetector::NoteNameType DawDetector::noteNameType_;
int DawDetector::noteOffset_;

void DawDetector::initialize(FUnknown* context)
{
	IHostApplication* host;
	context->queryInterface(IHostApplication::iid, (void**)&host);

	host->getName(hostString_);
	dawName_[63] = '\0';
	dawId_ = DawID::UNKNOWN;
	noteNameType_ = NoteNameType::UNKNOWN;
	if (strcmp16(hostString_, STR("VST3PluginTestHost Standalone")) == 0) {
		dawId_ = DawID::VST3TESTHOST;
	}
	else if (strcmp16(hostString_, STR("Cubase")) == 0) {
		dawId_ = DawID::CUBASE;
	}
	else if (strncmp16(hostString_, STR("Ableton Live"), 12) == 0) {
		dawId_ = DawID::LIVE;
	}
	else if (strcmp16(hostString_, STR("Bitwig Studio")) == 0) {
		dawId_ = DawID::BITWIG;
	}
	else if (strcmp16(hostString_, STR("Fruity Wrapper")) == 0) {
		dawId_ = DawID::FLSTUDIO;
	}
	else if (strcmp16(hostString_, STR("Max")) == 0) {
		dawId_ = DawID::MAX;
	}
	else if (strcmp16(hostString_, STR("REAPER")) == 0) {
		dawId_ = DawID::REAPER;
	}
	else if (strcmp16(hostString_, STR("Cakewalk")) == 0) {
		dawId_ = DawID::CAKEWALK;
	}
	else if (strcmp16(hostString_, STR("sfvstisynth")) == 0) { // ACID VST Instrument
		dawId_ = DawID::ACID;
	}
	else if (strcmp16(hostString_, STR("sfvstwrap")) == 0) {   // ACID VST Fx
		dawId_ = DawID::ACID;
	}

	strncpy16(dawName_, dawNames[(int)dawId_], 127);
	noteNameType_ = noteNameTypes[(int)dawId_];
	switch (noteNameType_) {
	case NoteNameType::INTERNATIONAL:
		noteOffset_ = -12;
		break;
	case NoteNameType::YAMAHA:
		noteOffset_ = -24;
		break;
	case NoteNameType::FLSTUDIO:
		noteOffset_ = 0;
		break;
	default:
		noteOffset_ = -12;
		break;
	}
}

TChar* DawDetector::getHostString(void)
{
	return hostString_;
}

TChar* DawDetector::getDawName(void)
{
	return dawName_;
}

DawDetector::DawID DawDetector::getDawId(void)
{
	return DawDetector::dawId_;
}

DawDetector::NoteNameType DawDetector::getNoteNameType(void)
{
	return noteNameType_;
}

TChar* DawDetector::getNoteName(const int notenumber)
{
	if (notenumber > 127) {
		tstrcpy(noteName_, STR("-"));
		return noteName_;
	}

	int octave = (notenumber + noteOffset_) / 12;
	int note = notenumber % 12;

	char text[16];
	sprintf(text, "%s%d", noteNames[note], octave);
	Steinberg::UString(noteName_, 16).fromAscii(text);
	return noteName_;
}

int DawDetector::getNoteNumber(const TChar* notename)
{
	int note = 0;
	int oct = 0;
	int oct_sign = 1;
	int noteno;

	const TChar* p = notename;
	enum class State {
		NOTE1,
		NOTE2,
		OCT,
		END
	};
	State st = State::NOTE1;

	while (st != State::END) {
		switch (st) {
		case State::NOTE1:
			switch (*p) {
			case ' ':
				break;
			case 'c':
			case 'C':
				note = 0;
				st = State::NOTE2;
				break;
			case 'd':
			case 'D':
				note = 2;
				st = State::NOTE2;
				break;
			case 'e':
			case 'E':
				note = 4;
				st = State::NOTE2;
				break;
			case 'f':
			case 'F':
				note = 5;
				st = State::NOTE2;
				break;
			case 'g':
			case 'G':
				note = 7;
				st = State::NOTE2;
				break;
			case 'a':
			case 'A':
				note = 9;
				st = State::NOTE2;
				break;
			case 'b':
			case 'B':
				note = 11;
				st = State::NOTE2;
				break;
			default:
				return -1;
			}
			break;

		case State::NOTE2:
			switch (*p) {
			case ' ':
				break;
			case '#':
				note++;
				break;
			case 'b':
				note--;
				break;
			case '-':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				p--;
				st = State::OCT;
				break;
			default:
				return -1;
			}
			break;

		case State::OCT:
			switch (*p) {
			case ' ':
			case '\0':
				st = State::END;
				break;
			case '-':
				oct_sign = -1;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				oct = (oct * 10) + (*p - '0');
				break;
			default:
				return -1;
			}
			break;

		default:
			break;
		}

		p++;
	}

	noteno = -noteOffset_ + (oct_sign * oct * 12) + note;

	if ((noteno < 0) || (noteno > 127)) {
		return -1;
	}

	return noteno;
}

