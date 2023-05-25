//------------------------------------------------------------------------
// Copyright(c) 2023 aikelab.
//------------------------------------------------------------------------

#include "base/source/fstreamer.h"

#include "Nndcontroller.h"
#include "Nndcids.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "params.h"

#include "TextParameter.h"
#include "IntParameter.h"
#include "NoteNameParameter.h"
#include "../../DawDetector.h"

using namespace Steinberg;
using namespace Vst;

namespace aikelab {

//------------------------------------------------------------------------
// NoteNameDemoController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}


	// setup parameters
	auto* hoststringParam = new TextParameter(STR("HostName"), kHostStringId);
	parameters.addParameter(hoststringParam);
	auto* dawnameParam = new TextParameter(STR("DawName"), kDawNameId);
	parameters.addParameter(dawnameParam);
	auto* notenametypeParam = new TextParameter(STR("HostType"), kNoteNameTypeId);
	parameters.addParameter(notenametypeParam);
	auto* notenumberParam = new IntParameter(STR("NoteNumber"), kNoteNumberId);
	parameters.addParameter(notenumberParam);
	auto* notenameParam = new NoteNameParameter(STR("NoteName"), kNoteNameId);
	parameters.addParameter(notenameParam);

	DawDetector::initialize(context);
	
	// show hostname string
	hoststringParam->setText(DawDetector::getHostString());
	hoststringParam->setMaxLength(30);
	
	// show DAW name
	dawnameParam->setText(DawDetector::getDawName());
	dawnameParam->setMaxLength(30);

	// branch by DAW
	if (DawDetector::getDawId() == DawDetector::DawID::CUBASE) {
		// special process for Cubase
	}

	// branch by type
	switch (DawDetector::getNoteNameType()) {
	case DawDetector::NoteNameType::INTERNATIONAL:
		notenametypeParam->setText(STR("International type (C4=60)"));
		break;
	case DawDetector::NoteNameType::YAMAHA:
		notenametypeParam->setText(STR("Yamaha type (C4=72)"));
		break;
	case DawDetector::NoteNameType::FLSTUDIO:
		notenametypeParam->setText(STR("FL Studio type (C4=48)"));
		break;
	default:
		notenametypeParam->setText(STR("Unknown type (C4=60)"));
		break;
	}
	notenametypeParam->setMaxLength(30);

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API NoteNameDemoController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "Nndeditor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoController::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace aikelab
