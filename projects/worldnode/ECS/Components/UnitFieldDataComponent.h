/*
    MIT License

    Copyright (c) 2018-2019 NovusCore

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#pragma once
#include <NovusTypes.h>
#include <Networking/ByteBuffer.h>

#include "../../NovusEnums.h"
#include "../../Utils/UpdateMask.h"

struct UnitFieldDataComponent
{
    UnitFieldDataComponent() : changesMask(UNIT_END)
    {
        unitFields = ByteBuffer::Borrow<UNIT_END * 4>();
        std::memset(unitFields->GetInternalData(), 0, unitFields->Size);
    }

    void SetGuidValue(u16 index, u64 value)
    {
        unitFields->Put<u64>(value, index * 4);
        changesMask.SetBit(index);
        changesMask.SetBit(index + 1);
    }
    template <typename T>
    void SetFieldValue(u16 index, T value, u8 offset = 0)
    {
        unitFields->Put<T>(value, (index * 4) + offset);
        changesMask.SetBit(index);
    }
    template <typename T>
    T GetFieldValue(u16 index, u8 offset = 0)
    {
        return unitFields->ReadAt<T>((index * 4) + offset);
    }
    void ResetFields()
    {
        changesMask.Reset();
        unitFields->Reset();
    }

    UpdateMask<160> changesMask;
    std::shared_ptr<ByteBuffer> unitFields;
};
