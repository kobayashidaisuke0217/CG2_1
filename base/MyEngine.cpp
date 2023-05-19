#include "MyEngine.h"
#include <assert.h>




IDxcBlob* MyEngine::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler)
{
	//これからシェーダーをコンパイルする旨をログに出す
	Log(ConvertString(std::format(L"Begin CompileShader, path:{},profile:{}\n", filePath, profile)));
	//hlslファイルを読む
	IDxcBlobEncoding* shaderSource = nullptr;
	direct_->SetHr(dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource));
	//嫁なかったら決める
	assert(SUCCEEDED(direct_->GetHr()));
	//読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;
	LPCWSTR arguments[] = {
		filePath.c_str(),//コンパイル対象のhlslファイル名
		L"-E",L"main",//エントリーポイントの指定。基本的にmain以外にはしない
		L"-T",profile,//ShaderProflieの設定
		L"-Zi",L"-Qembed_debug",//デバッグ用の情報を埋め込む
		L"-Od", //最適化を外しておく
		L"-Zpr",//メモリレイアウトは行優先
	};
	//実際にShaderをコンパイルする
	IDxcResult* shaderResult = nullptr;
	direct_->SetHr(dxcCompiler->Compile(
		&shaderSourceBuffer,//読み込んだファイル
		arguments,//コンパイルオプション
		_countof(arguments),//コンパイルオプションの数
		includeHandler, // includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult)//コンパイル結果
	));
	//コンパイルエラーではなくdxcが起動できないなど致命的な状況
	assert(SUCCEEDED(direct_->GetHr()));

	//警告・エラーが出たらログに出して止める
	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		Log(shaderError->GetStringPointer());
		//警告・エラーダメ絶対
		assert(false);
	}
	//コンパイル結果から実行用のバイナリ部分を取得
	IDxcBlob* shaderBlob = nullptr;
	direct_->SetHr( shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr));
	assert(SUCCEEDED(direct_->GetHr()));
	//成功したログを出す
	Log(ConvertString(std::format(L"Compile Succeeded, path:{},profile:{}\n", filePath, profile)));
	//もう使わないリソースを開放
	shaderSource->Release();
	shaderResult->Release();
	//実行用のバイナリを返却
	return shaderBlob;
}

