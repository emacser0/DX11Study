#pragma once

enum class EResourceType : uint8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<uint8>(EResourceType::End)
};

class FResourceBase : public enable_shared_from_this<FResourceBase>
{
public:
	FResourceBase(EResourceType type);
	virtual ~FResourceBase();

	EResourceType GetType() { return Type; }

	void SetName(const std::wstring& name) { Name = name; }
	const std::wstring& GetName() { return Name; }
	uint32 GetID() { return Id; }

protected:
	virtual void Load(const std::wstring& path) { }
	virtual void Save(const std::wstring& path) { }

protected:
	EResourceType Type = EResourceType::None;
	std::wstring Name;
	std::wstring Path;
	uint32 Id = 0;
};

