#include "Triangle.h"
#include<assert.h>
#include"MyEngine.h"

void Triangle::Initialize(DirectXCommon* direct,MyEngine*engine)
{
	direct_ = direct;
	engine_ = engine;
	SettingVertex();
	SetColor();
	TransformMatrix();
}
void Triangle::SetColor() {
	 MaterialResource_ = CreateBufferResource(direct_->GetDevice(), sizeof(VertexData));
	
	MaterialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
}
void Triangle::TransformMatrix()
{
	wvpResource_ = CreateBufferResource(direct_->GetDevice(), sizeof(Matrix4x4));
	wvpResource_->Map  (0, NULL, reinterpret_cast<void**>(&wvpData_));
	*wvpData_ = MakeIdentity4x4();
}
void Triangle::Draw(const Vector4& a, const Vector4& b, const Vector4& c,const Vector4& material,const Matrix4x4& wvpdata)
{

	//左下
	vertexData_[0].position = a;
	vertexData_[0].texcoord = { 0.0f,1.0f };
	//上
	vertexData_[1].position = b;
	vertexData_[1].texcoord = { 0.5f,0.0f };
	//右下
	vertexData_[2].position = c;
	vertexData_[2].texcoord = { 1.0f,1.0f };
	*materialData_ = material;
	
	*wvpData_ = wvpdata;
	direct_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);//VBVを設定
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定すると考えておけばいい
	direct_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	direct_->GetCommandList()->SetGraphicsRootConstantBufferView(0, MaterialResource_->GetGPUVirtualAddress());//material用のCBufferの場所を設定

	direct_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());
	//srvのDescriptortableの先頭を設定2はrootParameter[2]である
	direct_->GetCommandList()->SetGraphicsRootDescriptorTable(2, engine_->GetSRVHandleGPU());
	//描画！(DrawCall/ドローコール)・3頂点で1つのインスタンス。インスタンスについては今後
	direct_->GetCommandList()->DrawInstanced(3, 1, 0, 0);

}
void Triangle::Finalize()
{
	wvpResource_->Release();
	MaterialResource_->Release();
	vertexResource_->Release();
	
}
void Triangle::SettingVertex() {

	
	vertexResource_=   CreateBufferResource(direct_->GetDevice(), sizeof(VertexData) * 3);
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(VertexData) * 3;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(VertexData);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

}

 ID3D12Resource* Triangle::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes)
{
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uplodeHeapProperties{};
	uplodeHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う
	//頂点リソースの設定
	D3D12_RESOURCE_DESC ResourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInBytes;//リソースサイズ
	//バッファの場合はこれらは１にする決まり
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;
	ID3D12Resource* Resource=nullptr;
	//実際に頂点リソースを作る
	hr = device->CreateCommittedResource(&uplodeHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&Resource));
	assert(SUCCEEDED(hr));
	
	return Resource ;
}
