//--------------------------------- NGUYEN MAU HAM ---------------------------------
void ScanNumber(editText *&txt, char c);
void ScanTextOnly(editText *&txt, char c);
void ScanTextSpace(editText *&txt, char c);
void ScanTextNumber(editText *&txt, char c);
void ScanTextNumberNoSpace(editText *&txt, char c);
void ScanMaLop(editText *&txt, char c);
void ScanPass(editText *&txt, char c);
void ScanAll(editText *&txt, char c);

//--------------------------------- DINH NGHIA HAM ---------------------------------
void Scan(editText *&txt, int maxn, ScanType type)
{
	if (txt == nullptr)
		return;

	int mx = -1, my = -1, mrx = -1, mry = -1;
	getmouseclick(WM_LBUTTONDOWN, mx, my);
	clearmouseclick(WM_LBUTTONDOWN);

	getmouseclick(WM_RBUTTONDOWN, mrx, mry);
	clearmouseclick(WM_RBUTTONDOWN);
	if (((mx != -1 && my != -1) || (mrx != -1 && mry != -1)) && (!txt->isMouseHover()))
	{
		txt->isChoose = false;
		txt->draw();
		txt = nullptr;
		return;
	}

	if (kbhit())
	{
		char c = getch();
		if (c == BACKSPACE)
		{
			if (txt->content.size() > 0)
			{
				txt->content.pop_back();
				txt->draw();
			}
		}
		else if (c == ENTER)
		{
			txt->isChoose = false;
			txt->draw();
			txt = txt->next;
			return;
		}
		else if (c == NULL) // Bat phim di chuyen
		{
			c = getch();
			if (c == KEY_DOWN)
			{

				txt->isChoose = false;
				txt->draw();
				txt = txt->next;
				return;
			}
			else if (c == KEY_UP)
			{
				txt->isChoose = false;
				txt->draw();
				txt = txt->pre;
				return;
			}
		}
		else if (txt->content.size() < maxn)
		{
			if (type == ONLY_NUMBER)
			{
				ScanNumber(txt, c);
			}
			else if (type == ONLY_TEXT)
			{
				ScanTextOnly(txt, c);
			}
			else if (type == SPACE_TEXT)
			{
				ScanTextSpace(txt, c);
			}
			else if (type == TEXT_NUMBER)
			{
				ScanTextNumber(txt, c);
			}
			else if (type == TEXT_NUMBER_NO_SPACE)
			{
				ScanTextNumberNoSpace(txt, c);
			}
			else if (type == SCAN_MALOP)
			{
				ScanMaLop(txt, c);
			}
			else if (type == SCAN_PASS)
			{
				ScanPass(txt, c);
			}
			else if (type == SCAN_ALL)
			{
				ScanAll(txt, c);
			}
		}
	}
}

void ScanNumber(editText *&txt, char c)
{
	if ( txt->content.size() == 0 && c == '0') {
		return;
	}
	if (c >= '0' && c <= '9')
	{
		txt->content += c;
	}
}

void ScanTextOnly(editText *&txt, char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
}

void ScanTextSpace(editText *&txt, char c)
{
	if (c == SPACE)
	{
		if (txt->content.size() > 0 && txt->content[txt->content.size() - 1] != ' ')
			txt->content += ' ';
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
}

void ScanTextNumber(editText *&txt, char c)
{
	if (c == SPACE)
	{
		if (txt->content.size() > 0 && txt->content[txt->content.size() - 1] != ' ')
			txt->content += ' ';
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
	else if (c >= '0' && c <= '9')
	{
		txt->content += c;
	}
}

void ScanTextNumberNoSpace(editText *&txt, char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
	else if (c >= '0' && c <= '9')
	{
		txt->content += c;
	}
}

void ScanMaLop(editText *&txt, char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
	else if (c >= '0' && c <= '9' || c == '-')
	{
		txt->content += c;
	}
}

void ScanPass(editText *&txt, char c)
{

	if (c >= ' ' && c <= '~')
	{
		txt->content += c;
	}
}

void ScanAll(editText *&txt, char c)
{
	if (c == SPACE)
	{
		if (txt->content.size() > 0 && txt->content[txt->content.size() - 1] != ' ')
			txt->content += ' ';
	}
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		txt->content += toupper(c);
	}
	else if (c != SPACE)
	{
		txt->content += toupper(c);
	}
}