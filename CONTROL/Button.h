class button
{
private:
	int x, y;
	int width, height;
	string title;
	bool isHover;

public:
	bool click;

	button(int x, int y, int width, int height, string title)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->title = title;
	}

	//Ve nut
	void draw()
	{
		setfillstyle(SOLID_FILL, click ? BG_BUTTON_CLICK : (isHover ? BG_BUTTON_SELECT : BG_BUTTON_DEFAULT));
		bar(x, y, x + width, y + height);

		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setbkcolor(click ? BG_BUTTON_CLICK : (isHover ? BG_BUTTON_SELECT : BG_BUTTON_DEFAULT));
		setcolor(isHover ? TEXT_BUTTON_SELECT : TEXT_BUTTON_DEFAULT);

		outtextxy(x + width / 2 - textwidth(&title[0]) / 2, y + (height - textheight(&title[0])) / 2, &title[0]);
		setbkcolor(BG_COLOR);
		setcolor(DRAW_COLOR);
	}

	bool isMouseHover()
	{
		int mx = mousex();
		int my = mousey();
		if (mx >= x && mx <= x + width && my >= y && my <= y + height)
		{
			return true;
		}
		return false;
	}

	//Hieu ung doi mau khi luot chuot qua
	void ButtonEffect()
	{
		if (isMouseHover())
		{
			if (isHover == false)
			{
				isHover = true;
				draw();
			}
		}
		else
		{
			if (isHover == true)
			{
				isHover = false;
				draw();
			}
		}
	}
};