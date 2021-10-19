#include "mlx.h"
#include <stdlib.h> 

typedef struct // та самая структура, в которой хранятся все переменные
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int zoom;
	int width;
	int height;
	void *mlx_ptr;
	void *win_ptr;
}	fdf;

int	close(int keycode, fdf *data)
{
	exit(0);
}

void horizontal_line (int x, int x1, int y, fdf *data)
{
	while(x < x1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff);	
		x++;
	}
}

void vertical_line (int x, int y, int y1, fdf *data)
{
	while(y < y1)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00ffffff);
		y++;
	}
}

void square(fdf *data, int color) // для рисования квадрата передаем структуру
{
	int x;
	int y;

	x = 0;
	while (x < data->zoom) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < data->zoom) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x1, y + data->y1, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}

void square2(fdf *data, int color) // для рисования квадрата передаем структуру
{
	int x;
	int y;

	x = 0;
	while (x < data->zoom) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < data->zoom) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x2, y + data->y2, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}

void square3(fdf *data, int color) // для рисования квадрата передаем структуру
{
	int x;
	int y;

	x = 0;
	while (x < data->zoom) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < data->zoom) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x3, y + data->y3, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}


void rectangle(fdf *data, int color) // ЛЕВАЯ РАКЕТКА
{
	int x;
	int y;

	x = 0;
	while (x < 4) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < 32) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x1, y + data->y1, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}

void rectangle2(fdf *data, int color) // ПРАВАЯ РАКЕТКА
{
	int x;
	int y;

	x = 0;
	while (x < 4) // пока Х меньше коэфицента зума
	{
		y = 0; // обнуляем y (возвращаемся в начало строки)
		while(y < 32) // пока Y меньше коэфицента зума
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + data->x2, y + data->y2, color); // рисуем точку
			y++; // смещаемся по строке
		}
		x++; // переходим на следующую строку
	}
}

int deal_key(int key, fdf *data)  // НАЖАТИЕ КНОПКИ
{
	printf("keycode : %d\n", key);
	if (key == 53) // ESC
	{
		exit(0); // выйти из программы
	}
//	if ((key == 123 || key == 0) && (data->x > data->zoom)) // <- & A и контроль за тем, чтоб квадрат не вышел за рамку
//	{
//		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
//		data->x -= data->zoom; // смещаемся по х влево
//	}
//	if ((key == 124 || key == 2) && (data->x < (data->width - 2 * data->zoom))) // -> & D и находимся не ближе чем край рамки минус один квадрат (два квадрата от края окна)
//	{	
//		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
//		data->x += data->zoom; // смещаемся по х вправо
//	}
	if ((key == 1) && (data->y1 < (data->height - 2 * data->zoom - 28)))// DOWN & S  || key == 1
	{
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->y1 += data->zoom; // смещаемся по у вниз
	}
	if ((key == 13) && (data->y1 > data->zoom))//UP & W  || key == 13
	{
		data->y1 += 28; // 28 - это 32(высота ракетки) минус zoom
		square(data, 0x00000000); // стираем квадрат равный zoom внизу прямоугольника
		data->y1 -= 28 + data->zoom; // смещаемся по у вверх
	}
	if ((key == 125) && (data->y2 < (data->height - 2 * data->zoom - 28)))  // DOWN
	{
		square2(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->y2 += data->zoom; // смещаемся по у вниз
	}
	if ((key == 126) && (data->y2 > data->zoom)) // UP
	{
		data->y2 += 28; // 28 - это 32(высота ракетки) минус zoom
		square2(data, 0x00000000); // стираем квадрат равный zoom внизу прямоугольника
		data->y2 -= 28 + data->zoom; // смещаемся по у вверх
	}
}

void init(fdf *data) // запись начальных значений
{
	data->width = 320;
	data->height = 200;
	data->mlx_ptr = mlx_init(); // инизиацизируем форму (значение в структуре data - mlx_ptr) 
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height, "TEST"); // создаем окно 
	data->zoom = 4; // коэффицент размера (будет не пиксель а квадрат 16х16)
	data->x1 = 16; // начальная точка х
	data->y1 = 16; // начальная точка у
	data->x2 = data->width - 16 - data->zoom; // начальная точка х
	data->y2 = 16; // начальная точка у
	data->x3 = 158;
	data->y3 = 98;
	square3(data, 0x00FFFFFF); // рисование квадрата
	rectangle(data, 0x00FFFFFF);
	rectangle2(data, 0x00FFFFFF);
}

int render_next_frame(fdf *data) // РЕНДЕРИНГ СЛЕДУЮЩЕГО КАДРА
{
	//mlx_clear_window (data->mlx_ptr, data->win_ptr); // ЧИСТИМ КАДР
	//square(data, 0x00FFFFFF); // РИСУЕМ НОВЫЙ КВАДРАТ
	rectangle(data, 0x00FFFFFF);
	rectangle2(data, 0x00FFFFFF);
}

void ramka(fdf *data) // рисуем рамку
{
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->zoom - 1), data);
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->height - data->zoom), data);
	vertical_line((data->zoom - 1), (data->zoom - 1), (data->height - data->zoom), data);
	vertical_line((data->width - data->zoom), (data->zoom - 1), (data->height - data->zoom + 1), data);
}

int	main(void)
{
	fdf	*data;

	data = (fdf*)malloc(sizeof(fdf));
	init(data);
	ramka(data); // рисуем рамку
	
	mlx_hook(data->win_ptr, 2, 1<<3, deal_key, data); 
	mlx_hook(data->win_ptr, 17, 0, close, data);

	mlx_loop_hook(data->mlx_ptr, render_next_frame, data); 
	mlx_loop(data->mlx_ptr);
	free(data);
}
