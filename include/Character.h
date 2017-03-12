#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <curses.h>
#include "Inventory.h"

/** \file Character.h
 *
 * \brief Abstract parent class for all living things.
 *
 *
 *
 */


using std::string;

class Map;

class Character
{
    public:

        // character information

        int x, y;             // position
        Map * owner;
        Inventory inv;
        char icon;
        short color;
        chtype effect;

        // visible stats

        short hitpoints_max;   // maximum amount of hitpoints
        short hitpoints;       // current amount of hitpoints
        short alignment;
        string name;
        string class_name;   // name of class (humanoid, lich, canine, etc.)
        string species_name; // name of species (hobbit, demilich, little dog, etc.)

        // seven major stats

        short stat_str_max;
        short stat_str;
        short stat_dex_max;
        short stat_dex;
        short stat_con_max;
        short stat_con;
        short stat_int_max;
        short stat_int;
        short stat_wis_max;
        short stat_wis;
        short stat_cha_max;
        short stat_cha;
        short stat_luk_max;
        short stat_luk;

        // hidden stats

        short speed;           // number of move tokens needed to attemp an action
        short tokens;           // current number of move tokens accumulated
        short energy_max;      // maximum amount of energy
        short energy;          // current amount of energy
        short encumbrance;
        short size;
        short protection;

        // resistances

        short res_acid;
        short res_cold;
        short res_confusion;
        short res_disentigration;
        short res_drain;
        short res_fire;
        short res_hallucination;
        short res_magic;
        short res_petrification;
        short res_poison;
        short res_shock;
        short res_sickness;
        short res_sleep;

        // flags

        bool flag_regenerate;
        bool flag_see_invisible;
        bool flag_invisible;
        bool flag_teleport;
        bool flag_teleport_control;
        bool flag_polymorph;
        bool flag_polymorph_control;
        bool flag_levitate;
        bool flag_stealth;
        bool flag_protection;  // only determines whether or not the character has protection. Actual protection value stored in short _protection.
        bool flag_unbreathing;
        bool flag_amphibious;
        bool flag_infravision;
        bool flag_reflect;
        bool flag_lifesaved;
        bool flag_phasing;
        bool flag_displaced;
        bool flag_energy_regenerate;
        bool flag_half_magic_dmg;
        bool flag_half_phys_dmg;
        bool flag_flying;

        // flags with timeouts

        bool flag_stunned;
        short timeout_stunned = -1;
        bool flag_confused;
        short timeout_confused = -1;
        bool flag_blind;
        short timeout_blind = -1;
        bool flag_sleepy;
        short timeout_sleepy = -1;
        bool flag_paralyzed;
        short timeout_paralyzed = -1;
        bool flag_hallucinating;
        short timeout_hallucinating = -1;
        bool flag_invulnerable;
        short timeout_invulnerable = -1;
        bool flag_detect_monsters;
        short timeout_detect_monsters = -1;

        // flags with deadly timeouts

        bool flag_sick;
        short timeout_sick = -1;
        bool flag_slimed;
        short timeout_slimed = -1;
        bool flag_strangled;
        short timeout_strangled = -1;
        bool flag_petrified;
        short timeout_petrified = -1;

        // monster flags

        bool mf_acidic;
        bool mf_amorphous;
        bool mf_animal;
        bool mf_carnivore;
        bool mf_covetous;
        bool mf_demonic;
        bool mf_divisive;
        bool mf_elven;
        bool mf_follower;
        bool mf_greedy;
        bool mf_growing;
        bool mf_has_head;
        bool mf_herbivore;
        bool mf_hiding;
        bool mf_human;
        bool mf_humanoid;
        bool mf_scared;
        bool mf_inediate;
        bool mf_kebabable;
        bool mf_metallivore;
        bool mf_nasty;
        bool mf_oviparous;
        bool mf_peaceful;
        bool mf_poisonous;
        bool mf_sessile;
        bool mf_thickskinned;
        bool mf_undead;
        bool mf_solid;
        bool mf_whirly;

        //character functions

        virtual void act() = 0;
        virtual void step(int dir);

        Character();
        virtual ~Character();
    protected:
    private:
};

#endif // CHARACTER_H
