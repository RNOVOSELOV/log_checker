# 📝 Log checker
Консольное приложение, с помощью которого можно быстро проанализировать ошибки в лог файлах и сохранить их в отдельных директориях. 
ПО с помощью регулярных выражений и переопределения одного метода легко адаптируется под любой формат лог файлов.

## О проекте

ПО написано с применением архитектурного паттерна Model-View-Presenter. Возможна его быстрая адаптация под оконное приложение.
UML диаграмма классов представлена ниже, либо [открыть в большом размере (SVG)](https://raw.githubusercontent.com/RNOVOSELOV/log_checker/main/images/UML.svg).

<p align="center">
  <img src="https://github.com/RNOVOSELOV/log_checker/blob/main/images/UML.svg"/>
</p>

Результат работы программы - каталоги с лог файлами, отсеянные по заданным параметрам.

## Работа ПО
Для запуска необходимо выполнить команду:

> analyser -I \<INPUT_PATH\> -O \<OUTPUT_PATH\>

  -   INPUT_PATH директория с анализируемыми логами. 
  -   OUTPUT_PATH директория с отсортированными логами.

> analyser -I c:\mylogs -O c:\errorlogs

Пример работы программы:
 
<p align="center">
  <img src="https://github.com/RNOVOSELOV/log_checker/blob/main/images/result.png" height="300"/>
</p>

Возможные команды:
  -   c	Очистить каталог выбранных логов
  -   s Начать сканирование входного каталога
  -   h	Показать справку по командам
  -   q Выйти из программы

## Развитие проекта

### Версия 1.2

- Печать в консоль строк, которые не удовлетворяют формату логов.

### Версия 1.1

- Обработка исключений файловой системы

### Версия 1.0

- Minimal Viable Product - разбор логов и запись ошибочных в отдельный каталог
- Абстракция отображения, возможность быстрого "переезда" на "оконный" интерфейс в будущем.
- Возможность быстрой адаптации к другому формату логов за счет переопеределния метода validateLine класса Model

## Индикация ошибок

### Возможные ошибки:

- Некорректный запуск программы

    > Error! Number of arguments error!
	
- Некорректный формат пути до каталога с логами
	
    > Error! Input directory not exist.

- Некорректный формат пути до каталога для записи результатов
	
    > Error! Output directory not exist.

- Каталог с логами отсутствует на файловой системе
	
    > Error! Input directory not exist on filesystem.

- Каталог для записи результатов отсутствует на файловой системе
	
    > Error! Output directory not exist on filesystem.

### Предупреждения:

- Указана не поддерживающая програмой опция запуска 

    > WARNING! Incorrect option is entered!
  
- Ошибка формата логов

    > Log format error: \[INFO\] 02:.444+00:00
    
    > Log format error: \[WARNING 06:20:12.567+05:00
    
    > Log format error: \[WARNINGQUIOPKJHG\] 06:20:12.567+05:00
    
    > Log format error: \[()$$\] 06:20:12.567+05:00

- Неизвестная комманда

    > Unrecognized command!

- Ошибка очистки каталога

    > Error clear output directory.

- Различные ошибки файловой системы

    > Error set output directory. Filesystem error! Code: {code}; description: {description}

- Другие ошибки

    > Error process input file {filepath}. Failure to allocate storage! Description: {description}

### Информационные сообщения:

- Каталог с отсортированными логами очищен

    > Output directory is removed.

- Сканированиие завершено

    > Scan finished. 15 error messages are copied.
