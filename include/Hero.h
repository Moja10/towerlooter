#ifndef HERO_H
#define HERO_H

#include <Character.h>

class Hero : public Character
{
    public:
        void act();
        void step(int dir);

        Hero();
        virtual ~Hero();
    protected:
    private:
};

class Marauder : public Hero // str - based
{
    public:
        Marauder();
        virtual ~Marauder();
};

class Plunderer : public Hero // dex - based
{

};

class Brigand : public Hero // con - based
{

};

class ConArtist : public Hero // int - based
{

};

class Highwayman : public Hero // wis - based
{

};

class Swindler : public Hero // cha - based
{

};

class Privateer : public Hero // luk - based
{

};

#endif // HERO_H
