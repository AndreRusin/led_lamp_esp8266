#pragma once

#include <ESP8266WebServer.h>


// ============= НАСТРОЙКИ =============
// --- ESP -----------------------------
#define ESP_MODE              (1U)                          // 0U - WiFi точка доступа, 1U - клиент WiFi (подключение к роутеру)
uint8_t espMode = ESP_MODE;                                 // ESP_MODE может быть сохранён в энергонезависимую память и изменён в процессе работы лампы без необходимости её перепрошивки
#define ESP_USE_IR                                
// #define ESP_USE_BUTTON                                      // если строка не закомментирована, должна быть подключена кнопка (иначе ESP может регистрировать "фантомные" нажатия и некорректно устанавливать яркость)
#if defined (ESP_USE_BUTTON)
#define BUTTON_STEP_TIMEOUT   (100U)                        // каждые BUTTON_STEP_TIMEOUT мс будет генерироваться событие удержания кнопки (для регулировки яркости)
#define BUTTON_CLICK_TIMEOUT  (500U)                        // максимальное время между нажатиями кнопки в мс, до достижения которого считается серия последовательных нажатий
#endif
#define ESP_RESET_ON_START    (false)                       // true - если при старте нажата кнопка (или кнопки нет!), сохранённые настройки будут сброшены; false - не будут
#define ESP_HTTP_PORT         (80U)                         // номер порта, который будет использоваться во время первой утановки имени WiFi сети (и пароля), к которой потом будет подключаться лампа в режиме WiFi клиента (лучше не менять)
#define ESP_UDP_PORT          (8888U)                       // номер порта, который будет "слушать" UDP сервер во время работы лампы как в режиме WiFi точки доступа, так и в режиме WiFi клиента (лучше не менять)
#define ESP_CONN_TIMEOUT      (7U)                          // время в секундах (ДОЛЖНО БЫТЬ МЕНЬШЕ 8, иначе сработает WDT), которое ESP будет пытаться подключиться к WiFi сети, после его истечения автоматически развернёт WiFi точку доступа
#define ESP_CONF_TIMEOUT      (300U)                        // время в секундах, которое ESP будет ждать ввода SSID и пароля WiFi сети роутера в конфигурационном режиме, после его истечения ESP перезагружается
//#define GENERAL_DEBUG                                       // если строка не закомментирована, будут выводиться отладочные сообщения
#define WIFIMAN_DEBUG         (true)                        // вывод отладочных сообщений при подключении к WiFi сети: true - выводятся, false - не выводятся; настройка не зависит от GENERAL_DEBUG
#define OTA                                                 // если строка не закомментирована, модуль будет ждать два последдовательных запроса пользователя на прошивку по воздуху (см. документацию в "шапке")
#ifdef OTA
#define ESP_OTA_PORT          (8266U)                       // номер порта, который будет "прослушиваться" в ожидании команды прошивки по воздуху
#endif
#define LED_PIN               (2U)                          // пин ленты                (D4)
// #define BTN_PIN               (4U)                          // пин кнопки               (D2)
#define BTN_IR               (4U)                           // пин ir приемника         (D2)

// --- ESP (WiFi клиент) ---------------
const uint8_t STA_STATIC_IP[] = {};                         // статический IP адрес: {} - IP адрес определяется роутером; {192, 168, 1, 66} - IP адрес задан явно (если DHCP на роутере не решит иначе); должен быть из того же диапазона адресов, что разадёт роутер
                                                            // SSID WiFi сети и пароль будут запрошены WiFi Manager'ом в режиме WiFi точки доступа, нет способа захардкодить их в прошивке

// --- AP (WiFi точка доступа) ---
#define AP_NAME               ("LedLamp")                   // имя WiFi точки доступа, используется как при запросе SSID и пароля WiFi сети роутера, так и при работе в режиме ESP_MODE = 0
#define AP_PASS               ("31415926")                  // пароль WiFi точки доступа
const uint8_t AP_STATIC_IP[] = {192, 168, 4, 1};            // статический IP точки доступа (лучше не менять)

// --- РАССВЕТ -------------------------
#define DAWN_BRIGHT           (200U)                        // максимальная яркость рассвета (0-255)
#define DAWN_TIMEOUT          (1U)                          // сколько рассвет светит после времени будильника, минут

// --- МАТРИЦА -------------------------
#define BRIGHTNESS            (40U)                         // стандартная маскимальная яркость (0-255)
#define CURRENT_LIMIT         (2000U)                       // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define WIDTH                 (8U)                         // ширина матрицы
#define HEIGHT                (18U)                         // высота матрицы

