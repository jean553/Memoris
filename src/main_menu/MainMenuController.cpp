/**
 * @file MainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MainMenuController.hpp"

using namespace controllers;

/**
 *
 */
MainMenuController::MainMenuController() : Controller()
{
    fontTitle.loadFromFile(PATH_FONT_TITLE);

    colorTitle.r = COLOR_TITLE_RED_INIT;
    colorTitle.g = COLOR_TITLE_GREEN_INIT;
    colorTitle.b = COLOR_TITLE_BLUE_INIT;
    colorTitle.a = COLOR_TITLE_ALPHA;

    title.setFont(fontTitle);
    title.setString("Memoris");
    title.setCharacterSize(SIZE_TITLE_FONT);
    title.setColor(colorTitle);
    title.setPosition(POSITION_TITLE_X, POSITION_TITLE_Y);

    textureGithub.loadFromFile(PATH_IMAGE_GITHUB);

    spriteGithub.setTexture(textureGithub, true);
    spriteGithub.setPosition(
        POSITION_GITHUB_X,
        POSITION_GITHUB_Y
    );

    musicMainMenu.openFromFile(PATH_MUSIC_MAIN_MENU);

    titleRedDirection = DIRECTION_TITLE_RED_INIT;
    titleGreenDirection = DIRECTION_TITLE_GREEN_INIT;
    titleBlueDirection = DIRECTION_TITLE_BLUE_INIT;

    //TODO: not an initialization function,
    //check if it can be moved in the rendering
    musicMainMenu.play();
}

/**
 *
 */
MainMenuController::~MainMenuController()
{
    musicMainMenu.stop();
}

/**
 *
 */
void MainMenuController::render(sf::RenderWindow* window)
{
    // animate the items
    if(clock.getElapsedTime().asMilliseconds() >
        INTERVAL_ANIMATION_TITLE
    ) {

        animateTitleColor();

        clock.restart();
    }

    window->draw(title);
    window->draw(spriteGithub);

    // render game and catch events
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            // action when a key is pressed
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    // terminate the program when
                    // escape button is pressed
                    case sf::Keyboard::Escape:
                    {
                        window->close();
                        break;
                    }
                }
            }
        }
    }
}

/**
 *
 */
void MainMenuController::animateTitleColor()
{
    // update color values
    colorTitle.r += titleRedDirection;
    colorTitle.g += titleGreenDirection;
    colorTitle.b += titleBlueDirection;

    // switch colors updates directions
    if(colorTitle.r == COLOR_TITLE_RED_MAX ||
       colorTitle.r == COLOR_TITLE_ALL_MIN
    ) {
        titleRedDirection = -titleRedDirection;
    }

    if(colorTitle.g == COLOR_TITLE_GREEN_MAX ||
       colorTitle.g == COLOR_TITLE_ALL_MIN
    ) {
        titleGreenDirection = -titleGreenDirection;
    }

    if(colorTitle.b == COLOR_TITLE_BLUE_MAX ||
    colorTitle.b == COLOR_TITLE_ALL_MIN
    ) {
        titleBlueDirection = -titleBlueDirection;
    }

    title.setColor(colorTitle);
}
