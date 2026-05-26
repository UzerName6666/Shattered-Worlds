#pragma once
#include <iostream>
#include <string>

class Logger{
	public:
	enum MessageType{
		Message, Warn, Error
	};
	static void Write(MessageType Type, std::wstring Message);
	static void Clear();
};
