#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
//        group0[0]=0;group0[1]=1;group0[2]=4;group0[3]=5;group0[4]=7;group0[5]=9;group0[6]=10;
//    group1[0]=0;group1[1]=3;group1[2]=4;group1[3]=6;group1[4]=7;group1[5]=8;group1[6]=10;
//    group2[0]=0;group2[1]=2;group2[2]=3;group2[3]=5;group2[4]=8;group2[5]=9;group2[6]=10;
//    group3[0]=0;group3[1]=1;group3[2]=2;group3[3]=6;group3[4]=7;group3[5]=8;group3[6]=9;
    //Initialisation des variables
    startTicks = 0;
    pausedTicks = 0;
    for(int i=0;i<10;i++)
        lastActionTick[i] = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //On demarre le timer
    started = true;

    //On enlève la pause du timer
    paused = false;

    //On récupére le temps courant
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //On stoppe le timer
    started = false;

    //On enlève la pause
    paused = false;
}

int Timer::get_ticks()
{
    //Si le timer est en marche
    if( started == true )
    {
        //Si le timer est en pause
        if( paused == true )
        {
            //On retourne le nombre de ticks quand le timer a été mis en pause
            return pausedTicks;
        }
        else
        {
            //On retourne le temps courant moins le temps quand il a démarré
            return SDL_GetTicks() - startTicks;
        }
    }

    //Si le timer n'est pas en marche
    return 0;
}

void Timer::pause()
{
    //Si le timer est en marche et pas encore en pause
    if( ( started == true ) && ( paused == false ) )
    {
        //On met en pause le timer
        paused = true;

        //On calcul le pausedTicks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //Si le timer est en pause
    if( paused == true )
    {
        //on enlève la pause du timer
        paused = false;

        //On remet à zero le startTicks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Remise à zero du pausedTicks
        pausedTicks = 0;
    }
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

bool Timer::do_action(int track, int diff)
{
    if(get_ticks()-getLastActionTick(track)>diff)
    {
        lastActionTick[track]=get_ticks();
        return true;
    }
    else
    {
        return false;
    }
}
