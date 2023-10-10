# Visualizer

![image](https://user-images.githubusercontent.com/91818705/203841200-730035a2-636a-48d4-a17b-8a4aa23b5367.png)

## 🤔 Description

ロボットに搭載されている紙飛行機の発射機構の操縦アプリです。

2022 年度全国高専ロボコン 四国地区大会、全国大会で使用しました。

[全国高専ロボコン競技ルール](https://official-robocon.com/robocon_wp/wordpress/wp-content/uploads/2022/04/kosen2022_rulebook.pdf)

## 🐣 Download

以下のリンクから実行ファイルをダウンロードできます。

[Windows x64](https://github.com/CaseyNelson314/Visualizer/releases/download/v1.0.1/Visualizer.exe)

> "Windows によって PC が保護されました" と表示される場合、続けて "詳細情報" をクリックすると実行できます。

curl を使用できる方はこちら。

```sh
curl -OL https://github.com/CaseyNelson314/Visualizer/releases/download/v1.0.1/Visualizer.exe
start .\Visualizer.exe
```

## 💬 Usage

### ロボット操作

WASD キーで平行移動、QE キーで旋回できます。

### 着陸点選択

紙飛行機の着陸点をタッチすることで選択できます。最大 2 箇所まで選択できます。

### 発射機構切り替え

ロボットをタッチすることで使用する発射機構の切り替えができます。

### スタートゾーン切替

スタートゾーンをタッチすることで切り替えられます。

### 浮動コントローラー

ロボットへ発射機構の微調整、発射、ゼロ点取り、射出ローラー回転切替、再装填の指示を送信します。

ドラッグすると画面上を自由に移動できます。

### 通信

右上の COM ポートリストからポートを選択後、OPEN ボタンを押すことで通信を開始します。

※Bluetooth 経由の COM ポートを開こうとした時、アプリが落ちる場合があります。

### その他

F キーを押すことでフルスクリーンモードに切り替えられます。

F1 キーを押すことで OpenSiv3D が使用しているサードパーティ・ソフトウェアのライセンス情報を表示します。

## 📗 Summary

### 通信

PC とロボット間の通信の流れは以下のようになっています。

各データがまとまった構造体をバイト列に変換し送受信しています。

```mermaid
flowchart LR
	subgraph ロボット
	Master[Master/Teensy4.0] <--I2C--> MasterForwarding[Teensy4.0] <--UART--> MasterIM920[IM920]
	end
	subgraph 操縦者
	MasterIM920 <-.920MHz.-> ToPC[IM920] <--UART--> PCForwarding[Teensy4.0] <--UART--> PC
	end
```

### GUI

描画用フレームワークである OpenSiv3D を使い、C++で記述しています。

使わせていただいた OpenSiv3D のリンクです。

<https://siv3d.github.io/ja-jp/>

<https://github.com/Siv3D/OpenSiv3D>

### Class Tree

このアプリはクラスの組み合わせによって構成されています。

| クラス名           | 役割                       |
| ------------------ | -------------------------- |
| Field              | 競技フィールドエリア       |
| Landing            | 着陸点                     |
| FloatingController | 浮動コントローラー         |
| SerialListView     | シリアルポートリスト(右上) |
| Coordinate         | 座標表示 (右下)            |
| SerialManager      | 通信管理                   |

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

## 💻 Development

|     |                                                       |
| :-: | ----------------------------------------------------- |
| OS  | Windows 11 Home, Pro                                  |
| IDE | Microsoft Visual Studio Community 2022 Version 17.4.4 |
| SDK | OpenSiv3D v0.6.6                                      |
