#include "fdf.h"

int render_next_frame(fdf *data) // РЕНДЕРИНГ СЛЕДУЮЩЕГО КАДРА
{
	//mlx_clear_window (data->mlx_ptr, data->win_ptr); // ЧИСТИМ КАДР
//	square(data, 0x00ff0000); // РИСУЕМ НОВЫЙ КВАДРАТ
	rectangle(data, 5, 20 ,0x00ffffff); 
	return(0);
}

int	close_app(int keycode, fdf *data) //НАЖАТИЕ НА х
{
	exit(0); 
}

int resize(int keycode, fdf *data) // СВОРАЧИВАНИЕ & РАЗВОРОТ ОКНА
{
//	printf("RESIZE\n");
	return(0);
}

int deal_key(int key, fdf *data)  // НАЖАТИЕ КНОПКИ
{
//	printf("keycode : %d\n", key);
	if (key == 53) // ESC
		exit(0); // выйти из программы
	if ((key == 123 || key == 0) && (data->x > data->zoom)) // <- & A и контроль за тем, чтоб квадрат не вышел за рамку
	{
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->x -= data->zoom; // смещаемся по х влево
	}
	if ((key == 124 || key == 2) && (data->x < (data->width - 2 * data->zoom))) // -> & D и находимся не ближе чем край рамки минус один квадрат (два квадрата от края окна)
	{	
		square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		data->x += data->zoom; // смещаемся по х вправо
	}
	if ((key == 125 || key == 1) && (data->y + 20 < (data->height - 19 * data->zoom + 2)))// DOWN & S
	{
		//square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		rectangle(data, 5, data->zoom ,0x00000000);
		data->y += data->zoom * 3; // смещаемся по у вниз

	}
	if ((key == 126 || key == 13) && (data->y > 3 * data->zoom - 6))//UP & W
	{
		//square(data, 0x00000000); // на месте старого квадрата рисуем черный квадрат
		//rectangle(data, 5, data->y + data->zoom + 20 ,0x00000000);
		data->y -= data->zoom * 3; // смещаемся по у вверх
		rectangle(data, 5, data->y ,0x00000000);
		
		
	}
	return(0);
}

int release_key(int key, fdf *data) //ОТПУСК КНОПКИ
{
	//printf("OTPUSK\n");
	return(0);
}

void init(fdf *data) // запись начальных значений
{
	data->width = 420;
	data->height = 300;
	data->mlx_ptr = mlx_init(); // инизиацизируем форму (значение в структуре data - mlx_ptr) 
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height, "TEST"); // создаем окно 
	data->zoom = 4; // коэффицент размера (будет не пиксель а квадрат 16х16)
	data->x = 10*2; // начальная точка х
	data->y = 30; // начальная точка у
	data->x_back = data->x;
	data->y_back = data->y;
//	square(data, 0x00FF0000); // рисование квадрата
	rectangle(data, 5, 20 ,0x00ffffff);
}

void ramka(fdf *data) // рисуем рамку
{
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->zoom - 1), data);
	horizontal_line((data->zoom - 1), (data->width - data->zoom), (data->height - data->zoom), data);
	vertical_line((data->zoom - 1), (data->zoom - 1), (data->height - data->zoom), data);
	vertical_line((data->width - data->zoom), (data->zoom - 1), (data->height - data->zoom + 1), data);
}

int main(int argc, char** argv)
{
	fdf *data; // структура, в которой хранятся все данные вместо переменных

	data = (fdf*)malloc(sizeof(fdf)); // Выделяем память
	init(data); // записываем начальные значения
	ramka(data); // рисуем рамку

	mlx_hook(data->win_ptr, 2, 0, deal_key, data); // следим за кнопками ( передаем окно, функцию deal_key и структуру(для изменения значений в ней))
	mlx_hook(data->win_ptr, 3 ,0, release_key, data); // отпустил кнопку
	mlx_hook(data->win_ptr, 17, 0, close_app, data); // НАЖАТИЕ НА "x" (крестик для закрытия)
	mlx_hook(data->win_ptr, 12, 0, resize, data); // развернул окно или свернул

	//mlx_string_put(data->mlx_ptr, data->win_ptr, 75, 110, 0xFFFFFF, "PRESS SPACE");
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data); // СЛЕДУЮЩИЙ КАДР
	mlx_loop(data->mlx_ptr); // держим окно открытым пока программа работает 
	free(data); // освобождаем память
	return(0);
}

//	bresenham(16, 16, 784, 16, data);  //рисование линии
//	mlx_pixel_put(data->mlx_ptr, data->win_ptr, data->x, data->y, 0x00FF0000); // рисование пикселя