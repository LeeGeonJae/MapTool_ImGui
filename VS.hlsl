
cbuffer TEST_B0 : register(b0)
{
    float4 offset0;
};

struct VSInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VSOutput main(VSInput vsInput)
{
    VSOutput vsOutput;

    vsOutput.position = vsInput.position;
    output.position += offset0;
    vsOutput.uv = vsInput.uv;

    return vsOutput;
}