#define COLOR_ORDER           (RGB)                         // порядок цветов на ленте. Если цвет отображается некорректно - меняйте. Начать можно с RGB

#define MATRIX_TYPE           (1U)                          // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE      (3U)                          // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION       (1U)                          // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
                                                            // при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
                                                            // шпаргалка по настройке матрицы здесь! https://alexgyver.ru/matrix_guide/

// == перечень и номера эффектов ниже в списке согласованы со стандартным android приложением! =========================
// == если меняете, ваше приложение должно поддерживать передачу списка режимов (передачу реестра доступных эффектов) ==
                                                            
#define EFF_SPARKLES          (0U)                          // Конфетти
#define EFF_FIRE              (1U)                          // Огонь
#define EFF_WHITTE_FIRE       (2U)                          // Белый огонь
#define EFF_RAINBOW_VER       (3U)                          // Радуга вертикальная
#define EFF_RAINBOW_HOR       (4U)                          // Радуга горизонтальная
#define EFF_RAINBOW_DIAG      (5U)                          // Радуга диагональная
#define EFF_COLORS            (6U)                          // Смена цвета
#define EFF_MADNESS           (7U)                          // Безумие 3D
#define EFF_CLOUDS            (8U)                          // Облака 3D
#define EFF_LAVA              (9U)                          // Лава 3D
#define EFF_PLASMA            (10U)                         // Плазма 3D
#define EFF_RAINBOW           (11U)                         // Радуга 3D
#define EFF_RAINBOW_STRIPE    (12U)                         // Павлин 3D
#define EFF_ZEBRA             (13U)                         // Зебра 3D
#define EFF_FOREST            (14U)                         // Лес 3D
#define EFF_OCEAN             (15U)                         // Океан 3D
#define EFF_COLOR             (16U)                         // Цвет
#define EFF_SNOW              (17U)                         // Снегопад
#define EFF_SNOWSTORM         (18U)                         // Метель
#define EFF_STARFALL          (19U)                         // Звездопад
#define EFF_MATRIX            (20U)                         // Матрица
#define EFF_LIGHTERS          (21U)                         // Светлячки
#define EFF_LIGHTER_TRACES    (22U)                         // Светлячки со шлейфом
#define EFF_PAINTBALL         (23U)                         // Пейнтбол
#define EFF_CUBE              (24U)                         // Блуждающий кубик
#define EFF_WHITE_COLOR       (25U)                         // Белый свет
#define MODE_AMOUNT           (26U)                         // количество режимов


