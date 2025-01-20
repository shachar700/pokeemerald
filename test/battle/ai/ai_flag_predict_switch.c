#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI will predict use Pursuit on predicted switches")
{
    PASSES_RANDOMLY(5, 10, RNG_AI_PREDICT_SWITCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_PREDICT_SWITCH);
        PLAYER(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        PLAYER(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
        OPPONENT(SPECIES_TYRANITAR) { Moves(MOVE_PURSUIT, MOVE_CRUNCH); }
    } WHEN {
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_PURSUIT); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in Pursuit scenario")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_TYRANITAR) { Moves(MOVE_PURSUIT, MOVE_CRUNCH); }
        OPPONENT(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        OPPONENT(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
    } WHEN {
        TURN { MOVE(player, MOVE_PURSUIT); EXPECT_SWITCH(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI will predict switches with Wonder Guard")
{
    PASSES_RANDOMLY(5, 10, RNG_AI_PREDICT_SWITCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_PREDICT_SWITCH);
        PLAYER(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        PLAYER(SPECIES_SWELLOW) { Moves(MOVE_PECK); }
        OPPONENT(SPECIES_SHEDINJA) { Moves(MOVE_PURSUIT, MOVE_CRUNCH); }
    } WHEN {
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_PURSUIT); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in Wonder Guard scenario")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_SHEDINJA) { Moves(MOVE_PURSUIT, MOVE_CRUNCH); }
        OPPONENT(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SWELLOW) { Moves(MOVE_PECK); }
    } WHEN {
        TURN { MOVE(player, MOVE_PURSUIT); EXPECT_SWITCH(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI will use hit escape moves on predicted switches")
{
    PASSES_RANDOMLY(5, 10, RNG_AI_PREDICT_SWITCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_PREDICT_SWITCH);
        PLAYER(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        PLAYER(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
        OPPONENT(SPECIES_TYRANITAR) { Moves(MOVE_U_TURN, MOVE_CRUNCH); }
        OPPONENT(SPECIES_TYRANITAR) { Moves(MOVE_U_TURN, MOVE_CRUNCH); }
    } WHEN {
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_U_TURN); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in hit escape scenario")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_TYRANITAR) { Moves(MOVE_U_TURN, MOVE_CRUNCH); }
        PLAYER(SPECIES_TYRANITAR) { Moves(MOVE_U_TURN, MOVE_CRUNCH); }
        OPPONENT(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        OPPONENT(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
    } WHEN {
        TURN { EXPECT_SWITCH(opponent, 1); MOVE(player, MOVE_U_TURN); SEND_OUT(player, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: Considers ShouldSwitch and GetMostSuitableMonToSwitchInto from player's perspective")
{
    // Switching in trapper is an advanced feature of ShouldSwitch that requires GetMostSuitableMonToSwitchInto to also return a specific mon; this passing means the AI can use both in prediction
    PASSES_RANDOMLY(5, 10, RNG_AI_PREDICT_SWITCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_PREDICT_SWITCH);
        PLAYER(SPECIES_CACNEA) { Moves(MOVE_ABSORB); }
        PLAYER(SPECIES_DUGTRIO) { Ability(ABILITY_ARENA_TRAP); Moves(MOVE_ACROBATICS); }
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); Moves(MOVE_PURSUIT, MOVE_BITE); }
        OPPONENT(SPECIES_BRELOOM);
    } WHEN {
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_PURSUIT); }
        TURN { MOVE(player, MOVE_ACROBATICS); EXPECT_MOVE(opponent, MOVE_BITE); EXPECT_SEND_OUT(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in trapper-from-player's-perspective case")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_BRELOOM) { Speed(5); Ability(ABILITY_EFFECT_SPORE); Moves(MOVE_PURSUIT, MOVE_BITE); }
        PLAYER(SPECIES_BRELOOM) { Speed(5); }
        OPPONENT(SPECIES_CACNEA) { Speed(6); Moves(MOVE_ABSORB); }
        OPPONENT(SPECIES_DUGTRIO) { Speed(6); Ability(ABILITY_ARENA_TRAP); Moves(MOVE_ACROBATICS); }
    } WHEN {
        TURN { MOVE(player, MOVE_PURSUIT); EXPECT_SWITCH(opponent, 1); }
        TURN { EXPECT_MOVE(opponent, MOVE_ACROBATICS); MOVE(player, MOVE_BITE); SEND_OUT(player, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI can use Focus Punch on predicted switches")
{
    PASSES_RANDOMLY(5, 10, RNG_AI_PREDICT_SWITCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES | AI_FLAG_PREDICT_SWITCH);
        PLAYER(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        PLAYER(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
        OPPONENT(SPECIES_TYRANITAR) { Moves(MOVE_FOCUS_PUNCH, MOVE_BRICK_BREAK); }
    } WHEN {
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_FOCUS_PUNCH); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in Focus Punch scenario")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_SWITCHING | AI_FLAG_SMART_MON_CHOICES);
        PLAYER(SPECIES_TYRANITAR) { Moves(MOVE_FOCUS_PUNCH, MOVE_BRICK_BREAK); }
        OPPONENT(SPECIES_BRONZONG) { Moves(MOVE_PSYCHIC); }
        OPPONENT(SPECIES_CONKELDURR) { Moves(MOVE_HAMMER_ARM); }
    } WHEN {
        TURN { EXPECT_SWITCH(opponent, 1); MOVE(player, MOVE_FOCUS_PUNCH); }
    }
}

// This will be for a follow-up PR
TO_DO_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI will score against predicted incoming mon when switch predicted")
TO_DO_BATTLE_TEST("AI_FLAG_PREDICT_SWITCH: AI would switch out in predicted-incoming-mon scenario");
