#define SDL_MAIN_HANDLED
#include"Window.hpp"
#include"Button.hpp"
#include"Mouse.hpp"

// Initilizes the sdl Library
void Initilize() 
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "SDL_init has failed ERROR:" << SDL_GetError() << endl;
    }
    if (!(IMG_Init(IMG_INIT_JPG)))
    {
        cout << "IMG-init has failed ERROR:" << SDL_GetError() << endl;
    }

}

void main_game_loop() 
{
    // Main game loop 
    Window* window = new Window("Cup Head", 1280, 720);
    bool gameRunning = true;
    SDL_Event event;

    // Loding the images
    SDL_Texture* Back_ground = (window->loadTexture("C:/dev/FrontEnd/Images/BackGround3.png"));
    Button* b = new Button(600, 150, 100, 50, "C:/dev/FrontEnd/Images/play4.png");
    Button* b1 = new Button(550, 250, 200, 50, "C:/dev/FrontEnd/Images/Instructions1.png");


    Mouse* m = new Mouse();
    SDL_StartTextInput();
    SDL_Rect* s = new SDL_Rect();
    s->x = 50;
    s->y = 50;
    s->h = 50;
    s->w = 60;



    //** different screens
    bool Home_screen = true;
    bool Play_screen = false;
    bool Leader_board_screen = false;
    bool Exit_screen = false;



    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        //cout << m->get_mouse_x() << " " << m->get_mouse_y() << endl;



        if (Home_screen) 
        {

            window->clear();
            SDL_PumpEvents();
            SDL_SetTextInputRect(s);
            window->Render_texture(Back_ground);
            b->draw_button(window);
            b1->draw_button(window);
            if (b->isClicked(m)) 
            {
                Home_screen = false;
                Play_screen = true;
            }

            if (b1->isClicked(m))
            {
                Home_screen = false;
                Play_screen = true;
            }

            window->display();

        }

        if (Play_screen) 
        {
            window->clear();
            window->display();
        }

    }

    window->cleanUp();
    SDL_Quit();

}

int main()
{
    Initilize();
    main_game_loop();
}
