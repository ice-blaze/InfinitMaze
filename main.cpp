#include <iostream>

#include <SDL.h>
#include "Fonct_Main.h"
#include "Timer.h"

#include "Maze.hpp"


using namespace std;

int main(int argc, char **argv)
{
    double gridW=15;double gridH=15;
    Maze theMaze(gridW,gridH);
    vector<vector<double> > grid = theMaze.getGrid();

    //------------------------------------------------------------------------------------------------------

    //constante
    int SCREEN_WIDTH = theMaze.getGridWidth()*32;
    int SCREEN_HEIGHT = theMaze.getGridHeight()*32;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    SDL_Surface* surfP[12];
    surfP[0] = load_image("sprite/0.png");
    surfP[1] = load_image("sprite/1.png");
    surfP[2] = load_image("sprite/2.png");
    surfP[3] = load_image("sprite/3.png");
    surfP[4] = load_image("sprite/4.png");
    surfP[5] = load_image("sprite/5.png");
    surfP[6] = load_image("sprite/6.png");
    surfP[7] = load_image("sprite/7.png");
    surfP[8] = load_image("sprite/8.png");
    surfP[9] = load_image("sprite/9.png");
    surfP[10] = load_image("sprite/10.png");

    Timer fps;
    // program main loop
    bool done = false;

    SDL_WM_SetCaption("ESC to quite | any key press to regenerate the maze",NULL);

    while (!done)
    {
        fps.start();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keypresses
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE){done = true;}
                    // exit if ESCAPE is pressed
                    theMaze.newGrid(gridW,gridH);
                    grid = theMaze.getGrid();
                    if (event.key.keysym.sym == SDLK_ESCAPE)
//                        done = true;
                    break;
            }
        }

        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

        int w = surfP[0]->w;
        int h = surfP[0]->h;
        for (double i=0;i<theMaze.getGridWidth();i++)
        {
            for (double j=0;j<theMaze.getGridHeight();j++)
            {
                if((int)grid[i][j]>=0)
                    apply_surface(j*w,i*h,surfP[(int)grid[i][j]],screen,NULL);
            }
        }
        SDL_Flip(screen);

    }

   // free loaded bitmap
    SDL_FreeSurface(screen);
    //SDL_FreeSurface(surfP[0]);



    //------------------------------------------------------------------------------------------------------

    //show the grid
    //const vector<vector<double> > grid = theMaze.getGrid();
    for (double i=0;i<theMaze.getGridWidth();i++)
    {
    	for (double j=0;j<theMaze.getGridHeight();j++)
    	{
    	    double temp = grid[i][j];
    	    if(temp<10)
                cout<<"0";

            cout<<temp<<" ";
    	}
    	cout<<endl;
    }



    return 0;
}

