#include "kestrel/script/actions/SAction_EnablePursueFromTraffic.h"

const char* SAction_EnablePursueFromTraffic::GetName() const {
    return "EnablePursueFromTraffic";
}

void SAction_EnablePursueFromTraffic::GetOutputs(SCmdParams& params) const {
    if (params.m_CurrentParamIndex < 0) {
        params.m_CurrentParamIndex = 0;
    }
}