void MyEngine::InitializeDxcCompiler()
{
	HRESULT hr;
	dxcUtils_ = nullptr;
	dxcCompiler_ = nullptr;
	hr= DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr));
	hr= DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr));
	//現時点でincludeはしないが、includeに対応するための設定を行っていく
	includeHandler_ = nullptr;
	hr =dxcUtils_->CreateDefaultIncludeHandler(&includeHandler_);
	assert(SUCCEEDED(hr));

}
void MyEngine::CreateRootSignature() {
	//RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//シリアライズしてバイナリにする
	signatureBlob_ = nullptr;
	errorBlob_ = nullptr;
	HRESULT hr;
	hr= D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob_, &errorBlob_);
	if (FAILED(direct_->GetHr())) {
		Log(reinterpret_cast<char*>(errorBlob_->GetBufferPointer()));
		assert(false);
	}
	//バイナリを元に生成
	rootSignature_ = nullptr;
	hr= direct_->GetDevice()->CreateRootSignature(0, signatureBlob_->GetBufferPointer(),
		signatureBlob_->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	assert(SUCCEEDED(hr));
}
void MyEngine::CreateInputlayOut() {
	//inputElementDescsをメンバ変数にすると治った
	inputElementDescs_[0].SemanticName = "POSITION";
	inputElementDescs_[0].SemanticIndex = 0;
	inputElementDescs_[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs_[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	inputLayoutDesc_.pInputElementDescs = inputElementDescs_;
	inputLayoutDesc_.NumElements = _countof(inputElementDescs_);
}
void MyEngine::SettingBlendState() {

	//すべての色要素を書き込む
	blendDesc_.RenderTarget[0].RenderTargetWriteMask =
		D3D12_COLOR_WRITE_ENABLE_ALL;
}
void MyEngine::SettingRasterizerState() {

	//裏面（時計回り）を表示しない
	rasterizerDesc_.CullMode = D3D12_CULL_MODE_BACK;
	//三角形の中を塗りつぶす
	rasterizerDesc_.FillMode = D3D12_FILL_MODE_SOLID;

	//Shaderをコンパイルする
	vertexShaderBlob_ = CompileShader(L"Object3d.VS.hlsl",
		L"vs_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(vertexShaderBlob_ != nullptr);


	pixelShaderBlob_ = CompileShader(L"Object3d.PS.hlsl",
		L"ps_6_0", dxcUtils_, dxcCompiler_, includeHandler_);
	assert(pixelShaderBlob_ != nullptr);
}
void MyEngine::InitializePSO() {

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = rootSignature_;//RootSignature
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc_;//Inputlayout
	graphicsPipelineStateDesc.VS = { vertexShaderBlob_->GetBufferPointer(),
		vertexShaderBlob_->GetBufferSize() };//vertexShader
	graphicsPipelineStateDesc.PS = { pixelShaderBlob_->GetBufferPointer(),
		pixelShaderBlob_->GetBufferSize() };//pixcelShader
	graphicsPipelineStateDesc.BlendState = blendDesc_;//BlendState
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc_;//rasterizerState
	//書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	//利用するトポロジ（形状）のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType =
		D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//どのように画面に色を打ち込むのかの設定（気にしなく良い）
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	//実際に生成
	graphicsPipelineState_ = nullptr;
	HRESULT hr= direct_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState_));
	assert(SUCCEEDED(hr));
}
void MyEngine::SettingVertex() {
	
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uplodeHeapProperties{};
	uplodeHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う
	//頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	vertexResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	vertexResourceDesc.Width = sizeof(Vector4) * 3;//リソースサイズ　今回はvector4を四分割
	//バッファの場合はこれらは１にする決まり
	vertexResourceDesc.Height = 1;
	vertexResourceDesc.DepthOrArraySize = 1;
	vertexResourceDesc.MipLevels = 1;
	vertexResourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	vertexResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;

	//実際に頂点リソースを作る
	 hr = direct_->GetDevice()-> CreateCommittedResource(&uplodeHeapProperties, D3D12_HEAP_FLAG_NONE,
		&vertexResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexResource_));
	assert(SUCCEEDED(hr));
	//リソースの先頭のアドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(Vector4) * 3;
	//1頂点当たりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(Vector4);
	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

}
void MyEngine::SettingViePort() {
	//クライアント領域のサイズと一緒にして画面全体に表示
	viewport_.Width = WinApp::kClientWidth;
	viewport_.Height = WinApp::kClientHeight;
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;
}
void MyEngine::SettingScissor() {
	//基本的にビューポートと同じく敬が構成されるようにする
	scissorRect_.left = 0;
	scissorRect_.right = WinApp::kClientWidth;
	scissorRect_.top = 0;
	scissorRect_.bottom = WinApp::kClientHeight;
}
void MyEngine::variableInitialize()
{
		data1[0] = { -0.2f,-0.1f,0.0f,1.0f };
		data2[0] = { -0.15f,0.1f,0.0f,1.0f };
		data3[0] = { -0.1f,-0.1f,0.0f,1.0f };

		data1[1] = { -0.2f,-0.3f,0.0f,1.0f };
		data2[1] = { -0.15f,-0.1f,0.0f,1.0f };
		data3[1] = { -0.1f,-0.3f,0.0f,1.0f };

		data1[2] = { -0.2f,-0.5f,0.0f,1.0f };
		data2[2] = { -0.15f,-0.3f,0.0f,1.0f };
		data3[2] = { -0.1f,-0.5f,0.0f,1.0f };

		data1[3] = { -0.2f,-0.7f,0.0f,1.0f };
		data2[3] = { -0.15f,-0.5f,0.0f,1.0f };
		data3[3] = { -0.1f,-0.7f,0.0f,1.0f };

		data1[4] = { -0.2f,-0.9f,0.0f,1.0f };
		data2[4] = { -0.15f,-0.7f,0.0f,1.0f };
		data3[4] = { -0.1f,-0.9f,0.0f,1.0f };

		data1[5] = { -0.2f,0.7f,0.0f,1.0f };
		data2[5] = { -0.15f,0.9f,0.0f,1.0f };
		data3[5] = { -0.1f,0.7f,0.0f,1.0f };

		data1[6] = { -0.2f,0.5f,0.0f,1.0f };
		data2[6] = { -0.15f,0.7f,0.0f,1.0f };
		data3[6] = { -0.1f,0.5f,0.0f,1.0f };

		data1[7] = { -0.2f,0.3f,0.0f,1.0f };
		data2[7] = { -0.15f,0.5f,0.0f,1.0f };
		data3[7] = { -0.1f,0.3f,0.0f,1.0f };

		data1[8] = { -0.2f,0.1f,0.0f,1.0f };
		data2[8] = { -0.15f,0.3f,0.0f,1.0f };
		data3[8] = { -0.1f,0.1f,0.0f,1.0f };

		data1[9] = { -0.5f,-0.5f,0.0f,1.0f };
		data2[9] = { -0.4f,-0.3f,0.0f,1.0f };
		data3[9] = { -0.3f,-0.5f,0.0f,1.0f };
	
	for (int i = 0; i < 10; i++) {
		triangle[i] = new DrawTriangle();
		triangle[i]->Initialize(direct_);
	}
	
}
void MyEngine::Initialize(WinApp* win, int32_t width, int32_t height) {
	direct_->Initialize(win, win->kClientWidth, win->kClientHeight);
    
	InitializeDxcCompiler();
	

	CreateRootSignature();
	CreateInputlayOut();
	
	
	SettingBlendState();

	SettingRasterizerState();

	InitializePSO();

	SettingViePort();

	SettingScissor();

}


void MyEngine::BeginFrame() {
	direct_->PreDraw();
	direct_->GetCommandList()->RSSetViewports(1, &viewport_);//viewportを設定
	direct_->GetCommandList()->RSSetScissorRects(1, &scissorRect_);//scirssorを設定
	//RootSignatureを設定。PS0に設定しているけど別途設定が必要
	direct_->GetCommandList()->SetGraphicsRootSignature(rootSignature_);
	direct_->GetCommandList()->SetPipelineState(graphicsPipelineState_);//PS0を設定
}
void MyEngine::EndFrame() {
	direct_->PostDraw();
	
}

void MyEngine::Finalize()
{
	for (int i = 0; i < 10; i++) {
		triangle[i]->Finalize();
	}
	graphicsPipelineState_->Release();
	signatureBlob_->Release();
if (errorBlob_) {
		errorBlob_->Release();
	}
	rootSignature_->Release();
	pixelShaderBlob_->Release();
	vertexShaderBlob_->Release();
	direct_->Finalize();
	

	
}
void MyEngine::Update()
{

}
void MyEngine::Draw()
{
	for (int i = 0; i < 10; i++) {
		triangle[i]->Draw(data1[i], data2[i], data3[i]);
	}
	
}

WinApp*MyEngine:: win_;
DirectXCommon* MyEngine::direct_;