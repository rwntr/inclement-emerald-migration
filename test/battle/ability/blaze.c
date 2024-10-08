#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Blaze boosts Fire-type moves in a pinch", s16 damage)
{
    u16 hp;
    u16 ability;

    PARAMETRIZE { ability = ABILITY_SHIELD_DUST; hp = 33; }
    PARAMETRIZE { ability = ABILITY_BLAZE; hp = 33; }

    GIVEN {
        ASSUME(gMovesInfo[MOVE_EMBER].type == TYPE_FIRE);
        PLAYER(SPECIES_CHARMANDER) { Ability(ability); MaxHP(99); HP(hp); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Blaze boosts Fire-type moves outside of pinch", s16 damage)
{
    u16 hp;
    u16 ability;

    PARAMETRIZE {ability = ABILITY_SHIELD_DUST; hp = 33; }
    PARAMETRIZE {ability = ABILITY_BLAZE; hp = 99; }

    GIVEN {
        ASSUME(gMovesInfo[MOVE_EMBER].type == TYPE_FIRE);
        PLAYER(SPECIES_CHARMANDER) { Ability(ability); MaxHP(99); HP(hp); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.2), results[1].damage);
    }
}