// MIT License
#pragma once

#include "public.sdk/source/vst/vstcomponentbase.h"

using namespace Steinberg;
using namespace Vst;

class DawDetector
{
public:
	enum class DawID {
		UNKNOWN,
		VST3TESTHOST,
		CUBASE,
		LIVE,
		BITWIG,
		FLSTUDIO,
		MAX,
		REAPER,
		CAKEWALK,
		ACID,
	};

	enum class NoteNameType {
		UNKNOWN,
		INTERNATIONAL,
		YAMAHA,
		FLSTUDIO,
	};

	static void initialize(FUnknown* context);
	static TChar* getHostString(void);
	static TChar* getDawName(void);
	static DawDetector::DawID getDawId(void);
	static NoteNameType getNoteNameType(void);
	static TChar* getNoteName(const int notenumber);
	static int getNoteNumber(const TChar* notename);
	static inline const TChar* dawNames[] = {
		STR("Unknown"),
		STR("VST3 Test Host"),
		STR("Cubase"),
		STR("Live"),
		STR("Bitwig Studio"),
		STR("FL Studio"),
		STR("Max"),
		STR("REAPER"),
		STR("Cakewalk"),
		STR("ACID")
	};
	static inline const NoteNameType noteNameTypes[] = {
		NoteNameType::UNKNOWN,
		NoteNameType::YAMAHA,			// VST3 Test Host
		NoteNameType::YAMAHA,			// Cubase
		NoteNameType::YAMAHA,			// Live
		NoteNameType::YAMAHA,			// Bitwig
		NoteNameType::FLSTUDIO,			// FL Studio
		NoteNameType::INTERNATIONAL,	// Max  60=C3 MIDI / 60=C4 MIDI(C4)
		NoteNameType::INTERNATIONAL,	// REAPER
		NoteNameType::FLSTUDIO,			// Cakewalk
		NoteNameType::FLSTUDIO,			// ACID
	};
	static inline const char* noteNames[] = {
		"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
	};
protected:
	static DawID dawId_;
	static TChar hostString_[];
	static TChar dawName_[];
	static TChar noteName_[];
	static NoteNameType noteNameType_;
	static int noteOffset_;
};

