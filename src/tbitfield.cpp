// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

const int elemSize = sizeof(TELEM) * 8;
const int elemSizePower = log(elemSize) / log(2);

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) throw - 1;

    BitLen = len;
    
    MemLen = (len + (elemSize-1)) >> elemSizePower;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) 
    {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n > BitLen)) throw - 1;

    return n >> (elemSizePower);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n > BitLen)) throw - 1;

    int bitPos = n & (elemSize-1);

    return (1 << bitPos);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen)) throw - 1;

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen)) throw - 1;

    pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen)) throw - 1;

    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
        return 0;
    return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;

    delete[] this->pMem;
    this->pMem = new TELEM[bf.MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        this->pMem[i] = bf.pMem[i];
    }

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++)
    {
        if (this->pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) return 1;
    for (int i = 0; i < MemLen; i++)
    {
        if (this->pMem[i] != bf.pMem[i]) return 1;
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField res(max(this->BitLen, bf.BitLen));

    int minMemLen = min(this->MemLen, bf.MemLen);
    int maxMemLen = max(this->MemLen, bf.MemLen);
    
    if (this->MemLen == bf.MemLen)
    {
        for (int i = 0; i < MemLen; i++)
        {
            res.pMem[i] = this->pMem[i] | bf.pMem[i];
        }
    }
    else
    {
        for (int i = 0; i < minMemLen; i++)
        {
            res.pMem[i] = this->pMem[i] | bf.pMem[i];
        }
        if (this->MemLen == maxMemLen)
        {
            for (int i = minMemLen; i < maxMemLen; i++)
            {
                res.pMem[i] |= this->pMem[i];
            }
        }
        else
        {
            for (int i = minMemLen; i < maxMemLen; i++)
            {
                res.pMem[i] |= bf.pMem[i];
            }
        }
    }

    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField res(max(this->BitLen, bf.BitLen));

    int minMemLen = min(this->MemLen, bf.MemLen);
    int maxMemLen = max(this->MemLen, bf.MemLen);

    if (this->MemLen == bf.MemLen)
    {
        for (int i = 0; i < MemLen; i++)
        {
            res.pMem[i] = this->pMem[i] & bf.pMem[i];
        }
    }
    else
    {
        for (int i = 0; i < minMemLen; i++)
        {
            res.pMem[i] = this->pMem[i] & bf.pMem[i];
        }
        if (this->MemLen == maxMemLen)
        {
            for (int i = minMemLen; i < maxMemLen; i++)
            {
                res.pMem[i] &= this->pMem[i];
            }
        }
        else
        {
            for (int i = minMemLen; i < maxMemLen; i++)
            {
                res.pMem[i] &= bf.pMem[i];
            }
        }
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(this->BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        res.pMem[i] = ~(this->pMem[i]);
    }
    int bitPos = BitLen & (elemSize-1);
    res.pMem[MemLen - 1] &= (1 << bitPos) - 1;
    //for (int i = 0; i < (this->BitLen); i++)
    //    if (this->GetBit(i) == 0) res.SetBit(i);

    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int n;
    istr >> n;
    cout << endl;
    int bitInd;
    for (int i = 0; i < n; i++)
    {
        cout << "Какой бит Вы хотите установить? ";
        istr >> bitInd;
        cout << endl;
        bf.SetBit(bitInd);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i) << ' ';
    ostr << endl;
    return ostr;
}
