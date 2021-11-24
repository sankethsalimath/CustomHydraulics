#include "DCV_6_3.hpp"

#include "ComponentEssentials.h"
using namespace hopsan;

extern "C" DLLEXPORT void register_contents(ComponentFactory* pComponentFactory , NodeFactory*, pNodeFactory)
{
    pComponentFactory->registerCreatorFunction("DirectionControlValve_6_3", DirectionControlValve_6_3::Creator);

    HOPSAN_UNUSED(pNOdeFactory)
}

extern "C" DLLEXPORT void get_hopsan_info(...)
{
    pHopsanExternalLibInfo->libName = (char*)"CustomHydraulics";
    pHopsanExternalLibInfo->hopsanCoreVersion = (char*)hopsanCoreVersion;
    pHopsanExternalLibInfo->libCompiledDebugRelease = (char*)HOPSAN_BUILD_TYPE_STR;
}
