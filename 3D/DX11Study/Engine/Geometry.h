#pragma once

template<typename T>
class FGeometry
{
public:
	FGeometry() {} 
	~FGeometry() {}

	uint32 GetVertexCount() { return static_cast<uint32>(Vertices.size()); }
	void* GetVertexData() { return Vertices.data(); }
	const std::vector<T>& GetVertices() { return Vertices; }

	uint32 GetIndexCount() { return static_cast<uint32>(Indices.size());  }
	void* GetIndexData() { return Indices.data(); }
	const std::vector<uint32>& GetIndices() { return Indices; }

	void AddVertex(const T& vertex) { Vertices.push_back(vertex); }
	void AddVertices(const std::vector<T>& InVertices) { Vertices.insert(Vertices.end(), InVertices.begin(), InVertices.end()); }
	void SetVertices(const std::vector<T>& InVertices) { Vertices = InVertices; }

	void AddIndex(uint32 index) { Indices.push_back(index); }
	void AddIndices(const std::vector<uint32>& InIndices) { Indices.insert(Indices.end(), InIndices.begin(), InIndices.end()); }
	void SetIndices(const std::vector<uint32>& InIndices) { Indices = InIndices; }

private:
	std::vector<T> Vertices;
	std::vector<uint32> Indices;
};
