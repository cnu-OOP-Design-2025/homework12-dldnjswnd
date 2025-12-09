#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include "logger.h"

using namespace std;

enum class CharacterType
{
    Knight,
    Wizard,
    Archer,
    Unknown
};

class Character
{
protected:
    string description;
    CharacterType type = CharacterType::Unknown;

public:
    virtual string getDescription() const { return description; }
    virtual int getAttack() const = 0;
    virtual int getSpeed() const = 0;
    virtual int getDefense() const = 0;
    virtual CharacterType getType() const { return type; }

    virtual ~Character()
    {
        if (type != CharacterType::Unknown)
        {
            cout << "Delete Character: " << description << endl;
        }
    }
};

// Knight
class Knight : public Character
{
public:
    Knight()
    {
        description = "Knight";
        type = CharacterType::Knight;
        Logger::getInstance()->log("[Create] " + description);
    }

    int getAttack() const override { return 15; }
    int getSpeed() const override { return 8; }
    int getDefense() const override { return 20; }
};

// Wizard
class Wizard : public Character
{
public:
    Wizard()
    {
        description = "Wizard";
        type = CharacterType::Wizard;
        Logger::getInstance()->log("[Create] " + description);
    }

    int getAttack() const override { return 20; }
    int getSpeed() const override { return 10; }
    int getDefense() const override { return 10; }
};

// Archer
class Archer : public Character
{
public:
    Archer()
    {
        description = "Archer";
        type = CharacterType::Archer;
        Logger::getInstance()->log("[Create] " + description);
    }

    int getAttack() const override { return 18; }
    int getSpeed() const override { return 15; }
    int getDefense() const override { return 8; }
};

// 장비 데코레이터 기본 클래스
class EquipDeco : public Character
{
protected:
    shared_ptr<Character> character;

public:
    EquipDeco(shared_ptr<Character> c, const string &item) : character(c)
    {
        // 현재까지의 전체 설명 + 새 장비 이름을 로깅
        Logger::getInstance()->log("[Trying to Equip] " + c->getDescription() + " + " + item);
    }

    string getDescription() const override { return character->getDescription(); }
    int getAttack() const override { return character->getAttack(); }
    int getSpeed() const override { return character->getSpeed(); }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override { return character->getType(); }
};

// Armor
class Armor : public EquipDeco
{
public:
    Armor(shared_ptr<Character> c) : EquipDeco(c, "Armor") {}

    string getDescription() const override
    {
        return character->getDescription() + " + Armor";
    }

    int getAttack() const override
    {
        return character->getAttack();
    }

    int getSpeed() const override
    {
        return character->getSpeed() - 2;
    }

    int getDefense() const override
    {
        return character->getDefense() + 10;
    }

    CharacterType getType() const override { return character->getType(); }
};

// Boots
class Boots : public EquipDeco
{
public:
    Boots(shared_ptr<Character> c) : EquipDeco(c, "Boots") {}

    string getDescription() const override
    {
        return character->getDescription() + " + Boots";
    }

    int getAttack() const override
    {
        return character->getAttack();
    }

    int getSpeed() const override
    {
        return character->getSpeed() + 5;
    }

    int getDefense() const override
    {
        return character->getDefense();
    }

    CharacterType getType() const override { return character->getType(); }
};

// Staff (Wizard 전용)
class Staff : public EquipDeco
{
public:
    Staff(shared_ptr<Character> c) : EquipDeco(c, "Staff")
    {
        if (c->getType() != CharacterType::Wizard)
        {
            throw invalid_argument("Staff requires Wizard");
        }
    }

    string getDescription() const override
    {
        return character->getDescription() + " + Staff";
    }

    int getAttack() const override
    {
        return character->getAttack() + 8;
    }

    int getSpeed() const override
    {
        return character->getSpeed();
    }

    int getDefense() const override
    {
        return character->getDefense();
    }

    CharacterType getType() const override { return character->getType(); }
};

// Sword
class Sword : public EquipDeco
{
public:
    Sword(shared_ptr<Character> c) : EquipDeco(c, "Sword") {}

    string getDescription() const override
    {
        return character->getDescription() + " + Sword";
    }

    int getAttack() const override
    {
        return character->getAttack() + 10;
    }

    int getSpeed() const override
    {
        return character->getSpeed();
    }

    int getDefense() const override
    {
        return character->getDefense();
    }

    CharacterType getType() const override { return character->getType(); }
};

// Bow (Archer / Knight 전용)
class Bow : public EquipDeco
{
public:
    Bow(shared_ptr<Character> c) : EquipDeco(c, "Bow")
    {
        CharacterType t = c->getType();
        if (t != CharacterType::Archer && t != CharacterType::Knight)
        {
            throw invalid_argument("Bow requires Archer or Knight");
        }
    }

    string getDescription() const override
    {
        return character->getDescription() + " + Bow";
    }

    int getAttack() const override
    {
        return character->getAttack() + 7;
    }

    int getSpeed() const override
    {
        return character->getSpeed() + 2;
    }

    int getDefense() const override
    {
        return character->getDefense();
    }

    CharacterType getType() const override { return character->getType(); }
};
