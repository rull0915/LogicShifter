// ----- マウス関連 ----- //

// マウスの入力
extern int m_mouseInput;
extern int m_oldMouseInput;

// マウスの位置
extern Vector2DInt m_mousePos;
extern Vector2DInt m_oldMousePos;

extern float mouseWheelRot;

extern void MouseUpdate();
extern int MouseDown();
extern int MouseEnter();
extern int MouseUp();


// マウスの移動量を返す関数
extern Vector2DInt GetMouseMoveValue();

extern float MouseWheelRot();
