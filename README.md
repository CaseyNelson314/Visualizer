# Visualizer

ロボットの発射機構操縦、現在地表示アプリ

## 🤔 Description

四国地区、全国高専ロボコンで使用したロボットの操縦アプリです

![image](https://user-images.githubusercontent.com/91818705/203841200-730035a2-636a-48d4-a17b-8a4aa23b5367.png)

## ⭳ Download

Windows x64 用です

[Download]()

> ```sh
> ## clone && execute
> git clone https://github.com/CaseyNelson314/Visualizer.git
> cd Visualizer
> start ./Visualizer/App/Visualizer.exe
> ```

## 💬 Usage

-   スタートゾーン切り替え

    スタートゾーンをタッチすることで切り替えられます

-   着陸点選択

    着陸点(スポット、ベース、滑走路)をタッチすることで選択できます。最大 2 箇所まで選択できます

-   発射機構切り替え

    ロボットをタッチすることで使用する発射機構の切り替えができます

-   キー操作(デバッグ用)

    ロボットをキーボードで動かします。WASD で平行移動、QE で旋回できます

-   シリアル

    右上の COM ポートリストからポートを選択後、OPEN ボタンを押すことで通信を開始します

    Bluetooth 経由の COM ポートを OPEN しようとした場合アプリが落ちる場合があります

-   浮動コントローラー

    ロボットへ発射機構の微調整、発射、ゼロ点取り、射出ローラー回転切替、再装填の指示を送信します

-   その他

    F キーを押すことでフルスクリーンモードに切り替えられます

    F1 キーを押すことで OpenSiv3D が使用しているサードパーティ・ソフトウェアのライセンス情報を表示します

## 📗 処理概要

-   通信

    PC とロボット間の通信の流れは以下のようになっています

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

    プログラムは OpenSiv3D を使い、C++で記述しました

    使わせていただいた OpenSiv3D のリンクです。とても使いやすかったです!

    https://github.com/Siv3D/OpenSiv3D

    https://zenn.dev/reputeless/books/siv3d-documentation/viewer/introduction

## Author

[CaseyNelson314](https://github.com/CaseyNelson314)

## 📖 License

MIT License

## 💻 開発環境

|     |                                                       |
| --- | ----------------------------------------------------- |
| OS  | Windows 11 Home                                       |
| IDE | Microsoft Visual Studio Community 2022 Version 17.3.1 |
| SDK | OpenSiv3D v0.6.5                                      |
