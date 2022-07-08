#pragma once
#ifdef synapse_messaging_export_mode
#define synapse_messaging_dll _declspec(dllexport)
#else
#define synapse_messaging_dll _declspec(dllimport)
#endif