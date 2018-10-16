#include "DisplayScreenFadeInOut.h"
#include "Game.h"

const float DisplayScreenFadeInOut::TIME_FADE_DEAD = 0.5f;
const float DisplayScreenFadeInOut::TIME_FADE_TRANSITION = 1.0f;

DisplayScreenFadeInOut::DisplayScreenFadeInOut(GameObject * gameObject) : Component(gameObject), Renderer(this)
{
	blackTexture = TextureManager::LoadTexture("img/ui/black_square.png", sourceRect.w, sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = Game::instance()->getScreenSize().x;
	destRect.h = Game::instance()->getScreenSize().y;

	setLayer(RendererManager::MAX_LAYER - 1);

	setAlpha(SDL_ALPHA_OPAQUE);
}

DisplayScreenFadeInOut::~DisplayScreenFadeInOut()
{

}

void DisplayScreenFadeInOut::start()
{

}

void DisplayScreenFadeInOut::update()
{
	if (stateFading == FadingIn) {
		float alpha_value = SDL_ALPHA_OPAQUE - ( (timeLeft / timeToFade) * SDL_ALPHA_OPAQUE) ;
		setAlpha(alpha_value);

		std::cout << alpha_value << std::endl;

		if (timeLeft <= 0) {
			setState(Over);
		}
	}
	else if (stateFading == FadingOut) {
		float alpha_value = (timeLeft / timeToFade) * SDL_ALPHA_OPAQUE;
		setAlpha(alpha_value);

		if (timeLeft <= 0) {
			setState(Over);
		}
	}
	std::cout << timeLeft << std::endl;

	timeLeft -= Time::deltaTime;
}


void DisplayScreenFadeInOut::render()
{
	destRect.w = Game::instance()->getScreenSize().x;
	destRect.h = Game::instance()->getScreenSize().y;

	TextureManager::DrawTexture(blackTexture, sourceRect, destRect, SDL_FLIP_NONE, false);
}

void DisplayScreenFadeInOut::clean()
{
	SDL_DestroyTexture(blackTexture);

	Renderer::clean();
	Component::clean();
}

void DisplayScreenFadeInOut::setState(State value, float time)
{
	stateFading = value;

	timeLeft = time;
	timeToFade = time;
}

void DisplayScreenFadeInOut::setAlpha(float value)
{
	alpha = value;

	SDL_SetTextureAlphaMod(blackTexture, alpha);
}
