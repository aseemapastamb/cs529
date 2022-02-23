#include "GameObjectFactory.h"

#include "ComponentCreator.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "Renderer.h"
#include "GameObject.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

extern GameObjectManager* gpGameObjectManager;
extern ResourceManager* gpResourceManager;
extern EventManager* gpEventManager;
extern Renderer* gpRenderer;

GameObjectFactory::GameObjectFactory():
	mComponentCreator(new ComponentCreator())
{
}

GameObjectFactory::~GameObjectFactory() {
	delete mComponentCreator;
}

void GameObjectFactory::BuildLevel(const char* pFileName) {
	FILE* fp;
	rapidjson::Document json;
	GameObject* pNewGameObject;

	pNewGameObject = nullptr;

	fopen_s(&fp, pFileName, "r");

	char buffer[512] = { 0 };
	rapidjson::FileReadStream iFS(fp, buffer, sizeof(buffer));

	json.ParseStream(iFS);

	if (fp != nullptr) {
		rapidjson::Value& objects = json["Objects"];
		for (unsigned int i = 0; i < objects.Size(); ++i) {
			rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject = objects[i].GetObject();
			if (jsonObject.HasMember("Name")) {
				pNewGameObject = BuildGameObject(jsonObject["Name"].GetString());
				if (jsonObject.HasMember("Label")) {
					pNewGameObject->mLabel = jsonObject["Label"].GetString();
				}
				if (jsonObject.HasMember("Transform")) {
					((Transform*)pNewGameObject->GetComponent("Transform"))->Deserialize(jsonObject["Transform"].GetObject());
				}
				if (jsonObject.HasMember("Sprite")) {
					((Sprite*)pNewGameObject->GetComponent("Sprite"))->Deserialize(jsonObject["Sprite"].GetObject());
				}
				if (jsonObject.HasMember("UpDown")) {
					((UpDown*)pNewGameObject->GetComponent("UpDown"))->Deserialize(jsonObject["UpDown"].GetObject());
				}
				if (jsonObject.HasMember("Body")) {
					((Body*)pNewGameObject->GetComponent("Body"))->Deserialize(jsonObject["Body"].GetObject());
				}
				if (jsonObject.HasMember("Health")) {
					((Health*)pNewGameObject->GetComponent("Health"))->Deserialize(jsonObject["Health"].GetObject());
				}
				if (jsonObject.HasMember("Ammo")) {
					((Ammo*)pNewGameObject->GetComponent("Ammo"))->Deserialize(jsonObject["Ammo"].GetObject());
				}
				if (jsonObject.HasMember("Spawner")) {
					((Spawner*)pNewGameObject->GetComponent("Spawner"))->Deserialize(jsonObject["Spawner"].GetObject());
				}
			}
		}
	}

	gpEventManager->Initialize();
}

GameObject* GameObjectFactory::BuildGameObject(const char* pFileName) {
	rapidjson::Document* json;
	FILE* fp;
	GameObject* pNewGameObject;
	Component* pNewComponent;

	json = new rapidjson::Document;
	pNewGameObject = nullptr;
	pNewComponent = nullptr;

	fopen_s(&fp, pFileName, "r");

	char buffer[512] = { 0 };
	rapidjson::FileReadStream iFS(fp, buffer, sizeof(buffer));

	if (fp != nullptr) {
		json->ParseStream(iFS);
		rapidjson::GenericObject<false, rapidjson::Value::ValueType> jsonObject = json->GetObject();

		if (jsonObject.HasMember("Type")) {
			std::string gameObjectType = jsonObject["Type"].GetString();
			pNewGameObject = new GameObject();
			pNewGameObject->mType = gameObjectType;
			if (jsonObject.HasMember("Label")) {
				pNewGameObject->mLabel = jsonObject["Label"].GetString();
			}
			if (jsonObject.HasMember("Transform")) {
				pNewComponent = (Component*)mComponentCreator->CreateTransform();
				((Transform*)pNewComponent)->Deserialize(jsonObject["Transform"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Sprite")) {
				pNewComponent = (Component*)mComponentCreator->CreateSprite();
				((Sprite*)pNewComponent)->Deserialize(jsonObject["Sprite"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Controller")) {
				pNewComponent = (Component*)mComponentCreator->CreateController();
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("UpDown")) {
				pNewComponent = (Component*)mComponentCreator->CreateUpDown();
				((UpDown*)pNewComponent)->Deserialize(jsonObject["UpDown"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Body")) {
				pNewComponent = (Component*)mComponentCreator->CreateBody();
				((Body*)pNewComponent)->Deserialize(jsonObject["Body"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Health")) {
				pNewComponent = (Component*)mComponentCreator->CreateHealth();
				((Health*)pNewComponent)->Deserialize(jsonObject["Health"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Ammo")) {
				pNewComponent = (Component*)mComponentCreator->CreateAmmo();
				((Ammo*)pNewComponent)->Deserialize(jsonObject["Ammo"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Button")) {
				pNewComponent = (Button*)mComponentCreator->CreateButton();
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("AI")) {
				pNewComponent = (AI*)mComponentCreator->CreateAI();
				pNewGameObject->AddComponent(pNewComponent);
			}
			if (jsonObject.HasMember("Spawner")) {
				pNewComponent = (Component*)mComponentCreator->CreateSpawner();
				((Spawner*)pNewComponent)->Deserialize(jsonObject["Spawner"].GetObject());
				pNewGameObject->AddComponent(pNewComponent);
			}
		}

		gpGameObjectManager->AddObject(pNewGameObject);
	}

	return pNewGameObject;
}

void GameObjectFactory::Update() {

}