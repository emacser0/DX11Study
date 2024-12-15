#pragma once

#include "ResourceBase.h"

class FShader;
class FTexture;
class Mesh;

class FResourceManager
{
	DECLARE_SINGLE(FResourceManager);

public:
	void Init();

	template<typename T>
	std::shared_ptr<T> Load(const std::wstring& InKey, const std::wstring& InPath);

	template<typename T>
	bool Add(const std::wstring& InKey, std::shared_ptr<T> InObject);

	template<typename T>
	std::shared_ptr<T> Get(const std::wstring& InKey);

	template<typename T>
	EResourceType GetResourceType();

private:
	void CreateDefaultMesh();

private:
	std::wstring ResourcePath;

private:
	using KeyObjMap = map<std::wstring/*key*/, std::shared_ptr<FResourceBase>>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> Resources;
};

template<typename T>
std::shared_ptr<T> FResourceManager::Load(const std::wstring& InKey, const std::wstring& InPath)
{
	auto ObjectType = GetResourceType<T>();
	KeyObjMap& KeyObjMap = Resources[static_cast<uint8>(ObjectType)];

	auto FindIt = KeyObjMap.find(InKey);
	if (FindIt != KeyObjMap.end())
		return static_pointer_cast<T>(FindIt->second);

	std::shared_ptr<T> Object = std::make_shared<T>();
	Object->Load(InPath);
	KeyObjMap[InKey] = Object;

	return Object;
}

template<typename T>
bool FResourceManager::Add(const std::wstring& InKey, std::shared_ptr<T> InObject)
{
	EResourceType ResourceType = GetResourceType<T>();
	KeyObjMap& KeyObjMap = Resources[static_cast<uint8>(ResourceType)];

	auto FindIt = KeyObjMap.find(InKey);
	if (FindIt != KeyObjMap.end())
		return false;

	KeyObjMap[InKey] = InObject;
	return true;
}

template<typename T>
std::shared_ptr<T> FResourceManager::Get(const std::wstring& InKey)
{
	EResourceType ResourceType = GetResourceType<T>();
	KeyObjMap& KeyObjMap = Resources[static_cast<uint8>(ResourceType)];

	auto FindIt = KeyObjMap.find(InKey);
	if (FindIt != KeyObjMap.end())
		return static_pointer_cast<T>(FindIt->second);

	return nullptr;
}

template<typename T>
EResourceType FResourceManager::GetResourceType()
{
	if (std::is_same_v<T, FTexture>)
		return EResourceType::Texture;
	if (std::is_same_v<T, Mesh>)
		return EResourceType::Mesh;

	assert(false);
	return EResourceType::None;
}

