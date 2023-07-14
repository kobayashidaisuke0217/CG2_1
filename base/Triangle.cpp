#include "Triangle.h"
#include<assert.h>
#include"base/MyEngine.h"

void Triangle::Initialize(DirectXCommon* direct,MyEngine*engine)
{
	Engine = engine;
	direct_ = direct;
	SettingVertex();
	SetColor();
	TransformMatrix();
	CreateDictionalLight();
}
void Triangle::TransformMatrix()
{
	wvpResource_ = DirectXCommon::CreateBufferResource(direct_->GetDevice(), sizeof(Transformmatrix));
	wvpResource_->Map(0, NULL, reinterpret_cast<void**>(&wvpData_));
	wvpData_->WVP = MakeIdentity4x4();
}
void Triangle::SetColor() {
	materialResource_ = DirectXCommon::CreateBufferResource(direct_->GetDevice(), sizeof(Material));

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
}
void Triangle::Draw(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& material, const Transform& transform, const Transform& cameraTransform,const DirectionalLight& light)
{
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(direct_->GetWin()->kClientWidth) / float(direct_->GetWin()->kClientHeight), 0.1f, 100.0f);

	Matrix4x4 wvpmatrix_ = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	vertexData_[0].position = a;
	vertexData_[0].texcoord = { 0.0f,1.0f };
	
	//上
	vertexData_[1].position = b;
	vertexData_[1].texcoord = { 0.5f,0.0f };
	
	//右下
	vertexData_[2].position = c;
	vertexData_[2].texcoord = { 1.0f,1.0f };
	
	*materialData_ = { material,false };
	*wvpData_ = {wvpmatrix_,worldMatrix};
	*directionalLight_ = light;
	direct_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);//VBVを設定
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定すると考えておけばいい
	direct_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    direct_->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource_->GetGPUVirtualAddress());
	direct_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	direct_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());
	direct_->GetCommandList()->SetGraphicsRootDescriptorTable(2,Engine->textureSrvHandleGPU_[0]);
	

	//描画！(DrawCall/ドローコール)・3頂点で1つのインスタンス。インスタンスについては今後
	direct_->GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
void Triangle::Finalize()
{
	vertexResource_->Release();
	materialResource_->Release();
	wvpResource_->Release();
	directionalLightResource_->Release();
}
void Triangle::CreateDictionalLight()
{
	directionalLightResource_ = DirectXCommon::CreateBufferResource(direct_->GetDevice(), sizeof(DirectionalLight));
	directionalLightResource_->Map(0, NULL, reinterpret_cast<void**>(&directionalLight_));
}
void Triangle::SettingVertex() {

	vertexResource_ = DirectXCommon::CreateBufferResource(direct_->GetDevice(), sizeof(VertexData) * 3);
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * 3;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

}
