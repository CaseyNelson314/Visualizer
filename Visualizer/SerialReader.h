#pragma once

namespace Com {

	/// @brief シリアル通信受信

	class SerialReader {
		s3d::Serial& serial;
		Array<uint8> buffer;
	public:
		SerialReader(s3d::Serial& serial, size_t length)
			: serial(serial)
			, buffer(length)
		{}

		/// @brief バッファ更新
		void update() {
			if (serial.isOpen()) {
				while (serial.available()) {
					for (auto& buf : buffer) {
						serial.read(buf);
					}
				}
			}
		}

		/// @brief バッファの参照を取得
		/// @return 
		const Array<uint8>& getBuffer() {
			return buffer;
		}
	};
}
