#include "SerialManeger.h"



Com::SerialManeger::SerialManeger()
	: serial()
	, SerialWriter(serial, sizeof(WriteDataFrame))
	, SerialReader(serial, sizeof(ReadDataFrame))
	, writeData()
	, readData()
{}

Com::SerialManeger::~SerialManeger() {
	if (serial.isOpen())
		serial.close();
}


/// @brief ポートが開いているか
Com::SerialManeger::operator bool() const {
	return serial.isOpen();
}

/// @brief ポートを開ける
/// @param port 
/// @return 
Com::SerialManeger& Com::SerialManeger::open(const String& port) {
	if (not serial.isOpen()) {
		serial.open(port, 115200);
	}
	return *this;
}

/// @brief ポートを閉める
/// @return
Com::SerialManeger& Com::SerialManeger::close() {
	if (serial.isOpen())
		serial.close();
	return *this;
}

/// @brief 受信バッファの参照を取得
/// @return 
const Com::SerialManeger::ReadDataFrame& Com::SerialManeger::read() const {
	return readData;
}

/// @brief 送信バッファにデータセット
/// @param r 
/// @return 
Com::SerialManeger& Com::SerialManeger::write(const WriteDataFrame& r) {
	writeData = r;
	return *this;
}

/// @brief 更新
/// @return 
Com::SerialManeger& Com::SerialManeger::writeUpdate() {
	std::memcpy(SerialWriter::getBuffer().data(), &writeData, SerialWriter::getBuffer().size());
	SerialWriter::update();
	return *this;
}
Com::SerialManeger& Com::SerialManeger::readUpdate() {
	SerialReader::update();
	std::memcpy(&readData, SerialReader::getBuffer().data(), sizeof readData);
	return *this;
}
