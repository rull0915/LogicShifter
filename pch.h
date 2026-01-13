#pragma once

// 標準ライブラリ
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
#include <thread>


// Dxlib
#include "DxLib.h"

// ゲーム情報
#include "Game/GameLib/Screen.h"

// 数学系
#include "Game/GameMath/Vector2D.h"
#include "Game/GameMath/Vector3D.h"
#include "Game/GameMath/Vector4D.h"
#include "Game/GameMath/SquareMatrix3.h"
#include "Game/GameMath/SquareMatrix4.h"
#include "Game/GameMath/Easing.h"

// その他自作ライブラリ
#include "Game/Common/MyRender.h"
#include "Game/GameLib/GameLib.h"
#include "Game/GameLib/Resources.h"
#include "Game/GameLib/Mouse.h"

#include "Game/GameLib/Sound.h"

#include "Game/GameLib/Colors.h"

#include "Game/GameLib/OpenFileDialog.h"

// json関連
#include "nlohmann/json.hpp"
using json = nlohmann::json;
