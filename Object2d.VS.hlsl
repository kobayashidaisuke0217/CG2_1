#include"Object2D.hlsli"

//ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);


VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	output.position = input.position;
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float32_t3x3)gTransformationMatrix.World));

	return output;

}
