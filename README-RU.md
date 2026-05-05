# KoTR Modern Patch
Исходники [Modern Patch](https://www.moddb.com/games/hard-truck-2/downloads/king-of-the-road-modern-patch) для игры "Дальнобойщики 2".</br>
Версия v1.00/v1.01 (включая модификации) доступна [здесь](https://github.com/aleko2144/KoTR_Modern_Patch/tree/1.00).

## Что это?
Патч в виде asi-плагина, как исправляющий недоработки оригинальной игры, так и вносящий некоторые улучшения.</br>
Полный список изменений доступен [здесь](CHANGELOG-RU.md).

Важно! Данный патч не решает проблем с запуском игры. Для корректной работы игры на современных компьютерах рекомендуется использовать [D2GI](https://github.com/REDPOWAR/D2GI/).

## Совместимость с версиями игры
|Название|Описание|Поддерживаемые версии|
|-|-|-|
|QueueSortingFix|Исправляет секундную задержку при въезде в Алмазный и сокращает время загрузки игры|6.6 - 8.2/1.x|
|ExtCameraFix|Исправляет движение внешней камеры за машиной игрока| |
|CollisionsFix|Корректирует параметры обработки столкновений между динамическими объектами (исправляет "залипания" транспорта при столкновениях между собой)| |
|InfoPanelFix|Исправляет отображение двузначных передач в верхней панели интерфейса| |
|TechSystemFix*|Исправляет ошибки системы улушчений, такие как пропажа топлива при смене автомобиля с установленным дополнительным баком, проблемы с отображением установленных дополнений, и так далее| |
|DustParticlesFix|Корректирует направление летящих частиц пыли от автомобилей|6.9 - 8.2/1.x|
|STrailersPhysFix|Корректирует движение полуприцепов|7.0 - 8.2/1.x|
|AICarFix|Корректирует поведение трафика на двухполосных дорогах|7.4 - 8.2/1.x|
|CabinCamFix|Исправляет ошибку, из-за которой салоны были расположены слишком низко|8.0 - 8.2/1.x|

*_Экспериментальная модификация - влияние на игру до конца не изучено_</br>

## Сборка проекта
* Для компиляции текущей версии проекта требуется VS2019, для версий 1.00/1.01 - VS2012.
* Для подгрузки ASI-файла в игру рекомендуется использовать [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader) за авторством [ThirteenAG](https://github.com/ThirteenAG)
* Модифицированные ресурсы игры для текущей версии патча опубликованы здесь __(только для версий игры 8.x/1.x)__: https://disk.yandex.ru/d/8vJAj0gO_5vukA

## Использованные исходники
* Файл "CPatch.h" и некоторые игровые структуры взяты из [D2DInputWrapper](https://github.com/Voron295/rignroll-dinput-wrapper) за авторством [Voron295](https://github.com/Voron295)
* [ModUtils](https://github.com/CookiePLMonster/ModUtils) за авторством [CookiePLMonster](https://github.com/CookiePLMonster)
* Исходники D2GI доступны [здесь](https://github.com/REDPOWAR/D2GI)

## Благодарности
* [Voron295](https://github.com/Voron295)
* [CookiePLMonster](https://github.com/CookiePLMonster)
* [Duude92](https://github.com/Duude92)
* [AlexKimov](https://github.com/AlexKimov)
* [LabVaKars](https://github.com/LabVaKars)
