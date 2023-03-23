//========================================
// 
// メイン処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** main.cpp ***
//========================================
#include "main.h"
#include "_R.N.Lib/RNmain.h"
// Mode
#include "Mode\md_title.h"
#include "Mode\md_game.h"
#include "Mode\md_result.h"

//****************************************
// マクロ定義
//****************************************
// ウインドウの名前
#define WINDOW_NAME	"R.N.ModelViewer"
// ウインドウクラス
#define CLASS_NAME "WindowClass"
// 初期のモード
#define INIT_MODE (MODE_TITLE)
// 背景色
#define BGCOLOR Color{90,90,90,255}

//****************************************
// プロトタイプ宣言
//****************************************
// モードに応じた初期化処理
void ModeInit(MODE mode);
// モードに応じた終了処理
void ModeUninit(MODE mode);
// モードに応じた更新処理
void ModeUpdate(MODE mode);
// モードに応じた描画処理
void ModeDraw(MODE mode);
// 初期化処理
HRESULT Init(HINSTANCE hInstance);
// 終了処理
void Uninit(void);
// 更新処理
void Update(void);
// 描画処理
void Draw(void);
// 読み込み処理
void Load(void);
// 書き込み処理
void Save(void);
// ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************************************
// グローバル変数宣言
//****************************************
static Main g_main;								// メイン処理の情報構造体

//============================================================
//--------------------| *** モードに応じた処理 *** |----------
//============================================================
#if 1
//========================================
// ModeInit関数 - モードに応じた初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void ModeInit(MODE mode) {
	switch (mode) {
	case MODE_TITLE:InitMd_title(); break;
	case MODE_GAME:InitMd_game(); break;
	case MODE_RESULT:InitMd_result(); break;
	}
}

//========================================
// ModeUninit関数 - モードに応じた終了処理 -
// Author:RIKU NISHIMURA
//========================================
void ModeUninit(MODE mode) {
	switch (mode) {
	case MODE_TITLE:UninitMd_title(); break;
	case MODE_GAME:UninitMd_game(); break;
	case MODE_RESULT:UninitMd_result(); break;
	}
}

//========================================
// ModeUpdate関数 - モードに応じた更新処理 -
// Author:RIKU NISHIMURA
//========================================
void ModeUpdate(MODE mode) {
	switch (mode) {
	case MODE_TITLE:UpdateMd_title(); break;
	case MODE_GAME:UpdateMd_game(); break;
	case MODE_RESULT:UpdateMd_result(); break;
	}
}

//========================================
// ModeDraw関数 - モードに応じた描画処理 -
// Author:RIKU NISHIMURA
//========================================
void ModeDraw(MODE mode) {
	switch (mode) {
	case MODE_TITLE:DrawMd_title(); break;
	case MODE_GAME:DrawMd_game(); break;
	case MODE_RESULT:DrawMd_result(); break;
	}
}
#endif
//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================
#if 1
//========================================
// Init関数 - 初期化処理 -
// Author:RIKU NISHIMURA
//========================================
HRESULT Init(HINSTANCE hInstance)
{
	// 読み込み処理
	Load();

	// R.N.Libの初期化処理
	RNInit(hInstance);
	
	// モードを設定する
	SetMode(INIT_MODE);

	// 背景色を設定
	SetBackgroundColor(BGCOLOR);

	return S_OK;
}

//========================================
// Uninit関数 - 終了処理 -
// Author:RIKU NISHIMURA
//========================================
void Uninit(void)
{
	// 書き込み処理
	Save();

	// R.N.Libの終了処理
	RNUninit();
	// モードに応じた終了処理
	ModeUninit(g_main.mode);

	// タスクバーを表示
	ShowTaskBar(true);
}

//========================================
// Update関数 - 更新処理 - 
// Author:RIKU NISHIMURA
//========================================
void Update(void)
{
	// モードに応じた更新処理
	ModeUpdate(g_main.mode);
	// R.N.Libの更新処理
	RNUpdate();
}

//========================================
// Draw関数 - 描画処理 -
// Author:RIKU NISHIMURA
//========================================
void Draw(void)
{
	// R.N.Libの描画処理
	RNDraw();
	// モードに応じた描画処理
	ModeDraw(g_main.mode);
}

