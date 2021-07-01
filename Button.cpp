#include "Button.h"

Button::Button()
{
}

Button::Button(int x, int y, int w, int h)
{
	bPos.x = x;
	bPos.y = y;
	bPos.w = w;
	bPos.h = h;
}

Button::~Button()
{
}

void Button::setButtonPos(SDL_Rect tmpRect)
{
	bPos = tmpRect;
}

void Button::setButtonPos(int x, int y, int w, int h)
{
	bPos.x = x;
	bPos.y = y;
	bPos.w = w;
	bPos.h = h;
}

SDL_Rect* Button::getButtonChar()
{
	SDL_Rect tmpRect;
	tmpRect.x = 0;
	tmpRect.y = 0;
	tmpRect.w = bPos.w;
	tmpRect.h = bPos.h;
	return &tmpRect;
}
