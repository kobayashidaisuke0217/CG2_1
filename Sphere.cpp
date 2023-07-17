#include "Sphere.h"
#include<cmath>
void Sphere::Initialize(DirectXCommon* dxCommon, MyEngine* engine)
{
	
}

void Sphere::Draw(const Vector4& material, const Transform& transform, uint32_t texIndex, const Transform& cameraTransform, const DirectionalLight& light)
{
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(dxCommon_->GetWin()->kClientWidth) / float(dxCommon_->GetWin()->kClientHeight), 0.1f, 100.0f);

	Matrix4x4 wvpmatrix_ = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

	Transform uvTransform = { { 1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f} };

	Matrix4x4 uvtransformMtrix = MakeScaleMatrix(uvTransform.scale);
	uvtransformMtrix = Multiply(uvtransformMtrix, MakeRotateZMatrix(uvTransform.rotate.z));
	uvtransformMtrix = Multiply(uvtransformMtrix, MakeTranslateMatrix(uvTransform.translate));

	assert(texIndex < 2);
	//経度一つ分の角度
	const float kLonEvery = pi * 2.0f / float(kSubDivision);
	//緯度一つ分の角度
	const float kLatEvery = pi / float(kSubDivision);
	//緯度方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubDivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; ++lonIndex) {
			uint32_t start = (latIndex * kSubDivision + lonIndex) * 6;

			float lon = lonIndex * kLonEvery;
			/*頂点a*/vertexData_[start].position = { cos(lat) * cos(lon),sin(lat),cos(lat) * sin(lon),1.0f };
			vertexData_[start].texcoord = { float(lonIndex) / float(kSubDivision),1.0f - float(latIndex) / kSubDivision };

			/*頂点b*/vertexData_[start + 1].position = { cos(lat + kLatEvery) * cos(lon),sin(lat + kLatEvery),cos(lat + kLatEvery) * sin(lon),1.0f };
			vertexData_[start + 1].texcoord = { vertexData_[start].texcoord.x,vertexData_[start].texcoord.y - 1.0f / float(kSubDivision) };

			/*頂点c*/vertexData_[start + 2].position = { cos(lat) * cos(lon + kLonEvery),sin(lat),cos(lat) * sin(lon + kLonEvery),1.0f };
			vertexData_[start + 2].texcoord = { vertexData_[start].texcoord.x + 1.0f / float(kSubDivision),vertexData_[start].texcoord.y };

			/*頂点c*/vertexData_[start + 3].position = { cos(lat) * cos(lon + kLonEvery),sin(lat),cos(lat) * sin(lon + kLonEvery),1.0f };
			vertexData_[start + 3].texcoord = { vertexData_[start].texcoord.x + 1.0f / float(kSubDivision),vertexData_[start].texcoord.y };

			/*頂点b*/vertexData_[start + 4].position = { cos(lat + kLatEvery) * cos(lon),sin(lat + kLatEvery),cos(lat + kLatEvery) * sin(lon),1.0f };
			vertexData_[start + 4].texcoord = { vertexData_[start].texcoord.x,vertexData_[start].texcoord.y - 1.0f / float(kSubDivision) };

			/*頂点d*/vertexData_[start + 5].position = { cos(lat + kLatEvery) * cos(lon + kLonEvery),sin(lat + kLatEvery), cos(lat + kLatEvery) * sin(lon + kLonEvery),1.0f };
			vertexData_[start + 5].texcoord = { vertexData_[start].texcoord.x + 1.0f / float(kSubDivision),vertexData_[start].texcoord.y - 1.0f / float(kSubDivision) };

			vertexData_[start].normal.x = vertexData_[start].position.x;
			vertexData_[start].normal.y = vertexData_[start].position.y;
			vertexData_[start].normal.z = vertexData_[start].position.z;
			vertexData_[start + 1].normal.x = vertexData_[start + 1].position.x;
			vertexData_[start + 1].normal.y = vertexData_[start + 1].position.y;
			vertexData_[start + 1].normal.z = vertexData_[start + 1].position.z;
			vertexData_[start + 2].normal.x = vertexData_[start + 2].position.x;
			vertexData_[start + 2].normal.y = vertexData_[start + 2].position.y;
			vertexData_[start + 2].normal.z = vertexData_[start + 2].position.z;
			vertexData_[start + 3].normal.x = vertexData_[start + 3].position.x;
			vertexData_[start + 3].normal.y = vertexData_[start + 3].position.y;
			vertexData_[start + 3].normal.z = vertexData_[start + 3].position.z;
			vertexData_[start + 4].normal.x = vertexData_[start + 4].position.x;
			vertexData_[start + 4].normal.y = vertexData_[start + 4].position.y;
			vertexData_[start + 4].normal.z = vertexData_[start + 4].position.z;
			vertexData_[start + 5].normal.x = vertexData_[start + 5].position.x;
			vertexData_[start + 5].normal.y = vertexData_[start + 5].position.y;
			vertexData_[start + 5].normal.z = vertexData_[start + 5].position.z;




		}
	}

	*materialData_ = { material,true };
	materialData_->uvTransform = uvtransformMtrix;
	*wvpData_ = { wvpmatrix_,worldMatrix };
	*directionalLight_ = light;
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//形状を設定。PS0にせっていしているものとはまた別。同じものを設定すると考えておけばいい
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource_->GetGPUVirtualAddress());
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource_->GetGPUVirtualAddress());

	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, engine_->textureSrvHandleGPU_[texIndex]);
	dxCommon_->GetCommandList()->DrawInstanced(vertexCount, 1, 0, 0);

}


void Sphere::Finalize()
{
	vertexResource->Release();
	materialResource_->Release();
	wvpResource_->Release();
	directionalLightResource_->Release();
	
}

void Sphere::CreateVartexData()
{
	vertexResource = dxCommon_->CreateBufferResource(dxCommon_->GetDevice(), sizeof(VertexData) *vertexCount);


	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();

	vertexBufferView.SizeInBytes = sizeof(VertexData) * vertexCount;

	vertexBufferView.StrideInBytes = sizeof(VertexData);

	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	/*indexResource_ = dxCommon_->CreateBufferResource(dxCommon_->GetDevice(), sizeof(uint32_t) * 6);

	indexBufferView.BufferLocation = indexResource_->GetGPUVirtualAddress();

	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;

	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));*/
}



void Sphere::TransformMatrix()
{
	wvpResource_ = DirectXCommon::CreateBufferResource(dxCommon_->GetDevice(), sizeof(Transformmatrix));
	wvpResource_->Map(0, NULL, reinterpret_cast<void**>(&wvpData_));
	wvpData_->WVP = MakeIdentity4x4();
}
void Sphere::CreateDictionalLight()
{
	directionalLightResource_ = DirectXCommon::CreateBufferResource(dxCommon_->GetDevice(), sizeof(DirectionalLight));
	directionalLightResource_->Map(0, NULL, reinterpret_cast<void**>(&directionalLight_));
}
void Sphere::SetColor() {
	materialResource_ = DirectXCommon::CreateBufferResource(dxCommon_->GetDevice(), sizeof(Material));
	
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	materialData_->uvTransform = MakeIdentity4x4();
}
