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
Анализатор - консольное приложение. Для запуска необходимо выполнить команду:
> analyser -I \<INPUT_PATH\> -O \<OUTPUT_PATH\>

- INPUT_PATH директория с анализируемыми логами. 
- OUTPUT_PATH директория с отсортированными логами.

> analyser -I c:\mylogs -O c:\errorlogs

## Развитие проекта

### Версия 1.0

- Minimal Viable Product - разбор логов и запись ошибочных в отдельный каталог
- Абстракция отображения, возможность быстрого "переезда" на "оконный" интерфейс в будущем.
- Возможность быстрой адаптации к другому формату логов за счет переопеределния метода validateLine класса Model

