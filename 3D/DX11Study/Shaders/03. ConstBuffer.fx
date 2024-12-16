matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VertexOutput
{
	float4 position : POSITION;
	float4 color : COLOR;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);
	output.color = input.color;
	
	return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
	return input.color;
}

RasterizerState FillModeWireFrame
{
	FillMode = WireFrame;
};

technique11 TO
{
	pass PO
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetRasterizerState(FillModeWireFrame);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}