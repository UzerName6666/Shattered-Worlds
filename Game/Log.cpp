#include "Log.h"
#include <ctime>
#include <fstream>

void ShatteredEngine::Logger::Write(MessageType Type, std::wstring Message){
	std::wofstream Logfile(L"Log.txt", std::ios_base::app);
	if(!Logfile.is_open()){
		return;
	}
	time_t seconds = time(0);
	tm* timeinfo = localtime(&seconds);
	Logfile << L"[" << timeinfo -> tm_hour << L":" << timeinfo -> tm_min << L":" << timeinfo -> tm_sec << L", ";
	switch (Type){
	case MessageType::Message:
		Logfile << L"MSG]: ";
		break;
	case MessageType::Warn:
		Logfile << L"WRN]: ";
		break;
	case MessageType::Error:
		Logfile << L"ERR]: ";
		break;
	default:
		Logfile << L"UNK]: ";
		break;
	}
	Logfile << Message << L"\n";   
}

void ShatteredEngine::Logger::Init(){
	std::wofstream Logfile(L"Log.txt");
	if(!Logfile.is_open()){
		return;
	}
	time_t seconds = time(0);
	tm* timeinfo = localtime(&seconds);
	Logfile << "[Log.txt]\nDate: " << timeinfo -> tm_mday << "." << timeinfo -> tm_mon + 1 << "." << timeinfo -> tm_year + 1900 << "\n";
}