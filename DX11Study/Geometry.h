#pragma once

template <typename T>
class FGeometry
{
public:
	FGeometry();
	virtual ~FGeometry();

	uint32 GetVertexCount() const { return static_cast<uint32>(Vertices.size()); }
	void* GetVertexData() const { return Vertices.data(); }
	const std::vector<T>& GetVertices() const { return Vertices; }

	uint32 GetIndexCount() const { return static_cast<uint32>(Indices.size()); }
	void* GetIndexData() const { return Indices.data(); }
	const std::vector<uint32>& GetIndices() const { return Indices; }

	void AddVertex(const T& InVertex)
	{
		Vertices.push_back(InVertex);
	}

	void AddVertices(const std::vector<T>& InVertices)
	{
		Vertices.insert(Vertices.end(), InVertices.begin(), InVertices.end());
	}

	void SetVertices(const std::vector<T>& InVertices)
	{
		Vertices = InVertices;
	}

	void AddIndex(uint32 InIndex)
	{
		Indices.push_back(InIndex);
	}

	void AddIndices(const std::vector<uint32>& InIndices)
	{
		Indices.insert(Indices.end(), InIndices.begin(), InIndices.end());
	}

	void SetIndices(const std::vector<uint32>& InIndices)
	{
		Indices = InIndices;
	}

private:
	std::vector<T> Vertices;
	std::vector<uint32> Indices;
};

template<typename T>
inline FGeometry<T>::FGeometry()
{
}

template<typename T>
inline FGeometry<T>::~FGeometry()
{
}
