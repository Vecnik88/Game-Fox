#ifndef SOURCEDATA_H
#define SOURCEDATA_H

/**********************
 * исходные параметры *
 **********************/

// размеры таблицы
#define ROWS_TABLE              3
#define COLS_TABLE              3

// размеры игрового окна
#define WIDTH                   600
#define HEIGHT                  400

// смещение игрового окна при старте
#define OFFSET_X                100
#define OFFSET_Y                100

// имена таблиц в базе данных
#define NAME_TABLE_SUBJECT      "Subject"
#define NAME_TABLE_INVENTORY    "Inventory"

// имена полей в таблицах базы данных
#define TABLE_TYPE              "Type"
#define TABLE_PATH              "Path"
#define TABLE_AMOUNT            "Amount"

#define TYPE_SUBJECT            "fox"
#define HOST_NAME               "SQLHOST"
#define PATH_IMAGE              "/home/anton/qt_project/red/image/fox.png"
#define SOUND_FOX               "/home/anton/qt_project/red/sound/fox.wav"
#define DATABASE_NAME           "/home/anton/qt_project/red/database/gameFox"

// для сетевого соединения
#define IP_ADDR_LOCAL_HOST      "127.0.0.1"
#define PORT                    1234

#endif // SOURCEDATA_H
