#include "Leaderboard.hpp"

Text *tex[5];

Leaderboard::Leaderboard()
{
    SDL_StartTextInput();
    open();
}

void Leaderboard::open()
{
    file.open("database.txt");

    int counter = 0;

    cout << "sefs" << endl;

    while(getline(file, scores[counter]))
    {
        cout << scores[counter] << endl;

        tex[counter] = new Text();
        tex[counter]->set_color(255, 255, 255);
        tex[counter]->set_rect(SCREEN_WIDTH/2 - 100, 300 + counter*80, 200, 50);

        counter++;
    }

    cout << counter << endl;

    file.close();
}

void Leaderboard::update()
{
    while( SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_TEXTINPUT:
                name += e.text.text;
                break;
        }
    }
}

void Leaderboard::render()
{
    cout << name << endl;
    for(int i = 0; i < 5; i++)
    {
        tex[i]->Render(scores[i]);
    }
}