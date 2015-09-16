// ANPR
#include "gxsd.h"
#include "gxerror.h"
#include "gximage.h"
#include "cmanpr.h"

#define CANDIDATE_REMOVE_TIME (60000) // (ms)
#define CANDIDATE_COUNT_FOR_PASS (3)

typedef struct {
	int id; // reserved
	int foundCount;
	unsigned long firstfoundTime;
	wchar_t plate_string[32];
}PLATE_CANDIDATE;

// Unicode to Multibytes
void ConvertWCtoC(const wchar_t* str, char* pStr32, int bufLen)
{
	memset(pStr32, 0, bufLen);

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr32, strSize, 0, 0);
	return;
}

void checkErrorCode(char* text, int line)
{
	int errorCode = gxSystem::GetErrorCode();
	if (errorCode == GX_EHWKEY) {
		// No HW Key
		printf("[%d] %s: Check H/W Key (%d)\n", line, text, errorCode);
	}
	else {
		char errorStr[1024] = { 0, };
		ConvertWCtoC(gxSystem::GetErrorString().c_str(), errorStr, 1023);
		printf("[%d] %s: %s (%d)\n", line, text, errorStr, errorCode);
	}
}

bool isValidPlateString(const wchar_t* string)
{
	if (string[0] < 0 || _istdigit(string[0]) == false) {
		// Check Old (Loca-12-Kr-1234)
		if (string[2] < 0 || _istdigit(string[2]) == false) return false;
		if (string[3] < 0 || _istdigit(string[3]) == false) return false;
		if (string[5] < 0 || _istdigit(string[5]) == false) return false;
		if (string[6] < 0 || _istdigit(string[6]) == false) return false;
		if (string[7] < 0 || _istdigit(string[7]) == false) return false;
		if (string[8] < 0 || _istdigit(string[8]) == false) return false;
	}
	else {
		// 2006 yr. (12-Kr-1234)
		if (string[1] < 0 || _istdigit(string[1]) == false) return false;
		if (string[3] < 0 || _istdigit(string[3]) == false) return false;
		if (string[4] < 0 || _istdigit(string[4]) == false) return false;
		if (string[5] < 0 || _istdigit(string[5]) == false) return false;
		if (string[6] < 0 || _istdigit(string[6]) == false) return false;
	}

	return true;
}

int getValidPlates(cmAnpr* anpr, gxImage& image, std::vector<std::wstring>& output)
{
	int count = 0;
	char result[32];

	try {

		// Finds the first plate and displays it
		//QueryPerformanceCounter(&counter_before);
		bool found = anpr->FindFirst(image);
		//QueryPerformanceCounter(&counter_after);
		//double anprTime = (double)(counter_after.QuadPart - counter_before.QuadPart) / freq.QuadPart;

		output.clear();

		while (found) {
			const wchar_t* result = anpr->GetText();

			if (isValidPlateString(result)) {
				//printf( "[OK]%s\t", result );

				output.push_back(result);
				count++;

			}
			else {
				//printf( "[NG]%s\t", result );
			}

			// Finds other plates
			found = anpr->FindNext();
		}
		//printf("\n");
		//printf("\nMemLoad:%lf\tAnpr:%lf\n", loadTime, anprTime);
	}
	catch (gxException e) {
		checkErrorCode("Get Plates Failed", __LINE__);
	}

	return count;
}

void initANPR(cmAnpr* anpr)
{
	anpr->SetProperty(L"anprname", L"cmanpr-7.2.7.68:kor");
	anpr->SetProperty(L"size_min", L"8"); // Default 6
	anpr->SetProperty(L"size_max", L"40"); // Default 93

	anpr->SetProperty(L"nchar_min", L"7"); // Default 8
	anpr->SetProperty(L"nchar_max", L"9"); // Default 9

	// 10degree (Rightside is up)
	anpr->SetProperty(L"slope", L"-5"); // Default -22
	anpr->SetProperty(L"slope_min", L"-20"); // Default -22
	anpr->SetProperty(L"slope_max", L"10"); // Default 34

	anpr->SetProperty(L"slant", L"0"); // Default 10
	anpr->SetProperty(L"slant_min", L"-10"); // Default -55
	anpr->SetProperty(L"slant_max", L"10"); // Default 27
}
