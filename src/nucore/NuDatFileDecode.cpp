#include "nucore/NuDatFileDecode.h"

struct DecodeFileContext;

class DecodeManager {
public:
    void CloseFile(DecodeFileContext* ctx);
};

__attribute__((visibility("hidden"))) DecodeManager* g_pDecodeManager;

void NuDatFileDecodeCloseFile(DecodeFileContext* ctx) {
    g_pDecodeManager->CloseFile(ctx);
}
