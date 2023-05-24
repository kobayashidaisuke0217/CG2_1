#pragma once
#include<base/DirectXCommon.h>
#include"Vector4.h"
#include<math/matrixCalc.h>


class Triangle
{
public:
	void Initialize(DirectXCommon* direct);
	void Draw(const Vector4& a,const Vector4& b,const Vector4& c,const Vector4& material, const Matrix4x4& wvpdata);
	void Finalize();
	
private:
	void SettingVertex();

	
	void SetColor();

	void TransformMatrix();
private:
	ID3D12Resource* MaterialResource_;
	DirectXCommon* direct_;
	Vector4* vertexData_;
	ID3D12Resource* vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	Vector4* materialData_;
	ID3D12Resource* wvpResource_;
	Matrix4x4* wvpData_;

	
};