//========================================
// Load関数 - 読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void Load(void)
{
	// R.N.Libの読み込み処理
	RNLoad();
}

//========================================
// Save関数 - 書き込み処理 -
// Author:RIKU NISHIMURA
//========================================
void Save(void)
{
	// 書き込み
	RNSave();		// R.N.Lib
	SaveSetting();	// 設定
}
#endif
//============================================================
//--------------------| *** その他 *** |----------------------
//============================================================
#if 1
//========================================
// WinMain関数
// Author:RIKU NISHIMURA
//========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	MSG msg;				// メッセージを格納する変数
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwExecLastTime;	// 最後に処理した時刻
	DWORD dwFrameCount;		// フレームカウント
	DWORD dwFPSLastTime;	// 最後にFPSを計測した時刻

	// ウィンドウ生成情報
	CreateWindowInfo cwi =
	{
		WindowProc,		// ウィンドウプロシージャ
		hInstance,		// インスタンスハンドル
		CLASS_NAME,		// ウィンドウクラスの名前
		WINDOW_NAME,	// ウィンドウの名前
		SCREEN_WIDTH,	// ウィンドウの幅
		SCREEN_HEIGHT,	// ウィンドウの高さ
		true,			// ウィンドウモード
	};
	CreateWindowRN(cwi);

	// 初期化処理
	if (FAILED(Init(hInstance)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0; // 現在時刻を初期化する
	dwExecLastTime = timeGetTime(); // 現在時刻を取得(保存)

	dwFrameCount = 0;	// フレームカウントを初期化する
	dwFPSLastTime = timeGetTime();	// 現在時刻を取得(保存)

	// メッセージループ
	while (1){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取った時、メッセージループを抜ける
				break;
			}
			else {
				// メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime(); // 現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				// FPSを計測
				g_main.nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPSを測定した時刻を保存
				dwFPSLastTime = dwCurrentTime;

				// フレームカウントをクリア
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60/1秒経過
				Update();	// 更新処理
				Draw();		// 描画処理

				// 処理開始の時刻(現在時刻)を保存
				dwExecLastTime = dwCurrentTime;

				// フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//========================================
// WindowProc関数
// Author:RIKU NISHIMURA
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	// 返り値を格納

	// R.N.Lib
	RNWindowProc(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_DESTROY: // ウインドウ破棄のメッセージ

		PostQuitMessage(0); // WM_QUITメッセージを送る

		break;
	case WM_KEYDOWN: // キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO); // ウインドウを破棄する(WM_DESTROYメッセージを送る)

			if (nID == IDYES)
			{
				DestroyWindow(hWnd); // ウインドウを破棄する
			}

			break;
		}

		break;
	case WM_CLOSE: // 終了ボタンが押された時

		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO); // ウインドウを破棄する(WM_DESTROYメッセージを送る)

		if (nID == IDYES)
		{
			DestroyWindow(hWnd); // ウインドウを破棄する
		}
		else
		{
			return 0; // (※0を返さないと終了してしまう)
		}

		break;
	case WM_LBUTTONDOWN: // マウスクリックのメッセージ

		// 対象ウインドウにフォーカスを合わせる
		SetFocus(hWnd); // マウスを左クリックしたウインドウをアクティブにする

		break;
	case WM_CREATE: //ウインドウ生成のメッセージ

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); // 既定の処理を返す
}

//========================================
// GetMain関数 - メイン処理の情報の取得 -
// Author:RIKU NISHIMURA
//========================================
Main *GetMain(void)
{
	return &g_main;
}

//========================================
// GetMode関数 - モードの取得 -
// Author:RIKU NISHIMURA
//========================================
MODE GetMode(void)
{
	return g_main.mode;
}

//========================================
// SetMode関数 - モードの設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetMode(MODE mode)
{
	// 現在のモードの終了処理
	ModeUninit(g_main.mode);

	// 現在のモードを切り替える
	g_main.mode = mode;

	// 新しいモードの初期化処理
	ModeInit(mode);
}
#endif