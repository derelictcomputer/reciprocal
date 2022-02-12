#include <pluginterfaces/vst/ivstaudioprocessor.h>
#include "public.sdk/source/main/pluginfactory.h"
#include "plugcontroller.h"	// for createInstance
#include "plugprocessor.h"	// for createInstance
#include "plugids.h"			// for uids
#include "version.h"			// for version and naming

BEGIN_FACTORY_DEF (stringCompanyName, stringCompanyWeb,	stringCompanyEmail)

    DEF_CLASS2 (INLINE_UID_FROM_FUID(dc::euclid::EuclidProcId),
                PClassInfo::kManyInstances,	// cardinality
                kVstAudioEffectClass,	// the component category (do not changed this)
                stringPluginName "Fx",		// here the plug-in name (to be changed)
                Vst::kDistributable,	// means that component and controller could be distributed on different computers
                Vst::PlugType::kFx,		// Subcategory for this plug-in (to be changed)
                FULL_VERSION_STR,		// Plug-in version (to be changed)
                kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
                dc::euclid::PlugProcessor::createInstance)	// function pointer called when this component should be instantiated

    DEF_CLASS2 (INLINE_UID_FROM_FUID(dc::euclid::EuclidControllerId),
                PClassInfo::kManyInstances,  // cardinality
                kVstComponentControllerClass,// the Controller category (do not changed this)
                stringPluginName "Controller",	// controller name (could be the same than component name)
                0,						// not used here
                "",						// not used here
                FULL_VERSION_STR,		// Plug-in version (to be changed)
                kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
                dc::euclid::PlugController::createInstance)// function pointer called when this component should be instantiated

END_FACTORY
