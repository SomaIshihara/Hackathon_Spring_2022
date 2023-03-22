//========================================
// 
// R.N.Libのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** R.N.Lib.h ***
//========================================
#ifndef _RNLIB_H_	// このマクロ定義がされていなかった時
#define _RNLIB_H_	// 二重インクルード防止のマクロを定義する

// R.N.Lib
#include "RNmain.h"
// 2D
#include "Basis\2D\camera2D.h"
#include "Basis\2D\fade.h"
#include "Basis\2D\motion2D.h"
#include "Basis\2D\polygon2D.h"
#include "Basis\2D\text2D.h"
// 3D
#include "Basis\3D\camera3D.h"
#include "Basis\3D\draw3D.h"
#include "Basis\3D\light.h"
#include "Basis\3D\line3D.h"
#include "Basis\3D\map-chip3D.h"
#include "Basis\3D\map-generator3D.h"
#include "Basis\3D\material.h"
#include "Basis\3D\model.h"
#include "Basis\3D\model-setup.h"
#include "Basis\3D\motion3D.h"
#include "Basis\3D\parts3D.h"
#include "Basis\3D\polygon3D.h"
#include "Basis\3D\text3D.h"
// Graphic
#include "Basis\Graphic\text.h"
#include "Basis\Graphic\texture.h"
// Other
#include "Basis\Other\chunk.h"
#include "Basis\Other\color.h"
#include "Basis\Other\file.h"
#include "Basis\Other\geometry.h"
#include "Basis\Other\input.h"
#include "Basis\Other\matrix.h"
#include "Basis\Other\physics.h"
#include "Basis\Other\setting.h"
#include "Basis\Other\sound.h"
#include "Basis\Other\window.h"

#endif