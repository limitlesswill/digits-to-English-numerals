#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

#pragma comment (linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//globals
HWND btn1{}, input1{}, output1{};

//declerations/prototypes
std::string words(const unsigned length);
unsigned onetenhundred(const unsigned Length_of_number);
std::string toones(const unsigned number);
std::string totens(const unsigned number);
std::string tohundreds(const unsigned number);
std::string core(std::string number);
std::string numbertoword(const std::string number);
void CenterWindow(HWND hwnd, int screen_w = GetSystemMetrics(SM_CXSCREEN), int screen_h = GetSystemMetrics(SM_CYSCREEN));

void start()
{
	auto len = GetWindowTextLengthA(input1) + 1;
	std::vector<char> input_buffer(len);
	GetWindowTextA(input1, &input_buffer[0], len);
	std::string inputs(input_buffer.data());
	std::string tmp = numbertoword(inputs);
	//SetWindowTextA(wnd, inputs.c_str());//testing input on wnd caption
	SetWindowTextA(output1, tmp.c_str());//input_buffer.data());
}

//main procedure
LRESULT CALLBACK wndproc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_HOTKEY:
		start();
		SetFocus(input1);
		break;

	case WM_COMMAND:
		if ((HWND)lp == btn1)
		{
			start();
		}
		break;

	case WM_CREATE:
		btn1 = CreateWindowExA(0, "button", "Convert", WS_CHILD | WS_VISIBLE, 95, 55, 120, 35, wnd, 0, 0, 0);
		output1 = CreateWindowExA(0, "edit", "", WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | WS_BORDER | WS_VSCROLL | ES_READONLY, 300, 5, 280, 300, wnd, 0, 0, 0);//edit - pager-like ::center 600-250/2 :400-300 /2
		input1 = CreateWindowExA(0, "edit", "", WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL | ES_NUMBER | WS_BORDER | WS_VSCROLL, 5, 5, 280, 300, wnd, 0, 0, 0);//center 600-250/2 :400-300 /2
		RegisterHotKey(wnd, 0, 0, VK_RETURN);//instead of subclassing the edit control 
		CenterWindow(wnd);
		CenterWindow(btn1, 600, 675);//600 = width of wnd , 675 = below of the height of wnd
		SetFocus(input1);
		break;

	case WM_CLOSE:
		DestroyWindow(wnd);
		break;

	case WM_DESTROY:
		UnregisterHotKey(wnd, 0);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(wnd, msg, wp, lp);
	}
	return 0;
}
// MAIN FUNCTION (The Entry Point)
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE previnst, PSTR cmdline, int showcmd)
{
	WNDCLASSEX wc{};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hIconSm = 0;
	wc.hInstance = hinst;
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = "DigitToWords";
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClassExA(&wc);

	if (FindWindow(wc.lpszClassName, 0))
	{
		MessageBox(0, "Already Exist!", "ERROR", 0);
		return 0;
	}
	HWND main = CreateWindowExA(8, "DigitToWords", "Digit-Word", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, 600, 400, 0, 0, hinst, 0);

	if (!main)
	{
		MessageBoxA(0, "WINDOW FAILED", "ERROR", 0);
		return 0;
	}

	ShowWindow(main, 1);
	UpdateWindow(main);

	MSG mesg;
	while (GetMessage(&mesg, 0, 0, 0) > 0)
	{
		TranslateMessage(&mesg);
		DispatchMessage(&mesg);
	}

	return static_cast<int>(mesg.wParam);
}

void CenterWindow(HWND hwnd, int screen_w, int screen_h) {

	RECT rc = { 0 };

	GetWindowRect(hwnd, &rc);
	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;

	SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w) / 2,
		(screen_h - win_h) / 2, 0, 0, SWP_NOSIZE);
}

