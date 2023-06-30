#include "./Flax/GUICommon.hlsl"

struct BasicVertex
{
    float2 Position : POSITION0;
    float2 TexCoord : TEXCOORD0;
    float4 Color : COLOR0;
    float2 ClipOrigin : TEXCOORD1;
    float4 ClipExtents : TEXCOORD2;
};

META_CB_BEGIN(0, Data)
float4x4 ViewProjection;
float4x4 Model;
float2 Offset;
float2 Dummy1;
META_CB_END

Texture2D Image : register(t0);

META_VS(true, FEATURE_LEVEL_ES2)
META_VS_IN_ELEMENT(POSITION, 0, R32G32_FLOAT,       0, ALIGN, PER_VERTEX, 0, true)
META_VS_IN_ELEMENT(TEXCOORD, 0, R16G16_FLOAT,       0, ALIGN, PER_VERTEX, 0, true)
META_VS_IN_ELEMENT(COLOR,    0, R32G32B32A32_FLOAT, 0, ALIGN, PER_VERTEX, 0, true)
META_VS_IN_ELEMENT(TEXCOORD, 1, R32G32_FLOAT,       0, 0,     PER_VERTEX, 0, true)
META_VS_IN_ELEMENT(TEXCOORD, 2, R32G32B32A32_FLOAT, 0, ALIGN, PER_VERTEX, 0, true)
VS2PS VS(BasicVertex input)
{
    VS2PS output;

    output.Position = mul(mul(float4(input.Position + Offset, 0, 1), Model), ViewProjection);
    output.Color = input.Color;
    output.TexCoord = input.TexCoord;
    output.ClipOriginAndPos = float4(input.ClipOrigin.xy, input.Position);
    output.ClipExtents = input.ClipExtents;
    output.CustomData = input.ClipOrigin.xy;

    return output;
}

META_PS(true, FEATURE_LEVEL_ES2)
float4 PS_Image(VS2PS input) : SV_Target0
{
    PerformClipping(input);

    return Image.Sample(SamplerLinearClamp, input.TexCoord) * input.Color;
}

META_PS(true, FEATURE_LEVEL_ES2)
float4 PS_Font(VS2PS input) : SV_Target0
{
    PerformClipping(input);

    float4 color = input.Color;
    color.a *= Image.Sample(SamplerLinearClamp, input.TexCoord).r;
    return color;
}

META_PS(true, FEATURE_LEVEL_ES2)
float4 PS_Color(VS2PS input) : SV_Target0
{
    PerformClipping(input);

    return input.Color;
}