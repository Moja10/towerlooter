#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller
{
    public:
        Controller();
        virtual ~Controller();
    protected:
    private:
};

class Hero : Controller
{
    static short luck;

    static bool _flag_searching;
    static bool _flag_conflict;
    static bool _flag_hunger;
    static bool _flag_warning;
    static bool _flag_telepathy;
    static bool _flag_jumping;
    static bool _flag_adorned;
    static bool _flag_fumbling;
    static bool _flag_clairvoyant;
    static bool _flag_slow_digestion;
    static bool _flag_unchanging;
    static bool _flag_sustain_ability;
    static bool _flag_free_action;
    static bool _flag_waterwalking;
};

class Enemy : Controller
{

};

#endif // CONTROLLER_H
