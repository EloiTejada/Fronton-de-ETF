#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

const std::string title = "Fronton";
const float ballSpeedBase = 6.9f;
const float playerSpeed = 9.0f;
const int NumMaxBlocs = 10;
//const int x_min = 0, x_max = 1480;
//const int y_min = 0, y_max = 920;
const int incre_xr = 10, incre_yr = 10;
const int longitut = 250, amplada = 50;

struct Bloc {
    bool active = false;
    Sprite spriteBloc;

};