std::string words(const unsigned length)
{
	switch (length)
	{
	case 3: return "thousand";
	case 6: return "million";
	case 9: return "billion";
	case 12: return "trillion";
	case 15: return "quadrillion";
	case 18: return "quintillion";
	case 21: return "sextillion";
	case 24: return "septillion";
	case 27: return "octillion";
	case 30: return "nonillion";
	case 33: return "decillion";
	case 36: return "undecillion";
	case 39: return "duodecillion";
	case 42: return "tredecillion";
	case 45: return "quattuordecillion";
	case 48: return "quindecillion";
	case 51: return "sexdecillion";
	case 54: return "septendecillion";
	case 57: return "octodecillion";
	case 60: return "novemdecillion";
	case 63: return "vigintillion";
	case 66: return "unvigintillion";
	case 69: return "duovigintillion";
	case 72: return "tresvigintillion";
	case 75: return "quattuorvigintillion";
	case 78: return "quinquavigintillion";
	case 81: return "sesvigintillion";
	case 84: return "septemvigintillion";
	case 87: return "octovigintillion";
	case 90: return "novemvigintillion";
	case 93: return "trigintillion";
	case 96: return "untrigintillion";
	case 99: return "duotrigintillion/googol";
	case 102: return "trestrigintillion";
	case 105: return "quattuortrigintillion";
	case 108: return "quinquatrigintillion";
	case 111: return "sestrigintillion";
	case 114: return "septentrigintillion";
	case 117: return "octotrigintillion";
	case 120: return "noventrigintillion";
	case 123: return "quadragintillion";
	case 126: return "unquadragintillion";
	case 129: return "duoquadragintillion";
	case 132: return "tresquadragintillion";
	case 135: return "quattuorquadragintillion";
	case 138: return "quinquaquadragintillion";
	case 141: return "sesquadragintillion";
	case 144: return "septenquadragintillion";
	case 147: return "octoquadragintillion";
	case 150: return "novenquadragintillion";
	case 153: return "quinquagintillion";
	case 156: return "unquinquagintillion";
	case 159: return "duoquinquagintillion";
	case 162: return "tresquinquagintillion";
	case 165: return "quattuorquinquagintillion";
	case 168: return "quinquinquagintillion";
	case 171: return "sesquinquagintillion";
	case 174: return "septenquinquagintillion";
	case 177: return "octoquinquagintillion";
	case 180: return "novenquinquagintillion";
	case 183: return "sexagintillion";
	case 186: return "unsexagintillion";
	case 189: return "duosexagintillion";
	case 192: return "tresexagintillion";
	case 195: return "quattuorsexagintillion";
	case 198: return "quinsexagintillion";
	case 201: return "sesexagintillion";
	case 204: return "septensexagintillion";
	case 207: return "octosexagintillion";
	case 210: return "novensexagintillion";
	case 213: return "septuagintillion";
	case 216: return "unseptuagintillion";
	case 219: return "duoseptuagintillion";
	case 222: return "treseptuagintillion";
	case 225: return "quattuorseptuagintillion";
	case 228: return "quinseptuagintillion";
	case 231: return "seseptuagintillion";
	case 234: return "septenseptuagintillion";
	case 237: return "octoseptuagintillion";
	case 240: return "novenseptuagintillion";
	case 243: return "octogintillion";
	case 246: return "unoctogintillion";
	case 249: return "duooctogintillion";
	case 252: return "tresoctogintillion";
	case 255: return "quattuoroctogintillion";
	case 258: return "quinoctogintillion";
	case 261: return "sexoctogintillion";
	case 264: return "septemoctogintillion";
	case 267: return "octooctogintillion";
	case 270: return "novemoctogintillion";
	case 273: return "nonagintillion";
	case 276: return "unnonagintillion";
	case 279: return "duononagintillion";
	case 282: return "trenonagintillion";
	case 285: return "quattuornonagintillion";
	case 288: return "quinnonagintillion";
	case 291: return "senonagintillion";
	case 294: return "septenonagintillion";
	case 297: return "octononagintillion";
	case 300: return "novenonagintillion";
	case 303: return "centillion";
	case 306: return "uncentillion";
	case 309: return "duocentillion";
	case 312: return "trescentillion";
	case 315: return "quattuorcentillion";
	case 318: return "quincentillion";
	case 321: return "sexcentillion";
	case 324: return "septencentillion";
	case 327: return "octocentillion";
	case 330: return "novencentillion";
	case 333: return "decicentillion";
	case 336: return "undecicentillion";
	case 339: return "duodecicentillion";
	case 342: return "tredecicentillion";
	case 345: return "quattuordecicentillion";
	case 348: return "quindecicentillion";
	case 351: return "sedecicentillion";
	case 354: return "septendecicentillion";
	case 357: return "octodecicentillion";
	case 360: return "novendecicentillion";
	case 363: return "Viginticentillion";
	case 366: return "unviginticentillion";
	case 369: return "duoviginticentillion";
	case 372: return "tresviginticentillion";
	case 375: return "quattuorviginticentillion";
	case 378: return "quinviginticentillion";
	case 381: return "sesviginticentillion";
	case 384: return "septemviginticentillion";
	case 387: return "octoviginticentillion";
	case 390: return "novemviginticentillion";
	case 393: return "trigintacentillion";
	case 396: return "untrigintacentillion";
	case 399: return "duotrigintacentillion";
	case 402: return "trestrigintacentillion";
	case 405: return "quattuortrigintacentillion";
	case 408: return "quintrigintacentillion";
	case 411: return "sestrigintacentillion";
	case 414: return "septentrigintacentillion";
	case 417: return "octotrigintacentillion";
	case 420: return "noventrigintacentillion";
	case 423: return "quadragintacentillion";
	case 426: return "unquadragintacentillion";
	case 429: return "duoquadragintacentillion";
	case 432: return "tresquadragintacentillion";
	case 435: return "quattuorquadragintacentillion";
	case 438: return "quinquadragintacentillion";
	case 441: return "sesquadragintacentillion";
	case 444: return "septenquadragintacentillion";
	case 447: return "octoquadragintacentillion";
	case 450: return "novenquadragintacentillion";
	case 453: return "quinquagintacentillion";
	case 456: return "unquinquagintacentillion";
	case 459: return "duoquinquagintacentillion";
	case 462: return "tresquinquagintacentillion";
	case 465: return "quattuorquinquagintacentillion";
	case 468: return "quinquinquagintacentillion";
	case 471: return "sesquinquagintacentillion";
	case 474: return "septenquinquagintacentillion";
	case 477: return "octoquinquagintacentillion";
	case 480: return "novenquinquagintacentillion";
	case 483: return "sexagintacentillion";
	case 486: return "unsexagintacentillion";
	case 489: return "duosexagintacentillion";
	case 492: return "tresexagintacentillion";
	case 495: return "quattuorsexagintacentillion";
	case 498: return "quinsexagintacentillion";
	case 501: return "sesexagintacentillion";
	case 504: return "septensexagintacentillion";
	case 507: return "octosexagintacentillion";
	case 510: return "novensexagintacentillion";
	case 513: return "septuagintacentillion";
	case 516: return "unseptuagintacentillion";
	case 519: return "duoseptuagintacentillion";
	case 522: return "treseptuagintacentillion";
	case 525: return "quattuorseptuagintacentillion";
	case 528: return "quinseptuagintacentillion";
	case 531: return "seseptuagintacentillion";
	case 534: return "septenseptuagintacentillion";
	case 537: return "octoseptuagintacentillion";
	case 540: return "novenseptuagintacentillion";
	case 543: return "octogintacentillion";
	case 546: return "unoctogintacentillion";
	case 549: return "duooctogintacentillion";
	case 552: return "tresoctogintacentillion";
	case 555: return "quattuoroctogintacentillion";
	case 558: return "quinoctogintacentillion";
	case 561: return "sexoctogintacentillion";
	case 564: return "septemoctogintacentillion";
	case 567: return "octooctogintacentillion";
	case 570: return "novemoctogintacentillion";
	case 573: return "nonagintacentillion";
	case 576: return "unnonagintacentillion";
	case 579: return "duononagintacentillion";
	case 582: return "trenonagintacentillion";
	case 585: return "quattuornonagintacentillion";
	case 588: return "quinnonagintacentillion";
	case 591: return "senonagintacentillion";
	case 594: return "septenonagintacentillion";
	case 597: return "octononagintacentillion";
	case 600: return "novenonagintacentillion";
	case 603: return "ducentillion";
	case 606: return "unducentillion";
	case 609: return "duoducentillion";
	case 612: return "treducentillion";
	case 615: return "quattuorducentillion";
	case 618: return "quinducentillion";
	case 621: return "seducentillion";
	case 624: return "septenducentillion";
	case 627: return "octoducentillion";
	case 630: return "novenducentillion";
	case 633: return "deciducentillion";
	case 636: return "undeciducentillion";
	case 639: return "duodeciducentillion";
	case 642: return "tredeciducentillion";
	case 645: return "quattuordeciducentillion";
	case 648: return "quindeciducentillion";
	case 651: return "sedeciducentillion";
	case 654: return "septendeciducentillion";
	case 657: return "octodeciducentillion";
	case 660: return "novendeciducentillion";
	case 663: return "Vigintiducentillion";
	case 666: return "unvigintiducentillion";
	case 669: return "duovigintiducentillion";
	case 672: return "tresvigintiducentillion";
	case 675: return "quattuorvigintiducentillion";
	case 678: return "quinvigintiducentillion";
	case 681: return "sesvigintiducentillion";
	case 684: return "septemvigintiducentillion";
	case 687: return "octovigintiducentillion";
	case 690: return "novemvigintiducentillion";
	case 693: return "trigintaducentillion";
	case 696: return "untrigintaducentillion";
	case 699: return "duotrigintaducentillion";
	case 702: return "trestrigintaducentillion";
	case 705: return "quattuortrigintaducentillion";
	case 708: return "quintrigintaducentillion";
	case 711: return "sestrigintaducentillion";
	case 714: return "septentrigintaducentillion";
	case 717: return "octotrigintaducentillion";
	case 720: return "noventrigintaducentillion";
	case 723: return "quadragintaducentillion";
	case 726: return "unquadragintaducentillion";
	case 729: return "duoquadragintaducentillion";
	case 732: return "tresquadragintaducentillion";
	case 735: return "quattuorquadragintaducentillion";
	case 738: return "quinquadragintaducentillion";
	case 741: return "sesquadragintaducentillion";
	case 744: return "septenquadragintaducentillion";
	case 747: return "octoquadragintaducentillion";
	case 750: return "novenquadragintaducentillion";
	case 753: return "quinquagintaducentillion";
	case 756: return "unquinquagintaducentillion";
	case 759: return "duoquinquagintaducentillion";
	case 762: return "tresquinquagintaducentillion";
	case 765: return "quattuorquinquagintaducentillion";
	case 768: return "quinquinquagintaducentillion";
	case 771: return "sesquinquagintaducentillion";
	case 774: return "septenquinquagintaducentillion";
	case 777: return "octoquinquagintaducentillion";
	case 780: return "novenquinquagintaducentillion";
	case 783: return "sexagintaducentillion";
	case 786: return "unsexagintaducentillion";
	case 789: return "duosexagintaducentillion";
	case 792: return "tresexagintaducentillion";
	case 795: return "quattuorsexagintaducentillion";
	case 798: return "quinsexagintaducentillion";
	case 801: return "sesexagintaducentillion";
	case 804: return "septensexagintaducentillion";
	case 807: return "octosexagintaducentillion";
	case 810: return "novensexagintaducentillion";
	case 813: return "septuagintaducentillion";
	case 816: return "unseptuagintaducentillion";
	case 819: return "duoseptuagintaducentillion";
	case 822: return "treseptuagintaducentillion";
	case 825: return "quattuorseptuagintaducentillion";
	case 828: return "quinseptuagintaducentillion";
	case 831: return "seseptuagintaducentillion";
	case 834: return "septenseptuagintaducentillion";
	case 837: return "octoseptuagintaducentillion";
	case 840: return "novenseptuagintaducentillion";
	case 843: return "octogintaducentillion";
	case 846: return "unoctogintaducentillion";
	case 849: return "duooctogintaducentillion";
	case 852: return "tresoctogintaducentillion";
	case 855: return "quattuoroctogintaducentillion";
	case 858: return "quinoctogintaducentillion";
	case 861: return "sexoctogintaducentillion";
	case 864: return "septemoctogintaducentillion";
	case 867: return "octooctogintaducentillion";
	case 870: return "novemoctogintaducentillion";
	case 873: return "nonagintaducentillion";
	case 876: return "unnonagintaducentillion";
	case 879: return "duononagintaducentillion";
	case 882: return "trenonagintaducentillion";
	case 885: return "quattuornonagintaducentillion";
	case 888: return "quinnonagintaducentillion";
	case 891: return "senonagintaducentillion";
	case 894: return "septenonagintaducentillion";
	case 897: return "octononagintaducentillion";
	case 900: return "novenonagintaducentillion";
	case 903: return "trecentillion";
	case 906: return "untrecentillion";
	case 909: return "duotrecentillion";
	case 912: return "trestrecentillion";
	case 915: return "quattuortrecentillion";
	case 918: return "quintrecentillion";
	case 921: return "sestrecentillion";
	case 924: return "septentrecentillion";
	case 927: return "octotrecentillion";
	case 930: return "noventrecentillion";
	case 933: return "decitrecentillion";
	case 936: return "undecitrecentillion";
	case 939: return "duodecitrecentillion";
	case 942: return "tredecitrecentillion";
	case 945: return "quattuordecitrecentillion";
	case 948: return "quindecitrecentillion";
	case 951: return "sedecitrecentillion";
	case 954: return "septendecitrecentillion";
	case 957: return "octodecitrecentillion";
	case 960: return "novendecitrecentillion";
	case 963: return "Vigintitrecentillion";
	case 966: return "unvigintitrecentillion";
	case 969: return "duovigintitrecentillion";
	case 972: return "tresvigintitrecentillion";
	case 975: return "quattuorvigintitrecentillion";
	case 978: return "quinvigintitrecentillion";
	case 981: return "sesvigintitrecentillion";
	case 984: return "septemvigintitrecentillion";
	case 987: return "octovigintitrecentillion";
	case 990: return "novemvigintitrecentillion";
	case 993: return "trigintatrecentillion";
	case 996: return "untrigintatrecentillion";
	case 999: return "duotrigintatrecentillion";
	case 1002: return "trestrigintatrecentillion";
	case 1005: return "quattuortrigintatrecentillion";
	case 1008: return "quintrigintatrecentillion";
	case 1011: return "sestrigintatrecentillion";
	case 1014: return "septentrigintatrecentillion";
	case 1017: return "octotrigintatrecentillion";
	case 1020: return "noventrigintatrecentillion";
	case 1023: return "quadragintatrecentillion";
	case 1026: return "unquadragintatrecentillion";
	case 1029: return "duoquadragintatrecentillion";
	case 1032: return "tresquadragintatrecentillion";
	case 1035: return "quattuorquadragintatrecentillion";
	case 1038: return "quinquadragintatrecentillion";
	case 1041: return "sesquadragintatrecentillion";
	case 1044: return "septenquadragintatrecentillion";
	case 1047: return "octoquadragintatrecentillion";
	case 1050: return "novenquadragintatrecentillion";
	case 1053: return "quinquagintatrecentillion";
	case 1056: return "unquinquagintatrecentillion";
	case 1059: return "duoquinquagintatrecentillion";
	case 1062: return "tresquinquagintatrecentillion";
	case 1065: return "quattuorquinquagintatrecentillion";
	case 1068: return "quinquinquagintatrecentillion";
	case 1071: return "sesquinquagintatrecentillion";
	case 1074: return "septenquinquagintatrecentillion";
	case 1077: return "octoquinquagintatrecentillion";
	case 1080: return "novenquinquagintatrecentillion";
	case 1083: return "sexagintatrecentillion";
	case 1086: return "unsexagintatrecentillion";
	case 1089: return "duosexagintatrecentillion";
	case 1092: return "tresexagintatrecentillion";
	case 1095: return "quattuorsexagintatrecentillion";
	case 1098: return "quinsexagintatrecentillion";
	case 1101: return "sesexagintatrecentillion";
	case 1104: return "septensexagintatrecentillion";
	case 1107: return "octosexagintatrecentillion";
	case 1110: return "novensexagintatrecentillion";
	case 1113: return "septuagintatrecentillion";
	case 1116: return "unseptuagintatrecentillion";
	case 1119: return "duoseptuagintatrecentillion";
	case 1122: return "treseptuagintatrecentillion";
	case 1125: return "quattuorseptuagintatrecentillion";
	case 1128: return "quinseptuagintatrecentillion";
	case 1131: return "seseptuagintatrecentillion";
	case 1134: return "septenseptuagintatrecentillion";
	case 1137: return "octoseptuagintatrecentillion";
	case 1140: return "novenseptuagintatrecentillion";
	case 1143: return "octogintatrecentillion";
	case 1146: return "unoctogintatrecentillion";
	case 1149: return "duooctogintatrecentillion";
	case 1152: return "tresoctogintatrecentillion";
	case 1155: return "quattuoroctogintatrecentillion";
	case 1158: return "quinoctogintatrecentillion";
	case 1161: return "sexoctogintatrecentillion";
	case 1164: return "septemoctogintatrecentillion";
	case 1167: return "octooctogintatrecentillion";
	case 1170: return "novemoctogintatrecentillion";
	case 1173: return "nonagintatrecentillion";
	case 1176: return "unnonagintatrecentillion";
	case 1179: return "duononagintatrecentillion";
	case 1182: return "trenonagintatrecentillion";
	case 1185: return "quattuornonagintatrecentillion";
	case 1188: return "quinnonagintatrecentillion";
	case 1191: return "senonagintatrecentillion";
	case 1194: return "septenonagintatrecentillion";
	case 1197: return "octononagintatrecentillion";
	case 1200: return "novenonagintatrecentillion";
	case 1203: return "quadringentillion";
	case 1206: return "unquadringentillion";
	case 1209: return "duoquadringentillion";
	case 1212: return "tresquadringentillion";
	case 1215: return "quattuorquadringentillion";
	case 1218: return "quinquadringentillion";
	case 1221: return "sesquadringentillion";
	case 1224: return "septenquadringentillion";
	case 1227: return "octoquadringentillion";
	case 1230: return "novenquadringentillion";
	case 1233: return "deciquadringentillion";
	case 1236: return "undeciquadringentillion";
	case 1239: return "duodeciquadringentillion";
	case 1242: return "tredeciquadringentillion";
	case 1245: return "quattuordeciquadringentillion";
	case 1248: return "quindeciquadringentillion";
	case 1251: return "sedeciquadringentillion";
	case 1254: return "septendeciquadringentillion";
	case 1257: return "octodeciquadringentillion";
	case 1260: return "novendeciquadringentillion";
	case 1263: return "Vigintiquadringentillion";
	case 1266: return "unvigintiquadringentillion";
	case 1269: return "duovigintiquadringentillion";
	case 1272: return "tresvigintiquadringentillion";
	case 1275: return "quattuorvigintiquadringentillion";
	case 1278: return "quinvigintiquadringentillion";
	case 1281: return "sesvigintiquadringentillion";
	case 1284: return "septemvigintiquadringentillion";
	case 1287: return "octovigintiquadringentillion";
	case 1290: return "novemvigintiquadringentillion";
	case 1293: return "trigintaquadringentillion";
	case 1296: return "untrigintaquadringentillion";
	case 1299: return "duotrigintaquadringentillion";
	case 1302: return "trestrigintaquadringentillion";
	case 1305: return "quattuortrigintaquadringentillion";
	case 1308: return "quintrigintaquadringentillion";
	case 1311: return "sestrigintaquadringentillion";
	case 1314: return "septentrigintaquadringentillion";
	case 1317: return "octotrigintaquadringentillion";
	case 1320: return "noventrigintaquadringentillion";
	case 1323: return "quadragintaquadringentillion";
	case 1326: return "unquadragintaquadringentillion";
	case 1329: return "duoquadragintaquadringentillion";
	case 1332: return "tresquadragintaquadringentillion";
	case 1335: return "quattuorquadragintaquadringentillion";
	case 1338: return "quinquadragintaquadringentillion";
	case 1341: return "sesquadragintaquadringentillion";
	case 1344: return "septenquadragintaquadringentillion";
	case 1347: return "octoquadragintaquadringentillion";
	case 1350: return "novenquadragintaquadringentillion";
	case 1353: return "quinquagintaquadringentillion";
	case 1356: return "unquinquagintaquadringentillion";
	case 1359: return "duoquinquagintaquadringentillion";
	case 1362: return "tresquinquagintaquadringentillion";
	case 1365: return "quattuorquinquagintaquadringentillion";
	case 1368: return "quinquinquagintaquadringentillion";
	case 1371: return "sesquinquagintaquadringentillion";
	case 1374: return "septenquinquagintaquadringentillion";
	case 1377: return "octoquinquagintaquadringentillion";
	case 1380: return "novenquinquagintaquadringentillion";
	case 1383: return "sexagintaquadringentillion";
	case 1386: return "unsexagintaquadringentillion";
	case 1389: return "duosexagintaquadringentillion";
	case 1392: return "tresexagintaquadringentillion";
	case 1395: return "quattuorsexagintaquadringentillion";
	case 1398: return "quinsexagintaquadringentillion";
	case 1401: return "sesexagintaquadringentillion";
	case 1404: return "septensexagintaquadringentillion";
	case 1407: return "octosexagintaquadringentillion";
	case 1410: return "novensexagintaquadringentillion";
	case 1413: return "septuagintaquadringentillion";
	case 1416: return "unseptuagintaquadringentillion";
	case 1419: return "duoseptuagintaquadringentillion";
	case 1422: return "treseptuagintaquadringentillion";
	case 1425: return "quattuorseptuagintaquadringentillion";
	case 1428: return "quinseptuagintaquadringentillion";
	case 1431: return "seseptuagintaquadringentillion";
	case 1434: return "septenseptuagintaquadringentillion";
	case 1437: return "octoseptuagintaquadringentillion";
	case 1440: return "novenseptuagintaquadringentillion";
	case 1443: return "octogintaquadringentillion";
	case 1446: return "unoctogintaquadringentillion";
	case 1449: return "duooctogintaquadringentillion";
	case 1452: return "tresoctogintaquadringentillion";
	case 1455: return "quattuoroctogintaquadringentillion";
	case 1458: return "quinoctogintaquadringentillion";
	case 1461: return "sexoctogintaquadringentillion";
	case 1464: return "septemoctogintaquadringentillion";
	case 1467: return "octooctogintaquadringentillion";
	case 1470: return "novemoctogintaquadringentillion";
	case 1473: return "nonagintaquadringentillion";
	case 1476: return "unnonagintaquadringentillion";
	case 1479: return "duononagintaquadringentillion";
	case 1482: return "trenonagintaquadringentillion";
	case 1485: return "quattuornonagintaquadringentillion";
	case 1488: return "quinnonagintaquadringentillion";
	case 1491: return "senonagintaquadringentillion";
	case 1494: return "septenonagintaquadringentillion";
	case 1497: return "octononagintaquadringentillion";
	case 1500: return "novenonagintaquadringentillion";
	case 1503: return "quingentillion";
	case 1506: return "unquingentillion";
	case 1509: return "duoquingentillion";
	case 1512: return "tresquingentillion";
	case 1515: return "quattuorquingentillion";
	case 1518: return "quinquingentillion";
	case 1521: return "sesquingentillion";
	case 1524: return "septenquingentillion";
	case 1527: return "octoquingentillion";
	case 1530: return "novenquingentillion";
	case 1533: return "deciquingentillion";
	case 1536: return "undeciquingentillion";
	case 1539: return "duodeciquingentillion";
	case 1542: return "tredeciquingentillion";
	case 1545: return "quattuordeciquingentillion";
	case 1548: return "quindeciquingentillion";
	case 1551: return "sedeciquingentillion";
	case 1554: return "septendeciquingentillion";
	case 1557: return "octodeciquingentillion";
	case 1560: return "novendeciquingentillion";
	case 1563: return "Vigintiquingentillion";
	case 1566: return "unvigintiquingentillion";
	case 1569: return "duovigintiquingentillion";
	case 1572: return "tresvigintiquingentillion";
	case 1575: return "quattuorvigintiquingentillion";
	case 1578: return "quinvigintiquingentillion";
	case 1581: return "sesvigintiquingentillion";
	case 1584: return "septemvigintiquingentillion";
	case 1587: return "octovigintiquingentillion";
	case 1590: return "novemvigintiquingentillion";
	case 1593: return "trigintaquingentillion";
	case 1596: return "untrigintaquingentillion";
	case 1599: return "duotrigintaquingentillion";
	case 1602: return "trestrigintaquingentillion";
	case 1605: return "quattuortrigintaquingentillion";
	case 1608: return "quintrigintaquingentillion";
	case 1611: return "sestrigintaquingentillion";
	case 1614: return "septentrigintaquingentillion";
	case 1617: return "octotrigintaquingentillion";
	case 1620: return "noventrigintaquingentillion";
	case 1623: return "quadragintaquingentillion";
	case 1626: return "unquadragintaquingentillion";
	case 1629: return "duoquadragintaquingentillion";
	case 1632: return "tresquadragintaquingentillion";
	case 1635: return "quattuorquadragintaquingentillion";
	case 1638: return "quinquadragintaquingentillion";
	case 1641: return "sesquadragintaquingentillion";
	case 1644: return "septenquadragintaquingentillion";
	case 1647: return "octoquadragintaquingentillion";
	case 1650: return "novenquadragintaquingentillion";
	case 1653: return "quinquagintaquingentillion";
	case 1656: return "unquinquagintaquingentillion";
	case 1659: return "duoquinquagintaquingentillion";
	case 1662: return "tresquinquagintaquingentillion";
	case 1665: return "quattuorquinquagintaquingentillion";
	case 1668: return "quinquinquagintaquingentillion";
	case 1671: return "sesquinquagintaquingentillion";
	case 1674: return "septenquinquagintaquingentillion";
	case 1677: return "octoquinquagintaquingentillion";
	case 1680: return "novenquinquagintaquingentillion";
	case 1683: return "sexagintaquingentillion";
	case 1686: return "unsexagintaquingentillion";
	case 1689: return "duosexagintaquingentillion";
	case 1692: return "tresexagintaquingentillion";
	case 1695: return "quattuorsexagintaquingentillion";
	case 1698: return "quinsexagintaquingentillion";
	case 1701: return "sesexagintaquingentillion";
	case 1704: return "septensexagintaquingentillion";
	case 1707: return "octosexagintaquingentillion";
	case 1710: return "novensexagintaquingentillion";
	case 1713: return "septuagintaquingentillion";
	case 1716: return "unseptuagintaquingentillion";
	case 1719: return "duoseptuagintaquingentillion";
	case 1722: return "treseptuagintaquingentillion";
	case 1725: return "quattuorseptuagintaquingentillion";
	case 1728: return "quinseptuagintaquingentillion";
	case 1731: return "seseptuagintaquingentillion";
	case 1734: return "septenseptuagintaquingentillion";
	case 1737: return "octoseptuagintaquingentillion";
	case 1740: return "novenseptuagintaquingentillion";
	case 1743: return "octogintaquingentillion";
	case 1746: return "unoctogintaquingentillion";
	case 1749: return "duooctogintaquingentillion";
	case 1752: return "tresoctogintaquingentillion";
	case 1755: return "quattuoroctogintaquingentillion";
	case 1758: return "quinoctogintaquingentillion";
	case 1761: return "sexoctogintaquingentillion";
	case 1764: return "septemoctogintaquingentillion";
	case 1767: return "octooctogintaquingentillion";
	case 1770: return "novemoctogintaquingentillion";
	case 1773: return "nonagintaquingentillion";
	case 1776: return "unnonagintaquingentillion";
	case 1779: return "duononagintaquingentillion";
	case 1782: return "trenonagintaquingentillion";
	case 1785: return "quattuornonagintaquingentillion";
	case 1788: return "quinnonagintaquingentillion";
	case 1791: return "senonagintaquingentillion";
	case 1794: return "septenonagintaquingentillion";
	case 1797: return "octononagintaquingentillion";
	case 1800: return "novenonagintaquingentillion";
	case 1803: return "sescentillion";
	case 1806: return "unsescentillion";
	case 1809: return "duosescentillion";
	case 1812: return "tresescentillion";
	case 1815: return "quattuorsescentillion";
	case 1818: return "quinsescentillion";
	case 1821: return "sesescentillion";
	case 1824: return "septensescentillion";
	case 1827: return "octosescentillion";
	case 1830: return "novensescentillion";
	case 1833: return "decisescentillion";
	case 1836: return "undecisescentillion";
	case 1839: return "duodecisescentillion";
	case 1842: return "tredecisescentillion";
	case 1845: return "quattuordecisescentillion";
	case 1848: return "quindecisescentillion";
	case 1851: return "sedecisescentillion";
	case 1854: return "septendecisescentillion";
	case 1857: return "octodecisescentillion";
	case 1860: return "novendecisescentillion";
	case 1863: return "Vigintisescentillion";
	case 1866: return "unvigintisescentillion";
	case 1869: return "duovigintisescentillion";
	case 1872: return "tresvigintisescentillion";
	case 1875: return "quattuorvigintisescentillion";
	case 1878: return "quinvigintisescentillion";
	case 1881: return "sesvigintisescentillion";
	case 1884: return "septemvigintisescentillion";
	case 1887: return "octovigintisescentillion";
	case 1890: return "novemvigintisescentillion";
	case 1893: return "trigintasescentillion";
	case 1896: return "untrigintasescentillion";
	case 1899: return "duotrigintasescentillion";
	case 1902: return "trestrigintasescentillion";
	case 1905: return "quattuortrigintasescentillion";
	case 1908: return "quintrigintasescentillion";
	case 1911: return "sestrigintasescentillion";
	case 1914: return "septentrigintasescentillion";
	case 1917: return "octotrigintasescentillion";
	case 1920: return "noventrigintasescentillion";
	case 1923: return "quadragintasescentillion";
	case 1926: return "unquadragintasescentillion";
	case 1929: return "duoquadragintasescentillion";
	case 1932: return "tresquadragintasescentillion";
	case 1935: return "quattuorquadragintasescentillion";
	case 1938: return "quinquadragintasescentillion";
	case 1941: return "sesquadragintasescentillion";
	case 1944: return "septenquadragintasescentillion";
	case 1947: return "octoquadragintasescentillion";
	case 1950: return "novenquadragintasescentillion";
	case 1953: return "quinquagintasescentillion";
	case 1956: return "unquinquagintasescentillion";
	case 1959: return "duoquinquagintasescentillion";
	case 1962: return "tresquinquagintasescentillion";
	case 1965: return "quattuorquinquagintasescentillion";
	case 1968: return "quinquinquagintasescentillion";
	case 1971: return "sesquinquagintasescentillion";
	case 1974: return "septenquinquagintasescentillion";
	case 1977: return "octoquinquagintasescentillion";
	case 1980: return "novenquinquagintasescentillion";
	case 1983: return "sexagintasescentillion";
	case 1986: return "unsexagintasescentillion";
	case 1989: return "duosexagintasescentillion";
	case 1992: return "tresexagintasescentillion";
	case 1995: return "quattuorsexagintasescentillion";
	case 1998: return "quinsexagintasescentillion";
	case 2001: return "sesexagintasescentillion";
	case 2004: return "septensexagintasescentillion";
	case 2007: return "octosexagintasescentillion";
	case 2010: return "novensexagintasescentillion";
	case 2013: return "septuagintasescentillion";
	case 2016: return "unseptuagintasescentillion";
	case 2019: return "duoseptuagintasescentillion";
	case 2022: return "treseptuagintasescentillion";
	case 2025: return "quattuorseptuagintasescentillion";
	case 2028: return "quinseptuagintasescentillion";
	case 2031: return "seseptuagintasescentillion";
	case 2034: return "septenseptuagintasescentillion";
	case 2037: return "octoseptuagintasescentillion";
	case 2040: return "novenseptuagintasescentillion";
	case 2043: return "octogintasescentillion";
	case 2046: return "unoctogintasescentillion";
	case 2049: return "duooctogintasescentillion";
	case 2052: return "tresoctogintasescentillion";
	case 2055: return "quattuoroctogintasescentillion";
	case 2058: return "quinoctogintasescentillion";
	case 2061: return "sexoctogintasescentillion";
	case 2064: return "septemoctogintasescentillion";
	case 2067: return "octooctogintasescentillion";
	case 2070: return "novemoctogintasescentillion";
	case 2073: return "nonagintasescentillion";
	case 2076: return "unnonagintasescentillion";
	case 2079: return "duononagintasescentillion";
	case 2082: return "trenonagintasescentillion";
	case 2085: return "quattuornonagintasescentillion";
	case 2088: return "quinnonagintasescentillion";
	case 2091: return "senonagintasescentillion";
	case 2094: return "septenonagintasescentillion";
	case 2097: return "octononagintasescentillion";
	case 2100: return "novenonagintasescentillion";
	case 2103: return "septingentillion";
	case 2106: return "unseptingentillion";
	case 2109: return "duoseptingentillion";
	case 2112: return "treseptingentillion";
	case 2115: return "quattuorseptingentillion";
	case 2118: return "quinseptingentillion";
	case 2121: return "seseptingentillion";
	case 2124: return "septenseptingentillion";
	case 2127: return "octoseptingentillion";
	case 2130: return "novenseptingentillion";
	case 2133: return "deciseptingentillion";
	case 2136: return "undeciseptingentillion";
	case 2139: return "duodeciseptingentillion";
	case 2142: return "tredeciseptingentillion";
	case 2145: return "quattuordeciseptingentillion";
	case 2148: return "quindeciseptingentillion";
	case 2151: return "sedeciseptingentillion";
	case 2154: return "septendeciseptingentillion";
	case 2157: return "octodeciseptingentillion";
	case 2160: return "novendeciseptingentillion";
	case 2163: return "Vigintiseptingentillion";
	case 2166: return "unvigintiseptingentillion";
	case 2169: return "duovigintiseptingentillion";
	case 2172: return "tresvigintiseptingentillion";
	case 2175: return "quattuorvigintiseptingentillion";
	case 2178: return "quinvigintiseptingentillion";
	case 2181: return "sesvigintiseptingentillion";
	case 2184: return "septemvigintiseptingentillion";
	case 2187: return "octovigintiseptingentillion";
	case 2190: return "novemvigintiseptingentillion";
	case 2193: return "trigintaseptingentillion";
	case 2196: return "untrigintaseptingentillion";
	case 2199: return "duotrigintaseptingentillion";
	case 2202: return "trestrigintaseptingentillion";
	case 2205: return "quattuortrigintaseptingentillion";
	case 2208: return "quintrigintaseptingentillion";
	case 2211: return "sestrigintaseptingentillion";
	case 2214: return "septentrigintaseptingentillion";
	case 2217: return "octotrigintaseptingentillion";
	case 2220: return "noventrigintaseptingentillion";
	case 2223: return "quadragintaseptingentillion";
	case 2226: return "unquadragintaseptingentillion";
	case 2229: return "duoquadragintaseptingentillion";
	case 2232: return "tresquadragintaseptingentillion";
	case 2235: return "quattuorquadragintaseptingentillion";
	case 2238: return "quinquadragintaseptingentillion";
	case 2241: return "sesquadragintaseptingentillion";
	case 2244: return "septenquadragintaseptingentillion";
	case 2247: return "octoquadragintaseptingentillion";
	case 2250: return "novenquadragintaseptingentillion";
	case 2253: return "quinquagintaseptingentillion";
	case 2256: return "unquinquagintaseptingentillion";
	case 2259: return "duoquinquagintaseptingentillion";
	case 2262: return "tresquinquagintaseptingentillion";
	case 2265: return "quattuorquinquagintaseptingentillion";
	case 2268: return "quinquinquagintaseptingentillion";
	case 2271: return "sesquinquagintaseptingentillion";
	case 2274: return "septenquinquagintaseptingentillion";
	case 2277: return "octoquinquagintaseptingentillion";
	case 2280: return "novenquinquagintaseptingentillion";
	case 2283: return "sexagintaseptingentillion";
	case 2286: return "unsexagintaseptingentillion";
	case 2289: return "duosexagintaseptingentillion";
	case 2292: return "tresexagintaseptingentillion";
	case 2295: return "quattuorsexagintaseptingentillion";
	case 2298: return "quinsexagintaseptingentillion";
	case 2301: return "sesexagintaseptingentillion";
	case 2304: return "septensexagintaseptingentillion";
	case 2307: return "octosexagintaseptingentillion";
	case 2310: return "novensexagintaseptingentillion";
	case 2313: return "septuagintaseptingentillion";
	case 2316: return "unseptuagintaseptingentillion";
	case 2319: return "duoseptuagintaseptingentillion";
	case 2322: return "treseptuagintaseptingentillion";
	case 2325: return "quattuorseptuagintaseptingentillion";
	case 2328: return "quinseptuagintaseptingentillion";
	case 2331: return "seseptuagintaseptingentillion";
	case 2334: return "septenseptuagintaseptingentillion";
	case 2337: return "octoseptuagintaseptingentillion";
	case 2340: return "novenseptuagintaseptingentillion";
	case 2343: return "octogintaseptingentillion";
	case 2346: return "unoctogintaseptingentillion";
	case 2349: return "duooctogintaseptingentillion";
	case 2352: return "tresoctogintaseptingentillion";
	case 2355: return "quattuoroctogintaseptingentillion";
	case 2358: return "quinoctogintaseptingentillion";
	case 2361: return "sexoctogintaseptingentillion";
	case 2364: return "septemoctogintaseptingentillion";
	case 2367: return "octooctogintaseptingentillion";
	case 2370: return "novemoctogintaseptingentillion";
	case 2373: return "nonagintaseptingentillion";
	case 2376: return "unnonagintaseptingentillion";
	case 2379: return "duononagintaseptingentillion";
	case 2382: return "trenonagintaseptingentillion";
	case 2385: return "quattuornonagintaseptingentillion";
	case 2388: return "quinnonagintaseptingentillion";
	case 2391: return "senonagintaseptingentillion";
	case 2394: return "septenonagintaseptingentillion";
	case 2397: return "octononagintaseptingentillion";
	case 2400: return "novenonagintaseptingentillion";
	case 2403: return "octingentillion";
	case 2406: return "unoctingentillion";
	case 2409: return "duooctingentillion";
	case 2412: return "tresoctingentillion";
	case 2415: return "quattuoroctingentillion";
	case 2418: return "quinoctingentillion";
	case 2421: return "sexoctingentillion";
	case 2424: return "septemoctingentillion";
	case 2427: return "octooctingentillion";
	case 2430: return "novemoctingentillion";
	case 2433: return "decioctingentillion";
	case 2436: return "undecioctingentillion";
	case 2439: return "duodecioctingentillion";
	case 2442: return "tredecioctingentillion";
	case 2445: return "quattuordecioctingentillion";
	case 2448: return "quindecioctingentillion";
	case 2451: return "sedecioctingentillion";
	case 2454: return "septendecioctingentillion";
	case 2457: return "octodecioctingentillion";
	case 2460: return "novendecioctingentillion";
	case 2463: return "Vigintioctingentillion";
	case 2466: return "unvigintioctingentillion";
	case 2469: return "duovigintioctingentillion";
	case 2472: return "tresvigintioctingentillion";
	case 2475: return "quattuorvigintioctingentillion";
	case 2478: return "quinvigintioctingentillion";
	case 2481: return "sesvigintioctingentillion";
	case 2484: return "septemvigintioctingentillion";
	case 2487: return "octovigintioctingentillion";
	case 2490: return "novemvigintioctingentillion";
	case 2493: return "trigintaoctingentillion";
	case 2496: return "untrigintaoctingentillion";
	case 2499: return "duotrigintaoctingentillion";
	case 2502: return "trestrigintaoctingentillion";
	case 2505: return "quattuortrigintaoctingentillion";
	case 2508: return "quintrigintaoctingentillion";
	case 2511: return "sestrigintaoctingentillion";
	case 2514: return "septentrigintaoctingentillion";
	case 2517: return "octotrigintaoctingentillion";
	case 2520: return "noventrigintaoctingentillion";
	case 2523: return "quadragintaoctingentillion";
	case 2526: return "unquadragintaoctingentillion";
	case 2529: return "duoquadragintaoctingentillion";
	case 2532: return "tresquadragintaoctingentillion";
	case 2535: return "quattuorquadragintaoctingentillion";
	case 2538: return "quinquadragintaoctingentillion";
	case 2541: return "sesquadragintaoctingentillion";
	case 2544: return "septenquadragintaoctingentillion";
	case 2547: return "octoquadragintaoctingentillion";
	case 2550: return "novenquadragintaoctingentillion";
	case 2553: return "quinquagintaoctingentillion";
	case 2556: return "unquinquagintaoctingentillion";
	case 2559: return "duoquinquagintaoctingentillion";
	case 2562: return "tresquinquagintaoctingentillion";
	case 2565: return "quattuorquinquagintaoctingentillion";
	case 2568: return "quinquinquagintaoctingentillion";
	case 2571: return "sesquinquagintaoctingentillion";
	case 2574: return "septenquinquagintaoctingentillion";
	case 2577: return "octoquinquagintaoctingentillion";
	case 2580: return "novenquinquagintaoctingentillion";
	case 2583: return "sexagintaoctingentillion";
	case 2586: return "unsexagintaoctingentillion";
	case 2589: return "duosexagintaoctingentillion";
	case 2592: return "tresexagintaoctingentillion";
	case 2595: return "quattuorsexagintaoctingentillion";
	case 2598: return "quinsexagintaoctingentillion";
	case 2601: return "sesexagintaoctingentillion";
	case 2604: return "septensexagintaoctingentillion";
	case 2607: return "octosexagintaoctingentillion";
	case 2610: return "novensexagintaoctingentillion";
	case 2613: return "septuagintaoctingentillion";
	case 2616: return "unseptuagintaoctingentillion";
	case 2619: return "duoseptuagintaoctingentillion";
	case 2622: return "treseptuagintaoctingentillion";
	case 2625: return "quattuorseptuagintaoctingentillion";
	case 2628: return "quinseptuagintaoctingentillion";
	case 2631: return "seseptuagintaoctingentillion";
	case 2634: return "septenseptuagintaoctingentillion";
	case 2637: return "octoseptuagintaoctingentillion";
	case 2640: return "novenseptuagintaoctingentillion";
	case 2643: return "octogintaoctingentillion";
	case 2646: return "unoctogintaoctingentillion";
	case 2649: return "duooctogintaoctingentillion";
	case 2652: return "tresoctogintaoctingentillion";
	case 2655: return "quattuoroctogintaoctingentillion";
	case 2658: return "quinoctogintaoctingentillion";
	case 2661: return "sexoctogintaoctingentillion";
	case 2664: return "septemoctogintaoctingentillion";
	case 2667: return "octooctogintaoctingentillion";
	case 2670: return "novemoctogintaoctingentillion";
	case 2673: return "nonagintaoctingentillion";
	case 2676: return "unnonagintaoctingentillion";
	case 2679: return "duononagintaoctingentillion";
	case 2682: return "trenonagintaoctingentillion";
	case 2685: return "quattuornonagintaoctingentillion";
	case 2688: return "quinnonagintaoctingentillion";
	case 2691: return "senonagintaoctingentillion";
	case 2694: return "septenonagintaoctingentillion";
	case 2697: return "octononagintaoctingentillion";
	case 2700: return "novenonagintaoctingentillion";
	case 2703: return "nongentillion";
	case 2706: return "unnongentillion";
	case 2709: return "duonongentillion";
	case 2712: return "trenongentillion";
	case 2715: return "quattuornongentillion";
	case 2718: return "quinnongentillion";
	case 2721: return "senongentillion";
	case 2724: return "septenongentillion";
	case 2727: return "octonongentillion";
	case 2730: return "novenongentillion";
	case 2733: return "decinongentillion";
	case 2736: return "undecinongentillion";
	case 2739: return "duodecinongentillion";
	case 2742: return "tredecinongentillion";
	case 2745: return "quattuordecinongentillion";
	case 2748: return "quindecinongentillion";
	case 2751: return "sedecinongentillion";
	case 2754: return "septendecinongentillion";
	case 2757: return "octodecinongentillion";
	case 2760: return "novendecinongentillion";
	case 2763: return "Vigintinongentillion";
	case 2766: return "unvigintinongentillion";
	case 2769: return "duovigintinongentillion";
	case 2772: return "tresvigintinongentillion";
	case 2775: return "quattuorvigintinongentillion";
	case 2778: return "quinvigintinongentillion";
	case 2781: return "sesvigintinongentillion";
	case 2784: return "septemvigintinongentillion";
	case 2787: return "octovigintinongentillion";
	case 2790: return "novemvigintinongentillion";
	case 2793: return "trigintanongentillion";
	case 2796: return "untrigintanongentillion";
	case 2799: return "duotrigintanongentillion";
	case 2802: return "trestrigintanongentillion";
	case 2805: return "quattuortrigintanongentillion";
	case 2808: return "quintrigintanongentillion";
	case 2811: return "sestrigintanongentillion";
	case 2814: return "septentrigintanongentillion";
	case 2817: return "octotrigintanongentillion";
	case 2820: return "noventrigintanongentillion";
	case 2823: return "quadragintanongentillion";
	case 2826: return "unquadragintanongentillion";
	case 2829: return "duoquadragintanongentillion";
	case 2832: return "tresquadragintanongentillion";
	case 2835: return "quattuorquadragintanongentillion";
	case 2838: return "quinquadragintanongentillion";
	case 2841: return "sesquadragintanongentillion";
	case 2844: return "septenquadragintanongentillion";
	case 2847: return "octoquadragintanongentillion";
	case 2850: return "novenquadragintanongentillion";
	case 2853: return "quinquagintanongentillion";
	case 2856: return "unquinquagintanongentillion";
	case 2859: return "duoquinquagintanongentillion";
	case 2862: return "tresquinquagintanongentillion";
	case 2865: return "quattuorquinquagintanongentillion";
	case 2868: return "quinquinquagintanongentillion";
	case 2871: return "sesquinquagintanongentillion";
	case 2874: return "septenquinquagintanongentillion";
	case 2877: return "octoquinquagintanongentillion";
	case 2880: return "novenquinquagintanongentillion";
	case 2883: return "sexagintanongentillion";
	case 2886: return "unsexagintanongentillion";
	case 2889: return "duosexagintanongentillion";
	case 2892: return "tresexagintanongentillion";
	case 2895: return "quattuorsexagintanongentillion";
	case 2898: return "quinsexagintanongentillion";
	case 2901: return "sesexagintanongentillion";
	case 2904: return "septensexagintanongentillion";
	case 2907: return "octosexagintanongentillion";
	case 2910: return "novensexagintanongentillion";
	case 2913: return "septuagintanongentillion";
	case 2916: return "unseptuagintanongentillion";
	case 2919: return "duoseptuagintanongentillion";
	case 2922: return "treseptuagintanongentillion";
	case 2925: return "quattuorseptuagintanongentillion";
	case 2928: return "quinseptuagintanongentillion";
	case 2931: return "seseptuagintanongentillion";
	case 2934: return "septenseptuagintanongentillion";
	case 2937: return "octoseptuagintanongentillion";
	case 2940: return "novenseptuagintanongentillion";
	case 2943: return "octogintanongentillion";
	case 2946: return "unoctogintanongentillion";
	case 2949: return "duooctogintanongentillion";
	case 2952: return "tresoctogintanongentillion";
	case 2955: return "quattuoroctogintanongentillion";
	case 2958: return "quinoctogintanongentillion";
	case 2961: return "sexoctogintanongentillion";
	case 2964: return "septemoctogintanongentillion";
	case 2967: return "octooctogintanongentillion";
	case 2970: return "novemoctogintanongentillion";
	case 2973: return "nonagintanongentillion";
	case 2976: return "unnonagintanongentillion";
	case 2979: return "duononagintanongentillion";
	case 2982: return "trenonagintanongentillion";
	case 2985: return "quattuornonagintanongentillion";
	case 2988: return "quinnonagintanongentillion";
	case 2991: return "senonagintanongentillion";
	case 2994: return "septenonagintanongentillion";
	case 2997: return "octononagintanongentillion";
	case 3000: return "novenonagintanongentillion";
	case 3003: return "millinillion/millillion";
	case 3006: return "millimillion";
	case 3009: return "millibillion";
	case 3012: return "millitrillion";
	}
	return "";
}

