#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen
{
private:
    static int m_ScreenWidth;
    static int m_ScreenHeight;

    Screen() = delete;
    Screen(Screen &screen) = delete;

public:
    static int &getScreenWidth();
    static int &getScreenHeight();
};

#endif