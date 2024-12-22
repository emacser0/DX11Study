#include "pch.h"
#include "GeometryHelper.h"
#include "VertexData.h"

void FGeometryHelper::CreateQuad(std::shared_ptr<FGeometry<FVertexColorData>> InGeometry, FColor InColor)
{
	std::vector<FVertexColorData> Vertices;
	Vertices.resize(4);
	Vertices[0].Position = FVector3(-0.5f, 0.5f, 0.0f);
	Vertices[0].Color = InColor;
	Vertices[1].Position = FVector3(0.5f, 0.5f, 0.0f);
	Vertices[1].Color = InColor;
	Vertices[2].Position = FVector3(-0.5f, -0.5f, 0.0f);
	Vertices[2].Color = InColor;
	Vertices[3].Position = FVector3(0.5f, -0.5f, 0.0f);
	Vertices[3].Color = InColor;

	std::vector<uint32> Indices = { 0, 1, 2, 2, 1, 3 };

	InGeometry->SetVertices(Vertices);
	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateQuad(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry)
{
	std::vector<FVertexTextureData> Vertices;
	Vertices.resize(4);

	Vertices[0].Position = FVector3(-0.5f, -0.5f, 0.0f);
	Vertices[0].TexCoord = FVector2(0.0f, 1.0f);
	Vertices[1].Position = FVector3(-0.5f, 0.5f, 0.0f);
	Vertices[1].TexCoord = FVector2(0.0f, 0.0f);
	Vertices[2].Position = FVector3(0.5f, -0.5f, 0.0f);
	Vertices[2].TexCoord = FVector2(1.0f, 1.0f);
	Vertices[3].Position = FVector3(0.5f, 0.5f, 0.0f);
	Vertices[3].TexCoord = FVector2(1.0f, 0.0f);

	std::vector<uint32> Indices = { 0, 1, 2, 2, 1, 3 };

	InGeometry->SetVertices(Vertices);
	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateCube(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry)
{
	float W2 = 0.5f;
	float H2 = 0.5f;
	float D2 = 0.5f;

	vector<FVertexTextureData> Vertices(24);

	// �ո�
	Vertices[0] = FVertexTextureData{ FVector3(-W2, -H2, -D2), FVector2(0.0f, 1.0f) };
	Vertices[1] = FVertexTextureData{ FVector3(-W2, +H2, -D2), FVector2(0.0f, 0.0f) };
	Vertices[2] = FVertexTextureData{ FVector3(+W2, +H2, -D2), FVector2(1.0f, 0.0f) };
	Vertices[3] = FVertexTextureData{ FVector3(+W2, -H2, -D2), FVector2(1.0f, 1.0f) };
	// �޸�
	Vertices[4] = FVertexTextureData{ FVector3(-W2, -H2, +D2), FVector2(1.0f, 1.0f) };
	Vertices[5] = FVertexTextureData{ FVector3(+W2, -H2, +D2), FVector2(0.0f, 1.0f) };
	Vertices[6] = FVertexTextureData{ FVector3(+W2, +H2, +D2), FVector2(0.0f, 0.0f) };
	Vertices[7] = FVertexTextureData{ FVector3(-W2, +H2, +D2), FVector2(1.0f, 0.0f) };
	// ����
	Vertices[8] = FVertexTextureData{ FVector3(-W2, +H2, -D2), FVector2(0.0f, 1.0f) };
	Vertices[9] = FVertexTextureData{ FVector3(-W2, +H2, +D2), FVector2(0.0f, 0.0f) };
	Vertices[10] = FVertexTextureData{ FVector3(+W2, +H2, +D2), FVector2(1.0f, 0.0f) };
	Vertices[11] = FVertexTextureData{ FVector3(+W2, +H2, -D2), FVector2(1.0f, 1.0f) };
	// �Ʒ���
	Vertices[12] = FVertexTextureData{ FVector3(-W2, -H2, -D2), FVector2(1.0f, 1.0f) };
	Vertices[13] = FVertexTextureData{ FVector3(+W2, -H2, -D2), FVector2(0.0f, 1.0f) };
	Vertices[14] = FVertexTextureData{ FVector3(+W2, -H2, +D2), FVector2(0.0f, 0.0f) };
	Vertices[15] = FVertexTextureData{ FVector3(-W2, -H2, +D2), FVector2(1.0f, 0.0f) };
	// ���ʸ�
	Vertices[16] = FVertexTextureData{ FVector3(-W2, -H2, +D2), FVector2(0.0f, 1.0f) };
	Vertices[17] = FVertexTextureData{ FVector3(-W2, +H2, +D2), FVector2(0.0f, 0.0f) };
	Vertices[18] = FVertexTextureData{ FVector3(-W2, +H2, -D2), FVector2(1.0f, 0.0f) };
	Vertices[19] = FVertexTextureData{ FVector3(-W2, -H2, -D2), FVector2(1.0f, 1.0f) };
	// �����ʸ�
	Vertices[20] = FVertexTextureData{ FVector3(+W2, -H2, -D2), FVector2(0.0f, 1.0f) };
	Vertices[21] = FVertexTextureData{ FVector3(+W2, +H2, -D2), FVector2(0.0f, 0.0f) };
	Vertices[22] = FVertexTextureData{ FVector3(+W2, +H2, +D2), FVector2(1.0f, 0.0f) };
	Vertices[23] = FVertexTextureData{ FVector3(+W2, -H2, +D2), FVector2(1.0f, 1.0f) };

	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices(36);

	// �ո�
	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 0; Indices[4] = 2; Indices[5] = 3;
	// �޸�
	Indices[6] = 4; Indices[7] = 5; Indices[8] = 6;
	Indices[9] = 4; Indices[10] = 6; Indices[11] = 7;
	// ����
	Indices[12] = 8; Indices[13] = 9; Indices[14] = 10;
	Indices[15] = 8; Indices[16] = 10; Indices[17] = 11;
	// �Ʒ���
	Indices[18] = 12; Indices[19] = 13; Indices[20] = 14;
	Indices[21] = 12; Indices[22] = 14; Indices[23] = 15;
	// ���ʸ�
	Indices[24] = 16; Indices[25] = 17; Indices[26] = 18;
	Indices[27] = 16; Indices[28] = 18; Indices[29] = 19;
	// �����ʸ�
	Indices[30] = 20; Indices[31] = 21; Indices[32] = 22;
	Indices[33] = 20; Indices[34] = 22; Indices[35] = 23;

	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateGrid(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry, int32 InSizeX, int32 InSizeZ)
{
	std::vector<FVertexTextureData> Vertices;

	for (int32 Z = 0; Z < InSizeZ + 1; Z++)
	{
		for (int32 X = 0; X < InSizeX + 1; X++)
		{
			FVertexTextureData Vertex;
			Vertex.Position = FVector3(static_cast<float>(X), 0, static_cast<float>(Z));
			Vertex.TexCoord = FVector2(static_cast<float>(X), static_cast<float>(Z));

			Vertices.push_back(Vertex);
		}
	}

	InGeometry->SetVertices(Vertices);

	std::vector<uint32> Indices;

	for (int32 Z = 0; Z < InSizeZ; Z++)
	{
		for (int32 X = 0; X < InSizeX; X++)
		{
			//  [0]
			//   |	\
			//  [2] - [1]
			Indices.push_back((InSizeX + 1) * (Z + 1) + (X));
			Indices.push_back((InSizeX + 1) * (Z)+(X + 1));
			Indices.push_back((InSizeX + 1) * (Z)+(X));
			//  [1] - [2]
			//   	\  |
			//		  [0]
			Indices.push_back((InSizeX + 1) * (Z)+(X + 1));
			Indices.push_back((InSizeX + 1) * (Z + 1) + (X));
			Indices.push_back((InSizeX + 1) * (Z + 1) + (X + 1));
		}
	}

	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateSphere(std::shared_ptr<FGeometry<FVertexTextureData>> InGeometry)
{
	float Radius = 0.5f; // ���� ������
	uint32 StackCount = 20; // ���� ����
	uint32 SliceCount = 20; // ���� ����

	vector<FVertexTextureData> Vertices;

	FVertexTextureData Vertex;

	// �ϱ�
	Vertex.Position = FVector3(0.0f, Radius, 0.0f);
	Vertex.TexCoord = FVector2(0.5f, 0.0f);
	Vertices.push_back(Vertex);

	float StackAngle = XM_PI / StackCount;
	float SliceAngle = XM_2PI / SliceCount;

	float DeltaU = 1.0f / static_cast<float>(SliceCount);
	float DeltaV = 1.0f / static_cast<float>(StackCount);

	// ������ ���鼭 ������ ����Ѵ� (�ϱ�/���� �������� ���� X)
	for (uint32 Y = 1; Y <= StackCount - 1; ++Y)
	{
		float Phi = Y * StackAngle;

		// ���� ��ġ�� ����
		for (uint32 X = 0; X <= SliceCount; ++X)
		{
			float theta = X * SliceAngle;

			Vertex.Position.x = Radius * sinf(Phi) * cosf(theta);
			Vertex.Position.y = Radius * cosf(Phi);
			Vertex.Position.z = Radius * sinf(Phi) * sinf(theta);

			Vertex.TexCoord = FVector2(DeltaU * X, DeltaV * Y);

			Vertices.push_back(Vertex);
		}
	}

	// ����
	Vertex.Position = FVector3(0.0f, -Radius, 0.0f);
	Vertex.TexCoord = FVector2(0.5f, 1.0f);
	Vertices.push_back(Vertex);

	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices(36);

	// �ϱ� �ε���
	for (uint32 Idx = 0; Idx <= SliceCount; ++Idx)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		Indices.push_back(0);
		Indices.push_back(Idx + 2);
		Indices.push_back(Idx + 1);
	}

	// ���� �ε���
	uint32 RingFVertexCount = SliceCount + 1;
	for (uint32 Y = 0; Y < StackCount - 2; ++Y)
	{
		for (uint32 X = 0; X < SliceCount; ++X)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			Indices.push_back(1 + (Y)*RingFVertexCount + (X));
			Indices.push_back(1 + (Y)*RingFVertexCount + (X + 1));
			Indices.push_back(1 + (Y + 1) * RingFVertexCount + (X));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			Indices.push_back(1 + (Y + 1) * RingFVertexCount + (X));
			Indices.push_back(1 + (Y)*RingFVertexCount + (X + 1));
			Indices.push_back(1 + (Y + 1) * RingFVertexCount + (X + 1));
		}
	}

	// ���� �ε���
	uint32 bottomIndex = static_cast<uint32>(Vertices.size()) - 1;
	uint32 LastRingStartIndex = bottomIndex - RingFVertexCount;
	for (uint32 Idx = 0; Idx < SliceCount; ++Idx)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		Indices.push_back(bottomIndex);
		Indices.push_back(LastRingStartIndex + Idx);
		Indices.push_back(LastRingStartIndex + Idx + 1);
	}

	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateQuad(shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry)
{
	std::vector<FVertexTextureNormalData> Vertices;
	Vertices.resize(4);

	Vertices[0].Position = FVector3(-0.5f, -0.5f, 0.0f);
	Vertices[0].TexCoord = FVector2(0.0f, 1.0f);
	Vertices[0].Normal = FVector3(0.0f, 0.0f, -1.0f);
	Vertices[1].Position = FVector3(-0.5f, 0.5f, 0.0f);
	Vertices[1].TexCoord = FVector2(0.0f, 0.0f);
	Vertices[1].Normal = FVector3(0.0f, 0.0f, -1.0f);
	Vertices[2].Position = FVector3(0.5f, -0.5f, 0.0f);
	Vertices[2].TexCoord = FVector2(1.0f, 1.0f);
	Vertices[2].Normal = FVector3(0.0f, 0.0f, -1.0f);
	Vertices[3].Position = FVector3(0.5f, 0.5f, 0.0f);
	Vertices[3].TexCoord = FVector2(1.0f, 0.0f);
	Vertices[2].Normal = FVector3(0.0f, 0.0f, -1.0f);
	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices = { 0, 1, 2, 2, 1, 3 };
	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateCube(shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry)
{
	float W2 = 0.5f;
	float H2 = 0.5f;
	float D2 = 0.5f;

	std::vector<FVertexTextureNormalData> Vertices(24);

	// �ո�
	Vertices[0] = { FVector3(-W2, -H2, -D2), FVector2(0.0f, 1.0f), FVector3(0.0f, 0.0f, -1.0f) };
	Vertices[1] = { FVector3(-W2, +H2, -D2), FVector2(0.0f, 0.0f), FVector3(0.0f, 0.0f, -1.0f) };
	Vertices[2] = { FVector3(+W2, +H2, -D2), FVector2(1.0f, 0.0f), FVector3(0.0f, 0.0f, -1.0f) };
	Vertices[3] = { FVector3(+W2, -H2, -D2), FVector2(1.0f, 1.0f), FVector3(0.0f, 0.0f, -1.0f) };
	// �޸�
	Vertices[4] = { FVector3(-W2, -H2, +D2), FVector2(1.0f, 1.0f), FVector3(0.0f, 0.0f, 1.0f) };
	Vertices[5] = { FVector3(+W2, -H2, +D2), FVector2(0.0f, 1.0f), FVector3(0.0f, 0.0f, 1.0f) };
	Vertices[6] = { FVector3(+W2, +H2, +D2), FVector2(0.0f, 0.0f), FVector3(0.0f, 0.0f, 1.0f) };
	Vertices[7] = { FVector3(-W2, +H2, +D2), FVector2(1.0f, 0.0f), FVector3(0.0f, 0.0f, 1.0f) };
	// ����
	Vertices[8] = { FVector3(-W2, +H2, -D2), FVector2(0.0f, 1.0f), FVector3(0.0f, 1.0f, 0.0f) };
	Vertices[9] = { FVector3(-W2, +H2, +D2), FVector2(0.0f, 0.0f), FVector3(0.0f, 1.0f, 0.0f) };
	Vertices[10] = { FVector3(+W2, +H2, +D2), FVector2(1.0f, 0.0f), FVector3(0.0f, 1.0f, 0.0f) };
	Vertices[11] = { FVector3(+W2, +H2, -D2), FVector2(1.0f, 1.0f), FVector3(0.0f, 1.0f, 0.0f) };
	// �Ʒ���
	Vertices[12] = { FVector3(-W2, -H2, -D2), FVector2(1.0f, 1.0f), FVector3(0.0f, -1.0f, 0.0f) };
	Vertices[13] = { FVector3(+W2, -H2, -D2), FVector2(0.0f, 1.0f), FVector3(0.0f, -1.0f, 0.0f) };
	Vertices[14] = { FVector3(+W2, -H2, +D2), FVector2(0.0f, 0.0f), FVector3(0.0f, -1.0f, 0.0f) };
	Vertices[15] = { FVector3(-W2, -H2, +D2), FVector2(1.0f, 0.0f), FVector3(0.0f, -1.0f, 0.0f) };
	// ���ʸ�
	Vertices[16] = { FVector3(-W2, -H2, +D2), FVector2(0.0f, 1.0f), FVector3(-1.0f, 0.0f, 0.0f) };
	Vertices[17] = { FVector3(-W2, +H2, +D2), FVector2(0.0f, 0.0f), FVector3(-1.0f, 0.0f, 0.0f) };
	Vertices[18] = { FVector3(-W2, +H2, -D2), FVector2(1.0f, 0.0f), FVector3(-1.0f, 0.0f, 0.0f) };
	Vertices[19] = { FVector3(-W2, -H2, -D2), FVector2(1.0f, 1.0f), FVector3(-1.0f, 0.0f, 0.0f) };
	// �����ʸ�
	Vertices[20] = { FVector3(+W2, -H2, -D2), FVector2(0.0f, 1.0f), FVector3(1.0f, 0.0f, 0.0f) };
	Vertices[21] = { FVector3(+W2, +H2, -D2), FVector2(0.0f, 0.0f), FVector3(1.0f, 0.0f, 0.0f) };
	Vertices[22] = { FVector3(+W2, +H2, +D2), FVector2(1.0f, 0.0f), FVector3(1.0f, 0.0f, 0.0f) };
	Vertices[23] = { FVector3(+W2, -H2, +D2), FVector2(1.0f, 1.0f), FVector3(1.0f, 0.0f, 0.0f) };

	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices(36);

	// �ո�
	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 0; Indices[4] = 2; Indices[5] = 3;
	// �޸�
	Indices[6] = 4; Indices[7] = 5; Indices[8] = 6;
	Indices[9] = 4; Indices[10] = 6; Indices[11] = 7;
	// ����
	Indices[12] = 8; Indices[13] = 9; Indices[14] = 10;
	Indices[15] = 8; Indices[16] = 10; Indices[17] = 11;
	// �Ʒ���
	Indices[18] = 12; Indices[19] = 13; Indices[20] = 14;
	Indices[21] = 12; Indices[22] = 14; Indices[23] = 15;
	// ���ʸ�
	Indices[24] = 16; Indices[25] = 17; Indices[26] = 18;
	Indices[27] = 16; Indices[28] = 18; Indices[29] = 19;
	// �����ʸ�
	Indices[30] = 20; Indices[31] = 21; Indices[32] = 22;
	Indices[33] = 20; Indices[34] = 22; Indices[35] = 23;

	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateGrid(shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry, int32 sizeX, int32 sizeZ)
{
	std::vector<FVertexTextureNormalData> Vertices;

	for (int32 Z = 0; Z < sizeZ + 1; Z++)
	{
		for (int32 X = 0; X < sizeX + 1; X++)
		{
			FVertexTextureNormalData Vertex;
			Vertex.Position = FVector3(static_cast<float>(X), 0, static_cast<float>(Z));
			Vertex.TexCoord = FVector2(static_cast<float>(X), static_cast<float>(sizeZ - Z));
			Vertex.Normal = FVector3(0.0f, 1.0f, 0.0f);

			Vertices.push_back(Vertex);
		}
	}

	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices;

	for (int32 Z = 0; Z < sizeZ; Z++)
	{
		for (int32 X = 0; X < sizeX; X++)
		{
			//  [0]
			//   |	\
			//  [2] - [1]
			Indices.push_back((sizeX + 1) * (Z + 1) + (X));
			Indices.push_back((sizeX + 1) * (Z)+(X + 1));
			Indices.push_back((sizeX + 1) * (Z)+(X));
			//  [1] - [2]
			//   	\  |
			//		  [0]
			Indices.push_back((sizeX + 1) * (Z)+(X + 1));
			Indices.push_back((sizeX + 1) * (Z + 1) + (X));
			Indices.push_back((sizeX + 1) * (Z + 1) + (X + 1));
		}
	}

	InGeometry->SetIndices(Indices);
}

void FGeometryHelper::CreateSphere(shared_ptr<FGeometry<FVertexTextureNormalData>> InGeometry)
{
	float Radius = 0.5f; // ���� ������
	uint32 StackCount = 20; // ���� ����
	uint32 SliceCount = 20; // ���� ����

	std::vector<FVertexTextureNormalData> Vertices;

	FVertexTextureNormalData Vertex;

	// �ϱ�
	Vertex.Position = FVector3(0.0f, Radius, 0.0f);
	Vertex.TexCoord = FVector2(0.5f, 0.0f);
	Vertex.Normal = Vertex.Position;
	Vertex.Normal.Normalize();
	Vertices.push_back(Vertex);

	float StackAngle = XM_PI / StackCount;
	float SliceAngle = XM_2PI / SliceCount;

	float DeltaU = 1.0f / static_cast<float>(SliceCount);
	float DeltaV = 1.0f / static_cast<float>(StackCount);

	// ������ ���鼭 ������ ����Ѵ� (�ϱ�/���� �������� ���� X)
	for (uint32 Y = 1; Y <= StackCount - 1; ++Y)
	{
		float Phi = Y * StackAngle;

		// ���� ��ġ�� ����
		for (uint32 X = 0; X <= SliceCount; ++X)
		{
			float theta = X * SliceAngle;

			Vertex.Position.x = Radius * sinf(Phi) * cosf(theta);
			Vertex.Position.y = Radius * cosf(Phi);
			Vertex.Position.z = Radius * sinf(Phi) * sinf(theta);

			Vertex.TexCoord = FVector2(DeltaU * X, DeltaV * Y);

			Vertex.Normal = Vertex.Position;
			Vertex.Normal.Normalize();

			Vertices.push_back(Vertex);
		}
	}

	// ����
	Vertex.Position = FVector3(0.0f, -Radius, 0.0f);
	Vertex.TexCoord = FVector2(0.5f, 1.0f);
	Vertex.Normal = Vertex.Position;
	Vertex.Normal.Normalize();
	Vertices.push_back(Vertex);

	InGeometry->SetVertices(Vertices);

	vector<uint32> Indices(36);

	// �ϱ� �ε���
	for (uint32 Idx = 0; Idx <= SliceCount; ++Idx)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		Indices.push_back(0);
		Indices.push_back(Idx + 2);
		Indices.push_back(Idx + 1);
	}

	// ���� �ε���
	uint32 RingVertexCount = SliceCount + 1;
	for (uint32 Y = 0; Y < StackCount - 2; ++Y)
	{
		for (uint32 X = 0; X < SliceCount; ++X)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			Indices.push_back(1 + (Y)*RingVertexCount + (X));
			Indices.push_back(1 + (Y)*RingVertexCount + (X + 1));
			Indices.push_back(1 + (Y + 1) * RingVertexCount + (X));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			Indices.push_back(1 + (Y + 1) * RingVertexCount + (X));
			Indices.push_back(1 + (Y)*RingVertexCount + (X + 1));
			Indices.push_back(1 + (Y + 1) * RingVertexCount + (X + 1));
		}
	}

	// ���� �ε���
	uint32 BottomIndex = static_cast<uint32>(Vertices.size()) - 1;
	uint32 LastRingStartIndex = BottomIndex - RingVertexCount;
	for (uint32 Idx = 0; Idx < SliceCount; ++Idx)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		Indices.push_back(BottomIndex);
		Indices.push_back(LastRingStartIndex + Idx);
		Indices.push_back(LastRingStartIndex + Idx + 1);
	}

	InGeometry->SetIndices(Indices);
}
