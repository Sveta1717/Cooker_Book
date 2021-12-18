#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <direct.h>
#include <fstream> // для работы с файлами
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
enum BookObjects { PAGES, NAME, CAPTION, BORDER };
enum Colors { DARKBLUE = 9, YELLOW = 14, BLUE = 11, WHITE = 119, DARKYELLOW = 6, LIGHTBLUE = 48 };

void Filling(int book[][70], int width, int height) // алгоритм заполнения
{
	for (int y = 0; y < height; y++) // перебор строк
	{
		for (int x = 0; x < width; x++) // перебор столбцов
		{
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
			{
				book[y][x] = BookObjects::BORDER;
			}
		}
	}
}

void Book(int book[][70], int width, int height) // показ книги
{
	for (int y = 0; y < height; y++) // перебор строк
	{
		for (int x = 0; x < width; x++) // перебор столбцов
		{
			switch (book[y][x])
			{
			case BookObjects::PAGES: // страница	
				SetConsoleTextAttribute(h, Colors::BLUE);
				cout << " ";
				break;

			case BookObjects::BORDER: // рамка
				SetConsoleTextAttribute(h, Colors::WHITE);
				cout << (char)42;
				break;
			}
		}
		cout << "\n";
	}
}

void Cursor() // скрытие мигающего курсора 
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false; // спрятать курсор
	cursor.dwSize = 1; // 1...100
	SetConsoleCursorInfo(h, &cursor);
}

void Name()
{
	//system("mode con cols=50 lines=34"); // размер консоли
	//system("title LOGFONT");

	HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
	HDC hdc = GetDC(hwnd); // данные типа HDC представляют собой 32-разрядное целое беззнаковое число.

	LOGFONT font; // настройки логического шрифта
	font.lfHeight = 50;// высота символов
	font.lfEscapement = 0;// угол между вектором наклона и осью X устройства
	font.lfWeight = 10;// толщина шрифта в диапазоне от 0 до 1000
	font.lfItalic = true;// курсивный шрифт
	font.lfUnderline = true;// подчеркнутый шрифт
	font.lfStrikeOut = false;// зачеркнутый шрифт
	lstrcpy(font.lfFaceName, L"Calibri");// название шрифта

	SetTextColor(hdc, RGB(0, 215, 215)); // цвет текста
	SetBkColor(hdc, RGB(0, 0, 0)); // цвет фона

	SelectObject(hdc, CreateFontIndirect(&font)); // выбор объекта с настройками отображения

	TextOutA(hdc, 350, 15, "Кулинарная книга", 16); // вывод текста на экран в точке 350, 15,  16 - количество знаков

	ReleaseDC(hwnd, hdc);
}

void Coord() // координаты
{
	COORD position;

	position.X = 2;
	position.Y = 2;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::DARKYELLOW);
	cout << " Названия рецептов";

	position.X = 2;
	position.Y = 3;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Говядина Веллингтон";

	position.X = 2;
	position.Y = 4;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Кошковал пане";

	position.X = 2;
	position.Y = 5;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Клубничный ликер";

	position.X = 2;
	position.Y = 6;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Курица по китайски";

	position.X = 2;
	position.Y = 7;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Маринованный яйца";

	position.X = 2;
	position.Y = 8;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Кимчи";

	position.X = 2;
	position.Y = 9;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Пирог с зеленым луком";

	position.X = 2;
	position.Y = 10;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Бланманже";

	position.X = 2;
	position.Y = 11;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Шоколадный Павлова";

	position.X = 2;
	position.Y = 12;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::YELLOW);
	cout << "-Фрикасе из кролика";

	/*position.X = 23;
	position.Y = 13;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::LIGHTBLUE);
	cout << "Поиск   ";

	position.X = 32;
	position.Y = 13;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, Colors::LIGHTBLUE);
	cout << "Добавить";

	if (position.Y == 13 &&
		position.X == 32)
	{
		MessageBoxA(0, "Хотите добавить новый рецепт?", "рецепты!", 0);

	}*/
}

// картинка
struct IMAGE
{
	RGBTRIPLE** image;
	int width;
	int height;
};

