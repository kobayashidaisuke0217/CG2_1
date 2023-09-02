#include"Object3D.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);


VertexShaderOutput main(VertexShaderInput input) {
	VertexShaderOutput output;
	output.position = mul(input.position, gTransformationMatrix.matWorld);
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float32_t3x3)gTransformationMatrix.matWorld));
	
	return output;

}