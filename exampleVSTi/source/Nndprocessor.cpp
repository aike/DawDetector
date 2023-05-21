//------------------------------------------------------------------------
// Copyright(c) 2023 aikelab.
//------------------------------------------------------------------------

#include "Nndprocessor.h"
#include "Nndcids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/hosting/eventlist.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

#include "params.h"

using namespace Steinberg;

namespace aikelab {
//------------------------------------------------------------------------
// NoteNameDemoProcessor
//------------------------------------------------------------------------

NoteNameDemoProcessor::NoteNameDemoProcessor()
{
	//--- set the wanted controller for our processor
	setControllerClass(kNoteNameDemoControllerUID);
}

//------------------------------------------------------------------------
NoteNameDemoProcessor::~NoteNameDemoProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    /*if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
				}
			}
		}
	}*/
	
	//--- Here you have to implement your processing
	int32 index, index2;
	Vst::ParamValue paramval;
	Vst::IEventList* events = data.inputEvents;
	Vst::IParameterChanges* outParamChanges = data.outputParameterChanges;
	Vst::IParamValueQueue* paramQueue;

	if (events != NULL)
	{
		int32 numEvent = events->getEventCount();
		for (int32 i = 0; i < numEvent; i++)
		{
			Vst::Event event;
			if (events->getEvent(i, event) == kResultOk)
			{
				switch (event.type)
				{
				case Vst::Event::kNoteOnEvent:
					paramval = intToParamValue(event.noteOn.pitch);
					paramQueue = outParamChanges->addParameterData(kNoteNumberId, index);
					if (paramQueue)
					{
						paramQueue->addPoint(0, paramval, index2);
					}
					paramQueue = outParamChanges->addParameterData(kNoteNameId, index);
					if (paramQueue)
					{
						paramQueue->addPoint(0, paramval, index2);
					}
					break;
				case Vst::Event::kNoteOffEvent:
					paramval = intToParamValue(999);
					paramQueue = outParamChanges->addParameterData(kNoteNumberId, index);
					if (paramQueue)
					{
						paramQueue->addPoint(0, paramval, index2);
					}
					paramQueue = outParamChanges->addParameterData(kNoteNameId, index);
					if (paramQueue)
					{
						paramQueue->addPoint(0, paramval, index2);
					}
					break;
				}
			}
		}
	}


	// èoóÕÇÉ[ÉçÉNÉäÉA
	uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
	void** out = getChannelBuffersPointer(processSetup, data.outputs[0]);
	memset(out[0], 0, sampleFramesSize);
	memset(out[1], 0, sampleFramesSize);
	data.outputs[0].silenceFlags = 0b11;

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue;

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NoteNameDemoProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace aikelab
