#include "LevelManager.h"

void LevelManager::Initialize(Resources* resources)
{
	m_ObjectManager = new ObjectManager();
	m_ObjectManager->Initialize(resources);

	Manager::Initialize(resources);
}

void LevelManager::Close()
{
	delete m_ObjectManager;
	m_ObjectManager = 0;
}

void LevelManager::ReLoad()
{
	m_ObjectManager->DestroyAll();
	SpawnObjects(m_LevelData);
}

void LevelManager::Tick(double deltaTime)
{
	// tick tock 
}

void LevelManager::Render(SDL_Renderer* renderer)
{
	m_ObjectManager->RenderObjects(renderer);
}

void LevelManager::LoadData(LevelData data)
{
	m_LevelData = data;
	
	SpawnObjects(m_LevelData);
}

void LevelManager::SpawnObjects(LevelData data)
{
	for (size_t i = 0; i < data.Objects.size(); i++)
	{
		LevelObject lObject = data.Objects[i];
		GameObject* gObject = 0;

		switch (lObject.Type)
		{
		case Player:
			gObject = new PlayerObject();
			break;

		case LevelFinish:
			gObject = new FinishObject();
			break;

		case GeometryNormal:
			gObject = new GeometryObject();
			break;
		
		case GeometryHazard:
			gObject = new HazardGeometryObject();
			break;

		case GeometryBoost:
			gObject = new BoostGeometryObject();
			break;

		default:
			printf("UNIMPLEMENTED OBJECT TYPE\n");
			break;
		}

		gObject = m_ObjectManager->CreateObject(gObject);
		
		gObject->Position = lObject.InitialPosition;
		gObject->Rotation = lObject.InitialRotation;
		gObject->Velocity = lObject.InitialVelocity;
		gObject->AngularVelocity = lObject.InitialAnguarVelocity;
		gObject->SetColliderLength(lObject.ColliderLength);
	}
}