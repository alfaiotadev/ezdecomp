template <class T, bool B>
class NuSmartPtr;

class NuScene;
struct instNUGCUTSCENE;

NuSmartPtr<NuScene, true> (*NuCutSceneGetHGObj)(instNUGCUTSCENE*, int);

void NuSetGetHGObjFromIndxFn(NuSmartPtr<NuScene, true> (*fn)(instNUGCUTSCENE*, int)) {
    NuCutSceneGetHGObj = fn;
}
