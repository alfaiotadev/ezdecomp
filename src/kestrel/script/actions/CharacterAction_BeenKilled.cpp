#include "kestrel/script/actions/CharacterAction_BeenKilled.h"

struct ApiCharacter {
    char pad[1648];
    unsigned long long pair;
    int field3;
};

struct SVarBool;

struct ScriptContext {
    template <typename T, typename U>
    void SetReturn(int, U);
};

__attribute__((visibility("hidden"))) short g_KillerIdValue;
__attribute__((visibility("hidden"))) short* g_pKillerId = &g_KillerIdValue;

ActionState CharacterAction_BeenKilled::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    unsigned long long pair;
    asm volatile("ldr %0, [%1, #1648]" : "=r"(pair) : "r"(pCharacter));

    int field3 = pCharacter->field3;
    int killerIdRaw = *(volatile int*)g_pKillerId;
    short killerId = (short)killerIdRaw;
    int field1 = (int)pair;
    int field2 = (int)(pair >> 32);

    bool eq1 = (killerId == field1);
    asm volatile("" ::: "memory");
    bool eq2 = (killerId == field2);
    bool result = (field1 != field3) ? eq1 : eq2;

    context.SetReturn<SVarBool, bool>(0, result);
    return ACTION_FINISHED;
}
