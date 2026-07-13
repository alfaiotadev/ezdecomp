#include "kestrel/script/actions/CharacterAction_Stop.h"

struct Brain {
    enum TaskPriority : int {
        kStop = 4,
    };
    void ClearTasks(TaskPriority);
};

struct ApiCharacter {
    char pad[88];
    Brain* brain;
};

const char* CharacterAction_Stop::GetName() const {
    return "Character_Stop";
}

ActionState CharacterAction_Stop::CharacterExec(ApiCharacter* pCharacter, ScriptContext& context) {
    pCharacter->brain->ClearTasks(Brain::kStop);
    return ACTION_FINISHED;
}

void CharacterAction_Stop::GetOutputs(SCmdParams& params) const {
    params.SanityCheck();
}
