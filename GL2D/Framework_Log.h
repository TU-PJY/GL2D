// FWM Version 3
#pragma once
#include "Framework_Conf.h"
#include <iostream>

enum class LogType {
	FM_INIT,
	MODE_SWITCH,
	ADD_OBJECT,
	SET_FLOATING_OBJECT,
	SET_STATIC_OBJECT,
	DELETE_OBJECT,
	START_FLOATING_MODE,
	END_FLOATING_MODE,
	ERROR_SAME_MODE
};

class FWM_Log {
public:
	std::string PrevMode{};
	std::string CurrentMode{};
	std::string ObjectTag{};
	bool IsOnlyFloating{};

	void Log(LogType Type) {
		using namespace std;
		if (DebugMessage) {
			cout << "======== Framework Message ========\n";
			cout << "Message Type: ";

			switch (Type) {
			case LogType::FM_INIT:
				cout << "Framework Init\n";
				cout << "Framework Started running with Mode [ " << CurrentMode << " ].\n";
				break;

			case LogType::MODE_SWITCH:
				cout << "Mode Switch\n";
				cout << "Mode Switched from [ " << PrevMode << " ] to [ " << CurrentMode << " ].\n";
				if (IsOnlyFloating)
					cout << "Floating Focus is activated.\n";
				else
					cout << "Floating Focus is not activated.\n";
				break;

			case LogType::START_FLOATING_MODE:
				cout << "Floating Mode\n";
				cout << "Floating mode started.\n";
				break;

			case LogType::END_FLOATING_MODE:
				cout << "Floating Mode\n";
				cout << "FLoating Mode ended.\n";
				break;

			case LogType::ADD_OBJECT:
				cout << "Object Add\n";
				cout << "Object [ " << ObjectTag << " ] added.\n";
				break;

			case LogType::SET_FLOATING_OBJECT:
				cout << "Set Object Floating Object\n";
				cout << "Object [ " << ObjectTag << " ] set as floating object.\n";
				break;

			case LogType::SET_STATIC_OBJECT:
				cout << "Set Object Static Object\n";
				cout << "Object [ " << ObjectTag << " ] set as static object.\n";
				break;

			case LogType::DELETE_OBJECT:
				cout << "Object Delete\n";
				cout << "Object [ " << ObjectTag << " ] deleted.\n";
				break;
			}

			cout << "\n";
		}
	}

	void ErrorLog(LogType Type) {
		using namespace std;

		cout << "======== Framework Error ========\n";
		cout << "Error Type: ";

		switch (Type) {
		case LogType::ERROR_SAME_MODE:
			cout << "Mode Switch Error\n";
			cout << "Duplicate mode switch of the same mode as the current mode detected.\n";
			cout << "While mode [ " << PrevMode << " ]\n";
			break;
		}

		cout << "\n";

		exit(EXIT_FAILURE);
	}
};