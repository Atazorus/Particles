/*   This project is created by Atazorus.
     You can use this project for every purpose (including commercial and personal projects).
     Feel free to use!!!
*/


#include <iostream>
#include "particle.hpp"

using namespace std;
using namespace sf;
using namespace particle;

#define TOTALX 1300
#define TOTALY 700


inline float calc_distance(Vector2f pos,Vector2f target)
{
    return (pos.x-target.x)*(pos.x-target.x)+(pos.y-target.y)*(pos.y-target.y);
}

int main()
{
    srandom(time(NULL));

    const int amount=rand()%50;   /// Maximum particle types
    const int number=rand()%1250; /// Maximum particle amount
    Particle *particles[number];

    Color colors[amount];
    float behaviours[amount][amount];

    for(int i=0;i<amount;i++)
    {
        int a=rand()%255;
        int b=rand()%255;
        int c=rand()%255;
        colors[i]=Color(a,b,c);
        for(int j=0;j<amount;j++)
        {
            behaviours[i][j]=rand()/(float)RAND_MAX*(3 - -3) + -3;
        }
    }



    for(int i=0;i<number;i++) // Initialize the particles.
    {
        particles[i]=new Particle;
        short myrand=rand() % 3;

        particles[i]->type=myrand;
        particles[i]->color=colors[myrand];

        particles[i]->position=Vector2f(rand()%TOTALX,rand()%TOTALY);
    }

    RenderWindow* window=new RenderWindow(VideoMode(TOTALX,TOTALY+38),"Particles");


    window->setFramerateLimit(60);

    Event ev;


    while(window->isOpen())
    {

        while(window->pollEvent(ev))
        {
        if(ev.type==Event::Closed)
        {
            window->close();
        }

        }
        window->clear();
        for(int i=0;i<number;i++)
        {
            for(int j=0;j<number;j++)
            {
                if(i!=j)
                {
                    Vector2f pos=particles[i]->position;
                    Vector2f tar=particles[j]->position;


                    float distance=calc_distance(pos,tar)/1000+0.1;

                    float val=behaviours[particles[i]->type][particles[j]->type]/distance;

                    Vector2f translate=Vector2f(val,val);

                    if(pos.x>tar.x)
                    {
                        translate.x=-translate.x;
                    }

                    if(pos.y>tar.y)
                    {
                        translate.y=-translate.y;
                    }


                    if(pos.x>TOTALX)
                    {
                        particles[i]->position=Vector2f(TOTALX,pos.y);
                    }
                    if(pos.x<0)
                    {
                        particles[i]->position=Vector2f(0,pos.y);
                    }

                    if(pos.y>TOTALY)
                    {
                        particles[i]->position=Vector2f(pos.x,TOTALY);
                    }
                    if(pos.y<0)
                    {
                        particles[i]->position=Vector2f(pos.x,0);
                    }


                    particles[i]->position+=translate;
                }
            }

            CircleShape cir;
            cir.setPosition(particles[i]->position);
            cir.setRadius(3);
            cir.setFillColor(particles[i]->color);
            window->draw(cir);
        }

        window->display();

    }
    for(long unsigned int i=0;i<number;i++)
    {
        delete particles[i];
    }
    delete window;

    return 0;
}
