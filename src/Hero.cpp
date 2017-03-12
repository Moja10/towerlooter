#include "Hero.h"
#include <curses.h>
#include "Tile.h"

Hero::Hero()
{
    icon = '@';
    effect = COLOR_PAIR(16)|WA_BLINK;

    hitpoints_max = 10;   // maximum amount of hitpoints
    hitpoints = 10;       // current amount of hitpoints
    alignment = 0;
    name = "Player";
    class_name = "Hero";   // name of class (humanoid, lich, canine, etc.)
    species_name = ""; // name of species (hobbit, demilich, little dog, etc.)

    // seven major stats

    stat_str_max = 32;
    stat_str = 0;
    stat_dex_max = 32;
    stat_dex = 0;
    stat_con_max = 32;
    stat_con = 0;
    stat_int_max = 32;
    stat_int = 0;
    stat_wis_max = 32;
    stat_wis = 0;
    stat_cha_max = 32;
    stat_cha = 0;
    stat_luk_max = 32;
    stat_luk = 0;

    // hidden stats

    speed = 12;           // number of move tokens needed to attemp an action
    tokens = 0;           // current number of move tokens accumulated
    energy_max = 0;      // maximum amount of energy
    energy = 0;          // current amount of energy
    encumbrance = 0;
    size = 3;
    protection = 0;

    // resistances

    res_acid = 0;
    res_cold = 0;
    res_confusion = 0;
    res_disentigration = 0;
    res_drain = 0;
    res_fire = 0;
    res_hallucination = 0;
    res_magic = 0;
    res_petrification = 0;
    res_poison = 0;
    res_shock = 0;
    res_sickness = 0;
    res_sleep = 0;

    // flags

    flag_regenerate = false;
    flag_see_invisible = false;
    flag_invisible = false;
    flag_teleport = false;
    flag_teleport_control = false;
    flag_polymorph = false;
    flag_polymorph_control = false;
    flag_levitate = false;
    flag_stealth = false;
    flag_protection = false;  // only determines whether or not the character has protection. Actual protection value stored in short _protection.
    flag_unbreathing = false;
    flag_amphibious = false;
    flag_infravision = false;
    flag_reflect = false;
    flag_lifesaved = false;
    flag_phasing = false;
    flag_displaced = false;
    flag_energy_regenerate = false;
    flag_half_magic_dmg = false;
    flag_half_phys_dmg = false;
    flag_flying = false;

    // flags with timeouts

    flag_stunned = false;
    timeout_stunned = -1;
    flag_confused = false;
    timeout_confused = -1;
    flag_blind = false;
    timeout_blind = -1;
    flag_sleepy = false;
    timeout_sleepy = -1;
    flag_paralyzed = false;
    timeout_paralyzed = -1;
    flag_hallucinating = false;
    timeout_hallucinating = -1;
    flag_invulnerable = false;
    timeout_invulnerable = -1;
    flag_detect_monsters = false;
    timeout_detect_monsters = -1;

    // flags with deadly timeouts

    flag_sick = false;
    timeout_sick = -1;
    flag_slimed = false;
    timeout_slimed = -1;
    flag_strangled = false;
    timeout_strangled = -1;
    flag_petrified = false;
    timeout_petrified = -1;

    // monster flags

    mf_acidic = false;
    mf_amorphous = false;
    mf_animal = false;
    mf_carnivore = true;
    mf_covetous = false;
    mf_demonic = false;
    mf_divisive = false;
    mf_elven = false;
    mf_follower = false;
    mf_greedy = false;
    mf_growing = false;
    mf_has_head = true;
    mf_herbivore = true;
    mf_hiding = false;
    mf_human = true;
    mf_humanoid = true;
    mf_scared = false;
    mf_inediate = false;
    mf_kebabable = false;
    mf_metallivore = false;
    mf_nasty = false;
    mf_oviparous = false;
    mf_peaceful = false;
    mf_poisonous = false;
    mf_sessile = false;
    mf_thickskinned = false;
    mf_undead = false;
    mf_solid = true;
    mf_whirly = false;
}

void Hero::act()
{
    char c = getch();
    if (c > 48 && c < 58 && c != '5')
        step(c - 48);
    if (c == '.')
        step(5);
}

void Hero::step(int dir)
{
    int pos_x = x;
    int pos_y = y;
    Map * m = owner;
    int x_dir = dir % 3;
    int y_dir = (dir - 1) / 3;
    switch(x_dir)
    {
    case 1:
        pos_x -= 1;
        break;
    case 2:
        break;
    case 0:
        pos_x += 1;
        break;
    }
    switch(y_dir)
    {
    case 2:
        pos_y -= 1;
        break;
    case 1:
        break;
    case 0:
        pos_y += 1;
        break;
    }
    if (!m->tiles[pos_y][pos_x].is_wall())
    {
        m->tiles[y][x].occupant = nullptr;
        m->tiles[pos_y][pos_x].occupant = this;
        this->x = pos_x;
        this->y = pos_y;
    }
}

Hero::~Hero()
{
    //dtor
}

Marauder::Marauder()
{
    Hero();
    class_name = "Marauder";
}

Marauder::~Marauder()
{

}
