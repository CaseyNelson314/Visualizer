#pragma once

namespace Com {

	/// @brief シリアル通信送信

	class SerialWriter {
		s3d::Serial& serial;
		Array<uint8> buffer;
	public:
		SerialWriter(s3d::Serial& serial, size_t length)
			: serial(serial)
			, buffer(length)
		{}

		/// @brief バッファ送信
		void update() {
			if (serial.isOpen()) {
				serial.write(buffer.data(), buffer.size());
			}
		}

		/// @brief バッファの参照を取得
		/// @return 
		Array<uint8>& getBuffer() {
			return buffer;
		}
	};

}