IMAGE load_image(const char* filename)
{
	FILE* f;
	fopen_s(&f, filename, "r");

	if (!f)
	{
		cout << "wrong open for reading file\n";
		exit(0);
	}

	BITMAPFILEHEADER header = {};
	BITMAPINFOHEADER info = {};
	fread(&header, sizeof(header), 1, f);
	fread(&info, sizeof(info), 1, f);

	IMAGE img{};
	img.width = info.biWidth;
	img.height = info.biHeight;
	img.image = new RGBTRIPLE * [img.height];
	fseek(f, header.bfOffBits, SEEK_SET);
	unsigned char* massiv = new unsigned char[img.width * img.height * sizeof(RGBTRIPLE)];
	fread(massiv, 1, img.width * img.height * sizeof(RGBTRIPLE), f);

	for (int i = 0; i < img.height; i++)
	{
		img.image[img.height - 1 - i] = new RGBTRIPLE[img.width];
		memcpy(img.image[img.height - 1 - i],
			massiv + i * img.width * sizeof(RGBTRIPLE),
			img.width * sizeof(RGBTRIPLE));
	}
	fclose(f);
	delete[]massiv;

	return img;
}

void show_image(IMAGE img, int x, int y)
{
	HDC hdc = GetDC(GetConsoleWindow());
	for (int h = 0; h < img.height; h++)
	{
		for (int w = 0; w < img.width; w++)
		{
			auto& color = img.image[h][w];
			SetPixel(hdc, w + x, y + h, RGB(color.rgbtRed, color.rgbtGreen, color.rgbtBlue));
		}
	}
}

void LoadReceipt(int line) // загрузка рецепта
{
	int real_line = line - 3;
	if (real_line < 0 || real_line > 9) return;

	string const file_name[] = { "C:/1/1.txt", "C:/1/2.txt", "C:/1/3.txt", "C:/1/4.txt",
		"C:/1/5.txt", "C:/1/6.txt", "C:/1/7.txt", "C:/1/8.txt", "C:/1/9.txt", "C:/1/10.txt" };

	FILE* file;
	fopen_s(&file, file_name[real_line].c_str(), "r");//открываем файл на чтение "r"
	if (!file)
		exit(0); //при отсутствии файла выходим из приложения
	fseek(file, 0, SEEK_END);
	int file_length = ftell(file); // узнаем текущую позицию курсора (сколько символов)    	
	char* receipt = new char[file_length + 1]; // выделяяем строку под это количество символов
	rewind(file); // перевод курсора в начало файла
	int symbols = fread(receipt, sizeof(char), file_length, file); // считываем весь файл одним куском
	receipt[symbols] = '\0';

	COORD place = { 0, 15 }; // выставляем курсор под списком рецептов
	SetConsoleCursorPosition(GetStdHandle(-11), place);
	cout << receipt << "\n\n";
	delete[] receipt;
}

int main()
{
	system("title Cookbook");
	setlocale(0, "UKR");
	MoveWindow(GetConsoleWindow(), 20, 60, 1500, 1000, true);
	//LOGFONT font; // настройки логического шрифта
	// 20 - отступ слева от левой границы рабочего стола до левой границы окна консоли (в пикселях!)
	// 60 - отступ сверху от верхней границы РС до верхней границы окна консоли
	// 1500 - ширина окна консоли в пикселях
	// 1000 - высота окна консоли		

	COORD c; // переменная, отвечающая за координаты в консоли
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hin, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	const int events_count = 256;
	INPUT_RECORD all_events[events_count]; // массив событий, произошедших в консоли
	DWORD read_event; // переменная, в которую запишется количество произошедших событий

	const int width = 70; // ширина книги
	const int height = 15; // высота книги

	int book[height][width]{};

	Filling(book, 70, 15);

	Book(book, 70, 15);

	Name();

	IMAGE image = load_image("C:\\1\\pic6.bmp");
	show_image(image, 675, 35); // картинка

	Cursor();

	Coord();

	// курсор
	while (true)
	{
		ReadConsoleInput(hin, all_events, events_count, &read_event); // получить все события, произошедшие в консоли
		for (int i = 0; i < read_event; i++)
		{ // пройтись по всем событиям
			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X; // запомнить координаты мышки
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;

			if (c.X > 0 && c.X < 100 &&
				all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				SetConsoleCursorPosition(h, c); // установка координат в то место, где курсор	
				//cout << "CLICK!\n";
				LoadReceipt(c.Y);
			}
		}
	}

}