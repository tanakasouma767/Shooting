![Image](https://github.com/user-attachments/assets/64bab448-4ef8-49f9-bbf2-b5c055623c99)

OpenGLでシューティングゲームを作りました。

使用しているライブラリは
・freeglut
・vecmath C++
です。

力を入れた部分は、・GameObject.h ・GameObject.cpp に含まれている、プレイヤーや敵、弾といったゲームに必要なオブジェクトの設計と、・Scene.h ・Scene.cppに含まれているゲームオブジェクトの呼び出し、シーンの制御です。特に、オブジェクト指向的なクラス設計に留意し、オブジェクトの描画や状態の更新に必要な処理はオブジェクト自身に持たせ、シーンの側からは簡潔な呼び出しになるよう心掛けました。

実行ファイルはbinフォルダに入れています。