unsigned onetenhundred(const unsigned Length_of_number)
{
	unsigned x{ Length_of_number };
	for (; x > 3; x -= 3);
	return x;
	//same solution with recursion
	//if (Length_of_number < 4) return Length_of_number;
	//return onetenhundred(Length_of_number - 3);
}

std::string toones(const unsigned number)
{
	switch (number)
	{
	case 0: return "zero";
	case 1: return "one";
	case 2: return "two";
	case 3: return "three";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
	case 10: return "ten";
	case 11: return "eleven";
	case 12: return "twelve";
	case 13: return "thirteen";
	case 14: return "fourteen";
	case 15: return "fifteen";
	case 16: return "sixteen";
	case 17: return "seventeen";
	case 18: return "eighteen";
	case 19: return "nineteen";
	case 20: return "twenty";
	case 30: return "thirty";
	case 40: return "forty";
	case 50: return "fifty";
	case 60: return "sixty";
	case 70: return "seventy";
	case 80: return "eighty";
	case 90: return "ninety";
	}
	return "ERROR at toones() function";
}

std::string totens(const unsigned number)
{
	const unsigned tensDigit = (number / 10) % 10;
	const unsigned onesDigit = number % 10;

	if ((10U <= number && number <= 20U) || number == tensDigit * 10) return toones(number);

	if (tensDigit * 10 + 1 <= number && number <= tensDigit * 10 + 9)
		return toones(tensDigit * 10) + " " + toones(onesDigit);

	return "Failure in Tens";
}

