#include "Leaderboard.hpp"
#include <bits/stdc++.h>

Text *tex[5];
Text *enter_name;
Text *tex_name;

Leaderboard::Leaderboard()
{
    SDL_StartTextInput();
    enter_name = new Text();
    tex_name = new Text();

    enter_name->set_color(255, 255, 255);
    enter_name->set_rect(SCREEN_WIDTH/2 - 100, 400, 200, 50);

    tex_name->set_color(255, 255, 255);
    tex_name->set_rect(SCREEN_WIDTH/2 - 100, 450, 15, 50);
}

Leaderboard::~Leaderboard()
{
    enter_name = NULL;
    tex_name = NULL;
    delete enter_name;
    delete tex;
    delete tex_name;
}

void Leaderboard::open()
{
    file.open("database.txt");

    int counter = 0;

    while(getline(file, scores[counter]))
    {
        tex[counter] = new Text();
        tex[counter]->set_color(255, 255, 255);
        tex[counter]->set_rect(SCREEN_WIDTH/2 - 100, 300 + counter*80, 15 * scores[counter].length(), 50);

        counter++;
        if(counter > 4)
            break;
    }

    file.close();
}

void Leaderboard::sort()
{
    map <string, int> m;
    string s;

    file.open("database.txt");
    while(getline(file, s))
    {
        string temp = s.substr(0, s.find(":") - 1);
        int sc = stoi(s.substr(s.find(":") + 1, s.length()));
        m.insert({temp, sc});
    }

    file.close();

    vector<pair<string, int>> v;
 
    copy(m.begin(), m.end(), back_inserter<vector<pair<string, int>>>(v));

    std::sort(v.begin(), v.end(),

            [](const pair<string, int> &l, const pair<string, int> &r)
            {
                if (l.second != r.second) {
                    return l.second > r.second;
                }
 
                return l.first > r.first;
            });

    file.open("database.txt", ios::out);

    file << v[0].first << " : " << v[0].second;

    for(int i = 1; i < v.size(); i++)
    {
        file << "\n" << v[i].first << " : " << v[i].second;
    }

    file.close();

    open();
}

void Leaderboard::update()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if(set_score == 1 && buffer_time == -1)
    {
        if(currentKeyStates[SDL_SCANCODE_RETURN])
        {
            set_score = 0;
            add();
            sort();
        }

        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_TEXTINPUT:
                    name += e.text.text;
                    tex_name->set_rect(SCREEN_WIDTH/2 - 100, 450, 15 * name.length(), 50);
                    break;
            }
        }
    }

    if(buffer_time > -1)
        buffer_time--;
}

void Leaderboard::add()
{
    file.open("database.txt", ios::app);

    if (file.is_open())
    {
        file << "\n" << name << " : " << score;
    }

    file.close();
}

void Leaderboard::render(int s)
{
    score = s;

    if(set_score)
    {
        enter_name->Render("Enter Name :");
        tex_name->Render(name);
    }

    else
    {
        for(int i = 0; i < 5; i++)
        {
            tex[i]->Render(scores[i]);
        }
    }
    
}