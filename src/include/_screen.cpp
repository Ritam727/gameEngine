#include "_screen.hpp"

int &Screen::getScreenWidth()
{
    return m_ScreenWidth;
}

int &Screen::getScreenHeight()
{
    return m_ScreenHeight;
}

int Screen::m_ScreenWidth = 1920;
int Screen::m_ScreenHeight = 1016;