// ================ РЕЕСТР ДОСТУПНЫХ ЭФФЕКТОВ ===================
// ==== ДЛЯ ПЕРЕДАЧИ В ПРИЛОЖЕНИЯ С ПОДДЕРЖКОЙ ЭТОЙ ФУНКЦИИ =====
// формат записи:
//"Название эффекта,min_скорость,max_скорость,min_масштаб,max_масштаб,выбор_ли_цвета_это(0-нет,1-да, 2-для кометы);"
// Порядок эффектов можно менять на своё усмотрение, не забывая при этом менять им номера в списке ВЫШЕ
// Можно добавлять новые или удалять ненужные эффекты сохраняя количество эффектов в каждой строке примерно одинаковым,
// т.е. общее количество эффектов делим примерно пропорционально на три строки. Когда перестанет влезать - приложение начнёт глючить.
// Не забывайте подключать добавленные эффекты в файле effectTicker.ino
// Список эффектов из лампы (этот реестр) передаётся частями из 3-х строк. !!!ЭФФЕКТ БЕГУЩАЯ СТРОКА ДОЛЖЕН БЫТЬ ПОСЛЕДНИМ ВСЕГДА!!!
// ОЧЕНЬ ВАЖНО!!! Следите за знаками при редавктировании эффектов. Не допускайте пробелов, кроме как в названии эффекта.
// В кавычках Имя эффекта и его параметры должны быть разделены запятой, а на конце точка с запятой.
const String efList_1 = String("LIST1;") +              // ПЕРВАЯ СТРОКА ============================
String("Конфетти,1,255,1,100,0;") +                     // EFF_SPARKLES          (0U)
String("Огонь,50,255,1,100,1;") +                       // EFF_FIRE              (1U)
String("Водопад,50,255,1,100,1;") +                     // EFF_WHITTE_FIRE       (2U)
String("Радуга горизонтальная,50,255,1,50,0;") +        // EFF_RAINBOW_HOR       (3U)
String("Радуга вертикальная,50,255,1,50,0;") +          // EFF_RAINBOW_VER       (4U)
String("Радуга диагональная,50,255,1,100,0;") +         // EFF_RAINBOW_DIAG      (5U)
String("Пульс + Смена цвета,50,255,1,100,0;") +         // EFF_COLORS            (6U)
String("Безумие,1,150,100,1,0;") +                      // EFF_MADNESS           (7U)
String("Облака,1,15,50,1,0;") +                         // EFF_CLOUDS            (8U)
String("Лава,5,60,100,1,0;") +                          // EFF_LAVA              (9U)
String(+ "\n");
const String efList_2 = String("LIST2;") +              // ВТОРАЯ СТРОКА ============================
String("Плазма,1,30,100,1,0;") +                        // EFF_PLASMA            (10U)
String("Радуга 3D,1,70,100,1,0;") +                     // EFF_RAINBOW           (11U)
String("Павлин,1,15,30,1,0;") +                         // EFF_RAINBOW_STRIPE    (12U)
String("Зебра,1,30,40,7,0;") +                          // EFF_ZEBRA             (13U)
String("Лес,2,30,100,70,0;") +                          // EFF_FOREST            (14U)
String("Океан,2,15,30,4,0;") +                          // EFF_OCEAN             (15U)
String("Бассейн + Цвет,100,255,1,100,1;") +             // EFF_COLOR             (16U)
String("Снегопад,50,255,1,100,0;") +                    // EFF_SNOW              (17U)
String("Метель,50,255,1,100,0;") +                      // EFF_SNOWSTORM         (18U)
String("Звездопад,50,255,1,100,0;") +                   // EFF_STARFALL          (19U)
String(+ "\n");
const String efList_3 = String("LIST3;") +              // ТРЕТЬЯ СТРОКА =============================
String("Матрица,100,240,1,100,0;") +                    // EFF_MATRIX            (20U)
String("Светлячки,50,240,1,100,0;") +                   // EFF_LIGHTERS          (21U)
String("Светлячки со шлейфом,60,255,1,100,0;") +        // EFF_LIGHTER_TRACES    (22U)
String("Пейнтбол,215,255,1,100,0;") +                   // EFF_PAINTBALL         (23U)
String("Блуждающий кубик,70,235,1,100,0;") +            // EFF_CUBE              (24U)
String("Белый свет,1,255,1,100,0;") +                   // EFF_WHITE_COLOR       (25U)
String(+ "\n");
// ============= КОНЕЦ РЕЕСТРА =====


// === ОСТАЛЬНОЕ ДЛЯ РАЗРАБОТЧИКОВ =====

//#define MAX_UDP_BUFFER_SIZE (UDP_TX_PACKET_MAX_SIZE + 1)
#define MAX_UDP_BUFFER_SIZE   (129U)                        // максимальный размер буффера UDP сервера

#define GENERAL_DEBUG_TELNET  (false)                       // true - отладочные сообщения будут выводиться в telnet вместо Serial порта (для удалённой отладки без подключения usb кабелем)
#define TELNET_PORT           (23U)                         // номер telnet порта

#if defined(GENERAL_DEBUG) && GENERAL_DEBUG_TELNET
WiFiServer telnetServer(TELNET_PORT);                       // telnet сервер
WiFiClient telnet;                                          // обработчик событий telnet клиента
bool telnetGreetingShown = false;                           // признак "показано приветствие в telnet"
#define LOG                   telnet
#else
#define LOG                   Serial
#endif

// --- БИБЛИОТЕКИ ----------------------
#define FASTLED_INTERRUPT_RETRY_COUNT   (0)                 // default: 2; // Use this to determine how many times FastLED will attempt to re-transmit a frame if interrupted for too long by interrupts
//#define FASTLED_ALLOW_INTERRUPTS      (1)                 // default: 1; // Use this to force FastLED to allow interrupts in the clockless chipsets (or to force it to disallow), overriding the default on platforms that support this. Set the value to 1 to allow interrupts or 0 to disallow them.
#define FASTLED_ESP8266_RAW_PIN_ORDER                       // FASTLED_ESP8266_RAW_PIN_ORDER, FASTLED_ESP8266_D1_PIN_ORDER or FASTLED_ESP8266_NODEMCU_PIN_ORDER

#define NUM_LEDS              (uint16_t)(WIDTH * HEIGHT)
#define SEGMENTS              (1U)                          // диодов в одном "пикселе" (для создания матрицы из кусков ленты)
