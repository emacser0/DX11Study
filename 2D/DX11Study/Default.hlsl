struct VS_INPUT
{
	float4 position : POSITION;
//	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer TransformData : register(b0)
{
	row_major matrix world;
	row_major matrix view;
	row_major matrix projection;
}

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	float4 position = mul(input.position, world);
	position = mul(position, view);
	position = mul(position, projection);

	output.position = position;
	output.texCoord = input.texCoord;

	return output;
}

Texture2D texture0 : register(t0);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	float4 color = texture0.Sample(sampler0, input.texCoord);

	return color;
}