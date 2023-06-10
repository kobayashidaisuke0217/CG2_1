#pragma once
#include<base/DirectXCommon.h>
#include"Vector4.h"
class MyEngine;

class Triangle
{
public:
	void Initialize(DirectXCommon* direct);
	void Draw(const Vector4& a,const Vector4& b,const Vector4& c);
	void Finalize();
	
private:
	void SettingVertex();

private:
	//MyEngine* Engine;
	DirectXCommon* direct_;
	Vector4* vertexData_;
	ID3D12Resource* vertexResource_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	
};

