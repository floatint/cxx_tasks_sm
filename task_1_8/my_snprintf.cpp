#include "my_snprintf.h"

/*

	���������� ������������ ����� �� ���� ��������.
	��� ���������� ������� ������ �� ������� ������������� ������� 
	������ �������������� � �������� �� "���������" �������� ��������������, ���
	������� ������� �������������� ��� �� ������������ - ���������.

	�����������, ��� ��� ������ ���������, � ��������� ������� ���� �������� 
	���� �������� �����������, �� ��� ���������, �������� ������:

	"%0*d" �� ����� ��������, �.�. � ����������� ���������� ��������� �����������, � ��
	��������������� ������� �������� �� �����. � ���� �� ���������� ����� ���-�� ������� ��������,
	��� �� ��������� ��� � ��������� ������. �� �������, � �����. ����� ��� ����� �������.

*/

int my_snprintf(char* buffer, int size, const char* format, int argc, ...) {
	//���� ������-�������� == null
	if (buffer == nullptr) {
		return BUFFER_IS_NULL;
	}
	else { //���� ���
		//���� ������ �������������� �����
		if (format == nullptr) {
			//������ ������ 0, ��� ������ ������
			return FORMAT_IS_NULL;
		}
		else {
			//������ ����������
			va_list args;
			va_start(args, argc);
			//������� ������ � buffer
			int curr_buff_offset = 0;
			//������ ��������������
			char fmt[PLACEHOLDER_MAX_SIZE];
			//������� ������ � ������ ��������������
			int fmt_pos = 0;
			
			//���� �� ���������� ������ ��������������
			while(*format != '\0') {
				//���� ��������� ������� �������������� - %
				if (*format == '%') {
					fmt_pos = 0;
					//������ �����������
					fmt[fmt_pos++] = *format++;
					int res = placeholder_handler(&fmt[1], PLACEHOLDER_MAX_SIZE, format);
					//���� ����������� ����� �������� ������
					if (res < 0)
						return res;
					else { //� ������������ ��� ������
						format += res;
						fmt_pos += res;
						//��������� ��� ������. ����������� ��������� ������ �����
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
							//�������� ��������� � �������
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
			//��������� ��� ����������
			buffer[curr_buff_offset] = '\0';
			//��������� ������ ����������
			va_end(args);
			return curr_buff_offset;
		}
	}
	return 0;
}

/*

	���������� �����������.
	����� � ������ ����������� placeholder.
	���������� ����� ����������� � ������ �����, ����� - ��� ������

*/

int placeholder_handler(char* buff, int size, const char* format) {
	//�������� ��������� �����
	char *tmp = buff;
	//������� � �������
	int curPos = 0;
	//���� ����� % ���-�� ����
	if (*format != '\0') {
		//���� �� �����
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
		//���� �� ������������ ������
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
		//���� �� ������������ ��������
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
		//���� �� ������������ �������
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
	else { //����� ������ �������
		return EMPTY_PLACEHOLDER;
	}
	//���� �� �����, �� ��� ������, ������ ������� �������� ��������
	return (buff + curPos) - tmp;
}