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
	direct_->SetHr(shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr));
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
	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils_));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler_));
	assert(SUCCEEDED(hr));
	//現時点でincludeはしないが、includeに対応するための設定を行っていく
	includeHandler_ = nullptr;
	hr = dxcUtils_->CreateDefaultIncludeHandler(&includeHandler_);
	assert(SUCCEEDED(hr));

}
void MyEngine::CreateRootSignature() {
	//RootSignature作成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	//RootParameter作成。複数設定できるので配列。今回は結果1つだけなので長さ１の配列
	D3D12_ROOT_PARAMETER rootParameters[2] = {};
	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//CBVを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//pixelShaderを使う
	rootParameters[0].Descriptor.ShaderRegister = 0;//レジスタ番号0とバインド
	rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//CBVを使う
	rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;//vertexShaderを使う
	rootParameters[1].Descriptor.ShaderRegister = 0;//レジスタ番号0とバインド
	descriptionRootSignature.pParameters = rootParameters;//ルートパラメータ配列へのポインタ
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	//シリアライズしてバイナリにする
	signatureBlob_ = nullptr;
	errorBlob_ = nullptr;
	HRESULT hr;
	hr = D3D12SerializeRootSignature(&descriptionRootSignature,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob_, &errorBlob_);
	if (FAILED(direct_->GetHr())) {
		Log(reinterpret_cast<char*>(errorBlob_->GetBufferPointer()));
		assert(false);
	}
	//バイナリを元に生成
	rootSignature_ = nullptr;
	hr = direct_->GetDevice()->CreateRootSignature(0, signatureBlob_->GetBufferPointer(),
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
	HRESULT hr = direct_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc,
		IID_PPV_ARGS(&graphicsPipelineState_));
	assert(SUCCEEDED(hr));
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
	data1[0] = { -0.4f,-0.1f,0.0f,1.0f };
	data2[0] = { 0.0f,0.1f,0.0f,1.0f };
	data3[0] = { 0.4f,-0.1f,0.0f,1.0f };
	material[0] = { 0.1f,1.0f,1.0f,1.0f };

	data1[1] = { -0.4f,-0.3f,0.0f,1.0f };
	data2[1] = { 0.0f,-0.1f,0.0f,1.0f };
	data3[1] = { 0.4f,-0.3f,0.0f,1.0f };
	material[1] = { 1.0f,0.1f,1.0f,1.0f };

	data1[2] = { -0.4f,-0.5f,0.0f,1.0f };
	data2[2] = { 0.0f,-0.3f,0.0f,1.0f };
	data3[2] = { 0.4f,-0.5f,0.0f,1.0f };
	material[2] = { 1.0f,1.0f,0.1f,1.0f };
	cameraTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
	

	vertexTransform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	for (int i = 0; i < 3; i++) {
		triangle[i] = new Triangle();
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
	direct_->ImGuiInitialize();

}


void MyEngine::BeginFrame() {
	direct_->PreDraw();
	direct_->GetCommandList()->RSSetViewports(1, &viewport_);//viewportを設定
	direct_->GetCommandList()->RSSetScissorRects(1, &scissorRect_);//scirssorを設定
	//RootSignatureを設定。PS0に設定しているけど別途設定が必要
	direct_->GetCommandList()->SetGraphicsRootSignature(rootSignature_);
	direct_->GetCommandList()->SetPipelineState(graphicsPipelineState_);//PS0を設定
	ImGui::ShowDemoWindow();
}
void MyEngine::EndFrame() {
	ImGui::Render();
	direct_->PostDraw();

}

void MyEngine::Finalize()
{
	
	for (int i = 0; i < 3; i++) {
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
	 worldMatrix_ = MakeAffineMatrix(vertexTransform_.scale , vertexTransform_.rotate, vertexTransform_.translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraTransform_.scale,cameraTransform_.rotate,cameraTransform_.translate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(win_->kClientWidth) / float(win_->kClientHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix_, Multiply(viewMatrix, projectionMatrix));
	

	material[0].x += 0.5f;
	vertexTransform_.rotate.y -= 0.05f;
  
  worldMatrix_ = worldViewProjectionMatrix;
  ImGui::Begin("Window");
  ImGui::DragFloat3("CameraTranslate", &cameraTransform_.translate.x, 0.01f);
  
  ImGui::End();
}
void MyEngine::Draw()
{
	for (int i = 0; i < 3; i++) {
		triangle[i]->Draw(data1[i], data2[i], data3[i],material[i],worldMatrix_);
	}

}

WinApp* MyEngine::win_;
DirectXCommon* MyEngine::direct_;