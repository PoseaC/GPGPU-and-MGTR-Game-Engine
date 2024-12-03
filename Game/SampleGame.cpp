#include "SampleGame.h"

SampleGame::SampleGame()
{
}

SampleGame::~SampleGame()
{
}

void SampleGame::OnCreate()
{
	Game::OnCreate();
	m_player = getEntitySystem()->createEntity<Player>();
}

void SampleGame::OnUpdate(float deltaTime)
{
}
