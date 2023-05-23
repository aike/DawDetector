DAW Detector
---

## Description
DAW detection utility for VST plugin

## Example

```cpp
//
// YourVSTController.cpp
//
#include "DawDetector.h"

// (snip)

tresult PLUGIN_API YourVSTController::initialize (FUnknown* context)
{
  // Here the Plug-in will be instantiated

  //---do not forget to call parent ------
  tresult result = EditControllerEx1::initialize (context);
  if (result != kResultOk)
  {
    return result;
  }

  // (snip)

  DawDetector::initialize(context); // initialize and detection

  DawDetector::getHostString();     // return hostname string
  DawDetector::getDawName();        // return DAW name
  DawDetector::getNoteName(60);     // return note name of note number 60

  // branch by DAW
  if (DawDetector::getDawId() == DawDetector::DawID::CUBASE) {
    // special process for Cubase
  }

  // branch by type
  switch (DawDetector::getNoteNameType()) {
  case DawDetector::NoteNameType::INTERNATIONAL:
    // International type (C4=60)
    break;
  case DawDetector::NoteNameType::YAMAHA:
    // Yamaha type (C4=72)
    break;
  case DawDetector::NoteNameType::FLSTUDIO:
    // FL Studio type (C4=48)
    break;
  default:
    // Unknown type (C4=60)
    break;
  }

  return result;
}
```

## License
DAW Detector is licensed under MIT License.  
Copyright 2023, aike (@aike1000)  
