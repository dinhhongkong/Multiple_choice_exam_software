const int w = 1600;
#define MAXLOP 100
#define MAXMONHOC 100
#define MIN_ID 1    // The minimum of quantity of questions
#define MAX_ID 5000 // The maximum of quantity of questions

// Define button
#define BG_BUTTON_DEFAULT           7
#define BG_BUTTON_SELECT            1
#define BG_BUTTON_CLICK             4
#define TEXT_BUTTON_SELECT          15
#define TEXT_BUTTON_DEFAULT         0
#define BG_COLOR                    0

// Define edittext
#define TEXT_EDIITEXT_TITLE_COLOR   13
#define BG_EDITTEXT_COLOR           2
#define TEXT_EDIITEXT_HINT_COLOR    7
#define TEXT_EDITTEXT_COLOR         4
#define DRAW_COLOR                  15

// Define radiobutton
#define RADIO_BUTTON_CLICK          4
#define RADIO_BUTTON_DEFAULT        0
#define RADIO_BUTTON_SELECT         7

// Define keyboard
#define ENTER                       13
#define BACKSPACE                   8
#define SPACE                       32
#define KEYUP                       38
#define KEYDOWN                     40

enum ScanType
{
    ONLY_NUMBER,
    ONLY_TEXT,
    SPACE_TEXT,
    TEXT_NUMBER,
    TEXT_NUMBER_NO_SPACE,
    SCAN_MALOP,
    SCAN_PASS,
    SCAN_ALL
};

enum Display
{
    DISPLAY_LOGIN,
    DISPLAY_HOCSINH,
    DISPLAY_DOIMK,
    LUACHON_THI_HS,
    DISPLAY_HSTHI,
    DISPLAY_DIEMSV,
    DISPLAY_GIAOVIEN,
    DISPLAY_DSMON,
    DISPLAY_DSLOP,
    DISPLAY_DSSV,
    DISPLAY_DIEMMON,
    DISLPAY_DIEM_THEO_SV,
    DISPLAY_DSDIEMGV,
    LUACHON_LOP,
    LUACHON_MON,
    CHUCNANG_CAUHOI,
    DISPLAY_THITHU,
    VAO_THITHU,
    XEMBAI_THUTHU
};