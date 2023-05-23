#include <tchar.h>

#include "public.sdk/source/vst/vstparameters.h"
#include "pluginterfaces/base/ustring.h"
#include "DawDetector.h"

DawDetector::DawID DawDetector::dawId_;
String128 DawDetector::hostString_;
String128 DawDetector::dawName_;
String128 DawDetector::noteName_;
DawDetector::NoteNameType DawDetector::noteNameType_;
int DawDetector::noteOffset_;

void DawDetector::initialize(FUnknown* context)
{
	IHostApplication* host;
	context->queryInterface(IHostApplication::iid, (void**)&host);

	host->getName(hostString_);
	dawName_[127] = '\0';
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

String128& DawDetector::getHostString(void)
{
	return hostString_;
}

String128& DawDetector::getDawName(void)
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

String128& DawDetector::getNoteName(const int notenumber)
{
	if (notenumber > 127) {
		strcpy16(noteName_, STR("-"));
		return noteName_;
	}

	int octave = (notenumber + noteOffset_) / 12;
	int note = notenumber % 12;

	char text[32];
	sprintf(text, "%s%d", noteNames[note], octave);
	Steinberg::UString(noteName_, 128).fromAscii(text);
	return noteName_;
}

int DawDetector::getNoteNumber(const tchar notename)
{
	return 0;
}

