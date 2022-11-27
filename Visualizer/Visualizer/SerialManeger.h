#pragma once

#include "SerialReader.h"
#include "SerialWriter.h"

namespace Com {

	/// @brief シリアル通信

	class SerialManeger : private SerialWriter, private SerialReader {
	public:

/// メモリアライメント無効(teensy側も無効)
#pragma pack(push, 1)
		struct ReadDataFrame {
			float x;
			float y;
			float yaw;
		};
		struct WriteDataFrame {
			struct Target {
				uint8 id;      /// 着陸点のID
				float length;  /// 着陸点までの距離 [mm]
				float angle;   /// 着陸点への角度   [deg]
			} leftTarget, rightTarget;
			struct Shooter {
				bool upPress      : 1;
				bool rightPress   : 1;
				bool downPress    : 1;
				bool leftPress    : 1;
				bool speedUp      : 1;
				bool speedDown    : 1;
				bool releasePress : 1;
			} leftShooter, rightShooter;
		};
#pragma pack(pop)

	private:
		Serial serial;
		ReadDataFrame  readData;
		WriteDataFrame writeData;
	public:
		SerialManeger();
		~SerialManeger();

		/// @brief ポートが開いているか
		explicit operator bool() const;

		/// @brief ポートを開ける
		/// @param port 
		/// @return 
		SerialManeger& open(const String& port);

		/// @brief ポートを閉める
		/// @return 
		SerialManeger& close();

		/// @brief 受信バッファの参照を取得
		/// @return 
		const ReadDataFrame& read() const;

		/// @brief 送信バッファにデータセット
		/// @param r 
		/// @return 
		SerialManeger& write(const WriteDataFrame& r);

		/// @brief 更新
		/// @return 
		SerialManeger& writeUpdate();
		SerialManeger& readUpdate();
	};
}
