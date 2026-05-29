#pragma once
#include <iostream>
#include <string>
namespace ShatteredEngine{
class Logger{
	public:
	enum MessageType{
		Message, Warn, Error
	};
	static void Write(MessageType Type, std::wstring Message);
	static void Init();
};
};

