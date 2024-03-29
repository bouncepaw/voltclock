# Про часы на вольтметрах #
Здравствуйте. Меня зовут Тимур Исмагилов, и я расскажу вам про свой проект —
часы на вольтметрах.
## Вступление ##

### Суть проекта ###
Вот сами часы. *показывает часы* Спереди три вольметра: один для часов, один для
минут, один для секунд. Слева кнопка питания и разьём питания. Наверху две
кнопки и светодиод. Кнопки используются для настройки, светодиод — для обратной
связи.

## Технические детали ##

### Электросхема ###

В сердце проекта — китайский клон Arduino UNO. В него заложена программа,
исполняющая инструкции и управляющая электроникой. *слайд со схемой* Вот схема.

Это — разьём питания. Здесь, выключатель — если на него нажать, часы включатся.
*нажимает на него* Часы включились! Счёт времени продолжался даже когда
не было питания на ардуино. За отсчёт времени отвечает этот модуль часов
реального времени, который подключен по протоколу I²C. В него вставлена 
батарейка, которой хватает на несколько лет отсчёта времени. Время можно
настроить при помощи вот этих двух кнопок, светодиод используется для обратной
связи при настройке. Здесь сами вольтметры на 3 В. Мне нужно было, чтобы они
показывали 5 В. Я нигде в Уфе не нашёл пятивольтовые вольтметры, поэтому просто
прицепил резисторы на 330 Ом. Благодаря ним, вольтметры показывают около 5 В.

### Алгоритм работы ###

#### Настройка часов ####

Есть два режима: основной и режим настройки. В основном режиме часы показывают
текущее время. В режиме настройки это время можно настроить. У меня было только
две кнопки, поэтому их пришлось конкретно нагрузить. В главном режиме можно
выбрать, что именно настраивать (часы, секунды, минуты), в режиме настройки
можно увеличить или уменьшить выбранное.

*слайд с комбинаци клавиш* В главном режиме следующие комбинации кнопок:
    11: перейти в режим настройки
    12: выбрать секунды
    21: выбрать минуты
    22: выбрать часы

В режиме настройки такие: 
    11 или 22: вернуться в главный режим
    12: увеличить на единицу
    21: уменьшить на единицу

Сейчас я продемонстрирую это. *смотрит в телефон* Часы отстают на час. Сначала
 выбираем настройку часов: 22. Потом входим в режим настройки: 11. Затем
увеличиваем время: 12. Теперь выходим: 11. Было бы у меня больше таких кнопок,
всё было бы удобнее.

#### Отображение времени ####

Я реализовал выставление стрелки вольтметра при помощи широтно-импульсной
модуляции. *слайд про ШИМ* В ардуино у ШИМ разрешение 8 битов, то есть всего
доступно 255 значений. Это не очень удобное для меня число, но я более-менее
подобрал неплохие значения для часов, минут и секунд.

В главном режиме секундная стрелка двигается каждую секунду, то есть каждые
1000 мс. Из-за столь резкого движения, стрелка вольтметра постоянно трясётся.
Это можно уменьшить, если двигать стрелку не сразу, а пошагово. Для этого
каждые 13 мс специальная функция двигает стрелки на 1 значение ШИМ. Я выбрал
13 мс, вдохновившись жизненным образом цикад.

Большую часть жизни цикады живут под землёй, но раз в 7, 11, 13 или 17 лет они 
вылезают из-под земли для размножения. Эти числа выбраны неслучайно. Животные,
которые охотятся на цикад демонстрируют цикл 2 — 6 лет между спадоми ростом
популяции. Если бы цикады просыпались бы каждые 8 лет, то они бы всегда
попадали в период наибольшей численности хищников. 

Я выбрал число 13, потому что 17 слишком большое, а 11 слишком маленькое. Из-за
того, что я выбрал 13, *процесс* движения стрелки и *тиканья* секунды совпадают
не так часто, как могли бы.
