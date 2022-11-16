# Visualizer

## 🤔 Description

四国地区、全国高専ロボコンで使用したロボットの操縦アプリです

目標着地点の指定、発射機構の角度計算等を行い、ロボットへ送信します

![image](https://user-images.githubusercontent.com/91818705/201993305-4e0fefde-cc37-4ee9-a389-7b74a643f83b.png)

## Install

[Download]()

```sh
git clone https://github.com/CaseyNelson314/Visualizer.git
cd Visualizer
start ./Visualizer/App/Visualizer.exe
```

## 💬 Usage

## 📗 内部処理

-   通信

    腕に装着するモニターからロボットのマスターまでの通信の流れは以下のようになっています

    ```mermaid
    flowchart LR
    	subgraph ロボット
    	master[master/teensy4.0] <--I2c--> toMaster[teensy4.0,im920]
    	end
    	subgraph 操縦者
    	toMaster <-.920Mhz.-> toPc[im920,teensy4.0] <--UART--> pc <--HDMI--> monitor
    	end
    ```

-   GUI

    GUIプログラム は OpenSiv3D を使い、C++で記述しています。

    練習時に誰の PC でも使用できるよう、画面のリサイズに対応する必要がありました。OpenSiv3D では図形の描画を座標を指定して行います。そのためリサイズ時でも座標を気にせず描画できる VirtualElement クラスを作成しました。

## 📖License

MIT License

アプリ起動時に F1 キーを押すことで OpenSiv3D が使用しているサードパーティ・ソフトウェアのライセンス情報を表示します

## 💻 開発環境

Microsoft Visual Studio Community 2022 Version 17.3.1

OpenSiv3D v0.6.5
