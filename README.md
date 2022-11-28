# Visualizer

ロボットの発射機構操縦、現在位置表示アプリ

## 🤔 Description

ロボットに搭載されている左右の発射機構の操縦アプリです。

2022 年度 四国地区、全国高専ロボコンで使用しました。

![image](https://user-images.githubusercontent.com/91818705/203841200-730035a2-636a-48d4-a17b-8a4aa23b5367.png)

## ⭳ Download

Windows x64 のみ対応しています。

[ダウンロード](https://github.com/CaseyNelson314/Visualizer/releases/download/v1.0.0/Visualizer.exe)

git でのダウンロード

> ```sh
> git clone https://github.com/CaseyNelson314/Visualizer.git
> start ./Visualizer/Visualizer/App/Visualizer.exe
> ```

## 💬 Usage

-   スタートゾーン切替

    スタートゾーンをタッチすることで切り替えられます。

-   着陸点選択

    着陸点(スポット、ベース、滑走路)をタッチすることで選択できます。最大 2 箇所まで選択できます。

-   発射機構切り替え

    ロボットをタッチすることで使用する発射機構の切り替えができます。

-   キー操作(デバッグ用)

    ロボットをキーボードで動かします。WASD キーで平行移動、QE キーで旋回できます。

-   通信

    右上の COM ポートリストからポートを選択後、OPEN ボタンを押すことで通信を開始します。

    ※Bluetooth 経由の COM ポートを OPEN しようとした場合アプリが落ちる場合があります。

-   浮動コントローラー

    ロボットへ発射機構の微調整、発射、ゼロ点取り、射出ローラー回転切替、再装填の指示を送信します。

    ドラッグすると画面上を自由に移動できます

-   その他

    F キーを押すことでフルスクリーンモードに切り替えられます。

    F1 キーを押すことで OpenSiv3D が使用しているサードパーティ・ソフトウェアのライセンス情報を表示します。

## 📗 Summary

-   通信

    PC とロボット間の通信の流れは以下のようになっています。

    各データがまとまった構造体をバイト列に変換し送受信しています。

    ```mermaid
    flowchart LR
    	subgraph ロボット
    	master[master/teensy4.0] <--I2c--> masterForwarding[teensy4.0] <--UART--> masterIm920[im920]
    	end
    	subgraph 操縦者
    	masterIm920 <-.920Mhz.-> toPc[im920] <--UART--> pcForwarding[teensy4.0] <--UART--> pc
    	end
    ```

-   GUI

    プログラムは OpenSiv3D を使い、C++で記述しています。

    使わせていただいた OpenSiv3D のリンクです。

    https://siv3d.github.io/ja-jp/

    https://github.com/Siv3D/OpenSiv3D

-   Class Tree

    このアプリはクラスを組み合わせて構成されています。

    主なクラス

    -   Field

        フィールドエリアを管理

    -   Landing

        着陸点を管理

    -   SerialManager

        通信を管理

    -   Coordinate

        座標の表示 (右下に表示)

    -   SerialListView

        シリアルポートのリストを管理 (右上に表示)

    -   FloatingController

        浮動コントローラーを管理

    ```mermaid
    flowchart BT

    loop

    vis[Visualizer] --> loop

    Field --> VirtualElement --仮想座標から実座標に変換 --> vis

    Robot --> Field

    SerialManager --> vis
    SerialWriter --継承--> SerialManager
    SerialReader --継承--> SerialManager

    LandingInterface --継承--> Landing --> Field

    Coordinate --> vis

    SerialListView --> vis

    FloatingController --> vis
    ```

## 👤 Author

[CaseyNelson](https://github.com/CaseyNelson314)

## 📖 License

MIT License

## 💻 開発環境

|     |                                                       |
| :-: | ----------------------------------------------------- |
| OS  | Windows 11 Home                                       |
| IDE | Microsoft Visual Studio Community 2022 Version 17.3.1 |
| SDK | OpenSiv3D v0.6.5                                      |
