#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void toClipboard(const std::string &s){
	OpenClipboard(0);
	EmptyClipboard();	
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size());
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main() {
    string text, derped_text;
    bool switcher = true;

    cout << "\t|------------|\n\t|  DerpMode  |\n\t|------------|\n\nEnter "
            "text: ";
    getline(cin, text);

    for (char &c : text) {
        if (c == ' ') {
            derped_text.push_back(c);
            switcher = true;
        } else {
            if(switcher){
                derped_text.push_back(toupper(c));
                switcher = false;
            }
            else{
                derped_text.push_back(tolower(c));
                switcher = true;
            }
        }
    }

    derped_text.push_back('\0');

    toClipboard(derped_text);

    cout << "Text as been derped and copied to the clipboard.\n";

    Sleep(750);

    return 0;
}