//VS
struct VS_INPUT
{
	float4 Position : POSITION0;
	float4 TexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Position : POSITION0;
	float4 TexCoord : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.Position = Input.Position;
	Output.TexCoord = Input.TexCoord;

	return(Output);
}

//PS
//sampler NormalSampler;
//sampler PositionSampler;
//sampler DepthSampler;

//Texture2D txNormal : register(t1);
//Texture2D txPosition : register(t2);
//Texture2D txDepth : register(t3);
//
//float2 fViewPortDimensions;
//
//float Sample_radius;
//float Intensity;
//float Scale;
//float Bias;
//
//struct PS_INPUT
//{
//	float4 TexCoord : TEXCOORD0;
//};
//
//float4 GetPosition(in float2 uv)
//{
//	return tex2D(PositionSampler, uv);
//}
//
//float3 GetNormal(in float2 uv)
//{
//	return normalize(tex2D(NormalSampler, uv).xyz * 2.0f - 1.0f);
//}
//
//float3 GetRandom(in float2 uv)
//{
//	float noiseX = frac(sin(dot(uv, float2(15.8989f, 76.132f)*1.0f))*46336.23745f);
//	float noiseY = frac(sin(dot(uv, float2(11.6566f, 62.223f)*2.0f))*34748.34744f);
//	float noiseZ = frac(sin(dot(uv, float2(13.3238f, 63.122f)*3.0f))*59998.47362f);
//
//	return normalize(float3(noiseX, noiseY, noiseZ));
//}
//
//float DoAmbientOcclusion(in float2 tcoord, in float2 uv, in float3 p, in float3 cnorm)
//{
//	float3 diff = GetPosition(tcoord + uv) - p;
//	const float3 v = normalize(diff);
//	const float d = length(diff)* Scale;
//
//	return max(0.0f, dot(cnorm, v) - Bias) * (1.0f / (1.0 + d))* Intensity;
//}
//
//float4 ps_main(PS_INPUT Input) : COLOR0
//{
//	float4 FinalColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
//
//	const float2 vec[4] =
//	{
//		float2(1,0), float2(-1,0), float2(0,1), float2(0,-1)
//	};
//
//	float4 p = GetPosition(Input.TexCoord);
//
//	float3 n = GetNormal(Input.TexCoord);
//	float2 rand = GetRandom(Input.TexCoord);
//
//	float ao = 0.0f;
//	float rad = Sample_radius / p.z;
//
//	int iterations = 4;
//
//	for (int j = 0; j < iterations; j++)
//	{
//		float2 coord1 = reflect(vec[j], rand)*rad;
//		float2 coord2 = float2(coord1.x - coord1.y*0.707,
//			coord1.x + coord1.y*0.707);
//
//		ao += DoAmbientOcclusion(Input.TexCoord, coord1 * 0.25, p.xyz, n);
//		ao += DoAmbientOcclusion(Input.TexCoord, coord2 * 0.05, p.xyz, n);
//		ao += DoAmbientOcclusion(Input.TexCoord, coord1 * 0.75, p.xyz, n);
//		ao += DoAmbientOcclusion(Input.TexCoord, coord2, p.xyz, n);
//	}
//
//	ao /= (iterations * 4);
//
//	FinalColor = float4(1 - ao.xxx,1.0f);
//
//	return FinalColor;
//}