cbuffer cbView : register(b0)
{
	matrix View;
};

cbuffer cbProj : register(b1)
{
	matrix Projection;
};

cbuffer cbWorld : register(b2)
{
	matrix World;
};

cbuffer cbColor : register(b3)
{
	float4 Color;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 WorldPos : TEXCOORD1;
	float4 Color : TEXCOORD2;
};

struct PS_OUTPUT
{
	float4 Color : SV_Target0;
	float4 WorldPos : SV_Target1;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.WorldPos = input.Pos;

	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	float4 viewpos = output.Pos;
	output.Pos = mul(output.Pos, Projection);

	output.Color = Color;

	return output;
}

PS_OUTPUT PS(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	output.Color = input.Color;
	output.WorldPos = input.WorldPos;

	return output;
}