std::string tohundreds(const unsigned number)
{
	const unsigned hundredsDigit = (number / 100) % 10;
	const unsigned tensDigit = (number / 10) % 10;
	const unsigned onesDigit = number % 10;

	if (number == hundredsDigit * 100) return toones(hundredsDigit) + " hundred";

	if (hundredsDigit * 100 + 1 <= number && number <= hundredsDigit * 100 + 9)
		return toones(hundredsDigit) + " hundred " + toones(onesDigit);

	if (hundredsDigit * 100 + 10 <= number && number <= hundredsDigit * 100 + 99)
		return toones(hundredsDigit) + " hundred " + totens((tensDigit * 10) + onesDigit);

	return "Failure in Hundreds";
}

std::string core(std::string number)
{
	std::string result = "";
	const short pos = onetenhundred(number.length());
	switch (pos)
	{
	case 3:
		result = tohundreds(stoi(number.substr(0, pos)));
		break;
	case 2:
		result = totens(stoi(number.substr(0, pos)));
		break;
	case 1:
		result = toones(stoi(number.substr(0, pos)));
		break;
	default:
		result = "";
	}
	result += " " + words(number.length() - pos);

	for (unsigned x = pos; x <= number.length() - 1; x += 3)
	{//trim start 0 in number.substr if number.substr = 0 add nothing to tmp 
		auto tmp = std::to_string(std::stoi(number.substr(x, 3)));
		if (tmp == "0") tmp.clear();

		switch (onetenhundred(tmp.length()))
		{
		case 3:// substr > 99 && substr < 1000
			result += " " + tohundreds(std::stoi(tmp));
			break;
		case 2: // substr < 100
			result += " " + totens(std::stoi(tmp));
			break;
		case 1: // substr > 0 && substr < 10
			result += " " + toones(std::stoi(tmp));
		}
		if (!tmp.empty()) result += " " + words(number.substr(x + 3, number.length() - 1).length());
	}
	return result;
}

std::string numbertoword(const std::string number)
{
	std::string tmp{ number };
	if (std::any_of(number.begin(), number.end(),
		[](unsigned char it) {return !isdigit(it); })) tmp = "";
	else tmp = [&tmp, &number](unsigned count = 0) -> std::string {if (tmp.empty())return ""; while (number[count] == '0')count++; if (count == number.length()) return "0"; return number.substr(count); }();

	switch (tmp.length())
	{
	case 0: return "ERROR: Insert numbers only";
	case 1: return toones(std::stoi(tmp));
	case 2: return totens(std::stoi(tmp));
	case 3: return tohundreds(std::stoi(tmp));
	}
	return core(tmp);
}
