#include "my_snprintf.h"

/*

	Реализация представляет собой по сути фронтенд.
	Она валидирует входную строку на предмет неправильного формата 
	строки форматирования и передает ее "настоящим" функциям форматирования, ибо
	реально сделать форматирование как по документации - нереально.

	Подчеркиваю, что это только валидатор, в некоторых случаях если передать 
	даже валидную подстановку, то это сломается, например случаи:

	"%0*d" не будут работать, т.к. в стандартной библиотеке потоковая конвертация, и он
	непосредственно заберет аргумент со стека. В моей же реализации нужно где-то хранить аргумент,
	как то отправить его в системные вызову. Не вариант, в общем. Лучше про такое молчать.

*/

int my_snprintf(char* buffer, int size, const char* format, int argc, ...) {
	//если буффер-приемник == null
	if (buffer == nullptr) {
		return BUFFER_IS_NULL;
	}
	else { //если нет
		//если строка форматирования пуста
		if (format == nullptr) {
			//просто вернем 0, ибо писать нечего
			return FORMAT_IS_NULL;
		}
		else {
			//список аргументов
			va_list args;
			va_start(args, argc);
			//текущий индекс в buffer
			int curr_buff_offset = 0;
			//строка форматирования
			char fmt[PLACEHOLDER_MAX_SIZE];
			//текущий индекс в строке форматирования
			int fmt_pos = 0;
			
			//идем по переданной строке форматирования
			while(*format != '\0') {
				//если встречаем признак форматирования - %
				if (*format == '%') {
					fmt_pos = 0;
					//парсим подстановку
					fmt[fmt_pos++] = *format++;
					int res = placeholder_handler(&fmt[1], PLACEHOLDER_MAX_SIZE, format);
					//если подстановка имеет неверный формат
					if (res < 0)
						return res;
					else { //с подстановкой все хорошо
						format += res;
						fmt_pos += res;
						//проверяем тип данных. Ограничимся небольшим числом типов
						switch (fmt[fmt_pos - 1])
						{
						case 'c':
							res = sprintf_s(buffer + curr_buff_offset, size - (curr_buff_offset - 2), fmt, va_arg(args, unsigned char));
							break;
						case 's':
							res = sprintf_s(buffer + curr_buff_offset, size - curr_buff_offset, fmt, va_arg(args, const char*));
							break;
						case 'd':
							res = sprintf_s(buffer + curr_buff_offset, size - curr_buff_offset, fmt, va_arg(args, int));
							break;
						default:
							res = INVALID_PLACEHOLDER_SIZE_SPEC;
						}
						if (res < 0)
							return res;
						else {
							//сдвигаем указатель в буффере
							curr_buff_offset += res;
						}
					}
				}
				else {
					//TODO: check size
					if (curr_buff_offset + 1 > size)
						return BUFFER_TOO_SMALL;
					buffer[curr_buff_offset++] = *format++;
				}
				//return 0;
			}
			//нормально все подставили
			buffer[curr_buff_offset] = '\0';
			//закрываем список аргументов
			va_end(args);
			return curr_buff_offset;
		}
	}
	return 0;
}

/*

	Обработчик подстановок.
	Пишет в буффер разобранный placeholder.
	Возвращает длину подстановки в случае удачи, иначе - код ошибки

*/

int placeholder_handler(char* buff, int size, const char* format) {
	//сохраним стартовый адрес
	char *tmp = buff;
	//позиция в буффере
	int curPos = 0;
	//если после % что-то есть
	if (*format != '\0') {
		//есть ли флаги
		if (*format == '-' ||
			*format == '+' ||
			*format == ' ' ||
			*format == '#' ||
			*format == '0'
			)
		{
			if (curPos + 1 >= size)
				return PLACEHOLDER_BUFFER_TOO_SMALL;
			buff[curPos++] = *format++;
		}
		//есть ли спецификатор ширины
		if (isdigit(*format) || *format == '*') {
			if (*format == '*') {
				if (curPos + 1 >= size)
					return PLACEHOLDER_BUFFER_TOO_SMALL;
				buff[curPos++] = *format++;
			} else {
				while (isdigit(*format)) {
					if (curPos + 1 >= size)
						return PLACEHOLDER_BUFFER_TOO_SMALL;
					buff[curPos++] = *format++;
				}
			}
		}
		//есть ли спецификатор точности
		if (*format == '.') {
			if (isdigit(*(format + 1)) || *(format + 1) == '*') {
				format++;
				if (*format == '*') {
					if (curPos + 1 >= size)
						return PLACEHOLDER_BUFFER_TOO_SMALL;
					buff[curPos++] = *format++;
				} else {
					while (isdigit(*format)) {
						if (curPos + 1 >= size)
							return PLACEHOLDER_BUFFER_TOO_SMALL;
						buff[curPos++] = *format++;
					}
				}
			}
			else {
				return INVALID_PLACEHOLDER_CURRENCY_SPEC;
			}
		}
		//есть ли спецификатор размера
		if (*format == 'c' ||
			*format == 's' ||
			*format == 'd' ||
			*format == 'i' ||
			*format == 'f' ||
			*format == 'u')
		{
			if (curPos + 2 >= size)
				return PLACEHOLDER_BUFFER_TOO_SMALL;
			buff[curPos++] = *format++;
			buff[curPos] = '\0';
		}
		else {
			return INVALID_PLACEHOLDER_SIZE_SPEC;
		}
	}
	else { //обрыв строки формата
		return EMPTY_PLACEHOLDER;
	}
	//если мы здесь, то все хорошо, вернем сколько символов записали
	return (buff + curPos) - tmp;
}