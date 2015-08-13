#ifndef UTILITY_H
#define UTILITY_H

#include <Qt>
#include <stdint.h>
#include <QByteArray>
#include <QDateTime>



class Utility
{
public:

    static bool decimalMode;

    static int ParseStringToNum(QByteArray input)
    {
        int temp = 0;

        input = input.toUpper();
        if (input.startsWith("0X") || input.startsWith("X")) //hex number
        {
            temp = input.right(input.size() - 2).toInt(NULL, 16);
        }
        else if (input.startsWith("B")) //binary number
        {
            input = input.right(input.size() - 1); //remove the B
            for (int i = 0; i < input.length(); i++)
            {
                if (input[i] == '1') temp += 1 << (input.length() - i - 1);
            }
        }
        else //decimal number
        {
            temp = input.toInt();
        }

        return temp;
    }

    static int ParseStringToNum(QString input)
    {
        return ParseStringToNum(input.toUtf8());
    }

    static long GetTimeMS()
    {
        QDateTime stamp = QDateTime::currentDateTime();
        return (long)(((stamp.time().hour() * 3600) + (stamp.time().minute() * 60) + (stamp.time().second()) * 1000) + stamp.time().msec());
    }

    //prints hex numbers in uppercase with 0's filling out the number depending
    //on the size needed. Promotes hex numbers to either 2, 4, or 8 digits
    static QString formatHexNum(uint64_t input)
    {
        if (input < 256)
            return "0x" + QString::number(input, 16).toUpper().rightJustified(2,'0');
        if (input < 65536)
            return "0x" + QString::number(input, 16).toUpper().rightJustified(4,'0');
        if (input < 4294967296)
            return "0x" + QString::number(input, 16).toUpper().rightJustified(8,'0');
        return "0x" + QString::number(input, 16).toUpper().rightJustified(16,'0');
    }

    //uses decimalMode to see if it should show value as decimal or hex
    static QString formatNumber(uint64_t value)
    {
        if (decimalMode)
        {
            return QString::number(value, 10);
        }
        else return formatHexNum(value);
    }
};

#endif // UTILITY_H
