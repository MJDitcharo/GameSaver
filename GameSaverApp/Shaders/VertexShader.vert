
cbuffer VSInput
{
[vk::location(0)] float3 Position : POSITION0;
[vk::location(1)] float3 Color : COLOR0;
};


float4 main(float2 input : POSITION) : SV_POSITION
{
    return float4(input, 0, 1);
}